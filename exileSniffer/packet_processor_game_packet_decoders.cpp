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
	packetDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	packetDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	packetDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	packetDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;

	packetDeserialisers[SRV_PRELOAD_MONSTER_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST;
	packetDeserialisers[SRV_UNK_0x13] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x13;
	packetDeserialisers[SRV_PLAYER_ITEMS] = (deserialiser)&packet_processor::deserialise_SRV_PLAYER_ITEMS;
	packetDeserialisers[CLI_CLICKED_GROUND_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM;
	packetDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;

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
	packetDeserialisers[SRV_UNK_ACCT_SOCIAL_NAME] = (deserialiser)&packet_processor::deserialise_SRV_UNK_ACCT_SOCIAL_NAME;
	packetDeserialisers[CLI_REQUEST_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES;
	packetDeserialisers[SRV_RESPOND_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_SRV_RESPOND_PUBLICPARTIES;
	packetDeserialisers[SRV_CREATE_ITEM] = (deserialiser)&packet_processor::deserialise_SRV_CREATE_ITEM;
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
	packetDeserialisers[SRV_MOBILE_UNK_0xeb] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UNK_0xeb;
	packetDeserialisers[SRV_MOBILE_UPDATE_HMS] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UPDATE_HMS;
	packetDeserialisers[SRV_STAT_CHANGED] = (deserialiser)&packet_processor::deserialise_SRV_STAT_CHANGED;
	
	packetDeserialisers[CLI_REQUEST_PLAYERID] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PLAYERID;
	packetDeserialisers[SRV_NOTIFY_PLAYERID] = (deserialiser)&packet_processor::deserialise_SRV_NOTIFY_PLAYERID;
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

	//why are two bytes used for this?
	byte control1 = consume_Byte();
	byte control2 = consume_Byte();

	consume_add_byte(L"Unk4", uipkt);

	if (control1 & 8) //bit 4 set
	{
		consume_add_dword(L"Unk5_b4_1", uipkt);
		consume_add_byte(L"Unk5_b4_2", uipkt);
		consume_add_word(L"Unk5_b4_3", uipkt);
	}
	if (control1 & 16) //bit 5 set
	{
		consume_add_dword(L"Unk5_b5_1", uipkt);
	}


	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue preloadHashList(rapidjson::kArrayType);

	ushort hashCount = consumeUShort();
	for (int i = 0; i < hashCount; i++)
	{
		WValue preloadhash((UINT64)consume_DWORD());
		preloadHashList.PushBack(preloadhash, allocator);
		if (errorFlag != eNoErr) return;
	}
	uipkt->payload.AddMember(L"PreloadHashList", preloadHashList, allocator);

	//no idea what to do with any of these values yet

	ushort countl2 = consumeUShort();
	WValue list2(rapidjson::kArrayType);
	for (int i = 0; i < countl2; i++)
	{
		byte b = consume_Byte(); //todo
		list2.PushBack(b, allocator);
	}
	uipkt->payload.AddMember(L"ByteList1", list2, allocator);

	byte countl3 = consume_Byte(); 
	WValue list3(rapidjson::kArrayType);
	for (int i = 0; i < countl3; i++)
	{
		byte b = consume_Byte(); //todo
		list3.PushBack(b, allocator);
	}
	uipkt->payload.AddMember(L"ByteList2", list3, allocator);

	if (control2 & 0x2) //2nd bit set
	{
		WValue list4(rapidjson::kArrayType);
		byte countl4 = consume_Byte();
		for (int i = 0; i < countl4; i++)
		{
			byte b = consume_Byte(); //todo
			list4.PushBack(b, allocator);
		}
		uipkt->payload.AddMember(L"ByteList4", list4, allocator);
	}

	if (control2 & 0x4) //3rd bit set
	{
		WValue list5(rapidjson::kArrayType);
		byte countl5 = consume_Byte();
		for (int i = 0; i < countl5; i++)
		{
			byte b = consume_Byte(); //todo
			list5.PushBack(b, allocator);
		}
		uipkt->payload.AddMember(L"ByteList5", list5, allocator);
	}

	if (control2 & 0x1) //1st bit set
	{
		WValue list6(rapidjson::kArrayType);
		DWORD paircount = customSizeByteGet();
		for (int i = 0; i < paircount; i++)
		{
			WValue pair(rapidjson::kArrayType);

			DWORD first = customSizeByteGet();
			pair.PushBack((UINT64)first, allocator);

			DWORD second = customSizeByteGet_signed();
			pair.PushBack((UINT64)second, allocator);

			list6.PushBack(pair, allocator);
		}
		uipkt->payload.AddMember(L"PairList", list6, allocator);
	}
}

void packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt* uipkt)
{
	/*
	00 12 
	00 9A 
	74 00 B3 01 07 02 A9 05 AC 05 AD 05	B3 05 B9 05 
	BA 05 BF 05 C0 05 C1 05 C2 05 C3 05
	C4 05 D1 05 D2 05 D3 05 D4 05 EE 05 EF 05 F0 05
	F4 05 FE 05 08 06 12 06 1C 06 28 06 49 06 22 07
	2C 07 32 07 33 07 45 07 4B 07 54 07 D4 07 D5 07
	D6 07 D7 07 FA 07 70 08 73 08 D9 08 E0 08 77 0A
	10 0B 3E 0B 47 0B 48 0B 49 0B 4A 0B 4B 0B 4C 0B
	4D 0B 4E 0B 4F 0B 50 0B 51 0B 52 0B 53 0B 54 0B
	83 0C 87 0C 8D 0C 96 0C 9D 0C A1 0C D1 0C D2 0C
	D3 0C D4 0C D5 0C D6 0C D7 0C D8 0C D9 0C DA 0C
	DB 0C DC 0C DD 0C DE 0C DF 0C E1 0C E2 0C E7 0C
	E8 0C E9 0C EA 0C EB 0C EC 0C ED 0C EE 0C EF 0C
	F0 0C F1 0C F2 0C F3 0C F4 0C F5 0C F6 0C F7 0C
	F8 0C FA 0C FB 0C FC 0C 01 0D 02 0D 03 0D 04 0D
	05 0D 06 0D 07 0D 08 0D 09 0D 0A 0D 0B 0D 0C 0D
	0D 0D 0E 0D 0F 0D 11 0D 12 0D 13 0D 4B 0D 4C 0D
	4D 0D 63 0D 6C 0D B6 0D BC 0D EE 0D F0 0D 32 0F
	35 0F 47 11 4B 11 4E 11 FF 11 01 12 02 12 05 12
	06 12 08 12 0C 12 0D 12 0E 12 18 12 1B 12 1C 12
	1D 12 1E 12 24 12 25 12 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 2A 38 17 00 17 17 17 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	00 00 
	00 0F 00 00 22 33 00 08 53 00 74 00 61 00
	6E 00 64 00 61 00 72 00 64 00 A0 9D 5B 72 02 04
	13 00 01 00 00 12 0B 0B 12 C1 20 E8 D3 8A 26 60
	0C 9F 29 0D B7 4B 2A 3C 0A 1D 2B 47 8C D2 54 5B
	0C 85 57 6D 80 32 63 83 87 90 76 0C C1 43 86 43
	51 AA 89 43 DA 9C 8A E4 D3 9F 93 90 EC 1E A7 F2
	77 12 CD 68 5C 01 D0 68 74 58 FA 37 7B DF 00 03
	02 17 19 01 02 01 96 D7 01
	*/
	std::vector<std::pair<ushort, byte>> preloadList;

	unsigned short listCount = consumeUShort();
	preloadList.resize(listCount);

	//index into data/monstervarieties.dat 
	for (int i = 0; i < listCount; i++)
	{
		preloadList.at(i).first = ntohs(consumeUShort());
		if (errorFlag != eNoErr) return;
	}

	//level?
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

void packet_processor::deserialise_SRV_UNK_0x13(UIDecodedPkt * uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue blobArray(rapidjson::kArrayType);
	ushort listSize = consumeUShort();

	for (int i = 0; i < listSize; i++)
	{
		WValue blobobj(rapidjson::kObjectType);

		blobobj.AddMember(L"DW1", (UINT64)consume_DWORD(), allocator);
		blobobj.AddMember(L"DW2", (UINT64)consume_DWORD(), allocator);

		ushort stringlen_words = consumeUShort();
		wstring unkstr = consumeWString(stringlen_words * 2);
		WValue unkstring(unkstr.c_str(), allocator);
		blobobj.AddMember(L"UnkString", unkstring, allocator);

		blobobj.AddMember(L"Short1", consumeUShort(), allocator);
		byte controlByte = consume_Byte();
		blobobj.AddMember(L"ControlByte", controlByte, allocator);
		blobobj.AddMember(L"Short2", consumeUShort(), allocator);
		blobobj.AddMember(L"DW3", (UINT64)consume_DWORD(), allocator);
		blobobj.AddMember(L"DW4", (UINT64)consume_DWORD(), allocator);
		blobobj.AddMember(L"Byte2", consume_Byte(), allocator);

		if (controlByte > 0x80)
		{
			blobobj.AddMember(L"DW_8_1", (UINT64)consume_DWORD(), allocator);
			blobobj.AddMember(L"DW_8_2", (UINT64)consume_DWORD(), allocator);
		}
		if (controlByte & 0x40)
		{
			blobobj.AddMember(L"Byte_b7", consume_Byte(), allocator);
		}

		blobArray.PushBack(blobobj, allocator);
	}

	uipkt->payload.AddMember(L"BlobList", blobArray, allocator);

	ushort endstringlen_words = consumeUShort();
	wstring endstr = consumeWString(endstringlen_words * 2);
	WValue endstring(endstr.c_str(), allocator);
	uipkt->payload.AddMember(L"EndString", endstring, allocator);
	consume_add_word(L"EndShort", uipkt);
	consume_add_dword(L"EndDWORD", uipkt);

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
	/*
			0x00, 0x0a, 
		0x00, 0x04, //len name
		CHAT_TARGET_GLOBAL, 0x00,
		0x4e, 0x00, 0x69, 0x00, 0x61, 0x00, //name
		0x00, 0x14, 
		//text - welcome to crashland
		0x77, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x65, 
		0x00, 0x20, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x63, 0x00, 0x72, 0x00, 
		0x61, 0x00, 0x73, 0x00, 0x68, 0x00, 0x6c, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x64, 0x00,
		0x00, 0x04, //guild tag len
		0x68, 0x00, 0x61, 0x00, 0x78, 0x00, 0x78, 0x00, //tag
		0x01, //dev flag
		0x10, //challenges completed
		0x00, //hide sender? 
		0x00 //more pkts?

	//items
	//rare gold ring 15 dex '10% rarity bramble finger', 8-15 cold, 14% rarity, 20% lighting
	//magic '12% magpies' gold ring, 1.4 liferegen, 12 rarity
	02 //number of items
	00 00 00 00 //itemnum
	00 2B //len
	98 76 F7 29  //ring3 hash
	00 A1 55 01
	00 00 2B 1F 00 00 00 57 01 37 DA 0A 02 4B 55 66
	DA 3C C1 B0 64 04 2D 41 0F D4 91 0E B6 5F 14 93
	DC 08 0F 
	00 00 00 01 //itemnum
	00 1C //len
	98 76 F7 29 //ring3 hash
	00 A1 55
	01 00 00 3F 14 00 00 00 27 01 37 DA 0C 02 C0 E6
	0C AA 22 80 51

	///
	00 0A 
	00 09 
	23 00 6E 00 6F 00 6F 00 62 00 65 00	6D 00 6F 00 6E 00 
	00 1D 69 00 20 00 68 00 61 00 76 00 65 00 20 00 61 00 20 00 73 00 68 00 69 00 74 00 6C 00 6F 00 61 00 64 00 20 00 6F 00 66 00
	20 00 65 00 78 00 61 00 6C 00 74 00 65 00 64 00	73 00 
	00 00 00 00 00 00
	
	*/
	ushort namelen = consumeUShort();
	uipkt->add_wstring(L"Name", consumeWString(namelen * 2));
	ushort textlen = consumeUShort();
	uipkt->add_wstring(L"Text", consumeWString(textlen * 2));
	ushort taglen = consumeUShort();
	uipkt->add_wstring(L"Tag", consumeWString(taglen * 2));
	//guesswork
	consume_add_byte(L"Dev", uipkt);
	consume_add_byte(L"Challenges", uipkt);
	consume_add_byte(L"Hide", uipkt);
	byte itemCount = consume_Byte();


	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue itemArray(rapidjson::kArrayType);
	for (int i = 0; i < itemCount; i++)
	{
		WValue itemObj(rapidjson::kObjectType);
		itemObj.AddMember(L"ChatIndex", WValue((UINT64)consume_DWORD()), allocator);
		ushort modsLen = consumeUShort();
		DWORD hash = consume_DWORD();
		itemObj.AddMember(L"ItemHash", WValue((UINT64)ntohl(hash)), allocator);
		discard_data(modsLen - sizeof(hash));
		itemArray.PushBack(itemObj, allocator);
	}
	uipkt->payload.AddMember(L"ItemList", itemArray, allocator);
}

void packet_processor::deserialise_SRV_SERVER_MESSAGE(UIDecodedPkt *uipkt)
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
	for (int i = 0; i < 8; i++)
	{
		wstring skillName = L"Skill" + to_wstring(i);
		uipkt->add_word(skillName, ntohs(consumeUShort()));
	}
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

void packet_processor::deserialise_SRV_UNK_ACCT_SOCIAL_NAME(UIDecodedPkt *uipkt)
{
	unsigned short namelen = consumeUShort();
	std::wstring name = consumeWString(namelen * 2);
	uipkt->add_wstring(L"Name", name);

	//havent checked any of these yet, just getting the data in
	consume_add_dword(L"Unk1", uipkt);
	consume_add_dword(L"Unk2", uipkt);
	consume_add_word(L"Unk3", uipkt);
	consume_add_byte(L"Unk4", uipkt);
}

void packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_RESPOND_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_CREATE_ITEM(UIDecodedPkt *uipkt)
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
		discard_data(modsLen - sizeof(hash));


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

	consume_add_word(L"Unk1", uipkt); //ntohl used


	byte modifier = consume_Byte();
	uipkt->add_byte(L"Modifier", modifier);
	
	DWORD unk2 = 0;
	if (modifier & 0x80)
		unk2 = consume_DWORD();//ntohl used

	uipkt->add_dword(L"Unk2", unk2);

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
	consume_add_word(L"PkCount", uipkt); //0x1408EF03D

	/*
	conformant:
	00 EA 
	00 00 01 39 
	00 00 00 00 
	00 00 
	08   
	83 95 //coord
	82 90 //coord
	83 B0 //coord
	82 88 //coord
	29 09 
	02 94

	non conformant 1 <zombie>:

	00 EA
	00 00 01 39 
	00 00 00 00 
	00 00 
	88 
	00 00 01 2A //objID?
	83 B1 //coord
	82 88 //coord
	83 B0 //coord
	82 70 //coord
	40 00 02 97 00 EB 
	00 00 01 39 
	00 00 00 00 
	00 00


	nonconformant 2 <hillock>:
	00 EA 
	00 00 01 39 
	00 00 00 00 
	00 00 
	88 
	00 00 01 0F 
	84 A0 82 94 84 CC 82 8C 40 00 03 E0 00 EB 
	00 00 01 39 
	00 00 00 00 
	00 00

	*/
}


void packet_processor::deserialise_SRV_MOBILE_UNK_0xeb(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"ID1", uipkt);
	consume_add_dword(L"ID2", uipkt);
	consume_add_word(L"Unk1", uipkt);
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

void packet_processor::deserialise_SRV_STAT_CHANGED(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"ObjID", uipkt);
}

void packet_processor::deserialise_CLI_REQUEST_PLAYERID(UIDecodedPkt *)
{
	//nothing expected
}


//briefly glanced at the disassembly to do this, not seen the packet be anything but nulls yet
void packet_processor::deserialise_SRV_UNKNOWN_0x111(UIDecodedPkt *uipkt)
{
	unsigned short count = consume_Byte();
	uipkt->add_word(L"Count1", count);//0x14091327B

	for (int i = 0; i < count; i++)
	{
		consume_DWORD();

		consume_DWORD();

		consume_DWORD();
		consume_DWORD();
	}

	unsigned short count2 = consume_Byte();
	uipkt->add_word(L"Count2", count2);
	for (int i = 0; i < count; i++)
	{
		consume_DWORD();

		consume_DWORD();

		consume_DWORD();

		consume_DWORD();
		consume_DWORD();
	}

}


void packet_processor::deserialise_SRV_NOTIFY_PLAYERID(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"ID1", uipkt);
	consume_add_dword(L"ID2", uipkt);
	consume_add_word(L"ID3", uipkt);
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
	//10 bytes all retrieved at once
	consume_add_dword(L"ObjID", uipkt);
	consume_add_dword(L"unkID1", uipkt);
	consume_add_word(L"unk2", uipkt);

	consume_add_dword(L"objHash", uipkt);

	unsigned short dataLen = consumeUShort();
	uipkt->add_word(L"DataLen", dataLen);
	if (dataLen >= 8)
	{
		consume_add_dword(L"Coord1", uipkt);
		consume_add_dword(L"Coord2", uipkt);
		discard_data(dataLen - 8); //todo
	}
	else
		discard_data(dataLen); //todo

}