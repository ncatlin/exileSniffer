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
		msg->setData(data, dataLen);
		uiMsgQueue->addItem(msg);
		return;
	}

	byte *decrypted = new byte[dataLen];

	memset(decrypted, 0, dataLen);

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
			streamObj->fromLoginSalsa.ProcessData(decrypted, data, dataLen);

			unsigned short packetID = getUshort(decrypted);
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
				UIaddLogMsg("ERROR: Loginserver receive bad decrypt for packet 4",
					0,	uiMsgQueue);
				return;
			}
		}

		std::cout << "Character List (" << (int)decrypted[45] << " characters)" << std::endl;

		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
			std::cout << std::hex << std::setw(2) << (int)item;
			if (i % 16 == 0) std::cout << std::endl;
		}

		UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, false);
		msg->setData(decrypted, dataLen);
		uiMsgQueue->addItem(msg);
		delete decrypted;
		return;
	}

	streamObj->fromLoginSalsa.ProcessData(decrypted, data, dataLen);

	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingRecvKey->sourceProcess, eLogin, true);
	msg->setData(decrypted, dataLen);
	uiMsgQueue->addItem(msg);

	char pktType = decrypted[1];
	switch (pktType)
	{
	case SRVPK_GAMESERVER_INFO:
	{
		std::cout << "Got gameserver info from loginserver" << std::endl;
		//outfile << "Got gameserver info from loginserver" << std::endl;
		unsigned int pktidx = 2;

		unsigned long connectionID = getUlong(decrypted + 10);
		std::cout << "Got key for connection ID " << std::hex << connectionID << std::endl;

		pktidx = 17;
		unsigned int port = (decrypted[17] << 8) + decrypted[18];
		std::stringstream serverIP;
		serverIP << (int)decrypted[19] << ".";
		serverIP << (int)decrypted[20] << ".";
		serverIP << (int)decrypted[21] << ".";
		serverIP << (int)decrypted[22] << ":" << std::dec << port;
		std::cout << "\tGameserver: " << serverIP.str() << std::endl;

		DWORD *keyblob = (DWORD *)((byte*)decrypted + 43);


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
		std::cout << "League data from login server" << decrypted << std::endl;
		return;


	default:
		printf("Unknown packet from login server: byte[1]==0x%x (dec %d)\n", decrypted[1], decrypted[1]);

		std::cout << "Hex Payload: " << std::endl;
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
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
		msg->setData(data, dataLen);
		uiMsgQueue->addItem(msg);
		return;
	}


	byte *decrypted = new byte[dataLen];
	memset(decrypted, 0, dataLen);
	if (!streamObj->workingSendKey)
	{
		std::cout << "Login request: " << std::endl;
		while (true)
		{
			//should use hint here, but have to reliably find corresponding stream
			KEYDATA *keyCandidate = keyGrabber->getUnusedMemoryKey(streamID, false);
			if (!keyCandidate) {
				std::cout << "sleep no key candidate for sid " << streamID << std::endl;
				Sleep(200);
				continue;
			}

			if (keyCandidate->used) std::cout << "assert 4" << std::endl;
			assert(!keyCandidate->used);

			streamObj->toLoginSalsa.SetKeyWithIV((byte *)keyCandidate->salsakey,
				32,
				(byte *)keyCandidate->IV);
			streamObj->toLoginSalsa.ProcessData(decrypted, data, dataLen);

			if (decrypted[0] == 0 && decrypted[1] == 3)
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
		msg->setData(decrypted, dataLen);
		uiMsgQueue->addItem(msg);

		std::cout << std::setfill('0');
		std::cout << std::hex << std::setw(2) << "ID2: 0x" << (int)decrypted[5] << (int)decrypted[4] << (int)decrypted[3] << (int)decrypted[2] << std::endl;
		unsigned int emailLen = decrypted[7] * 2;
		if (decrypted[6] != 0)
			printf("Warning, long login email not handled\n");
		std::wstring email(reinterpret_cast<wchar_t*>(decrypted + 8), (emailLen) / sizeof(wchar_t));
		std::wcout << "\tUsername: " << email << std::endl;

		unsigned int pktindex = 8 + emailLen;
		std::cout << "\tPOE.exe hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decrypted[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tuser creds: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decrypted[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;
		std::cout << "\tMAC hash: ";
		for (int i = 0; i < 32; ++i)
		{
			byte item = decrypted[pktindex + i];
			std::cout << std::hex << std::setw(2) << (int)item;
		}
		std::cout << std::endl;

		pktindex += 32;

		std::cout << "\tPW save1: " << (int)(decrypted[pktindex++]) << std::endl;
		std::cout << "\tPW save2: " << (int)(decrypted[pktindex]) << std::endl;



		delete decrypted;
		return;
	}

	streamObj->toLoginSalsa.ProcessData(decrypted, data, dataLen);

	std::cout << "Sent to login server...\n\n";
	std::cout << "\nhex:\n";
	std::cout << std::setfill('0');
	for (int i = 0; i < dataLen; ++i)
	{
		byte item = decrypted[i];
		if (item)
			std::cout << std::hex << std::setw(2) << (int)item << " ";
		else
			std::cout << "00 ";
		if (i % 16 == 0) { std::cout << std::endl; break; }
	}
	std::cout << "\n\n";
	std::cout.flush();
	
	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(streamObj->workingSendKey->sourceProcess, eLogin, false);
	msg->setData(decrypted, dataLen);
	uiMsgQueue->addItem(msg);

	char pktType = decrypted[1];
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

		unsigned int charNameLen = decrypted[3] * 2;
		if (decrypted[2] != 0)
			printf("Warning, long login charname not handled\n");
		std::wstring charn(reinterpret_cast<wchar_t*>(decrypted + 4), (charNameLen) / sizeof(wchar_t));
		std::wcout << "\tSelected Char: " << charn << std::endl;
		//uidata.charname = charn;

		return;
	}
	case 11:
	{
		std::cout << "Character selection sent to login server by number: " << (int)decrypted[6] << std::endl;
		return;
	}
	default:
		printf("Client sent unknown packet to login server: 0x%x\n", decrypted[1]);

		std::cout << "Hex Payload: " << std::endl;
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
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

	char *dLen = strtok_s(next_token, ",", &next_token);
	unsigned int dataLen = atoi(dLen);
	if (!dataLen)
		return;

	std::cout << "handling game data, size "<<std::dec <<dataLen<<" incoming- "<<(int)isIncoming << std::endl;

	byte *data = (byte *)next_token;

	if (dataLen > 0)
	{
		if (isIncoming)
			handle_packet_from_gameserver(streamID, data, dataLen);
		else
			handle_packet_to_gameserver(streamID, data, dataLen);
	}

	++streamObj->packetCount;
}

bool sanityCheckPacketID(unsigned short pktID)
{
	if (pktID > 0x220)
	{
		std::cout << "\n\n-------------" <<
			"!!!WARNING! Very high Packet ID! (0x" << std::hex << pktID <<
			") Decrypt probably out of sync or using wrong key/IV!---------\n" << std::endl;

		return false;
	}
	return true;
}

std::string explainMouseLastByte(byte lastByte)
{
	/*
	00001000 click       0x8
	00001001 +shift		 0x9
	00001010 +windowOpen 0xa
	00001100 +ctrl		 0xc

	8 = inventory/etc open
	9 = shift held
	c = control held
	*/

	std::string result = "";

	if (lastByte & 0x1)
		result += "+shift ";
	if (lastByte & 0x2)
		result += "+dilog ";
	if (lastByte & 0x4)
		result += "+ctrl ";

	return result;
}

bool packet_processor::lookup_areaCode(unsigned long code, std::string& result)
{
	auto areasIt = areaCodes.find(code);
	if (areasIt != areaCodes.end())
	{
		result = areasIt->second;
		return true;
	}

	std::stringstream failResString;
	failResString << "<LookupFailure UnknownArea 0x" << std::hex << code << ">";
	result = failResString.str();
	return false;
}

bool packet_processor::lookup_hash(unsigned long hash, std::string& result, std::string& category)
{
	auto monstersIt = monsterHashes.find(hash);
	if (monstersIt != monsterHashes.end())
	{
		result = monstersIt->second;
		category = "Monster";
		return true;
	}

	auto objectsIt = gameObjHashes.find(hash);
	if (objectsIt != gameObjHashes.end())
	{
		result = objectsIt->second;
		category = "Object";
		return true;
	}

	auto chestsIt = chestHashes.find(hash);
	if (chestsIt != chestHashes.end())
	{
		result = chestsIt->second;
		category = "Chest";
		return true;
	}

	auto charactersIt = characterHashes.find(hash);
	if (charactersIt != characterHashes.end())
	{
		result = charactersIt->second;
		category = "Character";
		return true;
	}

	auto npcsIt = NPCHashes.find(hash);
	if (npcsIt != NPCHashes.end())
	{
		result = npcsIt->second;
		category = "NPC";
		return true;
	}

	auto petsIt = petHashes.find(hash);
	if (petsIt != petHashes.end())
	{
		result = petsIt->second;
		category = "Pet";
		return true;
	}

	auto itemsIt = itemHashes.find(hash);
	if (itemsIt != itemHashes.end())
	{
		result = itemsIt->second;
		category = "Item";
		return true;
	}

	std::stringstream resString;
	resString << "<0x" << std::hex << hash << ">";
	result = resString.str();
	category = "UnknownHash";

	return false;
}












void packet_processor::handle_packet_to_gameserver(networkStreamID streamID, byte* data, unsigned int dataLen)
{

	STREAMDATA *streamObj = &streamDatas.at(streamID);
	if (streamObj->packetCount == 0)
	{
		if (data[0] == 0 && data[1] == 3)
		{
			unsigned long connectionID = getUlong(data + 2);
			std::cout << "Continuing connection ID " << std::hex<< connectionID << std::endl;

			streamObj->workingSendKey = pendingGameserverKeys.at(connectionID).first;
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			streamObj->workingRecvKey = pendingGameserverKeys.at(connectionID).second;
			streamObj->toGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingSendKey->salsakey, 32,
				(byte *)streamObj->workingSendKey->IV);

			pendingGameserverKeys.erase(connectionID);

			UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
				streamObj->workingSendKey->sourceProcess, eGame, false);
			msg->setData(data, dataLen);
			uiMsgQueue->addItem(msg);

		}
		else
		{
			std::cerr << "Warning! Unexpected first client packet|||!!!" << std::endl;
		}
		return;
	}

	byte *decrypted = new byte[dataLen];
	memset(decrypted, 0, dataLen);
	streamObj->toGameSalsa.ProcessData(decrypted, data, dataLen);

	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
		streamObj->workingSendKey->sourceProcess, eGame, false);
	msg->setData(decrypted, dataLen);
	uiMsgQueue->addItem(msg);


	bool dumpHex = false;
	int remainingBytes = dataLen;

	int index = 0;
	int sIdx = index;

	while (true)
	{
		if (remainingBytes == 0) break;
		if (remainingBytes < 2) {
			std::cerr << "ERROR! Bad remaining len. Datalen was " << dataLen
				<< ", remaining now " << remainingBytes << std::endl;
			dumpHex = true;
			break;
		}

		unsigned short pktId = getUshort(decrypted + sIdx); sIdx += 2;

		sanityCheckPacketID(pktId);

		switch (pktId)
		{
		case CLI_CHAT_MESSAGE_ITEMS:
		{
			/*
			used when items are linked, but replaces CLI_CHAT_MESSAGE entirely with 2+ items
			-------
			00 06 //pkt id

			//header. expands 15 bytes for every extra item.
			//cant see obvious link between values and item codes

			00 00 00 01
			00 00 00 01
			00 00 04 04 00 00 08

			00 06 //text len (bytes*2)
			23 00 5f 00 61  00 61 00 61 00 5f 00  //text with 5f00 replacing items
			02 //item count
			00 00 00 01  //item reference
			00 00 00 05
			-------
			need to understand header bytes but not a priority at the moment.
			notes for 2+ items:
			[header]

			header has 15 bytes per item

			*/
			std::cout << "Player linked items in chat" << std::endl;
			break;
		}

		case CLI_CHAT_MESSAGE:
		{
			unsigned short msgLen = getUshort(decrypted + sIdx); sIdx += 2;
			std::string msgmb(decrypted + sIdx, decrypted + sIdx + msgLen * 2); sIdx += (msgLen * 2);
			std::wstring msg = mb_to_utf8(msgmb);
			byte itemCount = decrypted[sIdx++];

			if (itemCount == 0)
				std::wcout << "[You In Chat]:\"" << msg << "\"" << std::endl;
			else
			{
				int itemPos = msg.find(0x5f, 0);
				std::wcout << "[You In Chat]:\"" << msg.substr(0, itemPos);
				std::wcout << "_ITEM";
				std::wcout << msg.substr(itemPos, msg.size()) << std::endl;
			}

			sIdx += (4 * itemCount);




			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;

		}
		case CLI_CHAT_COMMAND:
		{
			byte commandID = decrypted[sIdx]; sIdx += 1;
			short unk = getUshort(decrypted + sIdx); sIdx += 2;

			std::cout << "Client used command: ";

			bool knownShortCommand = true;

			//todo - future GGPK integration: 
			//	can look up as (RowID+1) in Data/Commands.dat 
			switch (commandID) {
			case 0x04:
				std::cout << "/remaining";
				break;
			case 0x06:
				std::cout << "/pvp";
				break;
			case 0x08:
				std::cout << "/oos";
				break;
			case 0x0d:
				std::cout << "/fixmyhelmet";
				break;
			case 0x2f:
				std::cout << "/menagerie";
				break;
			default:
				std::cout << std::hex << (int)commandID <<
					" [not bothered to list - todo put these in a map and lookup]" << std::endl;
				knownShortCommand = false;
				break;
			}

			if (knownShortCommand)
			{
				remainingBytes -= (sIdx - index);
				index = sIdx;
				continue;
			}
			else
			{
				dumpHex = true;
				break;
			}
		}
		case CLI_LOGGED_OUT:
		{
			//logout: arg 0
			byte arg = decrypted[sIdx]; sIdx += 1;
			std::cout << "Client logged out. Arg: " << (int)arg << std::endl;
			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case CLIPK_PING_CHALLENGE:
		{
			//ignore for now
			sIdx += 4;
			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case CLI_CLICKED_GROUND_ITEM:
		{
			unsigned long targID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk1 = getUlong(decrypted + sIdx); sIdx += 4;
			char controlStatus = decrypted[sIdx]; sIdx += 1;


			std::cout << std::hex << "Client clicked" << explainMouseLastByte(controlStatus)
				<< " on world obj ID 0x" << targID << " unk1: 0x" << unk1 << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;

		}

		case CLI_ACTION_PREDICTIVE:
		{
			unsigned long targcoord1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long targcoord2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned short skill = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short pcount = getUshort(decrypted + sIdx); sIdx += 2;
			char controlStatus = decrypted[sIdx]; sIdx += 1;

			std::cout << std::hex << "Player used" << explainMouseLastByte(controlStatus)
				<< " skill 0x" << skill << " on coord (" <<
				targcoord1 << "," << targcoord2 << ") " << std::endl;

			if (controlStatus > 0xf || !(controlStatus & 0x8))
				std::cout << "\t!Unusual controlStatus " << (int)controlStatus << " - window open?>" << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case 0x17:
			std::cout << std::hex << "[" << pktId << "] client dropped held item on floor" << std::endl;
			if (dataLen != 2)
				dumpHex = true;
			break;

		case 0x18:
			std::cout << std::hex << "[" << pktId << "] client put item down in inventory" << std::endl;
			dumpHex = true;
			break;

		case CLIPK_PICKUP_ITEM:
		{
			unsigned short unk1 = getUshort(decrypted + 2);
			unsigned long itemID = getUlong(decrypted + 6);
			byte slot = decrypted[5];
			byte unk2 = decrypted[10]; //divisible by 4?
			std::cout << "Player clicked item 0x" << std::hex << itemID << " in slot " << slotToString(slot) << std::endl;
			std::cout << "Unknown Values 1: 0x" << unk1 << ", 0x2: " << (int)unk2 << std::endl;
			break;
		}

		case CLI_PLACE_ITEM:
		{
			unsigned long container = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long column = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long row = getUlong(decrypted + sIdx); sIdx += 4;
			byte unk2 = decrypted[sIdx++];

			std::cout << "player placed picked up item? Row: " << row << " Column: " << column
				<< " Container: " << slotToString(container) << " unk2: 0x" << (int)unk2 << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLI_REMOVE_FROM_SOCKET:
		{
			/*
			001d
			00000001
			00000054
			00000001
			00
			*/
			unsigned long container = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long sourceItemID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long sockID = getUlong(decrypted + sIdx); sIdx += 4;
			byte unk = decrypted[sIdx++];


			std::cout << std::hex << "Client removed gem from [" << slotToString(container) << " - ItemID 0x" << sourceItemID <<
				" - socket " << sockID << "] unk: 0x" << (int)unk << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLI_INSERT_INTO_SOCKET:
		{
			//001e
			//00000001
			//0000004c
			//00000000
			unsigned long container = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long targitemID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long sockID = getUlong(decrypted + sIdx); sIdx += 4;

			std::cout << std::hex << "Client inserted held gem into [" << slotToString(container) <<
				" - item 0x" << targitemID << " - socket " << sockID << "]" << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLIPK_LEVEL_SKILL_GEM:
		{
			unsigned long container = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long itemID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long slot = getUlong(decrypted + sIdx); sIdx += 4;
			std::cout << "Client clicked level skillgem on [ItemID 0x" << std::hex << itemID <<
				" - container " << slotToString(container) << " - slot " << slot << "]" << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLIPK_SKILLPOINT_CHANGE:
		{
			unsigned long passiveGraphIdx = getUlong(decrypted + sIdx); sIdx += 4;
			std::cout << std::hex << "Client invested in passive skill node 0x" << passiveGraphIdx << std::endl;
			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLI_CANCEL_BUF:
		{
			unsigned long bufid = getUlong(decrypted + sIdx); sIdx += 4;
			std::cout << std::hex << "[" << CLI_CANCEL_BUF << "] Client cancelled buf 0x" <<
				bufid << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case CLIPK_SET_HOTBARSKILL:
		{
			byte slot = decrypted[sIdx++];
			unsigned short skillID = getUshort(decrypted + sIdx); sIdx += 2;

			std::cout << std::hex << "Client put skill 0x" << skillID << " on skillbar slot " << (int)slot << std::endl;
			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case 0x32:
			std::cout << std::hex << "[" << pktId << "] client used flask/item with right mouse" << std::endl;
			dumpHex = true;
			break;

		case 0x33:
			std::cout << std::hex << "[" << pktId << "] client identified item?" << std::endl;
			dumpHex = true;
			break;

		case CLI_USE_BELT_SLOT:
		{
			//003700000004 = 5th slot
			unsigned long slot = getUlong(decrypted + sIdx); sIdx += 4;
			std::cout << std::hex << "Player activated potion slot 0x" << slot << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case CLI_USE_ITEM:
		{
			/*
			0038
			00 00 00 01
			00 00  04 02
			00 00 00 01
			00 00  04 03
			*/
			unsigned long unk1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long item1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long item2 = getUlong(decrypted + sIdx); sIdx += 4;

			std::cout << std::hex << "Player activated item 0x" << item1 << " on item 0x" << item2;
			std::cout << "i1unk: 0x" << unk1 << " i2unk: 0x" << unk2 << std::endl;
			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case 0x48:
			std::cout << std::hex << "[" << pktId << "] Client possibly clicked dialog option " << std::endl;
			dumpHex = true;
			break;

		case CLIPK_REQUEST_PUBLICPARTIES:
			std::cout << std::hex << "[" << pktId << "] client request social update" << std::endl;
			dumpHex = true;
			break;

		case CLIPK_SWAPPED_WEAPONS:
		{
			byte setIdx = decrypted[sIdx++];

			std::cout << std::hex << "Client swapped to weapon set " << (1 + (int)setIdx) << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case CLIPK_SKILLPANE_ACTION:
			std::cout << std::hex << "[" << pktId << "] Client skill pane ";
			if ((int)decrypted[2])
				std::cout << "opened";
			else
				std::cout << "closed";
			std::cout << std::endl;
			break;

		case CLIPK_MICROSTRANSACTIONPANE_ACTION:
			std::cout << std::hex << "[" << pktId << "] Client microtransactions pane opened";
			break;
			//case 0x98:
			//	std::cout << std::hex << "[" << pktId << "] client unsubscribe from chat" << std::endl;
			//	break;



		case 0xca:
		{
			unsigned int skillID = (decrypted[10] << 8) + decrypted[11];
			unsigned int xLoc = getUlong(decrypted + 2);
			unsigned int yLoc = getUlong(decrypted + 6);

			std::cout << std::hex << "[" << pktId << "] Player performed action " << std::hex << skillID << " [" << getSkillName(skillID) << "]"
				<< " at location [" << xLoc << "," << yLoc << "]" << std::endl;
			break;
		}

		case CLIPK_USED_SKILL:
		{
			if (dataLen != 13)
				std::cerr << "Warning, expected skill usage packed 0xd8 to be 13 bytes but it is " << std::dec << dataLen << std::endl;
			unsigned skillID = (decrypted[10] << 8) + decrypted[11];
			std::cout << "Client used skill: " << getSkillName(skillID) << std::endl;
			dumpHex = true;
			break;
		}
		case CLIPK_CLICK_OBJ:
			std::cout << std::hex << "[" << pktId << "]  Client clicked ground item" << std::endl;
			dumpHex = true;
			break;

		case CLIPK_MOUSE_HELD:
		{
			unsigned long coord1 = getUlong(decrypted + 2);
			unsigned long coord2 = getUlong(decrypted + 6);
			std::cout << std::hex << "[" << pktId << "]  Client mouse held on location (" << coord1 << "," << coord2 << ")" << std::endl;
			dumpHex = true;
			break;
		}

		case CLIPK_MOUSE_RELEASE:
		{
			std::cout << std::hex << "[" << pktId << "]  Client released mouse" << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		//case 0xce:
		//	std::cout << std::hex << "[" << pktId << "] Action button press"<<std::endl;
		//	break;

		case CLIPK_OPTOUT_TUTORIALS:
			if (dataLen != 3) {
				std::cerr << "Warning! Packet ID " << CLIPK_OPTOUT_TUTORIALS << " changed length, may no longer be tutorial cancel" << std::endl;
			}
			std::cout << std::hex << "[" << pktId << "] Client skipped tutorials" << std::endl;
			break;



		default:
			std::cout << "C->S UnkPkID: 0x" << std::hex << pktId
				<< " size: " << std::dec << dataLen << " bytes" << std::endl;
			//outfile << "Unhandled packet ID - client to gameserver: 0x" << std::hex << pktId
			//	<< " size: " << std::dec << dataLen << " bytes" << std::endl;
			dumpHex = true;
			break;
		}


		remainingBytes = 0;
	}



	if (dumpHex)
	{
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
			std::cout << std::hex << std::setw(2) << (int)item;
			//if (i && (i % 16 == 0)) std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//write packet only at end
	unsigned short firstid = getUshort(decrypted);
	/*
	outfile << "\nPacket from client to gameserver starting with ID 0x" << std::hex << firstid << std::endl;
	outfile << "Raw:" << std::endl;
	for (int i = 0; i < dataLen; i++)
	{
		char nextChar = decrypted[i];
		if (nextChar < 0x20 || nextChar > 0x7f)
			outfile << ".";
		else
			outfile << nextChar;

		if ((i + 1) % 48 == 0) outfile << std::endl;
	}
	outfile << "\nHex:\n";
	outfile << std::setfill('0');
	for (int i = 0; i < dataLen; ++i)
	{
		byte item = decrypted[i];
		if (item)
			outfile << std::hex << std::setw(2) << (int)item << " ";
		else
			outfile << "00 ";
		if ((i + 1) % 16 == 0) outfile << std::endl;
	}
	outfile << "\n\n";
	outfile << "\Packet from client end\n";
	outfile.flush();
	*/
	delete decrypted;
}


void packet_processor::handle_packet_from_gameserver(networkStreamID streamID, byte* data, unsigned int dataLen)
{
	std::cout << "halding packet from gameserver... " << std::endl;

	//first packet from gameserver starts 0005, followed by crypt which start 0012
	STREAMDATA *streamObj = &streamDatas.at(streamID);

	if (dataLen == 0) {

		printf("Skipping datalen 0 packet from gameserver...\n");
		return;
	}

	byte *decrypted = new byte[dataLen];
	memset(decrypted, 0, dataLen);

	if (streamObj->packetCount == 1)
	{
		if (data[0] != 0 || data[1] != 5) {
			std::cout << "assert 1" << std::endl;
		}
		assert(data[0] == 0 && data[1] == 5);


			streamObj->fromGameSalsa.SetKeyWithIV(
				(byte *)streamObj->workingRecvKey->salsakey, 32,
				(byte *)streamObj->workingRecvKey->IV);
			decrypted[0] = data[0];
			decrypted[1] = data[1];
			streamObj->fromGameSalsa.ProcessData(decrypted + 2, data + 2, dataLen - 2);
			if (decrypted[2] != 0 || decrypted[3] != 0x12) {
				std::cout << "assert 2" << std::endl;
			}
			assert(decrypted[2] == 0 && decrypted[3] == 0x12);

	}
	else
	{
		streamObj->fromGameSalsa.ProcessData(decrypted, data, dataLen);
	}


	UI_RAWHEX_PKT *msg = new UI_RAWHEX_PKT(
		streamObj->workingRecvKey->sourceProcess, eGame, false);
	msg->setData(decrypted, dataLen);
	uiMsgQueue->addItem(msg);

	bool dumpHex = false;
	int remainingBytes = dataLen;
	bool deserialiseMore = false;
	int index = 0;
	short lastPktID = -1;

	while (true)
	{

		if (remainingBytes == 0) break;


		if (remainingBytes < 2) {
			std::cerr << "ERROR! Bad remaining length " << std::dec << remainingBytes << std::endl;
			std::cerr << "Probable bad handling of previous packet " << lastPktID << std::endl;
			dumpHex = true;
			break;
		}

		int sIdx = index;
		unsigned short pktId = getUshort(decrypted + sIdx); sIdx += 2;
		lastPktID = pktId;

		sanityCheckPacketID(pktId);

		switch (pktId)
		{
		case 0:
		{
			//handling of items in incoming chat messages needs implementing
			if (lastPktID != SRVPK_CHAT_INCOMING_MESSAGE)
			{
				std::cout << "Bad packet ID 0 <gameserver to client>: 0x" << std::hex << pktId
					<< " size: " << std::dec << dataLen << " bytes";
				dumpHex = true;
			}
			break;
		}
		case SRV_PKT_ENCAPSULATED:
		{
			unsigned short pktID2 = getUshort(decrypted + sIdx); sIdx += 2;
			std::cout << "Processing encapsulated packet subpacket ID 0x" << pktID2 << std::endl;

			if (pktID2 == SRV_MONSTERS_PRELOAD)
			{
				unsigned short varietyCount = getUshort(decrypted + sIdx); sIdx += 2;
				std::cout << "\tprocessing first subpacket 0x12, Inner len is liekly 3x " <<
					std::dec << varietyCount << std::endl;

				std::vector<std::pair<unsigned short, byte>> varietyList;
				for (int i = 0; i < varietyCount; i++)
				{
					unsigned short monsterVariety = ntohs(getUshort(decrypted + sIdx)); sIdx += 2;
					varietyList.push_back(std::make_pair(monsterVariety, 0));
				}
				//this flag tends to be 1 if you would expect the monster in the zone
				//or 0 if it makes no sense at all...
				for (int i = 0; i < varietyCount; i++)
				{
					varietyList.at(i).second = decrypted[sIdx++];
				}

				for (int i = 0; i < varietyCount; i++)
				{
					unsigned short varietyIndex = varietyList.at(i).first;
					if (varietyIndex < monsterVarieties.size())
						std::cout << "\t Monster: " << monsterVarieties.at(varietyIndex);
					else
						std::cout << std::hex << "Unknown MonsterVariety Idx: 0x" << varietyIndex;
					std::cout << " {" << (int)varietyList.at(i).second << "}" << std::endl;
				}
				std::cout << std::endl;

				remainingBytes -= (sIdx - index);
				index = sIdx;
				continue;
			}
			else
			{
				std::cout << "\t Unknown subpacket" << std::endl;
			}

			break;

		}
		case SRVPK_PING_RESPONSE:
		{
			sIdx += 4;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
			//std::cout << std::hex << "[" << pktId << "] d:" << std::endl;
			//dumpHex = true;
			//ping response?
		}

		case SRVPK_CHAT_INCOMING_MESSAGE: //chat message
		{
			unsigned short nameLen = getUshort(decrypted + sIdx); sIdx += 2;
			std::string namemb(decrypted + sIdx, decrypted + sIdx + nameLen * 2); sIdx += nameLen * 2;
			std::wstring name = mb_to_utf8(namemb);
			unsigned short chatLen = getUshort(decrypted + sIdx); sIdx += 2;
			std::string chatmb(decrypted + sIdx, decrypted + sIdx + chatLen * 2); sIdx += chatLen * 2;
			std::wstring chat = mb_to_utf8(chatmb);
			unsigned short tagLen = getUshort(decrypted + sIdx); sIdx += 2;
			std::string tagmb(decrypted + sIdx, decrypted + sIdx + tagLen * 2); sIdx += tagLen * 2;
			std::wstring tag = mb_to_utf8(tagmb);

			byte isDev = decrypted[sIdx++];
			byte challengesComplete = decrypted[sIdx++];
			unsigned short unk = getUshort(decrypted + sIdx); sIdx += 2;

			/*
			if (isDev)
			std::wcout << "!DEV!";

			std::wcout << "<Chat>";
			std::wcout << name;
			if (tagLen)
			std::wcout << "[" << tag << "]";
			if (challengesComplete)
			std::wcout << std::dec << "{" << (challengesComplete) << "}";
			std::wcout << ": " << chat << std::endl;
			*/

			break; //because chats with items breaks it

			remainingBytes -= (sIdx - index);
			index = sIdx;

			continue;
		}

		case SRVPK_SERVER_MESSAGE:
		{
			/*
			33 remaining:

			00 0b
			00 99
			ff ff
			02 00 00 00
			00 01 00 00
			00 00 00 21  //33


			"downtime will be approx 20 mins
			00 0b
			01 16
			ff ff
			01 00 00 00
			00 00 02 00
			06
			33 00 2e 00
			32 00 2e 00
			31 00 62 00

			00 2a //len 42
			44 00 6f 00
			77 00 6e 00 74 00 69 00 6d 00 65 00 20 00 77 00
			69 00 6c 00 6c 00 20 00 62 00 65 00 20 00 61 00
			70 00 70 00 72 00 6f 00 78 00 69 00 6d 00 61 00
			74 00 65 00 6c 00 79 00 20 00 32 00 30 00 20 00
			6d 00 69 00 6e 00 75 00 74 00 65 00 73 00 2e 00
			*/
			std::cout << std::hex << "[" << pktId << "]" << "Server sent remaining response for area 0x";
			unsigned int remaining = (unsigned long)htonl(*((unsigned long *)(decrypted + 8)));
			std::cout << (unsigned long)htonl(*((DWORD *)(decrypted + 3))) << " : " << std::dec << remaining << std::hex << std::endl;
			dumpHex = true;
			break;
		}


		case SRV_AREA_INFO:
		{
			//code of area to load <"unknown6" in worldareas.dat> eg: 0x64, 0x83, is toxic conduit>
			unsigned long areaCode = getUlong(decrypted + sIdx); sIdx += 4;
			std::string areaname;
			lookup_areaCode(areaCode, areaname);

			unsigned short difficultyLen = getUshort(decrypted + sIdx); sIdx += 2;
			std::wstring difficultyName(reinterpret_cast<wchar_t*>(decrypted + sIdx), difficultyLen);
			sIdx += (difficultyLen * sizeof(wchar_t));

			unsigned long areaSeedVariantID = getUlong(decrypted + sIdx); sIdx += 4;
			byte unkb1 = decrypted[sIdx++];
			byte unkb2 = decrypted[sIdx++];
			byte unkb3 = decrypted[sIdx++];
			unsigned short unks4 = getUshort(decrypted + sIdx); sIdx += 2;
			byte unkb4 = decrypted[sIdx++];

			unsigned short hashCount = getUshort(decrypted + sIdx); sIdx += 2;
			std::vector<unsigned long> hashlist;
			hashlist.reserve(hashCount);
			for (int i = 0; i < hashCount; i++)
			{
				unsigned long preloadhash = getUlong(decrypted + sIdx); sIdx += 4;
				hashlist.push_back(preloadhash);
			}

			unsigned short unks5 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short unks6 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short unks7 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short unks8 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short unks9 = getUshort(decrypted + sIdx); sIdx += 2;

			std::cout << "Pkt 0x" << std::hex << SRV_AREA_INFO <<
				" from gameserver, entered area: " << areaname << " - ";
			std::wcout << difficultyName << " (seed " << areaSeedVariantID << ")" << std::endl;

			for (auto monstersIt = hashlist.begin(); monstersIt != hashlist.end(); monstersIt++)
			{
				unsigned long hash = *monstersIt;
				std::string hashResult;
				std::string hashCategory;
				lookup_hash(hash, hashResult, hashCategory);
				std::cout << "\tPreload hash: [" << hashCategory << "]: " << hashResult << std::endl;
			}


			std::cout << "Unk1: 0x" << (int)unkb1 << std::endl;
			std::cout << "Unk2: 0x" << (int)unkb2 << std::endl;
			std::cout << "Unk3: 0x" << (int)unkb3 << std::endl;
			std::cout << "Unks4: 0x" << unks4 << std::endl;
			std::cout << "Unkb4: 0x" << (int)unkb4 << std::endl;
			std::cout << "Unk5: 0x" << unks5 << std::endl;
			std::cout << "Unk6: 0x" << unks6 << std::endl;
			std::cout << "Unk7: 0x" << unks7 << std::endl;
			std::cout << "Unk8: 0x" << unks8 << std::endl;
			std::cout << "Unk9: 0x" << unks9 << std::endl;


			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}

		case SRVPK_PLAYER_ITEMS_DATA:
		{
			std::cout << std::hex << "[" << pktId << "] Player Items Listing" <<
				std::hex << getUlong(decrypted) << std::endl;
			//handle_server_items_packet(decrypted, dataLen);
			dumpHex = true;
			break;
		}

		case SRVPK_INSTANCE_SERVER_DATA:
		{
			/*
			unsigned long unk1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long areacode = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk3 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk4 = getUlong(decrypted + sIdx); sIdx += 4; //starting coord?
			unsigned short port = getUshort(decrypted + sIdx); sIdx += 2;

			std::stringstream serverIP;
			serverIP << (int)decrypted[sIdx++] << ".";
			serverIP << (int)decrypted[sIdx++] << ".";
			serverIP << (int)decrypted[sIdx++] << ".";
			serverIP << (int)decrypted[sIdx++];

			std::cout << std::hex << "[" << pktId << "] New game server data. AREA TRANSITION" << std::endl;
			std::cout << "\tGameserver: " << serverIP.str() << ":" << std::dec << port << std::hex << std::endl;

			sIdx += 20; //??

			KEYDATA key1A, key1B;
			memcpy(key1A.salsakey, decrypted + sIdx, 32);
			memcpy(key1B->salsakey, decrypted + sIdx, 32);

			if (key1A.salsakey[0] == 0 && key1A.salsakey[3] == 0 && key1A.salsakey[7])
			{
				std::cout << "Discarding bad key in area transition" << std::endl;
				break; //probably an old zero-ed out key
			}



			memcpy(nextGameSalsaKey, key1A.salsakey, 32);	sIdx += 32;
			memcpy(key1A.IV, decrypted + sIdx, 8); sIdx += 8;
			sIdx += 8;
			memcpy(key1B->IV, decrypted + sIdx, 8); sIdx += 8;

			memcpy(nextGameIVClientToServer, key1A.IV, 8);
			memcpy(nextGameIVServerToClient, key1B->IV, 8);

			key1A.foundAddress = key1B->foundAddress = (void *)1;

			WaitForSingleObject(this->keyVecMutex, INFINITE);
			keys.emplace(keys.end(), key1A);
			keys.emplace(keys.end(), key1B);
			ReleaseMutex(keyVecMutex);

			areaTransition = true;
			previousGameStreamID = streamID;
			*/
			std::cout << "todo me" << std::endl;
			break;
		}

		//case 0x1d:
		//	std::cout << std::hex << "[" << pktId << "] level up gem confirm" << std::endl;
		//	break;

		case SRV_SKILL_SLOTS_LIST:
		{
			std::cout << std::hex << "Skills on hotbar now:" << std::endl;
			for (int i = 0; i < 8; i++)
			{
				std::cout << "(" << i << ", 0x" << getUshort(decrypted + sIdx) << ") ";
				sIdx += 2;
				if (sIdx >= dataLen) break;
			}
			std::cout << std::endl;
			break;
		}
		case SRVPK_STASH_INFO:
			std::cout << std::hex << "[" << pktId << "] server sent stash data?" << std::endl;
			dumpHex = true;
			break;

		case SRVPK_RESPOND_PUBLICPARTIES:
			std::cout << std::hex << "[" << pktId << "] social pane info response" << std::endl;
			break;

		case SRV_CREATE_ITEM:
		{
			/*
			used identify scroll on blue leather cap
			0038
			00000001
			00000015
			00000001
			00000016

			leads to this-->
			'thorny leather cap of plunder'
			7% inc rarity
			reflect 3 phys damage

			006d
			00000000
			01
			0000001a
			00000002
			00000016	<- itemid 1
			00000015	<- itemid 2
			00000002
			00000018
			0601001f
			1d28cdfc
			00701101
			00000302
			00000025
			026a3d03  <- physdam?
			0063bf07  <- rarity?
			00000102
			00010100
			00001a0b
			04000caf
			0b885000
			23080000
			00080000

			preumably destroyed scroll is in that mess too
			*/
			/*
			armscrap x1c on ironhat x12 -> ironhat 20% qual
			006d
			00000000
			01
			00000023
			00000002
			00000020
			0000001e
			00000001
			00000022
			03020019
			8b9d7cd9
			00b29401
			00000100
			00000001
			14	<- 20% quality
			000203
			00020001
			0200

			006d
			00
			00000001
			0000005e
			00000000
			00000001
			0000005e
			0503
			001a
			55bca13a00d47b0100000100000000010000020300030002010100006d000000000d0000006d000000010000006c0000000000
			*/
			//id1 = in mouse
			byte unk0 = decrypted[sIdx++]; sIdx += 1;
			DWORD unk1 = getUlong(decrypted + sIdx); sIdx += 4;
			DWORD newID = getUlong(decrypted + sIdx); sIdx += 4;
			DWORD action1 = getUlong(decrypted + sIdx); sIdx += 4;
			DWORD prevID = getUlong(decrypted + sIdx); sIdx += 4;
			byte col = decrypted[sIdx++];
			byte row = decrypted[sIdx++];
			short unk2 = getUshort(decrypted + sIdx); sIdx += 2;
			DWORD unk3 = getUlong(decrypted + sIdx); sIdx += 4;
			byte unk4 = decrypted[sIdx++];

			std::string action;
			switch (action1) {
			case 0x0:
				action = "Bag";
				break;
			case 0x1:
				action = "Hand";
				break;
			case 0x2:
				action = "0x" + action1;
				break;
			}

			std::cout << std::hex << "[" << pktId << "] Item update ";
			std::cout << "unk0: 0x" << (int)unk0 << "unk1: 0x" << (int)unk1 << " new ID: 0x" << newID << " In: " << action;
			if (action1 == 0)
				std::cout << " [Row " << (int)row << ", Col" << (int)col << "]";
			std::cout << " PrevID: 0x" << prevID << " unk2: 0x" << unk2
				<< " unk3: 0x" << unk3 << " unk4: " << (int)unk4 << std::endl;
			dumpHex = true;
			break;
		}

		case SRV_VENDOR_INVENTORY:
		{
			short unk1 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned int ID1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned int ID2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned int numItems = getUlong(decrypted + sIdx); sIdx += 4;

			std::cout << std::hex << "Vendor inventory listing (" << std::dec << numItems << " items )" <<
				std::hex << " ID1 0x" << ID1 << " ID2: 0x" << ID2 << std::endl;
			dumpHex = true;
			break;
		}
		case SRVPK_SKILLPANE_DATA:
			std::cout << std::hex << "[" << pktId << "] Skill pane info" << std::endl;
			break;
			/*
			case 0xd8:
			{
			std::cout << std::hex << "[" << pktId << "] Object vanished/picked up?: ";
			dumpHex = true;
			break;
			}*/
		case SRVPK_MICROSTRANSACTIONSPANE_RESP: //7 bytes of other data, expect reflects changes?
			std::cout << std::hex << "[" << pktId << "] Server acknowledge microtranspane opened";
			dumpHex = true;
			break;
		case SRV_DISPLAY_BUILTIN_MSG:
		{
			std::cout << "Server requested client display a builtin message" << std::endl;
			dumpHex = true;
			break;
		}
		case 0xd9:
		{

			DWORD objID = getUlong(decrypted);
			DWORD objID2 = getUlong(decrypted + 4);

			DWORD unk0 = getUlong(decrypted + 8) >> 2;

			DWORD pos1x = getUshort(decrypted + 11) - 0x8000;
			DWORD pos1y = getUshort(decrypted + 13) - 0x8000;

			DWORD pos2x = getUshort(decrypted + 15) - 0x8000;
			DWORD pos2y = getUshort(decrypted + 17) - 0x8000;

			DWORD skillSlot = getUshort(decrypted + 19);

			DWORD counter = getUshort(decrypted + 21);

			std::cout << std::hex << "[" << pktId <<
				"]  Targeted skill used by object " << objID << " (" << pos1x << " , " << pos1y << ")->" <<
				" on obj2 " << objID2 << " (" << pos2x << " , " << pos2y << ")" <<
				"unk1: " << unk0 << ", skillSlot:" << skillSlot << " unk2:" << (int)decrypted[23] << std::endl;

			dumpHex = true;
			break;
		}
		/*
		case 0xdd: //??
		{
		decrypted++;

		std::cout << std::endl;
		unsigned long target = getUlong(decrypted);
		unsigned long source = getUlong(decrypted + 4);
		unsigned int unknown2 = getUlong(decrypted + 8);
		unsigned int unknown3 = getUshort(decrypted + 10);
		unsigned int unknown4 = getUshort(decrypted + 14);
		unsigned int unknown5 = getUshort(decrypted + 18);
		unsigned int damage = getUshort(decrypted + 22);
		unsigned int unknown7 = getUshort(decrypted + 24);

		if (decrypted[4] == 0)
		{
		std::cout << std::hex << "[" << pktId
		<< "] [fixme?]Obj " << target << "(player?) took " << damage << " damage from obj (" << source <<
		") UNKVALS: (" << "," << unknown2 << "," <<
		unknown3 << "," << unknown4 << "," << unknown5 << "," <<
		unknown7 << std::endl;

		deserialiseMore = true;
		dumpHex = true;
		decrypted += 30;
		}
		else
		{
		std::cout << std::hex << "[" << pktId
		<< "] - something strange happened! - Obj " << target << "," << damage << " ," << source <<
		") UNKVALS: (" << "," << unknown2 << "," <<
		unknown3 << "," << unknown4 << "," << unknown5 << "," <<
		unknown7 << std::endl;
		}
		break;
		}
		*/
		/*
		case 0xde: //melee attacked
		{
		decrypted++;
		/*
		std::cout << "printing dd hex:" << std::endl;
		for (int i = 0; i < dataLen - 1; ++i)
		{
		byte item = decrypted[i];
		std::cout << std::hex << std::setw(2) << (int)item;
		}*/
		/*
		std::cout << std::endl;
		unsigned long objid1 = getUlong(decrypted);
		unsigned long objid2 = getUlong(decrypted + 4);
		unsigned int unknown2 = getUshort(decrypted + 8);
		unsigned int counter = getUshort(decrypted + 10);
		unsigned long zeros = getUlong(decrypted + 12);
		unsigned long unknown = getUlong(decrypted + 12);

		std::cout << std::hex << "[" << pktId
		<< "] Damage1 taken from objs (" << objid1 << "," << objid2
		<< ") UNKVALS: (" << unknown << "," << unknown2 << ") ctr?:" << counter
		<< " 0?:" << zeros << std::endl;

		deserialiseMore = true;
		dumpHex = true;
		decrypted += 20;
		break;
		}
		case 0xdf:
		{
		decrypted++;
		unsigned long target = getUlong(decrypted);
		unsigned long source = getUlong(decrypted + 4);
		unsigned int flag1 = decrypted[8];
		unsigned int direction = decrypted[9];
		unsigned int value = getUlong(decrypted + 10);
		unsigned long zeros = getUlong(decrypted + 14);
		unsigned int attribute = getUshort(decrypted + 18);
		unsigned long next = decrypted[21];

		if (direction == 0x01)
		{
		std::cout << std::hex << "[" << pktId
		<< "] Player (" << target << ") hit by obj: " << source << " flag1: " << flag1;
		if (attribute == 0)
		std::cout << " Health now: " << std::dec << value;
		else if (attribute == 0x200)
		std::cout << " Shield now: " << std::dec << value;
		else
		std::cout << " UNKNOWNATTs (" << attribute << ") now: " << std::dec << value;

		std::cout << std::hex << " 0?:" << zeros << std::endl;
		}
		else if (direction == 0x02) {
		std::cout << std::hex << "[" << pktId
		<< "] Damage from " << source << " reflected to obj: " << target << " flag1: " << flag1;
		if (attribute == 0)
		std::cout << " It's Health now: " << std::dec << value;
		else if (attribute == 0x200)
		std::cout << " It's Shield now: " << std::dec << value;
		else
		std::cout << " UNKNOWNATTs (" << attribute << ") now: " << std::dec << value;

		std::cout << std::hex << ") 0?:" << zeros << std::endl;
		}
		else {
		std::cout << std::hex << "[" << pktId
		<< "] Unknown direction health/shield update. source: " << source << " target:" << target << " flag1: " << flag1;
		if (attribute == 0)
		std::cout << " Health: " << std::dec << value;
		else if (attribute == 0x200)
		std::cout << " Shield: " << std::dec << value;
		else
		std::cout << " UNKNOWNATT (" << attribute << ") now: " << std::dec << value;

		std::cout << std::hex << ", direction: " << direction << ") 0?:" << zeros << std::endl;
		}

		if (next != 0xf9)
		{
		decrypted += 21;
		deserialiseMore = true;
		}
		break;
		}
		*/
		case 0xe0:
			std::cout << std::hex << "[" << pktId << "] Server player info change update" << std::endl;
			dumpHex = true;
			break;

		case 0xe2:
			std::cout << std::hex << "[" << pktId << "] Possible aura effects!" << std::endl;
			dumpHex = true;
			break;

		case 0xe9:
			std::cout << std::hex << "[" << pktId << "] Picked item up?" << std::endl;
			dumpHex = true;
			break;

		case SRVPK_MOBILE_USED_SKILL:
		{
			//noisy
			break;

			/*
			doesnt always follow pattern

			00ea
			0000011b
			00000000
			000088
			000000eb
			8311
			822f
			8320
			8223
			026603050132
			*/

			unsigned int userID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned int ID2 = getUlong(decrypted + sIdx); sIdx += 4;
			byte controlstatus = decrypted[sIdx + 2]; sIdx += 3;
			unsigned short startCoord1 = getUshort(decrypted + sIdx) - 0x8000; sIdx += 2;
			unsigned short startCoord2 = getUshort(decrypted + sIdx) - 0x8000; sIdx += 2;
			unsigned short endCoord1 = getUshort(decrypted + sIdx) - 0x8000; sIdx += 2;
			unsigned short endCoord2 = getUshort(decrypted + sIdx) - 0x8000; sIdx += 2;
			unsigned short skillID = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short packCt = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned short unk1 = getUshort(decrypted + sIdx); sIdx += 2;
			std::cout << std::hex << "[" << pktId << "] Mobile ID 0x" << userID
				<< " used skill 0x" << skillID;

			if (ID2 != 0)
				std::cout << " on targID: " << std::hex << ID2;

			std::cout << "@ Loc(" << startCoord1 << "," << startCoord2 <<
				")->(" << endCoord1 << "," << endCoord2 << ")" << " unk1: 0x" << unk1 << std::endl;

			//remainingBytes -= (sIdx - index);
			//index = sIdx;

			break;
		}

		case 0xee:
			std::cout << std::hex << "[" << pktId << "] Effects or object related update ee" << std::endl;
			dumpHex = true;
			break;

		case SRV_MOBILE_UPDATE_HMS:
		{
			unsigned long mobileID = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unkl1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned short unks2 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned long val = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unks3 = getUlong(decrypted + sIdx); sIdx += 4;
			byte stat = decrypted[sIdx++];
			byte unkb4 = decrypted[sIdx++];

			std::cout << std::hex << "[Pkt 0x" << SRV_MOBILE_UPDATE_HMS <<
				"] Mobile 0x" << mobileID << " had stat ";
			switch (stat) {
			case 0: std::cout << "Life";
				break;
			case 1: std::cout << "Mana";
				break;
			case 2: std::cout << "Shield";
				break;
			default:
				std::cout << "UnkStat<0x" << (int)stat << ">";
			}
			std::cout << " updated to value " << std::dec << val << std::endl;

			std::cout << std::hex << "Unk1: 0x" << unkl1 << ", unk2: 0x" << unks2
				<< ", unk3: 0x" << unks3 << ", unk4: 0x" << (int)unkb4 << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;

			dumpHex = true;
			break;
		}

		case SRV_STAT_CHANGED:
			/*

			see 0x135 writeup in server for how stats work


			[f1] Server sent equipped item/armor/weapon update 1/f1
			//grace period expiry
			00f10000012100000121300003808d00836e009958000132

			//4% atkspd, 10% proj dam passive
			[21] Client skill point change
			0021000001d1
			[f1] Server sent equipped item/armor/weapon update 1/f1

			00f1
			00000121
			00000000
			00000347
			04
			812504 - mainhand attack speed 4%
			812604 - offhand attack speed 4%

			00f1
			00000121
			00000000
			00000181
			f41a0020
			0002
			d101ebaf
			00000000
			0000040200

			00f1
			00000121
			00000000
			00000575
			06788048
			811b 8059 - evasion rating 89 <top 0x80 bit set seems to mean another byte is coming>
			829f 07  - 7% magic find
			82ad 24  - 36 evade chance

			*/
			std::cout << std::hex << "[" << pktId << "] Server sent stat update" << std::endl;
			dumpHex = true;
			break;

		case 0xf2:
			std::cout << std::hex << "[" << pktId << "] Server sent equipped item/armor/weapon update 1/f2" << std::endl;
			dumpHex = true;
			break;

		case SRV_CRITTER_MOVEMENT:
		{
			//message volume inversely proportional to importance, don't want it printed
			/*
			00f3
			000001f0
			000001f0
			7000
			000001d3
			000001a4
			7fffffff
			7f7fffff
			*/
			unsigned long mobileID1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long mobileID2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned short unk1 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned long coord1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long coord2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk3 = getUlong(decrypted + sIdx); sIdx += 4;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;
		}
		case SRV_START_EFFECT:
		{
			/*
			00fb
			00000107 - targid
			00000107 - targid?
			30		 - buf ended operation
			000002	 - buf id 02
			*/
			std::cout << std::hex << "[" << pktId << "] Char status related update" << std::endl;
			dumpHex = true;
			break;
		}
		case SRV_END_EFFECT:
		{
			/*
			00fb
			00000107 - targid
			00000107 - targid?
			30		 - buf ended operation
			000002	 - buf id 02
			*/
			unsigned long targID1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long targID2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long unk3 = getUlong(decrypted + sIdx); sIdx += 4;

			std::cout << std::hex << "Status Effect ended. <Targ1: 0x" << targID1
				<< ", Targ2: 0x" << targID2 << "> - 0x" << unk3 << std::endl;

			remainingBytes -= (sIdx - index);
			index = sIdx;
			continue;

			//dumpHex = true;
			//break;
		}

		/*
		case 0xfd:
		std::cout << std::hex << "[" << pktId << "] Server new object updates" << std::endl;
		dumpHex = true;
		break;


		case 0xfe:
		std::cout << std::hex << "[" << pktId << "] Server weapon info" << std::endl;
		dumpHex = true;
		break;

		case 0xe7:
		std::cout << std::hex << "[" << pktId << "] Flask effect started" << std::endl;
		dumpHex = true;
		break;

		case 0xe8:
		std::cout << std::hex << "[" << pktId << "] Flask effect ended" << std::endl;
		dumpHex = true;
		break;
		*/
		
			/*
			case SRVPK_ITEM_MOVED:
			{
			dumpHex = true;

			unsigned long unk1 = getUshort(decrypted + 2);
			byte slot = decrypted[8];
			unsigned long id1 = getUlong(decrypted + 9);
			unsigned long unk2 = getUlong(decrypted + 13);
			unsigned long unk3 = getUlong(decrypted + 17);
			unsigned long id2 = getUlong(decrypted + 21);
			byte coord1 = decrypted[25];
			byte coord3 = decrypted[26];
			byte coord2 = decrypted[27];
			unsigned long itemcode1 = getUlong(decrypted + 28);
			unsigned long itemcode2 = getUlong(decrypted + 32);

			std::cout << "Item 0x" << std::hex << itemcode1 << itemcode2 << " moved in ";
			bool known = false;
			switch (slot) {
			case 0x01:
			std::cout << "BAG";
			known = true;
			break;
			case 0x0c:
			std::cout << "BELT";
			known = true;
			break;
			default:
			std::cout << "Unknown Area " << slot;
			break;
			}
			std::cout << " coord " << (int)coord1 << ", " << (int)coord2 << ", " << (int)coord3 << std::endl;
			std::cout << "id 1,2: " << id1 << "," << id2 << " unk 1,2,3: " << unk1 << ", " << unk2 << ", " << unk3 << std::endl;

			break;
			}
			*/
		case SRV_ADD_OBJECT:
		{
			//see server implementatio and 0xf1 for how the stats work

			unsigned long id = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long id2 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned short unk1 = getUshort(decrypted + sIdx); sIdx += 2;
			unsigned long objHash = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned short followingLen = getUshort(decrypted + sIdx); sIdx += 2;

			if (followingLen > 40)
				std::cout << "{INTERESTING SPAWN}\t" << std::endl;

			std::string category;
			std::string res;
			lookup_hash(objHash, res, category);
			printf("-----Spawn %s (%s)----\n", res.c_str(), category.c_str());

			std::cout << "Object type " << res <<
				" (" << category << ") spawned ";
			//outfile << "Object type " << res <<	" (" << category << ") spawned ";

			int bytesStillRemaining = (dataLen - sIdx);
			if (bytesStillRemaining < 8)
			{
				std::cout << "(no coord). Unk1: 0x" << unk1 << std::endl;
				//outfile << "(no coord). Unk1: 0x" << unk1 << std::endl;
				break;
			}

			unsigned long coordBig1 = getUlong(decrypted + sIdx); sIdx += 4;
			unsigned long coordBig2 = getUlong(decrypted + sIdx); sIdx += 4;

			unsigned long adjCoord1 = ntohl(coordBig1) >> 8;
			unsigned long adjCoord2 = ntohl(coordBig2) >> 8;
			if (bytesStillRemaining < 13)
			{
				std::cout << "at (" << adjCoord1 << "," << adjCoord2 << ") Unk1: 0x" << unk1 << std::endl;
				//outfile << "at (" << adjCoord1 << "," << adjCoord2 << ") Unk1: 0x" << unk1 << std::endl;
				break;
			}

			std::cout << "at (" << adjCoord1 << "," << adjCoord2 << ") Unk1: 0x" << unk1 << std::endl;
			//outfile << "at (" << adjCoord1 << "," << adjCoord2 << ") Unk1: 0x" << unk1 << std::endl;

			//byte unk3 = decrypted[sIdx++];
			//unsigned long unk3 = getUlong(decrypted + sIdx); sIdx += 4;
			dumpHex = true;
			break;
		}

		case SRV_UNK_13A:
		{
			std::cout << "What am I?? pkt ID 0x13a" << std::endl;
			dumpHex = true;
			break;
		}


		default:
			std::cout << "S->C UnkPkID: 0x" << std::hex << pktId
				<< " size: " << std::dec << dataLen << " bytes" << std::endl;
			//outfile << "Unhandled packet ID - gameserver to client: 0x" << std::hex << pktId
			//	<< " size: " << std::dec << dataLen << " bytes" << std::endl;
			dumpHex = true;
			break;
		}

		//should continue if we are confident handling packet
		//break will set remaining to 0 and leave loop
		remainingBytes = 0;
	}



	if (dumpHex)
	{

		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
			std::cout << std::setw(2) << std::hex << (int)item;
			//if (i && (i % 16 == 0)) std::cout << std::endl;
		}
		std::cout << std::flush << std::endl;;
	}

	if (dataLen != 2) //spammy keepalives with predictive mode
	{
		//write packet only at end
		/*
		unsigned short firstid = getUshort(decrypted);
		outfile << "\nPacket from gameserver starting with ID 0x" << std::hex << firstid << std::endl;
		outfile << "Raw:" << std::endl;
		for (int i = 0; i < dataLen; i++)
		{
			char nextChar = decrypted[i];
			if (nextChar < 0x20 || nextChar > 0x7f)
				outfile << ".";
			else
				outfile << nextChar;
			if ((i + 1) % 48 == 0)
				outfile << std::endl;
		}
		outfile << "\nHex:\n";
		outfile << std::setfill('0');
		for (int i = 0; i < dataLen; ++i)
		{
			byte item = decrypted[i];
			if (item)
				outfile << std::setw(2) << (int)item << " ";
			else
				outfile << "00 ";
			if ((i + 1) % 16 == 0) outfile << std::endl;
		}
		outfile << "\n\n";
		outfile << "\nPacket from gameserver end\n";
		outfile.flush();
		*/
	}

	delete decrypted;
}

bool packet_processor::process_packet_loop()
{
	/*
	std::cout << "writing to log " << "N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt" << std::endl;
	outfile = std::ofstream("N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt",
		std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	if (!outfile.is_open())
		outfile = std::ofstream("latestconndump.txt",
			std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	outfile << std::endl << std::endl << "New sniffing session" << std::endl << std::endl;
	*/
	std::vector<byte> pkt;
	std::queue< std::vector<byte>> pktQueue;
	while (true)
	{
		bool updated = false;

		if (checkPipe(patchpipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_patch_data(pkt);
				pktQueue.pop();
			}
			updated = true;
		}

		if (checkPipe(loginpipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_login_data(pkt);
				pktQueue.pop();
			}
			updated = true;
		}

		if (checkPipe(gamepipe, &pktQueue))
		{
			while (!pktQueue.empty())
			{
				pkt = pktQueue.front();
				handle_game_data(pkt);
				pktQueue.pop();
			}
			updated = true;
		}

		if (!updated)
			Sleep(30);
	}
	return true;
}

void genericHashesLoad(rapidjson::Value& itemsDoc, std::map <unsigned long, std::string>& targMap)
{
	rapidjson::Value::ConstMemberIterator recordsIt = itemsDoc.MemberBegin();
	for (; recordsIt != itemsDoc.MemberEnd(); recordsIt++)
	{
		std::string hashString = recordsIt->name.GetString();
		unsigned long hash = std::stoul(hashString);
		targMap[hash] = recordsIt->value.GetString();
	}
}

void packet_processor::fillObjCodeMap()
{

	char buffer[65536];

	FILE* pFile;
	std::string filename = "ggpk_exports.json";
	fopen_s(&pFile, filename.c_str(), "rb");
	if (!pFile)
	{
		std::cerr << "Warning: Could not open " << filename << " for reading. Abandoning Load." << std::endl;
		return;
	}

	//load it all from json
	rapidjson::Document jsondoc;
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	jsondoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	fclose(pFile);

	if (!jsondoc.IsObject())
	{
		std::cerr << "Warning: Corrupt ggpk_exports file. Abandoning Load." << std::endl;
		if (jsondoc.HasParseError())
		{
			std::cerr << "\t rapidjson parse error " << jsondoc.GetParseError()
				<< " at offset " << jsondoc.GetErrorOffset() << std::endl;
		}
		return;
	}

	rapidjson::Value& monsterVarietyIndexDoc = jsondoc.FindMember("MonsterVarietiesIndex")->value;
	rapidjson::Value::ConstValueIterator recordsIt = monsterVarietyIndexDoc.Begin();
	for (; recordsIt != monsterVarietyIndexDoc.End(); recordsIt++)
	{
		monsterVarieties.push_back(recordsIt->GetString());
	}


	rapidjson::Value& monsterVarietyDoc = jsondoc.FindMember("MonsterVarietiesHashes")->value;
	genericHashesLoad(monsterVarietyDoc, monsterHashes);

	rapidjson::Value& areaCodesDoc = jsondoc.FindMember("AreaCodes")->value;
	genericHashesLoad(areaCodesDoc, areaCodes);

	rapidjson::Value& objectRegisterDoc = jsondoc.FindMember("ObjRegisterHashes")->value;
	genericHashesLoad(objectRegisterDoc, gameObjHashes);

	rapidjson::Value& chestsDoc = jsondoc.FindMember("ChestHashes")->value;
	genericHashesLoad(chestsDoc, chestHashes);

	rapidjson::Value& petsDoc = jsondoc.FindMember("PetHashes")->value;
	genericHashesLoad(petsDoc, petHashes);

	rapidjson::Value& charactersDoc = jsondoc.FindMember("CharacterHashes")->value;
	genericHashesLoad(charactersDoc, characterHashes);

	rapidjson::Value& npcsDoc = jsondoc.FindMember("NPCHashes")->value;
	genericHashesLoad(npcsDoc, NPCHashes);

	rapidjson::Value& itemsDoc = jsondoc.FindMember("ItemHashes")->value;
	genericHashesLoad(itemsDoc, itemHashes);
}


void packet_processor::main_loop()
{
	fillObjCodeMap();

	printf("Connecting to sniffer pipes...\n");
	while (!patchpipe)
	{
		patchpipe = connectPipe(L"\\\\.\\pipe\\patchpipe");
		Sleep(500);
	}
	while (!loginpipe)
	{
		loginpipe = connectPipe(L"\\\\.\\pipe\\loginpipe");
		Sleep(500);
	}
	while (!gamepipe)
	{
		gamepipe = connectPipe(L"\\\\.\\pipe\\gamepipe");
		Sleep(500);
	}

	printf("Connected! Starting packet processing\n");

	process_packet_loop();
}