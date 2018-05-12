#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"

void packet_processor::init_loginPkt_deserialisers()
{
	loginPktDeserialisers[LOGIN_CLI_KEEP_ALIVE] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_KEEP_ALIVE;
	loginPktDeserialisers[LOGIN_EPHERMERAL_PUBKEY] = (deserialiser)&packet_processor::deserialise_LOGIN_EPHERMERAL_PUBKEY;
	loginPktDeserialisers[LOGIN_CLI_AUTH_DATA] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_AUTH_DATA;
	loginPktDeserialisers[LOGIN_SRV_UNK0x4] = (deserialiser)&packet_processor::deserialise_LOGIN_SRV_UNK0x4;
	loginPktDeserialisers[LOGIN_CLI_RESYNC] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_RESYNC;
	loginPktDeserialisers[LOGIN_CLI_CHANGE_PASSWORD] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_CHANGE_PASSWORD;
	loginPktDeserialisers[LOGIN_CLI_DELETE_CHARACTER] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_DELETE_CHARACTER;
	loginPktDeserialisers[LOGIN_CLI_CHARACTER_SELECTED] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_CHARACTER_SELECTED;
	loginPktDeserialisers[LOGIN_SRV_NOTIFY_GAMESERVER] = (deserialiser)&packet_processor::deserialise_LOGIN_SRV_NOTIFY_GAMESERVER;
	loginPktDeserialisers[LOGIN_CLI_CREATED_CHARACTER] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_CREATED_CHARACTER;
	loginPktDeserialisers[LOGIN_SRV_CHAR_LIST] = (deserialiser)&packet_processor::deserialise_LOGIN_SRV_CHAR_LIST;
	loginPktDeserialisers[LOGIN_SRV_FINAL_PKT] = (deserialiser)&packet_processor::deserialise_LOGIN_SRV_FINAL_PKT;
	loginPktDeserialisers[LOGIN_CLI_REQUEST_RACE_DATA] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_REQUEST_RACE_DATA;
	loginPktDeserialisers[LOGIN_SRV_LEAGUE_LIST] = (deserialiser)&packet_processor::deserialise_LOGIN_SRV_LEAGUE_LIST;
	loginPktDeserialisers[LOGIN_CLI_REQUEST_LEAGUES] = (deserialiser)&packet_processor::deserialise_LOGIN_CLI_REQUEST_LEAGUES;
}

void packet_processor::deserialise_LOGIN_CLI_KEEP_ALIVE(UIDecodedPkt *)
{
	//no data
}

void packet_processor::deserialise_LOGIN_EPHERMERAL_PUBKEY(UIDecodedPkt *uipkt)
{

	DWORD keylen = ntohs(consume_WORD());
	uipkt->add_word(L"KeySize", keylen);

	std::wstring keyhex = consume_hexblob(keylen);
	WValue keyVal(keyhex.c_str(), keyhex.length(), uipkt->jsn.GetAllocator());
	uipkt->payload->AddMember(L"EphermeralKey", keyVal, uipkt->jsn.GetAllocator());

	DWORD siglen = ntohs(consume_WORD());
	uipkt->add_word(L"SignatureSize", siglen);

	if (siglen)
	{
		std::wstring sighex = consume_hexblob(siglen);
		WValue sigVal(sighex.c_str(), sighex.length(), uipkt->jsn.GetAllocator());
		uipkt->payload->AddMember(L"Signature", sigVal, uipkt->jsn.GetAllocator());
	}
}


void packet_processor::deserialise_LOGIN_CLI_AUTH_DATA(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);

	ushort emailLen = ntohs(consume_WORD());
	uipkt->add_wstring(L"AccountName", consumeWString(emailLen * 2));


	std::wstring exeHashHex = consume_hexblob(32);
	WValue hashval1(exeHashHex.c_str(), exeHashHex.length(), uipkt->jsn.GetAllocator());
	uipkt->payload->AddMember(L"ClientEXEHash", hashval1, uipkt->jsn.GetAllocator());

	std::wstring creds = consume_hexblob(32);
	//nothing good can come from deserialising this, keeping it in logs, passing to feed readers etc
	//will allow it to be displayed in the hexdump of the analysis pane only


	std::wstring MAChex = consume_hexblob(32);
	WValue MACval(MAChex.c_str(), MAChex.length(), uipkt->jsn.GetAllocator());
	uipkt->payload->AddMember(L"MACHash", MACval, uipkt->jsn.GetAllocator());

	consume_add_byte(L"SavedFlag1", uipkt);
	consume_add_byte(L"SavedFlag2", uipkt);
	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_SRV_UNK0x4(UIDecodedPkt *uipkt)
{
	UINT32 unk1 = ntohs(consume_WORD());

	ushort string1len = ntohs(consume_WORD());
	if (string1len)
		uipkt->add_wstring(L"String1", consumeWString(string1len * 2));

	std::wstring blob1 = consume_hexblob(32);
	UINT32 unk2 = consume_DWORD();
}

void packet_processor::deserialise_LOGIN_CLI_RESYNC(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);
}

void packet_processor::deserialise_LOGIN_SRV_CHAR_LIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue charList(rapidjson::kArrayType);
	UINT32 charCount = ntohl(consume_DWORD());

	for (int i = 0; i < charCount; i++)
	{
		WValue characterObj(rapidjson::kObjectType);

		consume_add_lenprefix_string(L"Name", characterObj, allocator);
		consume_add_lenprefix_string(L"League", characterObj, allocator);

		characterObj.AddMember(L"Banner", consume_Byte(), allocator);
		characterObj.AddMember(L"Unk1", consume_Byte(), allocator);
		characterObj.AddMember(L"Level", (UINT32)ntohl(consume_DWORD()), allocator);
		characterObj.AddMember(L"Unk2", (UINT32)ntohl(consume_DWORD()), allocator);
		characterObj.AddMember(L"Class", consume_Byte(), allocator);
		characterObj.AddMember(L"Unk3", consume_Byte(), allocator);
		characterObj.AddMember(L"Unk4", consume_Byte(), allocator);
		charList.PushBack(characterObj, allocator);
	}

	uipkt->payload->AddMember(L"CharacterList", charList, allocator);

	consume_add_dword_ntoh(L"End1", uipkt);
	consume_add_byte(L"End2", uipkt);
}
void packet_processor::deserialise_LOGIN_CLI_CHANGE_PASSWORD(UIDecodedPkt *)
{
	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_CLI_DELETE_CHARACTER(UIDecodedPkt *)
{
	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_CLI_CHARACTER_SELECTED(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);
	consume_add_byte(L"CharacterIndex", uipkt);
}

void packet_processor::deserialise_LOGIN_SRV_NOTIFY_GAMESERVER(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"AreaCode", uipkt);
	DWORD connectionID = ntohl(consume_DWORD());
	uipkt->add_dword(L"ConnectionID", connectionID);

	byte unkBlobCount = consume_Byte();

	WValue blobList(rapidjson::kArrayType);
	for (int i = 0; i < unkBlobCount; i++)
	{
		WValue blobObj(rapidjson::kObjectType);

		blobObj.AddMember(L"Unk1", (UINT32)ntohs(consume_WORD()), allocator);
		blobObj.AddMember(L"Port", (UINT32)ntohs(consume_WORD()), allocator);
		blobObj.AddMember(L"IPAddr", (UINT32)ntohl(consume_DWORD()), allocator);

		std::wstring remainingHex = consume_hexblob(20);
		WValue remainingVal (remainingHex.c_str(), remainingHex.length(), uipkt->jsn.GetAllocator());
		blobObj.AddMember(L"RemainingHex", remainingVal, uipkt->jsn.GetAllocator());
		blobList.PushBack(blobObj, allocator);
	}
	uipkt->payload->AddMember(L"ServerBlobs", blobList, allocator);

	KEYDATA *key1A = new KEYDATA;
	KEYDATA *key1B = new KEYDATA;

	memcpy(key1A->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	memcpy(key1B->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	memcpy(key1A->IV, decryptedBuffer->data() + decryptedIndex + 32, 8);
	memcpy(key1B->IV, decryptedBuffer->data() + decryptedIndex + 32 + 16, 8);

	std::wstring cryptBlob = consume_hexblob(64);
	std::wstring salsaHex(cryptBlob.begin(), cryptBlob.begin() + 32);
	std::wstring sendIV(cryptBlob.begin()+32, cryptBlob.begin() + 40);
	std::wstring recvIV(cryptBlob.begin()+48, cryptBlob.begin() + 56);

	

	
	DWORD *keyblob = (DWORD *)(&decryptedBuffer->at(43));
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
		return;
	}

	key1A->sourceProcess = key1B->sourceProcess = currentStreamObj->workingRecvKey->sourceProcess;
	key1A->foundAddress = key1B->foundAddress = SENT_BY_SERVER;
	pendingGameserverKeys[connectionID] = make_pair(key1A, key1B);

	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_CLI_CREATED_CHARACTER(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	consume_add_lenprefix_string(L"Name", *(uipkt->payload), allocator);
	consume_add_lenprefix_string(L"League", *(uipkt->payload), allocator);
	consume_add_qword(L"Unk1", uipkt);
	consume_add_lenprefix_string(L"Class", *(uipkt->payload), allocator);

	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_SRV_FINAL_PKT(UIDecodedPkt *uipkt)
{
	UInotifyStreamState(currentMsgStreamID, eStreamTransitionGame, uiMsgQueue);
	consume_add_word(L"Arg", uipkt);
}

void packet_processor::deserialise_LOGIN_CLI_REQUEST_RACE_DATA(UIDecodedPkt *)
{
	consume_blob(remainingDecrypted);
}

void packet_processor::deserialise_LOGIN_SRV_LEAGUE_LIST(UIDecodedPkt *uipkt)
{
	vector<byte> firstBlob;
	consume_add_qword(L"UnkBlob1", uipkt);

	deserialise_SRV_EVENTSLIST_2(uipkt);
}

void packet_processor::deserialise_LOGIN_CLI_REQUEST_LEAGUES(UIDecodedPkt *)
{
	consume_blob(remainingDecrypted);
}
