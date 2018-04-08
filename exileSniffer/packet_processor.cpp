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
		printf("\tFolder info response: <Effort>\n", (char)data[1], (char)data[2], (char)data[3]);
		return;

	case 6:
		printf("\tPatch note response: <Effort>\n");
		return;
	}
	printf("\tUnhandled pkt type: %d, len %d\n", pktType, dataLen);
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
	printf("\tUnhandled pkt type: %d, len %d\n", pktType, dataLen);
}

void packet_processor::handle_patch_data(std::vector<byte> pkt)
{
	char *next_token = (char *)pkt.data();

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	networkStreamID streamID = (networkStreamID)atoi(streamID_s);

	char *incoming = strtok_s(next_token, ",", &next_token);
	bool isIncoming = (*incoming == '1') ? true : false;

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *dLen = strtok_s(next_token, ",", &next_token);
	unsigned int dataLen = atoi(dLen);

	byte *data = (byte *)next_token;


	if (isIncoming)
	{
		printf("Server patch data (%ld bytes):\n", dataLen);
		handle_packet_from_patchserver(data, dataLen);
	}
	else
	{
		printf("Client patch data (%ld bytes):\n", dataLen);
		handle_packet_to_patchserver(data, dataLen);
	}
}





void packet_processor::handle_packet_from_loginserver(networkStreamID streamID, byte* data, unsigned int dataLen)
{
	STREAMDATA *streamObj = &streamDatas.at(streamID);

	//ignore ephemeral public key
	if (streamObj->packetCount < 2) //warning - a null packet is ignored
	{
		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(0, eLogin, true);
		byte *plainTextBuf = new byte[dataLen];
		std::copy(data, data + dataLen, plainTextBuf);
		msg->setData(data, dataLen);
		uiMsgQueue->addItem(msg);
		return;
	}

	decryptedBuffer = new byte[dataLen];

	memset(decryptedBuffer, 0, dataLen);

	if (!streamObj->workingRecvKey)
	{
		std::cout << "Login Response: " << std::endl;

		while (!streamObj->workingRecvKey)
		{
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(streamID, true);
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
			streamObj->fromLoginSalsa.ProcessData(decryptedBuffer, data, dataLen);

			unsigned short packetID = getUshort(decryptedBuffer);
			if (packetID == 0x0004)
			{
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, streamID);

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

		std::cout << "Character List (" << (int)decryptedBuffer[45] << " characters)" << std::endl;

		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decryptedBuffer[i];
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, true);
		msg->setData(decryptedBuffer, dataLen);
		uiMsgQueue->addItem(msg);
		return;
	}

	streamObj->fromLoginSalsa.ProcessData(decryptedBuffer, data, dataLen);
	/*
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, true);
	msg->setData(decryptedBuffer, dataLen);
	uiMsgQueue->addItem(msg);
	*/

	char pktType = decryptedBuffer[1];
	switch (pktType)
	{
	case LSRV_GAMESERVER_INFO:
	{
		std::cout << "Got gameserver info from loginserver" << std::endl;
		//outfile << "Got gameserver info from loginserver" << std::endl;
		unsigned int pktidx = 2;

		unsigned long connectionID = getUlong(decryptedBuffer + 10);
		std::cout << "Got key for connection ID " << std::hex << connectionID << std::endl;

		pktidx = 17;
		unsigned int port = (decryptedBuffer[17] << 8) + decryptedBuffer[18];
		std::stringstream serverIP;
		serverIP << (int)decryptedBuffer[19] << ".";
		serverIP << (int)decryptedBuffer[20] << ".";
		serverIP << (int)decryptedBuffer[21] << ".";
		serverIP << (int)decryptedBuffer[22] << ":" << std::dec << port;
		std::cout << "\tGameserver: " << serverIP.str() << std::endl;

		DWORD *keyblob = (DWORD *)((byte*)decryptedBuffer + 43);


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
			byte item = decryptedBuffer[i];
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}
		std::cout << std::endl;
		return;
	}

}

void packet_processor::handle_packet_to_loginserver(networkStreamID streamID, byte* data, unsigned int dataLen)
{
	STREAMDATA *streamObj = &streamDatas.at(streamID);
	if (streamObj->packetCount == 0)
	{
		/*
		printf("\t[%x%x][Client ephemeral public key](%d bytes)\n", 
		(byte)data[0], (byte)data[1], dataLen - 2);
		*/
		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(0, eLogin, false);
		byte *plainTextBuf = new byte[dataLen];
		std::copy(data, data + dataLen, plainTextBuf);
		msg->setData(data, dataLen);
		uiMsgQueue->addItem(msg);
		return;
	}


	byte *decryptedBuffer = new byte[dataLen];
	memset(decryptedBuffer, 0, dataLen);
	if (!streamObj->workingSendKey)
	{
		unsigned int msWaited = 0;
		std::cout << "Login request: " << std::endl;
		while (true)
		{

			//should use hint here, but have to reliably find corresponding stream
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(streamID, false);
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
			streamObj->toLoginSalsa.ProcessData(decryptedBuffer, data, dataLen);

			if (decryptedBuffer[0] == 0 && decryptedBuffer[1] == 3)
			{
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, streamID);

				UIaddLogMsg("Loginserver send key recovered", 
					keyCandidate->sourceProcess, 
					uiMsgQueue);

				streamObj->workingSendKey = keyCandidate;
				break;
			}
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eLogin, false);
		msg->setData(decryptedBuffer, dataLen);
		uiMsgQueue->addItem(msg);

		std::cout << std::setfill('0');
		std::cout << std::hex << std::setw(2) << "ID2: 0x" << (int)decryptedBuffer[5] << (int)decryptedBuffer[4] << (int)decryptedBuffer[3] << (int)decryptedBuffer[2] << std::endl;
		unsigned int emailLen = decryptedBuffer[7] * 2;
		if (decryptedBuffer[6] != 0)
			printf("Warning, long login email not handled\n");
		std::wstring email(reinterpret_cast<wchar_t*>(decryptedBuffer + 8), (emailLen) / sizeof(wchar_t));
		std::wcout << "\tUsername: " << email << std::endl;

		unsigned int pktindex = 8 + emailLen;
		std::cout << "\tPOE.exe hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tuser creds: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tMAC hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decryptedBuffer[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;

		std::cout << "\tPW save1: " << (int)(decryptedBuffer[pktindex++]) << std::endl;
		std::cout << "\tPW save2: " << (int)(decryptedBuffer[pktindex]) << std::endl;

		return;
	}

	streamObj->toLoginSalsa.ProcessData(decryptedBuffer, data, dataLen);

	std::cout << "Sent to login server...\n\n";
	std::cout << "\nhex:\n";
	std::cout << std::setfill('0');
	for (int i = 0; i < dataLen; ++i)
	{
		byte item = decryptedBuffer[i];
		if (item)
			std::cout << std::hex << std::setw(2) << (int)item << " ";
		else
			std::cout << "00 ";
		if (i % 16 == 0) { std::cout << std::endl; break; }
	}
	std::cout << "\n\n";
	std::cout.flush();
	
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eLogin, false);
	msg->setData(decryptedBuffer, dataLen);
	uiMsgQueue->addItem(msg);

	char pktType = decryptedBuffer[1];
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

		unsigned int charNameLen = decryptedBuffer[3] * 2;
		if (decryptedBuffer[2] != 0)
			printf("Warning, long login charname not handled\n");
		std::wstring charn(reinterpret_cast<wchar_t*>(decryptedBuffer + 4), (charNameLen) / sizeof(wchar_t));
		std::wcout << "\tSelected Char: " << charn << std::endl;
		//uidata.charname = charn;

		return;
	}
	case 11:
	{
		std::cout << "Character selection sent to login server by number: " << (int)decryptedBuffer[6] << std::endl;
		return;
	}
	default:
		printf("Client sent unknown packet to login server: 0x%x\n", decryptedBuffer[1]);

		std::cout << "Hex Payload: " << std::endl;
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decryptedBuffer[i];
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}
		std::cout << std::endl;

		return;
	}

}

void packet_processor::handle_login_data(std::vector<byte> pkt)
{

	char *next_token = (char *)pkt.data();

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	networkStreamID streamID = (networkStreamID)atoi(streamID_s);

	char *incoming = strtok_s(next_token, ",", &next_token);
	bool isIncoming = (*incoming == '1') ? true : false;

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *dLen = strtok_s(next_token, ",", &next_token);
	unsigned int dataLen = atoi(dLen);
	if (!dataLen)
		return;

	byte *data = (byte *)next_token;

	STREAMDATA *streamObj = &streamDatas[streamID];
	printf("[%ld]: Login data (%ld bytes) ", streamObj->packetCount, dataLen);

	if (isIncoming)
	{
		handle_packet_from_loginserver(streamID, data, dataLen);
	}
	else
	{
		handle_packet_to_loginserver(streamID, data, dataLen);
	}


	++streamObj->packetCount;
}

void packet_processor::handle_game_data(std::vector<byte> pkt)
{

	char *next_token = (char *)pkt.data();

	char *streamID_s = strtok_s(next_token, ",", &next_token);
	networkStreamID streamID = (networkStreamID)atoi(streamID_s);
	STREAMDATA *streamObj = &streamDatas[streamID];

	char *incoming = strtok_s(next_token, ",", &next_token);
	bool isIncoming = (*incoming == '1');

	char *timeprocessed = strtok_s(next_token, ",", &next_token);
	long long msProcessed = atoll(timeprocessed);

	char *dLen = strtok_s(next_token, ",", &next_token);
	unsigned int dataLen = atoi(dLen);
	if (!dataLen)
		return;

	//std::cout << "handling game data, size "<<std::dec <<dataLen<<" incoming- "<<(int)isIncoming << std::endl;

	byte *data = (byte *)next_token;

	if (dataLen > 0)
	{
		if (isIncoming)
			handle_packet_from_gameserver(streamID, data, dataLen, msProcessed);
		else
			handle_packet_to_gameserver(streamID, data, dataLen, msProcessed);
	}

	++streamObj->packetCount;
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




void packet_processor::handle_packet_to_gameserver(networkStreamID streamID, byte* data, 
	unsigned int dataLen, long long timems)
{

	STREAMDATA *streamObj = &streamDatas.at(streamID);
	if (streamObj->packetCount == 0)
	{
		if (data[0] == 0 && data[1] == 3)
		{
			unsigned long connectionID = getUlong(data + 2);

			if (pendingGameserverKeys.find(connectionID) == pendingGameserverKeys.end())
			{
					UIaddLogMsg("Error: No pending gameserver key", activeClientPID, uiMsgQueue);
					return;
			}

			streamObj->workingSendKey = pendingGameserverKeys.at(connectionID).first;
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			streamObj->workingRecvKey = pendingGameserverKeys.at(connectionID).second;
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			pendingGameserverKeys.erase(connectionID);

			//todo: decoded ui packet

			UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
				streamObj->workingSendKey->sourceProcess, eGame, false);
			byte *plainTextBuf = new byte[dataLen];
			std::copy(data, data + dataLen, plainTextBuf);
			msg->setData(plainTextBuf, dataLen);
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
	decryptedBuffer = new byte[dataLen+1];
	memset(decryptedBuffer, 0, dataLen+1);
	streamObj->toGameSalsa.ProcessData(decryptedBuffer, data, dataLen);

	if (unfinishedPacket)
	{
		std::cout << "todo: multipacket packets" << std::endl;
		return;
	}

	remainingDecrypted = dataLen;
	decryptedIndex = 0;
	errorFlag = eNoErr;


	while (remainingDecrypted > 0)
	{
		unsigned short pktIDWord = consumeUShort();

		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(streamObj->workingSendKey->sourceProcess, eGame, PKTBIT_OUTBOUND, timems);
		pktVec.push_back(ui_decodedpkt);
		ui_decodedpkt->setBuffer(decryptedBuffer);
		ui_decodedpkt->setStartOffset(decryptedIndex);
		ui_decodedpkt->messageID = pktIDWord;
		ui_decodedpkt->toggle_payload_operations(true);

		if (sanityCheckPacketID(pktIDWord) && errorFlag == eNoErr)
		{

			auto it = packetDeserialisers.find(pktIDWord);
			if (it != packetDeserialisers.end())
			{
				packet_processor::deserialiser deserialiserForPktID = it->second;
				(this->*deserialiserForPktID)(ui_decodedpkt);

				if (errorFlag == eNoErr)
					ui_decodedpkt->setEndOffset(decryptedIndex);
			}
			else
			{
				std::cout << "Unhandled Hex Payload msgID <gamesrv in> 0x" << std::hex << pktIDWord << std::endl;
				for (int i = 0; i < dataLen; ++i)
				{
					byte item = decryptedBuffer[i];
					std::cout << std::setw(2) << (int)item;
					if (i % 16 == 0) std::cout << std::endl;
				}
				std::cout << std::endl;

				errorFlag = eDecodingErr::ePktIDUnimplemented;
			}
		}

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



	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eGame, false);
	msg->setData(decryptedBuffer, dataLen);
	if (errorFlag != eNoErr)
		msg->setErrorIndex(decryptedIndex);
	uiMsgQueue->addItem(msg);

}

/*
aside from the handling of crypt at the start, the from_ and to_ gameserver functions
are equivalent. could merge them.
*/
void packet_processor::handle_packet_from_gameserver(networkStreamID streamID, byte* data, 
	unsigned int dataLen, long long timems)
{


	STREAMDATA *streamObj = &streamDatas.at(streamID);

	decryptedBuffer = new byte[dataLen];
	memset(decryptedBuffer, 0, dataLen);

	if (streamObj->packetCount == 1)
	{
		//first packet from gameserver starts 0005, followed by crypt which start 0012
		ushort firstPktID = getUshort(data);
		assert(firstPktID == SRV_PKT_ENCAPSULATED);

		streamObj->fromGameSalsa.SetKeyWithIV(
			(byte *)streamObj->workingRecvKey->salsakey, 32,
				(byte *)streamObj->workingRecvKey->IV);

		dataLen -= 2;
		streamObj->fromGameSalsa.ProcessData(decryptedBuffer, data+2, dataLen);
	}
	else
	{
		streamObj->fromGameSalsa.ProcessData(decryptedBuffer, data, dataLen);
	}

	if (unfinishedPacket)
	{
		std::cout << "todo: multipacket packets" << std::endl;
		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eGame, true);
		msg->setData(decryptedBuffer, dataLen);
		if (errorFlag != eNoErr)
			msg->setErrorIndex(decryptedIndex);
		uiMsgQueue->addItem(msg);
		return;
	}

	remainingDecrypted = dataLen;
	decryptedIndex = 0;
	errorFlag = eNoErr;

	while (remainingDecrypted > 0)
	{
		unsigned short pktIDWord = consumeUShort();

		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(streamObj->workingSendKey->sourceProcess, eGame, PKTBIT_INBOUND, timems);
		pktVec.push_back(ui_decodedpkt);
		
		ui_decodedpkt->setBuffer(decryptedBuffer);
		ui_decodedpkt->setStartOffset(decryptedIndex);
		ui_decodedpkt->messageID = pktIDWord;
		ui_decodedpkt->toggle_payload_operations(true);

		if (sanityCheckPacketID(pktIDWord) && errorFlag == eNoErr)
		{
			map<unsigned short, deserialiser>::iterator it = packetDeserialisers.find(pktIDWord);
			if (it != packetDeserialisers.end())
			{
				packet_processor::deserialiser deserialiserForPktID = it->second;
				(this->*deserialiserForPktID)(ui_decodedpkt);
				if (errorFlag == eNoErr)
					ui_decodedpkt->setEndOffset(decryptedIndex);
				
			}
			else
			{
				std::cout << "Unhandled Hex Payload msgID <gamesrv in> 0x" << std::hex << pktIDWord << std::endl;
				for (int i = 0; i < dataLen; ++i)
				{
					byte item = decryptedBuffer[i];
					std::cout << std::setw(2) << (int)item;
					if (i % 16 == 0) std::cout << std::endl;
				}
				std::cout << std::endl;

				errorFlag = eDecodingErr::ePktIDUnimplemented;
			}
		}

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

	//print the whole blob in the raw log
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eGame, true);
	msg->setData(decryptedBuffer, dataLen);
	if (errorFlag != eNoErr)
		msg->setErrorIndex(decryptedIndex);
	uiMsgQueue->addItem(msg);
}


bool packet_processor::process_packet_loop()
{
	std::vector<byte> pkt;
	std::queue< std::vector<byte>> pktQueue;

	while (true)
	{
		//highest priority - only check patch/login if game is quiet
		if (checkPipe(gamepipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_game_data(pkt);
				pktQueue.pop();
			}
			continue;
		}

		if (checkPipe(loginpipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_login_data(pkt);
				pktQueue.pop();
			}
			continue;
		}

		if (checkPipe(patchpipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_patch_data(pkt);
				pktQueue.pop();
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