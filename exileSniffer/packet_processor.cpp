#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"
#include "utilities.h"
#include "inventory.h"
#pragma comment(lib, "N:\\code\\POEcode\\poeSRE\\clientX\\packages\\cryptopp.v140.5.6.5.2\\lib\\native\\v140\\windesktop\\msvcstl\\x64\\Debug\\md\\cryptopp.lib")

std::string getSkillName(unsigned long skillID)
{
	return "TODOSKILLNAMES";
}

void packet_processor::handle_packet_from_patchserver(byte* data, unsigned int dataLen)
{
	char pktType = data[0];
	int i = 1;

	switch (pktType)
	{
	case 2:
	{
		std::cout << "\tServer info Response:" << std::endl;
		bool nullHash = true;
		for (i = 1; i < 33; ++i)
			if (data[i] != 0)
				nullHash = false;

		std::cout << "\t\tHash:";
		if (nullHash) std::cout << "[Null]";
		else
		{
			for (i = 1; i < 33; ++i)
				std::cout << std::hex << std::setw(2) << data[i];
		}
		std::cout << std::endl;

		i++;
		byte url1Size = data[i++] * 2;
		std::wstring url1(reinterpret_cast<wchar_t*>(data + i), (url1Size) / sizeof(wchar_t));
		std::wcout << "\t\tServer: " << url1 << std::endl;


		i += (url1Size + 1);
		byte url2Size = data[i++] * 2;
		std::wstring url2(reinterpret_cast<wchar_t*>(data + i), (url2Size) / sizeof(wchar_t));
		std::wcout << "\t\tBackup Server: " << url2 << std::endl;

		return;
	}
	case 4:
		printf("\tFolder info response: <Effort>\n");
		return;

	case 6:
		printf("\tPatch note response: <Effort>\n");
		return;
	}
	printf("\tUnhandled pkt type: %d, len %ld\n", pktType, dataLen);
}


void packet_processor::handle_packet_to_patchserver(byte* data, unsigned int dataLen)
{
	char pktType = data[0];

	switch (pktType)
	{
	case 1:
		if (dataLen == 2)
		{
			printf("\tServer info request. Proto version: %x\n", (char)data[1]);
			return;
		}
		break;
	case 3:
		printf("\tFolder info request: %x%x%x\n", (char)data[1], (char)data[2], (char)data[3]);
		return;

	case 5:
		printf("\tPatch note request\n");
		return;

	}
	printf("\tUnhandled pkt type: %d, len %ld\n", pktType, dataLen);
}

void packet_processor::handle_patch_data(byte* data)
{
	char *next_token = (char *)data;

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	networkStreamID streamID = (networkStreamID)atoi(streamID_s);

	char *incoming = strtok_s(next_token, ",", &next_token);
	currentMsgIncoming = (*incoming == '1') ? true : false;

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *dLen = strtok_s(next_token, ",", &next_token);
	unsigned int payloadLen = atoi(dLen);

	byte *payload = (byte *)next_token;

	if (currentMsgIncoming)
	{
		printf("Server patch data (%ld bytes):\n", payloadLen);
		handle_packet_from_patchserver(payload, payloadLen);
	}
	else
	{
		printf("Client patch data (%ld bytes):\n", payloadLen);
		handle_packet_to_patchserver(payload, payloadLen);
	}
}





void packet_processor::handle_packet_from_loginserver(byte* data, unsigned int dataLen)
{
	STREAMDATA *streamObj = &streamDatas.at(currentMsgStreamID);

	//ignore ephemeral public key
	if (streamObj->packetCount < 2) //warning - a null packet is ignored
	{
		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(0, eLogin, true);
		vector<byte>*plainTextBuf = new vector<byte>(data, data+dataLen);
		msg->setData(plainTextBuf);
		uiMsgQueue->addItem(msg);
		return;
	}

	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);

	if (!streamObj->workingRecvKey)
	{
		std::cout << "Login Response: " << std::endl;

		while (!streamObj->workingRecvKey)
		{
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(currentMsgStreamID, true);
			if (!keyCandidate) {
				std::cout << "no unused memkey in from login!" << std::endl;
				Sleep(1200);
				continue;
			}

			if (keyCandidate->used) std::cout << "assert 3" << std::endl;
			assert(!keyCandidate->used);

			streamObj->fromLoginSalsa.SetKeyWithIV((const byte *)keyCandidate->salsakey, 
				32, 
				(const byte *)keyCandidate->IV);
			streamObj->fromLoginSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);

			
			unsigned short packetID = ntohs(getUshort(decryptedBuffer->data()));
			cout << "pkt from loginserveR: " << packetID << std::endl;
			if (packetID == 0x0004)
			{
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, currentMsgStreamID);

				UIaddLogMsg("Loginserver receive key recovered",
					keyCandidate->sourceProcess,
					uiMsgQueue);
				UIrecordLogin(keyCandidate->sourceProcess, uiMsgQueue);

				keyGrabber->stopProcessScan(keyCandidate->sourceProcess);
				streamObj->workingRecvKey = keyCandidate;
				break;
			}
			else
			{
				std::stringstream err;
				err << "Error expected packet 0x4 from loginserver but got 0x" << std::hex << packetID;

				UIaddLogMsg(err.str(),	0,	uiMsgQueue);

				//todo: need to handle gracefully

				return;
			}
		}

		std::cout << "Character List (" << (int)decryptedBuffer->at(45) << " characters)" << std::endl;

		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decryptedBuffer->at(i);
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, true);
		msg->setData(decryptedBuffer);
		uiMsgQueue->addItem(msg);
		return;
	}

	streamObj->fromLoginSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);
	/*
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, true);
	msg->setData(decryptedBuffer, dataLen);
	uiMsgQueue->addItem(msg);
	*/

	char pktType = decryptedBuffer->at(1);
	switch (pktType)
	{
	case LSRV_GAMESERVER_INFO:
	{
		std::cout << "Got gameserver info from loginserver" << std::endl;
		//outfile << "Got gameserver info from loginserver" << std::endl;
		unsigned int pktidx = 2;

		unsigned long connectionID = getUlong(&decryptedBuffer->at(10));
		std::cout << "Got key for connection ID " << std::hex << connectionID << std::endl;

		pktidx = 17;
		unsigned int port = (decryptedBuffer->at(17) << 8) + decryptedBuffer->at(18);
		std::stringstream serverIP;
		serverIP << (int)decryptedBuffer->at(19) << ".";
		serverIP << (int)decryptedBuffer->at(20) << ".";
		serverIP << (int)decryptedBuffer->at(21) << ".";
		serverIP << (int)decryptedBuffer->at(22) << ":" << std::dec << port;
		std::cout << "\tGameserver: " << serverIP.str() << std::endl;

		DWORD *keyblob = (DWORD *)(&decryptedBuffer->at(43));


		KEYDATA *key1A = new KEYDATA;
		KEYDATA *key1B = new KEYDATA;

		key1A->salsakey[0] = key1B->salsakey[0] = keyblob[0];
		key1A->salsakey[1] = key1B->salsakey[1] = keyblob[1];
		key1A->salsakey[2] = key1B->salsakey[2] = keyblob[2];
		key1A->salsakey[3] = key1B->salsakey[3] = keyblob[3];
		key1A->salsakey[4] = key1B->salsakey[4] = keyblob[4];
		key1A->salsakey[5] = key1B->salsakey[5] = keyblob[5];
		key1A->salsakey[6] = key1B->salsakey[6] = keyblob[6];
		key1A->salsakey[7] = key1B->salsakey[7] = keyblob[7];
		key1A->IV[0] = keyblob[8];
		key1A->IV[1] = keyblob[9];
		key1B->IV[0] = keyblob[12];
		key1B->IV[1] = keyblob[13];

		if (key1A->salsakey[0] == 0 && key1A->salsakey[3] == 0 && key1A->salsakey[7])
		{
			std::cout << "Discarding bad key in play response" << std::endl;
			break; //probably an old zero-ed out key
		}

		key1A->sourceProcess = key1B->sourceProcess = streamObj->workingRecvKey->sourceProcess;
		key1A->foundAddress = key1B->foundAddress = SENT_BY_SERVER;
		pendingGameserverKeys[connectionID] = make_pair(key1A, key1B);

		return;
	}

	case 18:
		printf("Race description response: <effort>\n");
		return;

	case 19:
		std::cout << "League data from login server" << decryptedBuffer << std::endl;
		return;


	default:
		printf("Unknown packet from login server: byte[1]==0x%x (dec %d)\n", decryptedBuffer[1], decryptedBuffer[1]);

		std::cout << "Hex Payload: " << std::endl;
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decryptedBuffer->at(i);
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}
		std::cout << std::endl;
		return;
	}

}

void packet_processor::handle_packet_to_loginserver(byte* data, unsigned int dataLen)
{
	STREAMDATA *streamObj = &streamDatas.at(currentMsgStreamID);
	if (streamObj->packetCount == 0)
	{
		/*
		printf("\t[%x%x][Client ephemeral public key](%d bytes)\n", 
		(byte)data[0], (byte)data[1], dataLen - 2);
		*/
		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(0, eLogin, false);
		vector<byte>*plainTextBuf = new vector<byte>(data, data + dataLen);
		msg->setData(plainTextBuf);
		uiMsgQueue->addItem(msg);

		return;
	}


	vector<byte> *decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);

	if (!streamObj->workingSendKey)
	{
		unsigned int msWaited = 0;
		std::cout << "Login request: " << std::endl;
		while (true)
		{

			//should use hint here, but have to reliably find corresponding stream
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(currentMsgStreamID, false);
			if (!keyCandidate) {
				Sleep(200);
				msWaited += 200;
				//every two seconds relax the memory scan filters
				if(msWaited % 2000 == 0)
					keyGrabber->relaxScanFilters();

				continue;
			}

			if (keyCandidate->used) std::cout << "assert 4" << std::endl;
			assert(!keyCandidate->used);

			streamObj->toLoginSalsa.SetKeyWithIV((byte *)keyCandidate->salsakey,
				32,
				(byte *)keyCandidate->IV);
			streamObj->toLoginSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);

			if (decryptedBuffer->at(0) == 0 && decryptedBuffer->at(1) == 3)
			{
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, currentMsgStreamID);

				UIaddLogMsg("Loginserver send key recovered", 
					keyCandidate->sourceProcess, 
					uiMsgQueue);

				streamObj->workingSendKey = keyCandidate;
				break;
			}
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eLogin, false);
		msg->setData(decryptedBuffer);
		uiMsgQueue->addItem(msg);

		std::cout << std::setfill('0');
		std::cout << std::hex << std::setw(2) << "ID2: 0x" << 
			(int)decryptedBuffer->at(5) << (int)decryptedBuffer->at(4) <<
			(int)decryptedBuffer->at(3) << (int)decryptedBuffer->at(2) << std::endl;
		unsigned int emailLen = decryptedBuffer->at(7) * 2;
		if (decryptedBuffer->at(6) != 0)
			printf("Warning, long login email not handled\n");
		std::wstring email(reinterpret_cast<wchar_t*>(decryptedBuffer + 8), (emailLen) / sizeof(wchar_t));
		std::wcout << "\tUsername: " << email << std::endl;

		unsigned int pktindex = 8 + emailLen;
		std::cout << "\tPOE.exe hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer->at(pktindex + i);
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tuser creds: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer->at(pktindex + i);
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tMAC hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer->at(pktindex + i);
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;

		std::cout << "\tPW save1: " << (int)(decryptedBuffer->at(pktindex++)) << std::endl;
		std::cout << "\tPW save2: " << (int)(decryptedBuffer->at(pktindex)) << std::endl;

		return;
	}

	streamObj->toLoginSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);

	std::cout << "Sent to login server...\n\n";
	std::cout << "\nhex:\n";
	std::cout << std::setfill('0');
	for (int i = 0; i < dataLen; ++i)
	{
		byte item = decryptedBuffer->at(i);
		if (item)
			std::cout << std::hex << std::setw(2) << (int)item << " ";
		else
			std::cout << "00 ";
		if (i % 16 == 0) { std::cout << std::endl; break; }
	}
	std::cout << "\n\n";
	std::cout.flush();
	
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eLogin, false);
	msg->setData(decryptedBuffer);
	uiMsgQueue->addItem(msg);

	char pktType = decryptedBuffer->at(1);
	switch (pktType)
	{
	case 01:
	{
		std::cout << "Client sent KeepAlive pkt (0x01) to login server" << std::endl;
		return;
	}
	case 10:
	{
		printf("Play request\n");

		unsigned int charNameLen = decryptedBuffer->at(3) * 2;
		if (decryptedBuffer->at(2) != 0)
			printf("Warning, long login charname not handled\n");
		std::wstring charn(reinterpret_cast<wchar_t*>(decryptedBuffer + 4), (charNameLen) / sizeof(wchar_t));
		std::wcout << "\tSelected Char: " << charn << std::endl;
		//uidata.charname = charn;

		return;
	}
	case 11:
	{
		std::cout << "Character selection sent to login server by number: " << (int)decryptedBuffer->at(6) << std::endl;
		return;
	}
	default:
		printf("Client sent unknown packet to login server: 0x%x\n", decryptedBuffer->at(1));

		std::cout << "Hex Payload: " << std::endl;
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decryptedBuffer->at(i);
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}
		std::cout << std::endl;

		return;
	}

}

void packet_processor::handle_login_data(byte* data)
{

	char *next_token = (char *)data;

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	currentMsgStreamID = (networkStreamID)atoi(streamID_s);

	char *incoming = strtok_s(next_token, ",", &next_token);
	currentMsgIncoming = (*incoming == '1') ? true : false;

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *pLen = strtok_s(next_token, ",", &next_token);
	unsigned int payloadLen = atoi(pLen);
	if (!payloadLen)
		return;

	byte *payload = (byte *)next_token;

	STREAMDATA *streamObj = &streamDatas[currentMsgStreamID];
	printf("[%ld]: Login data (%ld bytes) ", streamObj->packetCount, payloadLen);

	if (currentMsgIncoming)
	{
		handle_packet_from_loginserver(payload, payloadLen);
	}
	else
	{
		handle_packet_to_loginserver(payload, payloadLen);
	}


	++streamObj->packetCount;
}

bool packet_processor::handle_game_data(byte* data)
{

	char *next_token = (char *)data;

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	currentMsgStreamID = (networkStreamID)atoi(streamID_s);
	STREAMDATA *streamObj = &streamDatas[currentMsgStreamID];

	char *incoming = strtok_s(next_token, ",", &next_token);
	currentMsgIncoming = (*incoming == '1');

	//the keys are established during handling of the first packet to the gameserver
	//sometimes we will process the response from the gameserver first, causing badness.
	//this delays processing of recv data until we have a recv key
	if (currentMsgIncoming && streamObj->workingRecvKey == NULL)
		return false;

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *pLen = strtok_s(next_token, ",", &next_token);
	unsigned int payloadLen = atoi(pLen);
	if (!payloadLen)
		return true;

	//std::cout << "handling game data, size "<<std::dec <<dataLen<<" incoming- "<<(int)isIncoming << std::endl;

	byte *payload = (byte *)next_token;

	if (payloadLen > 0)
	{
		if (currentMsgIncoming)
			handle_packet_from_gameserver(payload, payloadLen, msProcessed);
		else
			handle_packet_to_gameserver(payload, payloadLen, msProcessed);
	}

	++streamObj->packetCount;
	return true;
}

bool packet_processor::sanityCheckPacketID(unsigned short pktID)
{
	if (!pktID || pktID > 0x220)
	{
		errorFlag = eDecodingErr::eBadPacketID;
		return false;
	}
	return true;
}




void packet_processor::handle_packet_to_gameserver(byte* data, 
	unsigned int dataLen, long long timems)
{

	STREAMDATA *streamObj = &streamDatas.at(currentMsgStreamID);
	if (streamObj->workingSendKey == NULL)
	{
		if (data[0] == 0 && data[1] == 3)
		{
			unsigned long connectionID = getUlong(data + 2);

			if (pendingGameserverKeys.find(connectionID) == pendingGameserverKeys.end())
			{
				if (!pendingGameserverKeys.empty())
				{
					std::cout << "no pending for conid but found a key... trying";
					streamObj->workingSendKey = pendingGameserverKeys.begin()->second.first;
					streamObj->workingRecvKey = pendingGameserverKeys.begin()->second.second;
					pendingGameserverKeys.clear();
				}
				else
				{
					UIaddLogMsg("Error: No pending gameserver key", activeClientPID, uiMsgQueue);
					return;
				}
			}
			else
			{
				streamObj->workingSendKey = pendingGameserverKeys.at(connectionID).first;
				streamObj->workingRecvKey = pendingGameserverKeys.at(connectionID).second;
			}
			
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			pendingGameserverKeys.erase(connectionID);

			//todo: decoded ui packet

			UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
				streamObj->workingSendKey->sourceProcess, eGame, false);
			vector<byte> *plainTextBuf = new vector<byte>(data, data+dataLen);
			msg->setData(plainTextBuf);
			uiMsgQueue->addItem(msg);

		}
		else
		{
			std::cerr << "Warning! Unexpected first client packet|||!!!" << std::endl;
		}
		return;
	}

	/*
	this is not deleted because pointers to it are held by the
	raw decoder and pointers into it are held by the decodedpackets. 
	Don't want to make a bunch of copies because it will balloon in size with long running streams
	*/
	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);
	streamObj->toGameSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);



	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eGame, false);
	msg->setData(decryptedBuffer);
	if (errorFlag != eNoErr)
		msg->setErrorIndex(decryptedIndex);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;
	decryptedIndex = 0;
	errorFlag = eNoErr;


	while (remainingDecrypted > 0)
	{
		unsigned short pktIDWord = ntohs(consumeUShort());

		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(streamObj->workingSendKey->sourceProcess, eGame, PKTBIT_OUTBOUND, timems);
		deserialisedPkts.push_back(ui_decodedpkt);
		ui_decodedpkt->setStartOffset(decryptedIndex);
		ui_decodedpkt->messageID = pktIDWord;
		ui_decodedpkt->toggle_payload_operations(true);

		if (sanityCheckPacketID(pktIDWord) && errorFlag == eNoErr)
		{
			//find and run deserialiser for this packet
			auto it = packetDeserialisers.find(pktIDWord);
			if (it != packetDeserialisers.end())
			{
				packet_processor::deserialiser deserialiserForPktID = it->second;
				(this->*deserialiserForPktID)(ui_decodedpkt);

				if (errorFlag == eNoErr || errorFlag == eAbandoned)
				{
					ui_decodedpkt->setEndOffset(decryptedIndex);

					if (errorFlag == eAbandoned)
					{
						errorFlag = eNoErr;
						ui_decodedpkt->setAbandoned();
					}
				}
			}
			else
			{
				std::cout << "Unhandled Hex Payload msgID <gamesrv in> 0x" << std::hex << pktIDWord << std::endl;
				for (int i = 0; i < dataLen; ++i)
				{
					byte item = decryptedBuffer->at(i);
					std::cout << std::setw(2) << (int)item;
					if (i % 16 == 0) std::cout << std::endl;
				}
				std::cout << std::endl;

				errorFlag = eDecodingErr::ePktIDUnimplemented;
			}
		}

		//warning - can be resized during deserialisation - only store pointers afterwards
		ui_decodedpkt->setBuffer(decryptedBuffer);

		if (errorFlag != eNoErr)
		{
			remainingDecrypted = 0;
			emit_decoding_err_msg(pktIDWord, streamObj->lastPktID);
			ui_decodedpkt->setFailedDecode();
			ui_decodedpkt->setEndOffset(dataLen);
		}

		if (currentMsgMultiPacket)
		{
			ui_decodedpkt->setMultiPacket();
			currentMsgMultiPacket = false;
		}
		uiMsgQueue->addItem(ui_decodedpkt);
		streamObj->lastPktID = pktIDWord;
	}



}

/*
aside from the handling of crypt at the start, the from_ and to_ gameserver functions
are equivalent. could merge them.
*/
void packet_processor::handle_packet_from_gameserver(byte* data, 
	unsigned int dataLen, long long timems)
{


	STREAMDATA *streamObj = &streamDatas.at(currentMsgStreamID);

	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);

	if (streamObj->packetCount == 1)
	{
		//first packet from gameserver starts 0005, followed by crypt which start 0012
		ushort firstPktID = ntohs(getUshort(data));
		assert(firstPktID == SRV_PKT_ENCAPSULATED);

		//if (streamObj->workingRecvKey == 0)


		streamObj->fromGameSalsa.SetKeyWithIV(
			(byte *)streamObj->workingRecvKey->salsakey, 32,
				(byte *)streamObj->workingRecvKey->IV);

		dataLen -= 2;
		streamObj->fromGameSalsa.ProcessData(decryptedBuffer->data(), data+2, dataLen);
	}
	else
	{
		streamObj->fromGameSalsa.ProcessData(decryptedBuffer->data(), data, dataLen);
	}

	//print the whole blob in the raw log
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eGame, true);
	msg->setData(decryptedBuffer);
	if (errorFlag != eNoErr)
		msg->setErrorIndex(decryptedIndex);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;
	decryptedIndex = 0;
	errorFlag = eNoErr;

	while (remainingDecrypted > 0)
	{
		unsigned short pktIDWord = ntohs(consumeUShort());

		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(streamObj->workingRecvKey->sourceProcess, eGame, PKTBIT_INBOUND, timems);
		deserialisedPkts.push_back(ui_decodedpkt);
		
		ui_decodedpkt->setStartOffset(decryptedIndex - 2);
		ui_decodedpkt->messageID = pktIDWord;
		ui_decodedpkt->toggle_payload_operations(true);

		if (sanityCheckPacketID(pktIDWord) && errorFlag == eNoErr)
		{
			//find and run deserialiser for this packet
			map<unsigned short, deserialiser>::iterator it = packetDeserialisers.find(pktIDWord);
			if (it != packetDeserialisers.end())
			{
				packet_processor::deserialiser deserialiserForPktID = it->second;
				(this->*deserialiserForPktID)(ui_decodedpkt);

				if (errorFlag == eNoErr || errorFlag == eAbandoned)
				{
					ui_decodedpkt->setEndOffset(decryptedIndex);

					if (errorFlag == eAbandoned)
					{
						errorFlag = eNoErr;
						ui_decodedpkt->setAbandoned();
					}
				}
			}
			else
			{
				std::cout << "Unhandled Hex Payload msgID <gamesrv in> 0x" << std::hex << pktIDWord << std::endl;
				for (int i = 0; i < dataLen; ++i)
				{
					byte item = decryptedBuffer->at(i);
					std::cout << std::setw(2) << (int)item;
					if (i % 16 == 0) std::cout << std::endl;
				}
				std::cout << std::endl;

				errorFlag = eDecodingErr::ePktIDUnimplemented;
			}
		}

		//warning - can be resized during deserialisation - only store pointers afterwards
		ui_decodedpkt->setBuffer(decryptedBuffer);

		if (errorFlag != eNoErr)
		{
			remainingDecrypted = 0;
			emit_decoding_err_msg(pktIDWord, streamObj->lastPktID);
			ui_decodedpkt->setFailedDecode();
			ui_decodedpkt->setEndOffset(dataLen);
		}

		uiMsgQueue->addItem(ui_decodedpkt);
		streamObj->lastPktID = pktIDWord;
	}


}


bool packet_processor::process_packet_loop()
{
	std::vector<byte> pkt;

	while (true)
	{
		//highest priority - only check patch/login if game is quiet
		if (checkPipe(gamepipe, &pendingPktQueue))
		{
			bool done = false;
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				done = handle_game_data(pkt.data());
				if(done)
					pendingPktQueue.pop_front();
				else
				{
					//tried to handle first response before first send so no key to read recv
					//wait until first send done
					while (!done)
					{
						Sleep(100);
						checkPipe(gamepipe, &pendingPktQueue);

						auto it = pendingPktQueue.begin();
						for (; it != pendingPktQueue.end(); it++)
						{
							pkt = *it;
							done = handle_game_data(pkt.data());
							if (done)
								break;
						}

						if (done)
							pendingPktQueue.erase(it);
					}
				}
			}
			continue;
		}

		if (checkPipe(loginpipe, &pendingPktQueue))
		{
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				handle_login_data(pkt.data());
				pendingPktQueue.pop_front();
			}
			continue;
		}

		if (checkPipe(patchpipe, &pendingPktQueue))
		{
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				handle_patch_data(pkt.data());
				pendingPktQueue.pop_front();
			}
		}
		else
			Sleep(10);
	}
	return true;
}




void packet_processor::main_loop()
{
	init_packetDeserialisers();

	unsigned int errCount = 0;

	//pipes were implemented when the pcap was done in another process
	//todo: use something else now
	while (!patchpipe)	{
		patchpipe = connectPipe(L"\\\\.\\pipe\\patchpipe");
		Sleep(200);
		if (errCount++ > 10) break;
	}

	while (!loginpipe)	{
		loginpipe = connectPipe(L"\\\\.\\pipe\\loginpipe");
		Sleep(200);
		if (errCount++ > 10) break;
	}

	while (!gamepipe)	{
		gamepipe = connectPipe(L"\\\\.\\pipe\\gamepipe");
		Sleep(200);
		if (errCount++ > 10) break;
	}

	if (loginpipe && gamepipe)
	{
		process_packet_loop();
	}
	else
	{
		UIaddLogMsg("ERROR: Unable to connect to our own packet capture pipes. Failing.", activeClientPID, uiMsgQueue);
	}
}