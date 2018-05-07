#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"
#include "utilities.h"
#include "inventory.h"
#pragma comment(lib, "N:\\code\\POEcode\\poeSRE\\clientX\\packages\\cryptopp.v140.5.6.5.2\\lib\\native\\v140\\windesktop\\msvcstl\\x64\\Debug\\md\\cryptopp.lib")

/*
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
*/




void packet_processor::handle_packet_from_loginserver(vector<byte> &nwkData, long long timems)
{
	if (currentStreamObj->failed) return;

	size_t dataLen = nwkData.size();
	if (currentStreamObj->ephKeys < 2) 
	{
		ushort pktID = ntohs(getUshort(nwkData.data()));
		if (pktID != LOGIN_EPHERMERAL_PUBKEY) return;

		currentStreamObj->ephKeys++;

		decryptedBuffer = new vector<byte>;
		decryptedBuffer->resize(dataLen, 0);
		remainingDecrypted = dataLen;
		decryptedIndex = 0;

		UI_RAWHEX_PKT *hexmsg = new UI_RAWHEX_PKT(0, eLogin, true);
		hexmsg->setData(decryptedBuffer);
		uiMsgQueue->addItem(hexmsg);

		UIDecodedPkt *ui_decodedpkt = new UIDecodedPkt(0, eLogin, currentMsgStreamID, PKTBIT_INBOUND, timems);

		deserialisedPkts.push_back(ui_decodedpkt);
		ui_decodedpkt->setBuffer(decryptedBuffer);
		ui_decodedpkt->setStartOffset(0);
		ui_decodedpkt->setEndOffset(dataLen);
		ui_decodedpkt->messageID = LOGIN_EPHERMERAL_PUBKEY;
		ui_decodedpkt->toggle_payload_operations(true);

		decryptedIndex = 2;
		remainingDecrypted = dataLen - 2;
		packet_processor::deserialiser deserialiserForPktID = loginPktDeserialisers.at(LOGIN_EPHERMERAL_PUBKEY);
		(this->*deserialiserForPktID)(ui_decodedpkt);

		uiMsgQueue->addItem(ui_decodedpkt);

		return;
	}

	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);

	bool alreadyDecrypted = false;

	if (!currentStreamObj->workingRecvKey)
	{
		while (!currentStreamObj->workingRecvKey)
		{
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(currentMsgStreamID, true);
			if (!keyCandidate) {
				std::cout << "no unused memkey in from login!" << std::endl;
				Sleep(1200);
				continue;
			}

			if (keyCandidate->used) std::cout << "assert 3" << std::endl;
			assert(!keyCandidate->used);

			currentStreamObj->recvSalsa.SetKeyWithIV((const byte *)keyCandidate->salsakey,
				32,	(const byte *)keyCandidate->IV);
			currentStreamObj->recvSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);

			unsigned short packetID = ntohs(getUshort(decryptedBuffer->data()));
			if (packetID == LOGIN_SRV_UNK0x4)
			{
				alreadyDecrypted = true;
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, currentMsgStreamID);

				UIaddLogMsg("Loginserver receive key recovered", keyCandidate->sourceProcess,
					uiMsgQueue);

				UIrecordLogin(keyCandidate->sourceProcess, uiMsgQueue);

				keyGrabber->stopProcessScan(keyCandidate->sourceProcess);
				currentStreamObj->workingRecvKey = keyCandidate;

				vector<byte> IVVec((byte*)keyCandidate->IV, ((byte*)keyCandidate->IV) + 8);
				UIUpdateRecvIV(IVVec, uiMsgQueue);
				sendIterationToUI(currentStreamObj->recvSalsa, false);


				UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamDecrypting, uiMsgQueue);

				break;
			}
			else
			{
				std::stringstream err;
				err << std::hex << "Decryption failure. Expected packet "<<LOGIN_SRV_UNK0x4<<
					" from loginserver but got 0x"  << packetID;

				UIaddLogMsg(err.str(), 0, uiMsgQueue);

				//todo: need to handle gracefully

				return;
			}
		}

	}

	if (!alreadyDecrypted)
	{
		try {
			currentStreamObj->recvSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);
		}
		catch (...) {
			QString msg = "An exception was caught during salsa decrypt. This is usually due to incorrect deserialisation";
			UIaddLogMsg(msg, getLatestDecryptProcess(), uiMsgQueue);
			currentStreamObj->failed = true;
			UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamFailed, uiMsgQueue);
			return;
		}

		sendIterationToUI(currentStreamObj->recvSalsa, false);
	}

	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(currentStreamObj->workingSendKey->sourceProcess, eLogin, true);
	msg->setData(decryptedBuffer);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;
	decryptedIndex = 0;

	deserialise_packets_from_decrypted(eLogin, PKTBIT_INBOUND, timems);
}

void packet_processor::sendIterationToUI(CryptoPP::Salsa20::Encryption sobj, bool send)
{
	if (!displayingIters) return;

	if (send)
		UIUpdateSendIter(extract_Iter_from_salsaObj(sobj), uiMsgQueue);
	else
		UIUpdateRecvIter(extract_Iter_from_salsaObj(sobj), uiMsgQueue);
}

void packet_processor::handle_packet_to_loginserver(vector<byte> &nwkData, long long timems)
{
	size_t dataLen = nwkData.size();
	if (currentStreamObj->failed) return;
	if (currentStreamObj->ephKeys < 2)
	{
		if (currentStreamObj->ephKeys == 0)
		{
			currentStreamObj->queue = loginQueue;
			UInotifyStreamState(currentMsgStreamID, eStreamLoggingIn, uiMsgQueue);
		}

		if (dataLen < 2) return;
		ushort pktID = ntohs(getUshort(nwkData.data()));
		if (pktID != LOGIN_EPHERMERAL_PUBKEY) { 
			UIaddLogMsg("Warning: First recorded login packets were not ephermeral keys.",0, uiMsgQueue);
			return; 
		}

		currentStreamObj->ephKeys++;

		decryptedBuffer = new vector<byte>;
		decryptedBuffer->resize(dataLen, 0);
		remainingDecrypted = dataLen;
		decryptedIndex = 0;

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(0, eLogin, false);
		
		msg->setData(decryptedBuffer);
		uiMsgQueue->addItem(msg);

		UIDecodedPkt *ui_decodedpkt = new UIDecodedPkt(0, eLogin, currentMsgStreamID, PKTBIT_OUTBOUND, timems);
		ui_decodedpkt->setBuffer(decryptedBuffer);
		ui_decodedpkt->setStartOffset(0);
		ui_decodedpkt->setEndOffset(dataLen);
		ui_decodedpkt->messageID = LOGIN_EPHERMERAL_PUBKEY;
		ui_decodedpkt->toggle_payload_operations(true);
		deserialisedPkts.push_back(ui_decodedpkt);

		decryptedIndex = 2;
		remainingDecrypted = dataLen - 2;
		packet_processor::deserialiser deserialiserForPktID = loginPktDeserialisers.at(LOGIN_EPHERMERAL_PUBKEY);
		(this->*deserialiserForPktID)(ui_decodedpkt);

		uiMsgQueue->addItem(ui_decodedpkt);

		return;
	}

	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);

	ushort firstPktID = 0;

	if (!currentStreamObj->workingSendKey)
	{
		unsigned int msWaited = 0;
		while (true)
		{
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(currentMsgStreamID, false);
			if (!keyCandidate) {

				Sleep(200);
				msWaited += 200;
				//every two seconds relax the memory scan filters
				if (msWaited % 2000 == 0)
				{
					keyGrabber->relaxScanFilters();
					if (msWaited > 4000)
					{
						UIaddLogMsg("Pkt_to_login - Warning: Long wait for memory key", 0, uiMsgQueue);
						if (msWaited > 15000)
						{
							UIaddLogMsg("Decryption abandoned due to long wait", 0, uiMsgQueue);
							currentStreamObj->failed = true;
							UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamFailed, uiMsgQueue);
							return;
						}
					}
				}
				continue;
			}

			if (keyCandidate->used) std::cout << "assert 4" << std::endl;
			assert(!keyCandidate->used);

			currentStreamObj->sendSalsa.SetKeyWithIV((byte *)keyCandidate->salsakey,
				32,
				(byte *)keyCandidate->IV);

			currentStreamObj->sendSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);

			firstPktID = ntohs(getUshort(&decryptedBuffer->at(0)));

			if (firstPktID == LOGIN_CLI_AUTH_DATA || firstPktID == LOGIN_CLI_RESYNC)
			{
				keyCandidate->used = true;
				keyGrabber->claimKey(keyCandidate, currentMsgStreamID);
				activeClientPID = keyCandidate->sourceProcess;

				currentStreamObj->workingSendKey = keyCandidate;

				vector<byte> keyVec((byte *)keyCandidate->salsakey, (byte *)(keyCandidate->salsakey) + 32);
				UIdisplaySalsaKey(keyVec, uiMsgQueue);

				vector<byte> IVVec((byte *)keyCandidate->IV, (byte *)(keyCandidate->IV) + 8);
				UIUpdateSendIV(IVVec, uiMsgQueue);

				UIaddLogMsg("Loginserver send key recovered", keyCandidate->sourceProcess, uiMsgQueue);

				break;
			}
		}

		sendIterationToUI(currentStreamObj->sendSalsa, true);

		if (firstPktID == LOGIN_CLI_AUTH_DATA)
		{
			//overwrite the creds so they don't get logged
			ushort namelen = ntohs(getUshort(&decryptedBuffer->at(6)));
			ushort credsloc = 2 + 4 + 2 + (namelen * 2) + 32;
			for (int i = 0; i < 32; i++)
				decryptedBuffer->at(credsloc + i) = 0xf;
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(currentStreamObj->workingSendKey->sourceProcess, eLogin, false);
		msg->setData(decryptedBuffer);
		uiMsgQueue->addItem(msg);


		
		UIDecodedPkt *ui_decodedpkt = new UIDecodedPkt(0, eLogin, currentMsgStreamID, PKTBIT_OUTBOUND, timems);

		ui_decodedpkt->setBuffer(decryptedBuffer);
		ui_decodedpkt->setStartOffset(0);
		ui_decodedpkt->setEndOffset(dataLen);
		ui_decodedpkt->messageID = firstPktID;
		ui_decodedpkt->toggle_payload_operations(true);
		deserialisedPkts.push_back(ui_decodedpkt);

		remainingDecrypted = dataLen - 2;
		decryptedIndex = 2;
		packet_processor::deserialiser deserialiserForPktID = loginPktDeserialisers.at(firstPktID);
		(this->*deserialiserForPktID)(ui_decodedpkt);

		uiMsgQueue->addItem(ui_decodedpkt);
		
		return;
	}

	currentStreamObj->sendSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);
	sendIterationToUI(currentStreamObj->sendSalsa, true);

	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(currentStreamObj->workingSendKey->sourceProcess, eLogin, false);
	msg->setData(decryptedBuffer);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;
	decryptedIndex = 0;

	deserialise_packets_from_decrypted(eLogin, PKTBIT_OUTBOUND, timems);
}

void packet_processor::handle_login_data(GAMEPACKET &pkt)
{
	currentMsgStreamID = pkt.streamID;
	currentStreamObj = &streamDatas[currentMsgStreamID];
	if (currentStreamObj->failed)
		return;

	currentMsgIncoming = pkt.incoming;

	if (!pkt.data.empty())
	{
		if (pkt.incoming)
			handle_packet_from_loginserver(pkt.data, pkt.time);
		else
			handle_packet_to_loginserver(pkt.data, pkt.time);
	}

	++currentStreamObj->packetCount;
}

bool packet_processor::handle_game_data(GAMEPACKET &pkt)
{
	currentMsgStreamID = pkt.streamID;
	currentStreamObj = &streamDatas[currentMsgStreamID];
	if (currentStreamObj->failed)
		return false;

	if (currentStreamObj->workingSendKey == NULL && pendingGameserverKeys.empty())
		return false;

	currentMsgIncoming = pkt.incoming;

	//the keys are established during handling of the first packet to the gameserver
	//sometimes we will process the response from the gameserver first, causing badness.
	//delays processing of recv data until we have a recv key
	if (currentMsgIncoming && currentStreamObj->workingRecvKey == NULL)
		return false;

	if (!pkt.data.empty())
	{
		if (pkt.incoming)
			handle_packet_from_gameserver(pkt.data, pkt.time);
		else
			handle_packet_to_gameserver(pkt.data, pkt.time);
	}

	++currentStreamObj->packetCount;
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


void packet_processor::deserialise_packets_from_decrypted(streamType streamServer, byte directionBit, long long timeSeen)
{
	unsigned int dataLen = remainingDecrypted;
	while (remainingDecrypted > 0)
	{
		unsigned short pktIDWord = ntohs(consume_WORD());
		DWORD sourceProcess = currentStreamObj->workingSendKey->sourceProcess;
		UIDecodedPkt *ui_decodedpkt = new UIDecodedPkt(sourceProcess,	
			streamServer, currentMsgStreamID, directionBit, timeSeen);

		deserialisedPkts.push_back(ui_decodedpkt);
		ui_decodedpkt->setStartOffset(decryptedIndex - 2);
		ui_decodedpkt->messageID = pktIDWord;
		ui_decodedpkt->toggle_payload_operations(true);

		if (sanityCheckPacketID(pktIDWord) && errorFlag == eNoErr)
		{
			//find and run deserialiser for this packet
			map<unsigned short, deserialiser>* deserialiserList;
			if (streamServer == streamType::eGame)
				deserialiserList = &gamePktDeserialisers;
			else
				deserialiserList = &loginPktDeserialisers;

			auto it = deserialiserList->find(pktIDWord);
			if (it != deserialiserList->end())
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
		
		//warning - can be resized (and thus moved) during deserialisation - only store pointers afterwards
		ui_decodedpkt->setBuffer(decryptedBuffer);

		if (errorFlag != eNoErr)
		{
			remainingDecrypted = 0;
			emit_decoding_err_msg(pktIDWord, currentStreamObj->lastPktID);
			ui_decodedpkt->setFailedDecode();
			ui_decodedpkt->setEndOffset(dataLen);
		}

		uiMsgQueue->addItem(ui_decodedpkt);
		currentStreamObj->lastPktID = pktIDWord;
	}
}

void packet_processor::handle_packet_to_gameserver(vector<byte> &nwkData, long long timems)
{
	size_t dataLen = nwkData.size();
	if (currentStreamObj->workingSendKey == NULL)
	{
		ushort pktID = ntohs(getUshort(nwkData.data()));
		currentStreamObj->queue = gameQueue;
		if (pktID == 3)
		{
			unsigned long connectionID = ntohl(getUlong(nwkData.data() + 2));

			if (pendingGameserverKeys.find(connectionID) == pendingGameserverKeys.end())
			{
				if (!pendingGameserverKeys.empty())
				{
					std::stringstream warn;
					warn << "Warning: Connection ID " << connectionID << " didn't match pending " <<
						pendingGameserverKeys.begin()->first << " (" << pendingGameserverKeys.size() << " pending)";
					UIaddLogMsg(warn.str(),	activeClientPID, uiMsgQueue);

					currentStreamObj->workingSendKey = pendingGameserverKeys.at(connectionID).first;
					currentStreamObj->workingRecvKey = pendingGameserverKeys.at(connectionID).second;
					UInotifyStreamState(currentMsgStreamID, eStreamDecrypting, uiMsgQueue);
					pendingGameserverKeys.clear();
				}
				else
				{
					UIaddLogMsg("Error: No pending gameserver key. Set during login or previous instance server.",
					activeClientPID, uiMsgQueue);
					currentStreamObj->failed = true;
					UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamFailed, uiMsgQueue);
					return; 
				}

			}
			else
			{
				currentStreamObj->workingSendKey = pendingGameserverKeys.at(connectionID).first;
				currentStreamObj->workingRecvKey = pendingGameserverKeys.at(connectionID).second;
				UInotifyStreamState(currentMsgStreamID, eStreamDecrypting, uiMsgQueue);
			}
			
			byte *salsaSendKey = (byte *)currentStreamObj->workingSendKey->salsakey;
			byte *salsaSendIV = (byte *)currentStreamObj->workingSendKey->IV;
			byte *salsaRecvIV = (byte *)currentStreamObj->workingRecvKey->IV;

			currentStreamObj->sendSalsa.SetKeyWithIV(salsaSendKey, 32, salsaSendIV);

			vector<byte> keyVec(salsaSendKey, salsaSendKey + 32);
			vector<byte> IVsVec(salsaSendIV, salsaSendIV + 8);
			vector<byte> IVrVec(salsaRecvIV, salsaRecvIV + 8);

			UIdisplaySalsaKey(keyVec, uiMsgQueue);
			UIUpdateSendIV(IVsVec, uiMsgQueue);
			UIUpdateRecvIV(IVrVec, uiMsgQueue);
			sendIterationToUI(currentStreamObj->sendSalsa, true);
			sendIterationToUI(currentStreamObj->recvSalsa, false);

			pendingGameserverKeys.erase(connectionID);

			UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
				currentStreamObj->workingSendKey->sourceProcess, eGame, false);
			vector<byte> *plainTextBuf = new vector<byte>(nwkData.begin(), nwkData.end());
			msg->setData(plainTextBuf);
			uiMsgQueue->addItem(msg);

		}
		else
		{
			currentStreamObj->failed = true;
			UIaddLogMsg("Failed to decrypt first packet - was sniffing started before login?", activeClientPID, uiMsgQueue);
			UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamFailed, uiMsgQueue);
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
	currentStreamObj->sendSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);
	sendIterationToUI(currentStreamObj->sendSalsa, true);


	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(currentStreamObj->workingSendKey->sourceProcess, eGame, false);
	msg->setData(decryptedBuffer);
	if (errorFlag != eNoErr)
		msg->setErrorIndex(decryptedIndex);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;
	decryptedIndex = 0;
	errorFlag = eNoErr;

	deserialise_packets_from_decrypted(eGame, PKTBIT_OUTBOUND, timems);

}

void packet_processor::handle_packet_from_gameserver(vector<byte> &nwkData, long long timems)
{
	size_t dataLen = nwkData.size();
	decryptedBuffer = new vector<byte>;
	decryptedBuffer->resize(dataLen, 0);
	decryptedIndex = 0;
	errorFlag = eNoErr;

	if (currentStreamObj->packetCount == 1)
	{
		//first packet from gameserver starts 0005, followed by crypt which starts 0012
		ushort firstPktID = ntohs(getUshort(nwkData.data()));
		assert(firstPktID == SRV_PKT_ENCAPSULATED);

		currentStreamObj->recvSalsa.SetKeyWithIV(
			(byte *)currentStreamObj->workingRecvKey->salsakey, 32,
				(byte *)currentStreamObj->workingRecvKey->IV);

		dataLen -= 2;
		currentStreamObj->recvSalsa.ProcessData(decryptedBuffer->data(), nwkData.data()+2, dataLen);

	}
	else
	{
		currentStreamObj->recvSalsa.ProcessData(decryptedBuffer->data(), nwkData.data(), dataLen);
	}
	sendIterationToUI(currentStreamObj->recvSalsa, false);


	//print the whole blob in the raw log
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(currentStreamObj->workingRecvKey->sourceProcess, eGame, true);
	msg->setData(decryptedBuffer);
	if (errorFlag != eNoErr) msg->setErrorIndex(0);
	uiMsgQueue->addItem(msg);

	remainingDecrypted = dataLen;

	deserialise_packets_from_decrypted(eGame, PKTBIT_INBOUND, timems);
}



bool packet_processor::process_packet_loop()
{
	GAMEPACKET pkt;

	while (true)
	{
		//highest priority - only check patch/login if game is quiet
		if (checkQueue(gameQueue, pendingPktQueue))
		{
			bool done = false;
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				done = handle_game_data(pkt);
				if (done)
				{
					pendingPktQueue.pop_front();
				}
				else
				{
					//tried to handle first response before first send so no key to read recv
					//wait until first send done
					while (!done)
					{
						Sleep(100);
						checkQueue(gameQueue, pendingPktQueue);

						auto it = pendingPktQueue.begin();
						for (; it != pendingPktQueue.end(); it++)
						{
							pkt = *it;
							done = handle_game_data(pkt);
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

		if (checkQueue(loginQueue, pendingPktQueue))
		{
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				handle_login_data(pkt);
				pendingPktQueue.pop_front();
			}
			continue;
		}

		/*
		if (checkPipe(patchpipe, &pendingPktQueue))
		{
			while (!pendingPktQueue.empty())
			{
				pkt = pendingPktQueue.front();
				handle_patch_data(pkt.data());
				pendingPktQueue.pop_front();
			}
		}
		*/
		Sleep(10);
	}
	return true;
}




void packet_processor::main_loop()
{
	init_loginPkt_deserialisers();
	init_gamePkt_deserialisers();

	unsigned int errCount = 0;
	process_packet_loop();

}