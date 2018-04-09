/*
These member functions attempt to reassemble the raw packet bytes 
into meaningful data as the game client/server would interpret it
*/
#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"


void packet_processor::init_packetDeserialisers()
{
	packetDeserialisers[SRV_PKT_ENCAPSULATED] = (deserialiser)&packet_processor::deserialise_SRV_PKT_ENCAPSULATED;
	packetDeserialisers[CLI_CHAT_MSG_ITEMS] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG_ITEMS;
	packetDeserialisers[CLI_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG;
	packetDeserialisers[CLI_PING_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_PING_CHALLENGE;
	packetDeserialisers[SRV_PING_RESPONSE] = (deserialiser)&packet_processor::deserialise_SRV_PING_RESPONSE;
	packetDeserialisers[SRV_AREA_INFO] = (deserialiser)&packet_processor::deserialise_SRV_AREA_INFO;
	packetDeserialisers[SRV_PRELOAD_MONSTER_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST;
	packetDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	packetDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	packetDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	packetDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;

	packetDeserialisers[CLI_CLICKED_GROUND_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM;
	packetDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;
	packetDeserialisers[SRV_PLAYER_ITEMS] = (deserialiser)&packet_processor::deserialise_SRV_PLAYER_ITEMS;
	packetDeserialisers[SRV_INSTANCE_SERVER_DATA] = (deserialiser)&packet_processor::deserialise_SRV_INSTANCE_SERVER_DATA;
	packetDeserialisers[CLI_PICKUP_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PICKUP_ITEM;
	packetDeserialisers[CLI_PLACE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PLACE_ITEM;
	packetDeserialisers[CLI_REMOVE_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_REMOVE_SOCKET;
	packetDeserialisers[CLI_INSERT_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_INSERT_SOCKET;

	packetDeserialisers[CLI_LEVEL_SKILLGEM] = (deserialiser)&packet_processor::deserialise_CLI_LEVEL_SKILLGEM;
	packetDeserialisers[CLI_SKILLPOINT_CHANGE] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPOINT_CHANGE;
	packetDeserialisers[CLI_CANCEL_BUF] = (deserialiser)&packet_processor::deserialise_CLI_CANCEL_BUF;
	packetDeserialisers[CLI_SET_HOTBARSKILL] = (deserialiser)&packet_processor::deserialise_CLI_SET_HOTBARSKILL;
	packetDeserialisers[SRV_SKILL_SLOTS_LIST] = (deserialiser)&packet_processor::deserialise_SRV_SKILL_SLOTS_LIST;

	packetDeserialisers[CLI_USE_BELT_SLOT] = (deserialiser)&packet_processor::deserialise_CLI_USE_BELT_SLOT;
	packetDeserialisers[CLI_USE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_USE_ITEM;
	packetDeserialisers[CLI_UNK_x56] = (deserialiser)&packet_processor::deserialise_CLI_UNK_x56;

	packetDeserialisers[CLI_REQUEST_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES;
	packetDeserialisers[SRV_RESPOND_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_SRV_RESPOND_PUBLICPARTIES;
	packetDeserialisers[SRV_SLOT_ITEMSLIST] = (deserialiser)&packet_processor::deserialise_SRV_SLOT_ITEMSLIST;

	packetDeserialisers[CLI_SKILLPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPANE_ACTION;
	packetDeserialisers[CLI_MICROSTRANSACTIONPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_MICROSTRANSACTIONPANE_ACTION;
	packetDeserialisers[CLI_PACKET_EXIT] = (deserialiser)&packet_processor::deserialise_CLI_PACKET_EXIT;
	packetDeserialisers[CLI_USED_SKILL] = (deserialiser)&packet_processor::deserialise_CLI_USED_SKILL;
	packetDeserialisers[CLI_CLICK_OBJ] = (deserialiser)&packet_processor::deserialise_CLI_CLICK_OBJ;
	packetDeserialisers[CLI_MOUSE_HELD] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_HELD;
	packetDeserialisers[CLI_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
	packetDeserialisers[SRV_DISPLAY_BUILTIN_MSG] = (deserialiser)&packet_processor::deserialise_SRV_DISPLAY_BUILTIN_MSG;
	packetDeserialisers[CLI_GUILD_CREATE] = (deserialiser)&packet_processor::deserialise_CLI_GUILD_CREATE;
	packetDeserialisers[SRV_MOBILE_USED_SKILL] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_USED_SKILL;
	packetDeserialisers[SRV_MOBILE_UPDATE_HMS] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UPDATE_HMS;
	packetDeserialisers[SRV_UNKNOWN_0x111] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x111;
	packetDeserialisers[CLI_OPTOUT_TUTORIALS] = (deserialiser)&packet_processor::deserialise_CLI_OPTOUT_TUTORIALS;
	packetDeserialisers[SRV_HEARTBEAT] = (deserialiser)&packet_processor::deserialise_SRV_HEARTBEAT;
	packetDeserialisers[SRV_ADD_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_ADD_OBJECT;
}

/*
this is deserialised within the processing loop as part of stream crypt resynchronisation
the packet within is then deserialised and actioned
this function only here for completeness - it should not be used!
*/
void packet_processor::deserialise_SRV_PKT_ENCAPSULATED(UIDecodedPkt *uipkt)
{

}

void packet_processor::deserialise_CLI_CHAT_MSG_ITEMS(UIDecodedPkt *uipkt)
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
}

void packet_processor::deserialise_CLI_CHAT_MSG(UIDecodedPkt *uipkt)
{
	ushort msgLenWords = consumeUShort();
	std::wstring msg = consumeWString(msgLenWords * 2);
	uipkt->add_wstring(L"Message", msg);
	consume_add_byte(L"NumLinkedItems", uipkt);
}

void packet_processor::deserialise_CLI_PING_CHALLENGE(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Challenge", uipkt);
}

void packet_processor::deserialise_SRV_PING_RESPONSE(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Response", uipkt);
}

void packet_processor::deserialise_SRV_AREA_INFO(UIDecodedPkt* uipkt)
{
	consume_add_dword(L"AreaCode", uipkt);

	size_t diffLenWords = consumeUShort();
	std::wstring msg = consumeWString(diffLenWords * 2);
	uipkt->add_wstring(L"Difficulty", msg);

	consume_add_dword(L"AreaVariant", uipkt);
	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
	consume_add_word(L"Unk4", uipkt);
	consume_add_byte(L"Unk5", uipkt);

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue preloadArray(rapidjson::kArrayType);

	ushort hashCount = consumeUShort();
	for (int i = 0; i < hashCount; i++)
	{
		WValue preloadhash((UINT64)consume_DWORD());
		preloadArray.PushBack(preloadhash, uipkt->jsn.GetAllocator());
		if (errorFlag != eNoErr) return;
	}
	uipkt->payload.AddMember(L"PreloadList", preloadArray, allocator);

	consume_add_word(L"Unk6", uipkt);
	consume_add_word(L"Unk7", uipkt);
	consume_add_word(L"Unk8", uipkt);
	consume_add_word(L"Unk9", uipkt);
	consume_add_word(L"Unk10", uipkt);
}

void packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt* uipkt)
{

	std::vector<std::pair<ushort, byte>> preloadList;

	unsigned short listCount = consumeUShort();
	preloadList.resize(listCount);

	//index into data/monstervarieties.dat 
	for (int i = 0; i < listCount; i++)
	{
		preloadList.at(i).first = ntohs(consumeUShort());
		if (errorFlag != eNoErr) return;
	}

	//0 = expected, 1 = ???
	for (int i = 0; i < listCount; i++)
	{
		preloadList.at(i).second = consume_Byte();
		if (errorFlag != eNoErr) return;
	}

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue jsarray(rapidjson::kArrayType);
	for (int i = 0; i < listCount; i++)
	{
		WValue pairArray(rapidjson::kArrayType);
		pairArray.PushBack(WValue(preloadList.at(i).first), allocator);
		pairArray.PushBack(WValue(preloadList.at(i).second), allocator);
		
		jsarray.PushBack(pairArray, allocator);
	}
	uipkt->payload.AddMember(L"PreloadList", jsarray, allocator);
}

void packet_processor::deserialise_SRV_PLAYER_ITEMS(UIDecodedPkt* uipkt)
{
	consume_add_dword(L"ObjID", uipkt);
}


void packet_processor::deserialise_CLI_CHAT_COMMAND(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"CommandID", uipkt);
	consume_add_word(L"Unk1", uipkt);
	
	//todo: certain commands may cause extra bytes to be sent
}

void packet_processor::deserialise_SRV_CHAT_MESSAGE(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_SERVER_MESSAGE(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_LOGGED_OUT(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}


void packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"TargID", uipkt);
	consume_add_dword(L"Unk1", uipkt);
	consume_add_byte(L"Modifier", uipkt);
}



void packet_processor::deserialise_CLI_ACTION_PREDICTIVE(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"TargCoord1", uipkt);
	consume_add_dword(L"TargCoord2", uipkt);
	consume_add_word(L"SkillID", uipkt);
	consume_add_word(L"PkCount", uipkt);
	consume_add_byte(L"Modifier", uipkt);
}

void packet_processor::deserialise_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);
	consume_add_dword(L"Unk2", uipkt);
	consume_add_dword(L"AreaCode", uipkt);
	consume_add_dword(L"Unk3", uipkt);
	DWORD nextConnectionID = consume_DWORD();
	uipkt->add_dword(L"NextConnectionID", nextConnectionID);
	consume_add_word(L"Port", uipkt);
	consume_add_dword(L"IP", uipkt);

	//std::cout << std::hex << "[" << pktId << "] New game server data. AREA TRANSITION" << std::endl;
	//std::cout << "\tGameserver: " << serverIP.str() << ":" << std::dec << port << std::hex << std::endl;

	discard_data(20);//0?


	KEYDATA *key1A = new KEYDATA;
	KEYDATA *key1B = new KEYDATA;
	memcpy(key1A->salsakey, decryptedBuffer + decryptedIndex, 32);
	memcpy(key1B->salsakey, decryptedBuffer + decryptedIndex, 32);
	discard_data(32);

	if (key1A->salsakey[0] == 0 && key1A->salsakey[3] == 0 && key1A->salsakey[7])
	{
		std::cout << "Discarding bad key in area transition" << std::endl;
		return; //probably an old zero-ed out key
	}

	memcpy(key1A->IV, decryptedBuffer + decryptedIndex, 8);
	discard_data(16);
	memcpy(key1B->IV, decryptedBuffer + decryptedIndex, 8);
	discard_data(8);

	key1A->sourceProcess = key1B->sourceProcess = uipkt->clientProcessID();
	key1A->foundAddress = key1B->foundAddress = SENT_BY_SERVER;
	pendingGameserverKeys[nextConnectionID] = make_pair(key1A, key1B);
}

void packet_processor::deserialise_CLI_PICKUP_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);
	consume_add_dword(L"ItemID", uipkt); //odd this is a dword. todo: check
	consume_add_byte(L"Unk2", uipkt);
}

void packet_processor::deserialise_CLI_PLACE_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Container", uipkt);
	consume_add_dword(L"Column", uipkt);
	consume_add_dword(L"Row", uipkt);
	consume_add_byte(L"Unk2", uipkt);
}

void packet_processor::deserialise_CLI_REMOVE_SOCKET(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Container", uipkt);
	consume_add_dword(L"SourceItemID", uipkt);
	consume_add_dword(L"SockID", uipkt);
	consume_add_byte(L"Unk1", uipkt);
}

void packet_processor::deserialise_CLI_INSERT_SOCKET(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Container", uipkt);
	consume_add_dword(L"TargItemID", uipkt);
	consume_add_dword(L"SockID", uipkt);
}


void packet_processor::deserialise_CLI_LEVEL_SKILLGEM(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Container", uipkt);
	consume_add_dword(L"TargItemID", uipkt);
	consume_add_dword(L"Slot", uipkt);
}

void packet_processor::deserialise_CLI_SKILLPOINT_CHANGE(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"GraphIndex", uipkt);
}

void packet_processor::deserialise_CLI_CANCEL_BUF(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"BuffID", uipkt);
}

void packet_processor::deserialise_CLI_SET_HOTBARSKILL(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Slot", uipkt);
	consume_add_word(L"SkillID", uipkt);
}


void packet_processor::deserialise_SRV_SKILL_SLOTS_LIST(UIDecodedPkt *uipkt)
{
	consume_add_word(L"Skill1", uipkt);
	consume_add_word(L"Skill2", uipkt);
	consume_add_word(L"Skill3", uipkt);
	consume_add_word(L"Skill4", uipkt);
	consume_add_word(L"Skill5", uipkt);
	consume_add_word(L"Skill6", uipkt);
	consume_add_word(L"Skill7", uipkt);
	consume_add_word(L"Skill8", uipkt);
}



void packet_processor::deserialise_CLI_USE_BELT_SLOT(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Slot", uipkt);
}

void packet_processor::deserialise_CLI_USE_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Unk1", uipkt);
	consume_add_dword(L"Item1", uipkt);
	consume_add_dword(L"Unk2", uipkt);
	consume_add_dword(L"Item2", uipkt);

	/*
	std::cout << std::hex << "Player activated item 0x" << item1 << " on item 0x" << item2;
	std::cout << "i1unk: 0x" << unk1 << " i2unk: 0x" << unk2 << std::endl;
	*/
}


void packet_processor::deserialise_CLI_UNK_x56(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}

void packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_RESPOND_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_SLOT_ITEMSLIST(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);
	consume_add_dword(L"Container", uipkt);

	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
	consume_add_byte(L"Unk4", uipkt);
	consume_add_byte(L"Unk5", uipkt);
	consume_add_byte(L"Unk6", uipkt);

	DWORD itemCount = consume_DWORD();
	uipkt->add_dword(L"Count", itemCount);


	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue itemArray(rapidjson::kArrayType);
	for (int i = 0; i < itemCount; i++)
	{
		WValue itemObj(rapidjson::kObjectType);

		itemObj.AddMember(L"InstanceID", WValue((UINT64)consume_DWORD()), allocator);
		itemObj.AddMember(L"PosX", WValue(consume_Byte()), allocator);
		itemObj.AddMember(L"PosY", WValue(consume_Byte()), allocator);
		ushort modsLen = consumeUShort();
		DWORD hash = consume_DWORD();
		itemObj.AddMember(L"ItemHash", WValue((UINT64)ntohl(hash)), allocator);
		//skip item data for now, apart from the hash so we at least know item type
		discard_data(modsLen - 4);


		itemArray.PushBack(itemObj, allocator);
	}
	uipkt->payload.AddMember(L"ItemList", itemArray, allocator);

	consume_add_word(L"FinalUnk", uipkt);

}



void packet_processor::deserialise_CLI_SKILLPANE_ACTION(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_MICROSTRANSACTIONPANE_ACTION(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_PACKET_EXIT(UIDecodedPkt *)
{
	//todo
}


void packet_processor::deserialise_CLI_USED_SKILL(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_CLICK_OBJ(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_MOUSE_HELD(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_MOUSE_RELEASE(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_DISPLAY_BUILTIN_MSG(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"MsgID", uipkt);
}

void packet_processor::deserialise_CLI_GUILD_CREATE(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_MOBILE_USED_SKILL(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"User1", uipkt);
	consume_add_dword(L"ID2", uipkt);
	consume_add_word(L"Unk1", uipkt);
	consume_add_byte(L"Modifier", uipkt);

	//shouldnt actually do this - the 8 (high bit) is a signal to read another byte. 
	//will wreck things when we get coords that under- or over- flow
	//worry when it happens
	unsigned short startCoord1 = consumeUShort() - 0x8000;
	uipkt->add_word(L"StartCoord1",startCoord1);
	unsigned short startCoord2 = consumeUShort() - 0x8000;
	uipkt->add_word(L"StartCoord2", startCoord2);
	unsigned short targCoord1 = consumeUShort() - 0x8000;
	uipkt->add_word(L"TargCoord1", targCoord1);
	unsigned short targCoord2 = consumeUShort() - 0x8000;
	uipkt->add_word(L"TargCoord2", targCoord2);

	consume_add_word(L"SkillID", uipkt);
	consume_add_word(L"PkCount", uipkt);
}


void packet_processor::deserialise_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt *uipkt)
{
	/*
				0x00, 0x00, 0x01, 0x07, //objid
				0x00, 0x00, 0x00, 0x00,	//possibly the obj that caused it?
				0x00, 0x00, //???
				0x00, 0x00,	0x00, 0x36, //amount
				0x00, 0x00, 0x00, 0x00, //???
				0x01, //0 life/1 mana/2 shield
				0x00 //stat is dword?
	*/

	consume_add_dword(L"ObjID", uipkt);
	consume_add_dword(L"Unk1", uipkt);
	consume_add_word(L"Unk2", uipkt);
	consume_add_dword(L"NewValue", uipkt);
	consume_add_dword(L"Unk3", uipkt);
	consume_add_byte(L"Stat", uipkt);
	consume_add_byte(L"Unk4", uipkt); //possible more stats here

}



void packet_processor::deserialise_SRV_UNKNOWN_0x111(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"UnkCount", uipkt); //0x14091327B - a count, nonzero will do more
	consume_add_byte(L"UnkZero", uipkt); //0x14090CF6A - expected to be 0
}



void packet_processor::deserialise_CLI_OPTOUT_TUTORIALS(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_HEARTBEAT(UIDecodedPkt *uipkt)
{
	//nothing
}

void packet_processor::deserialise_SRV_ADD_OBJECT(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"ObjID", uipkt);
	consume_add_dword(L"unkID1", uipkt);
	consume_add_word(L"unk2", uipkt);
	consume_add_dword(L"objHash", uipkt);

	unsigned short dataLen = consumeUShort();
	uipkt->add_word(L"DataLen", dataLen);
	discard_data(dataLen);

}