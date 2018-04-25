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

	packetDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	packetDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	packetDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	packetDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;


	packetDeserialisers[CLI_PING_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_PING_CHALLENGE;
	packetDeserialisers[SRV_PING_RESPONSE] = (deserialiser)&packet_processor::deserialise_SRV_PING_RESPONSE;
	packetDeserialisers[SRV_AREA_INFO] = (deserialiser)&packet_processor::deserialise_SRV_AREA_INFO;

	packetDeserialisers[SRV_PRELOAD_MONSTER_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST;
	packetDeserialisers[SRV_UNK_0x13] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x13;
	packetDeserialisers[SRV_PLAYER_ITEMS] = (deserialiser)&packet_processor::deserialise_SRV_PLAYER_ITEMS;
	packetDeserialisers[CLI_CLICKED_GROUND_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM;
	packetDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;
	packetDeserialisers[SRV_TRANSFER_INSTANCE] = (deserialiser)&packet_processor::deserialise_SRV_TRANSFER_INSTANCE;

	packetDeserialisers[SRV_INSTANCE_SERVER_DATA] = (deserialiser)&packet_processor::deserialise_SRV_INSTANCE_SERVER_DATA;
	packetDeserialisers[CLI_PICKUP_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PICKUP_ITEM;
	packetDeserialisers[CLI_PLACE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PLACE_ITEM;
	packetDeserialisers[CLI_REMOVE_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_REMOVE_SOCKET;
	packetDeserialisers[CLI_INSERT_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_INSERT_SOCKET;

	packetDeserialisers[CLI_LEVEL_SKILLGEM] = (deserialiser)&packet_processor::deserialise_CLI_LEVEL_SKILLGEM;
	packetDeserialisers[CLI_UNK_0x20] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0x20;
	packetDeserialisers[CLI_SKILLPOINT_CHANGE] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPOINT_CHANGE;
	packetDeserialisers[CLI_CANCEL_BUF] = (deserialiser)&packet_processor::deserialise_CLI_CANCEL_BUF;
	packetDeserialisers[CLI_UNK_0x2c] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0x2c;
	packetDeserialisers[CLI_SET_HOTBARSKILL] = (deserialiser)&packet_processor::deserialise_CLI_SET_HOTBARSKILL;
	packetDeserialisers[SRV_SKILL_SLOTS_LIST] = (deserialiser)&packet_processor::deserialise_SRV_SKILL_SLOTS_LIST;

	packetDeserialisers[CLI_USE_BELT_SLOT] = (deserialiser)&packet_processor::deserialise_CLI_USE_BELT_SLOT;
	packetDeserialisers[CLI_USE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_USE_ITEM;
	packetDeserialisers[CLI_UNK_0x41] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0x41;
	packetDeserialisers[SRV_STASH_INFO] = (deserialiser)&packet_processor::deserialise_SRV_STASH_INFO;
	packetDeserialisers[CLI_SEND_PARTY_INVITE] = (deserialiser)&packet_processor::deserialise_CLI_SEND_PARTY_INVITE;
	packetDeserialisers[CLI_TRY_JOIN_PARTY] = (deserialiser)&packet_processor::deserialise_CLI_TRY_JOIN_PARTY;
	packetDeserialisers[CLI_DISBAND_PUBLIC_PARTY] = (deserialiser)&packet_processor::deserialise_CLI_DISBAND_PUBLIC_PARTY;
	packetDeserialisers[CLI_CREATE_PUBLICPARTY] = (deserialiser)&packet_processor::deserialise_CLI_CREATE_PUBLICPARTY;
	packetDeserialisers[CLI_UNK_x56] = (deserialiser)&packet_processor::deserialise_CLI_UNK_x56;
	packetDeserialisers[CLI_GET_PARTY_DETAILS] = (deserialiser)&packet_processor::deserialise_CLI_GET_PARTY_DETAILS;

	packetDeserialisers[SRV_FRIENDSLIST] = (deserialiser)&packet_processor::deserialise_SRV_FRIENDSLIST;

	packetDeserialisers[SRV_PARTY_DETAILS] = (deserialiser)&packet_processor::deserialise_SRV_PARTY_DETAILS;

	packetDeserialisers[CLI_REQUEST_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES;
	packetDeserialisers[SRV_PUBLIC_PARTY_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PUBLIC_PARTY_LIST;
	packetDeserialisers[SRV_CREATE_ITEM] = (deserialiser)&packet_processor::deserialise_SRV_CREATE_ITEM;
	packetDeserialisers[SRV_SLOT_ITEMSLIST] = (deserialiser)&packet_processor::deserialise_SRV_SLOT_ITEMSLIST;
	packetDeserialisers[UNK_MESSAGE_0x70] = (deserialiser)&packet_processor::deserialise_UNK_MESSAGE_0x70;
	packetDeserialisers[UNK_MESSAGE_0x73] = (deserialiser)&packet_processor::deserialise_UNK_MESSAGE_0x73;
	packetDeserialisers[CLI_SET_STATUS_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_SET_STATUS_MESSAGE;
	
	packetDeserialisers[CLI_SWAPPED_WEAPONS] = (deserialiser)&packet_processor::deserialise_CLI_SWAPPED_WEAPONS;
	packetDeserialisers[CLI_SKILLPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPANE_ACTION;
	packetDeserialisers[SRV_UNK_0x92] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x92;

	packetDeserialisers[CLI_SKILLPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPANE_ACTION;
	packetDeserialisers[SRV_SKILLPANE_DATA] = (deserialiser)&packet_processor::deserialise_SRV_SKILLPANE_DATA;

	packetDeserialisers[CLI_MICROTRANSACTION_SHOP_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_MICROTRANSACTION_SHOP_ACTION;
	packetDeserialisers[SRV_MICROTRANSACTION_SHOP_DETAILS] = (deserialiser)&packet_processor::deserialise_SRV_MICROTRANSACTION_SHOP_DETAILS;
	packetDeserialisers[SRV_UNK_A3] = (deserialiser)&packet_processor::deserialise_SRV_UNK_A3;

	packetDeserialisers[CLI_PACKET_EXIT] = (deserialiser)&packet_processor::deserialise_CLI_PACKET_EXIT;
	packetDeserialisers[CLI_PACKET_EXIT_2] = (deserialiser)&packet_processor::deserialise_CLI_PACKET_EXIT_2;
	packetDeserialisers[CLI_DUEL_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_DUEL_CHALLENGE;
	packetDeserialisers[SRV_DUEL_RESPONSE] = (deserialiser)&packet_processor::deserialise_SRV_DUEL_RESPONSE;
	packetDeserialisers[SRV_DUEL_CHALLENGE] = (deserialiser)&packet_processor::deserialise_SRV_DUEL_CHALLENGE;

	packetDeserialisers[CLI_UNK_0xC7] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0xC7;

	packetDeserialisers[SRV_UNK_0xD5] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xD5;

	packetDeserialisers[CLI_USED_SKILL] = (deserialiser)&packet_processor::deserialise_CLI_USED_SKILL;
	packetDeserialisers[CLI_CLICK_OBJ] = (deserialiser)&packet_processor::deserialise_CLI_CLICK_OBJ;
	packetDeserialisers[CLI_MOUSE_HELD] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_HELD;
	packetDeserialisers[CLI_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
	packetDeserialisers[CLI_OPEN_WORLD_SCREEN] = (deserialiser)&packet_processor::deserialise_CLI_OPEN_WORLD_SCREEN;
	
	packetDeserialisers[SRV_CHAT_CHANNEL_ID] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_CHANNEL_ID;
	packetDeserialisers[CLI_GUILD_CREATE] = (deserialiser)&packet_processor::deserialise_CLI_GUILD_CREATE;
	packetDeserialisers[SRV_UNK_0xE6] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xE6;
	packetDeserialisers[SRV_ITEM_REMOVED] = (deserialiser)&packet_processor::deserialise_SRV_ITEM_REMOVED;
	packetDeserialisers[SRV_MOBILE_START_SKILL] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_START_SKILL;
	packetDeserialisers[SRV_MOBILE_FINISH_SKILL] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_FINISH_SKILL;
	packetDeserialisers[SRV_MOBILE_UNK_0xee] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UNK_0xee;
	packetDeserialisers[SRV_MOBILE_UNK_0xef] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UNK_0xef;
	packetDeserialisers[SRV_MOBILE_UPDATE_HMS] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UPDATE_HMS;
	packetDeserialisers[SRV_STAT_CHANGED] = (deserialiser)&packet_processor::deserialise_SRV_STAT_CHANGED;
	packetDeserialisers[SRV_UNK_0xf2] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf2;
	packetDeserialisers[SRV_UNK_0xf3] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf3;
	packetDeserialisers[SRV_START_EFFECT] = (deserialiser)&packet_processor::deserialise_SRV_START_EFFECT;
	packetDeserialisers[SRV_END_EFFECT] = (deserialiser)&packet_processor::deserialise_SRV_END_EFFECT;

	packetDeserialisers[CLI_REQUEST_PLAYERID] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PLAYERID;
	packetDeserialisers[SRV_NOTIFY_PLAYERID] = (deserialiser)&packet_processor::deserialise_SRV_NOTIFY_PLAYERID;
	packetDeserialisers[SRV_UNKNOWN_0x111] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x111;
	packetDeserialisers[SRV_UNKNOWN_0x118] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x118;
	packetDeserialisers[CLI_OPTOUT_TUTORIALS] = (deserialiser)&packet_processor::deserialise_CLI_OPTOUT_TUTORIALS;
	packetDeserialisers[SRV_HEARTBEAT] = (deserialiser)&packet_processor::deserialise_SRV_HEARTBEAT;
	packetDeserialisers[SRV_ADD_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_ADD_OBJECT;
	packetDeserialisers[SRV_UPDATE_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_UPDATE_OBJECT;
	packetDeserialisers[SRV_IDNOTIFY_0x137] = (deserialiser)&packet_processor::deserialise_SRV_IDNOTIFY_0x137;
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
	ushort msgLenWords = ntohs(consumeUShort());
	std::wstring msg = consumeWString(msgLenWords * 2);
	uipkt->add_wstring(L"Message", msg);
	consume_add_byte(L"NumLinkedItems", uipkt);
}


void packet_processor::deserialise_CLI_CHAT_COMMAND(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"CommandID", uipkt);
	consume_add_word_ntoh(L"Unk1", uipkt);

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
	ushort namelen = ntohs(consumeUShort());
	uipkt->add_wstring(L"Name", consumeWString(namelen * 2));
	ushort textlen = ntohs(consumeUShort());
	uipkt->add_wstring(L"Text", consumeWString(textlen * 2));
	ushort taglen = ntohs(consumeUShort());
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
		itemObj.AddMember(L"ChatIndex", WValue((UINT32)consume_DWORD()), allocator);
		ushort modsLen = ntohs(consumeUShort());
		DWORD hash = consume_DWORD();
		itemObj.AddMember(L"ItemHash", WValue((UINT32)hash), allocator);
		consume_blob(modsLen - sizeof(hash));
		itemArray.PushBack(itemObj, allocator);
	}
	uipkt->payload.AddMember(L"ItemList", itemArray, allocator);
}

void packet_processor::deserialise_SRV_SERVER_MESSAGE(UIDecodedPkt *uipkt)
{
	//outer
	consume_add_word_ntoh(L"BackendErrorsRow", uipkt);
	consume_add_word_ntoh(L"DevID", uipkt);
	consume_add_byte(L"TextModifier", uipkt);
	consume_add_dword_ntoh(L"Unk4", uipkt);

	//inner - shared with other packets
	byte pairCount = consume_Byte();
	byte stringCount = consume_Byte();

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue pairArray(rapidjson::kArrayType);

	for (int i = 0; i < pairCount; i++)
	{
		WValue pair(rapidjson::kArrayType);
		byte p1 = consume_Byte();
		pair.PushBack(p1, allocator);
		DWORD p2 = consume_DWORD();
		pair.PushBack((UINT32)p2, allocator);
		pairArray.PushBack(pair, allocator);
	}
	uipkt->payload.AddMember(L"PairList", pairArray, allocator);

	WValue stringArray(rapidjson::kArrayType);
	for (int i = 0; i < stringCount; i++)
	{
		ushort stringSize = ntohs(consumeUShort());
		std::wstring msgstr = consumeWString(stringSize * 2);
		WValue stringval(msgstr.c_str(), allocator);
		stringArray.PushBack(stringval, allocator);
	}
	uipkt->payload.AddMember(L"StringList", stringArray, allocator);

	/*
	//welcome to coast
	00 0B
	00 77
	FF FF
	02
	00 00 00 00
	01
	00
	07
	00 00 00 03
	00


	33 remaining:

	00 0b
	00 99
	ff ff
	02
	00 00 00 00
	01
	00
	00
	00 00 00 21  //33


	"downtime will be approx 20 mins
	00 0b
	01 16
	ff ff
	01
	00 00 00 00

	00
	02

	00 06
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

	//declined duel/left duel q
	//00 0B 00 AD FF FF 02 00 00 00 00 00 00

	//todo
}


void packet_processor::deserialise_CLI_PING_CHALLENGE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Challenge", uipkt);
}

void packet_processor::deserialise_SRV_PING_RESPONSE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Response", uipkt);
}

void packet_processor::deserialise_SRV_AREA_INFO(UIDecodedPkt* uipkt)
{
	
	consume_add_dword_ntoh(L"AreaCode", uipkt);

	size_t diffLenWords = ntohs(consumeUShort());
	std::wstring msg = consumeWString(diffLenWords * 2);
	uipkt->add_wstring(L"Difficulty", msg);

	consume_add_dword_ntoh(L"AreaVariant", uipkt);

	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);

	//why are two bytes used for this?
	byte control1 = consume_Byte();
	byte control2 = consume_Byte();

	consume_add_byte(L"Unk4", uipkt);

	if (control1 & 8) //bit 4 set
	{
		consume_add_dword_ntoh(L"Unk5_b4_1", uipkt);
		consume_add_byte(L"Unk5_b4_2", uipkt);
		consume_add_word_ntoh(L"Unk5_b4_3", uipkt);
	}
	if (control1 & 16) //bit 5 set
	{
		consume_add_dword_ntoh(L"Unk5_b5_1", uipkt);
	}


	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue preloadHashList(rapidjson::kArrayType);

	ushort hashCount = ntohs(consumeUShort());
	for (int i = 0; i < hashCount; i++)
	{
		WValue preloadhash((UINT32)ntohl(consume_DWORD()));
		preloadHashList.PushBack(preloadhash, allocator);
		if (errorFlag != eNoErr) return;
	}
	uipkt->payload.AddMember(L"PreloadHashList", preloadHashList, allocator);

	//no idea what to do with any of these values yet

	ushort countl2 = ntohs(consumeUShort());
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
			pair.PushBack((UINT32)first, allocator);

			DWORD second = customSizeByteGet_signed();
			pair.PushBack((UINT32)second, allocator);

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

	unsigned short listCount = ntohs(consumeUShort());
	preloadList.resize(listCount);

	//index into data/monstervarieties.dat 
	for (int i = 0; i < listCount; i++)
	{
		preloadList.at(i).first = consumeUShort();
		if (errorFlag != eNoErr) return;
	}

	//level?
	unsigned int lastLevel = 0xFFFF;
	for (int i = 0; i < listCount; i++)
	{
		byte level = consume_Byte();
		preloadList.at(i).second = level;
		if (level != lastLevel)
		{
			ggpk->generateMonsterLevelHashes(level);
			lastLevel = level;
		}
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
	ushort listSize = ntohs(consumeUShort());

	for (int i = 0; i < listSize; i++)
	{
		WValue blobobj(rapidjson::kObjectType);

		blobobj.AddMember(L"DW1", (UINT32)consume_DWORD(), allocator);
		blobobj.AddMember(L"DW2", (UINT32)consume_DWORD(), allocator);

		ushort stringlen_words = ntohs(consumeUShort());
		wstring unkstr = consumeWString(stringlen_words * 2);
		WValue unkstring(unkstr.c_str(), allocator);
		blobobj.AddMember(L"UnkString", unkstring, allocator);

		blobobj.AddMember(L"Short1", consumeUShort(), allocator);
		byte controlByte = consume_Byte();
		blobobj.AddMember(L"ControlByte", controlByte, allocator);
		blobobj.AddMember(L"Short2", consumeUShort(), allocator);
		blobobj.AddMember(L"DW3", (UINT32)consume_DWORD(), allocator);
		blobobj.AddMember(L"DW4", (UINT32)consume_DWORD(), allocator);
		blobobj.AddMember(L"Byte2", consume_Byte(), allocator);

		if (controlByte > 0x80)
		{
			blobobj.AddMember(L"DW_8_1", (UINT32)consume_DWORD(), allocator);
			blobobj.AddMember(L"DW_8_2", (UINT32)consume_DWORD(), allocator);
		}
		if (controlByte & 0x40)
		{
			blobobj.AddMember(L"Byte_b7", consume_Byte(), allocator);
		}

		blobArray.PushBack(blobobj, allocator);
	}

	uipkt->payload.AddMember(L"BlobList", blobArray, allocator);

	ushort endstringlen_words = ntohs(consumeUShort());
	wstring endstr = consumeWString(endstringlen_words * 2);
	WValue endstring(endstr.c_str(), allocator);
	uipkt->payload.AddMember(L"EndString", endstring, allocator);
	consume_add_word_ntoh(L"EndShort", uipkt);
	consume_add_dword_ntoh(L"EndDWORD", uipkt);

}

void packet_processor::deserialise_SRV_PLAYER_ITEMS(UIDecodedPkt* uipkt)
{
	consume_add_dword_ntoh(L"ObjID", uipkt);
}




void packet_processor::deserialise_CLI_LOGGED_OUT(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}


void packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"TargID", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
	consume_add_word_ntoh(L"Sequence", uipkt);
	consume_add_byte(L"Modifier", uipkt);
}



void packet_processor::deserialise_CLI_ACTION_PREDICTIVE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"TargCoord1", uipkt);
	consume_add_dword_ntoh(L"TargCoord2", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
	consume_add_word_ntoh(L"PkCount", uipkt);
	consume_add_byte(L"Modifier", uipkt);
}


void packet_processor::deserialise_SRV_TRANSFER_INSTANCE(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"Arg", uipkt);
}


void packet_processor::deserialise_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"AreaCode", uipkt);
	DWORD nextConnectionID = ntohl(consume_DWORD());
	uipkt->add_dword(L"NextConnectionID", nextConnectionID);
	consume_add_dword_ntoh(L"Unk3", uipkt);
	consume_add_word_ntoh(L"Port", uipkt);
	consume_add_dword_ntoh(L"IP", uipkt);

	std::cout << "Got area transition - next conn id is 0x" << std::hex << nextConnectionID << std::endl;
	//std::cout << std::hex << "[" << pktId << "] New game server data. AREA TRANSITION" << std::endl;
	//std::cout << "\tGameserver: " << serverIP.str() << ":" << std::dec << port << std::hex << std::endl;

	consume_blob(20);//0?


	KEYDATA *key1A = new KEYDATA;
	KEYDATA *key1B = new KEYDATA;
	//todo proper vectors
	memcpy(key1A->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	memcpy(key1B->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	consume_blob(32);

	if (key1A->salsakey[0] == 0 && key1A->salsakey[3] == 0 && key1A->salsakey[7])
	{
		std::cout << "Discarding bad key in area transition" << std::endl;
		consume_blob(32);
		return; //probably an old zero-ed out key
	}

	memcpy(key1A->IV, decryptedBuffer->data() + decryptedIndex, 8);
	consume_blob(16);
	memcpy(key1B->IV, decryptedBuffer->data() + decryptedIndex, 8);
	consume_blob(16);

	key1A->sourceProcess = key1B->sourceProcess = uipkt->clientProcessID();
	key1A->foundAddress = key1B->foundAddress = SENT_BY_SERVER;
	pendingGameserverKeys[nextConnectionID] = make_pair(key1A, key1B);
}

void packet_processor::deserialise_CLI_PICKUP_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"ItemID", uipkt); //odd this is a dword. todo: check
	consume_add_byte(L"Unk2", uipkt);
}

void packet_processor::deserialise_CLI_PLACE_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"Column", uipkt);
	consume_add_dword_ntoh(L"Row", uipkt);
	consume_add_byte(L"Unk2", uipkt);
}

void packet_processor::deserialise_CLI_REMOVE_SOCKET(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"SourceItemID", uipkt);
	consume_add_dword_ntoh(L"SockID", uipkt);
	consume_add_byte(L"Unk1", uipkt);
}

void packet_processor::deserialise_CLI_INSERT_SOCKET(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"TargItemID", uipkt);
	consume_add_dword_ntoh(L"SockID", uipkt);
}


void packet_processor::deserialise_CLI_LEVEL_SKILLGEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"TargItemID", uipkt);
	consume_add_dword_ntoh(L"Slot", uipkt);
}

void packet_processor::deserialise_CLI_UNK_0x20(UIDecodedPkt *uipkt)
{
	//todo 
	unsigned short itemCount = ntohs(consumeUShort());
	for (int i = 0; i < itemCount; i++)
	{
		consumeUShort();
	}
	consumeUShort(); 
	consumeUShort(); 
	consumeUShort(); 
	consume_Byte();
	consume_Byte();
	consume_Byte();

}

void packet_processor::deserialise_CLI_SKILLPOINT_CHANGE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"GraphIndex", uipkt);
}

void packet_processor::deserialise_CLI_CANCEL_BUF(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"BuffID", uipkt);
}

//todo
void packet_processor::deserialise_CLI_UNK_0x2c(UIDecodedPkt *uipkt)
{
	//todo 
	unsigned short itemCount = 4; //comes from a member variable, dunno where it's set yet
	for (int i = 0; i < itemCount; i++)
	{
		consume_Byte();
	}
	
	consume_blob(19);

}

void packet_processor::deserialise_CLI_SET_HOTBARSKILL(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Slot", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
}


void packet_processor::deserialise_SRV_SKILL_SLOTS_LIST(UIDecodedPkt *uipkt)
{
	for (int i = 1; i < 9; i++)
	{
		wstring skillName = L"Skill" + to_wstring(i);
		uipkt->add_word(skillName, consumeUShort());
	}
}



void packet_processor::deserialise_CLI_USE_BELT_SLOT(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Slot", uipkt);
}

void packet_processor::deserialise_CLI_USE_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Item1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"Item2", uipkt);

	/*
	std::cout << std::hex << "Player activated item 0x" << item1 << " on item 0x" << item2;
	std::cout << "i1unk: 0x" << unk1 << " i2unk: 0x" << unk2 << std::endl;
	*/
}

void packet_processor::deserialise_CLI_UNK_0x41(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
}

void packet_processor::deserialise_SRV_STASH_INFO(UIDecodedPkt *uipkt)
{

}

void packet_processor::deserialise_CLI_SEND_PARTY_INVITE(UIDecodedPkt *uipkt)
{
	unsigned short namelen = ntohs(consumeUShort());
	std::wstring name = consumeWString(namelen * 2);
	uipkt->add_wstring(L"Name", name);
}


void packet_processor::deserialise_CLI_TRY_JOIN_PARTY(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID", uipkt);
}

void packet_processor::deserialise_CLI_DISBAND_PUBLIC_PARTY(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID", uipkt);
}

void packet_processor::deserialise_CLI_CREATE_PUBLICPARTY(UIDecodedPkt *uipkt)
{
	unsigned short namelen = ntohs(consumeUShort());
	std::wstring name = consumeWString(namelen * 2);
	uipkt->add_wstring(L"Name", name);

	consume_add_byte(L"Arg", uipkt);

}

void packet_processor::deserialise_CLI_UNK_x56(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}

void packet_processor::deserialise_CLI_GET_PARTY_DETAILS(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID", uipkt);
}

void packet_processor::deserialise_SRV_FRIENDSLIST(UIDecodedPkt *uipkt)
{
	/*
	00 58 
		00 05 
			44 00 6F 00 72 00 65 00 65 00 - Doree
		
	00 00 01 --online?
	00 07 
		4E 00 65 00 65 00 52 00 6F 00 61 00 72 00 --neeroar
	00 00 00 55 --level 85
	01 --marauder
	FF FF FF FF 00 --location. oriath
	00 08 
		53 00 74 00 61 00 6E 00 64 00 61 00 72 00 64 --standard
	00 02 00 00
	*/

	/*
	00 58 
	00 05 
		44 00 6F 00 72 00 65 00 65 00 
	00 00  01 
	00 07 
	4E 00 65 00 65 00 52 00 6F 00 61 00 72 00 
	00 00 00 55 
	01 
	00 00 00 09 00 --location. the ledge
	00 08 
	53 00 74 00 61 00 6E 00 64 00 61 00 72 00 64 
	00 02 00 00
	

	00 00 00 08 00 --submerged passage

	*/
	unsigned short namelen = ntohs(consumeUShort());
	std::wstring name = consumeWString(namelen * 2);
	uipkt->add_wstring(L"Name", name);

	//havent checked any of these yet, just getting the data in
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_word_ntoh(L"Unk3", uipkt);
	consume_add_byte(L"Unk4", uipkt);
}

void packet_processor::deserialise_SRV_PARTY_DETAILS(UIDecodedPkt *uipkt)
{
	/*
	//invited directly
	00 5A 
	00 10 50 00 --partyid
	00 00 -namelen
	01 
	01 
	02 
	00 05 
		44 00 6F 00 72 00 65 00 65 00 --doree
	02 
	00 09 
	  77 00 61 00 6E 00  67 00 6C 00 65 00 73 00 37 00 37 00 --wangles77
	00 

	//from public list
	00 5A 
	00 10 28 2D --partyid
	00 08 -namelen
		43 00 61 00 6D 00 70 00	61 00 69 00 67 00 6E 00 --campaign
	FF 
	01 
	01 
	00 09 
		50 00 75 00 72 00 65 00 62 00 72 00 61 00 76 00 6F 00 --purebravo
	02

	//also got 'friend' to go with it
	00 58 00 09 50 00 75 00 72 00 65 00 62 00 72 00
	61 00 76 00 6F 00 00 00 01 00 09 50 00 75 00 72
	00 65 00 62 00 72 00 61 00 76 00 6F 00 00 00 00
	07 01 00 00 00 07 00 00 08 53 00 74 00 61 00 6E
	00 64 00 61 00 72 00 64 00 02 00 00
   */
	consume_add_dword_ntoh(L"ID", uipkt);

	unsigned short namelen = ntohs(consumeUShort());
	uipkt->add_wstring(L"Description", consumeWString(namelen * 2));

	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);

	namelen = ntohs(consumeUShort());
	uipkt->add_wstring(L"Account", consumeWString(namelen * 2));


	consume_add_word_ntoh(L"Unk4", uipkt);
}

void packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue partyArray(rapidjson::kArrayType);

	ushort listingCount = consumeUShort();
	for (int i = 0; i < listingCount; i++)
	{
		WValue partyDetails(rapidjson::kObjectType);
		partyDetails.AddMember(L"ID", (UINT32)consume_DWORD(), allocator);

		ushort stringlen = ntohs(consumeUShort());
		wstring name = consumeWString(stringlen * 2);
		WValue nameStringVal(name.c_str(), allocator);
		partyDetails.AddMember(L"Description", nameStringVal, allocator);

		partyDetails.AddMember(L"PlayersJoined", consume_Byte(), allocator);
		partyDetails.AddMember(L"MinLevel", consume_Byte(), allocator);
		partyDetails.AddMember(L"MaxLevel", consume_Byte(), allocator);

		//0 = free for all, 1 = short
		partyDetails.AddMember(L"LootMethod", consume_Byte(), allocator);

		partyArray.PushBack(partyDetails, allocator);
	}

	uipkt->payload.AddMember(L"PartyList", partyArray, allocator);
}

void packet_processor::deserialise_SRV_CREATE_ITEM(UIDecodedPkt *uipkt)
{
	//routine outer
	consume_add_byte(L"B1", uipkt);
	consume_add_dword_ntoh(L"DW1", uipkt);

	//routine inner
	consume_add_dword_ntoh(L"DW2", uipkt);
	DWORD listsize = ntohl(consume_DWORD());
	uipkt->add_dword(L"ListSize", listsize);

	for (int i = 0; i < listsize; i++)
		consume_DWORD(); //todo


	DWORD listsize2 = consume_DWORD();
	//todo - deserialise item. high effort but shared with other funcs - deserialise_SRV_SLOT_ITEMSLIST

	byte nextbyte = consume_Byte();
	if (nextbyte)
	{
		consume_DWORD();
		consume_DWORD();
		consume_DWORD();
		consume_DWORD();
	}
}


void packet_processor::deserialise_SRV_SLOT_ITEMSLIST(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Container", uipkt);

	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
	consume_add_byte(L"Unk4", uipkt);
	consume_add_byte(L"Unk5", uipkt);
	consume_add_byte(L"Unk6", uipkt);

	DWORD itemCount = ntohl(consume_DWORD());
	uipkt->add_dword(L"Count", itemCount);

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue itemArray(rapidjson::kArrayType);
	for (int i = 0; i < itemCount; i++)
	{
		//todo - move this into own func deserialiseItem()
		WValue itemObj(rapidjson::kObjectType);

		itemObj.AddMember(L"InstanceID", WValue((UINT32)ntohl(consume_DWORD())), allocator);
		itemObj.AddMember(L"PosX", WValue(consume_Byte()), allocator);
		itemObj.AddMember(L"PosY", WValue(consume_Byte()), allocator);
		ushort modsLen = ntohs(consumeUShort());
		DWORD hash = consume_DWORD();
		itemObj.AddMember(L"ItemHash", WValue((UINT32)hash), allocator);
		//skip item data for now, apart from the hash so we at least know item type
		consume_blob(modsLen - sizeof(hash));


		itemArray.PushBack(itemObj, allocator);
	}
	uipkt->payload.AddMember(L"ItemList", itemArray, allocator);

	consume_add_word_ntoh(L"FinalUnk", uipkt);

}


void packet_processor::deserialise_UNK_MESSAGE_0x70(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Arg", uipkt);
}

void packet_processor::deserialise_UNK_MESSAGE_0x73(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Data1", uipkt); //todo - this is not fixed at 4, its just what ive seen it as
	ushort strlen1 = ntohs(consumeUShort());
	std::cout << " 73 s1 len: " << std::dec << (strlen1*2) << ", rem: "<<remainingDecrypted<< std::endl;
	uipkt->add_wstring(L"String1",consumeWString(strlen1 * 2));
	ushort strlen2 = ntohs(consumeUShort());
	std::cout << " 73 s2 len: " << std::dec << (strlen2*2) << ", rem: " << remainingDecrypted << std::endl;
	uipkt->add_wstring(L"String2", consumeWString(strlen2 * 2));
}

void packet_processor::deserialise_CLI_SET_STATUS_MESSAGE(UIDecodedPkt *uipkt)
{
	unsigned short statuslen = ntohs(consumeUShort());
	std::wstring status = consumeWString(statuslen * 2);
	uipkt->add_wstring(L"StatusText", status);
}

void packet_processor::deserialise_CLI_SWAPPED_WEAPONS(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Byte", uipkt);
}

void packet_processor::deserialise_CLI_SKILLPANE_ACTION(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"State", uipkt);
}

void packet_processor::deserialise_SRV_SKILLPANE_DATA(UIDecodedPkt *uipkt)
{
	abandon_processing(); //todo
}

void packet_processor::deserialise_SRV_UNK_0x92(UIDecodedPkt *uipkt)
{
	//gets a short count
	ushort count = consumeUShort();
	uipkt->add_word(L"Count", count);
	//loop -> 4 strings, other stuff. easier to wait for a sample with >0 count
	if (count > 0)
		abandon_processing();
}


void packet_processor::deserialise_CLI_MICROTRANSACTION_SHOP_ACTION(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"State", uipkt);
}

void packet_processor::deserialise_SRV_MICROTRANSACTION_SHOP_DETAILS(UIDecodedPkt *uipkt)
{
	//not looked at what these actually are. one will be transaction credits
	consume_add_byte(L"State", uipkt);
	consume_add_dword_ntoh(L"State", uipkt);
}

void packet_processor::deserialise_SRV_UNK_A3(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"fff", uipkt);
	consume_add_dword_ntoh(L"fff3", uipkt);
}

void packet_processor::deserialise_CLI_PACKET_EXIT(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"State", uipkt);
}


void packet_processor::deserialise_CLI_PACKET_EXIT_2(UIDecodedPkt *)
{
	abandon_processing();//todo
}
void packet_processor::deserialise_CLI_DUEL_CHALLENGE(UIDecodedPkt *)
{
	abandon_processing();//todo
}
void packet_processor::deserialise_SRV_DUEL_RESPONSE(UIDecodedPkt *)
{

	abandon_processing();//todo
}
void packet_processor::deserialise_SRV_DUEL_CHALLENGE(UIDecodedPkt *)
{

	abandon_processing();//todo
}

void packet_processor::deserialise_CLI_UNK_0xC7(UIDecodedPkt *uipkt)
{

	abandon_processing();//no data
}

void packet_processor::deserialise_SRV_UNK_0xD5(UIDecodedPkt *uipkt)
{

	DWORD sizeCount = consume_DWORD();
	
	uipkt->add_dword(L"SizeCount", sizeCount);
	if (sizeCount != 0)
		abandon_processing();
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

void packet_processor::deserialise_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt *uipkt)
{
	abandon_processing();
}

void packet_processor::deserialise_SRV_CHAT_CHANNEL_ID(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"ChannelID", uipkt);
	consume_add_byte(L"Type", uipkt);
	consume_add_byte(L"Language", uipkt);
}

void packet_processor::deserialise_CLI_GUILD_CREATE(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_UNK_0xE6(UIDecodedPkt *uipkt)
{
	byte list1Len = consume_Byte();
	consume_blob(list1Len * 2);
	byte list2Len = consume_Byte();
	consume_blob(list2Len * 2);
	byte list3Len = consume_Byte();
	consume_blob(list3Len * 2);

	byte list4Len = consume_Byte();
	for (int i = 0; i < list4Len; i++)
	{
		consumeUShort();
		consume_Byte();
	}

	byte list5Len = consume_Byte();
	for (int i = 0; i < list5Len; i++)
	{
		consumeUShort();
		consume_Byte();
	}

	//aaaand here it gets more complicated. 
	byte list6Len = consume_Byte();
	for (int i = 0; i < list6Len; i++)
	{
		//items. lots of items
	}


	uipkt->add_byte(L"List1Len", list1Len);
	uipkt->add_byte(L"List2Len", list2Len);
	uipkt->add_byte(L"List3Len", list3Len);
	uipkt->add_byte(L"List4Len", list4Len);
	uipkt->add_byte(L"List5Len", list5Len);
	uipkt->add_byte(L"List6Len", list6Len);

	consumeUShort();
	consume_Byte();
}

void packet_processor::deserialise_SRV_ITEM_REMOVED(UIDecodedPkt * uipkt)
{
	consume_add_dword_ntoh(L"ItemID", uipkt);
	consume_add_dword_ntoh(L"Receiver", uipkt);
	consume_add_word_ntoh(L"unk2", uipkt);
}


void packet_processor::deserialise_SRV_MOBILE_START_SKILL(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);


	byte modifier = consume_Byte();
	uipkt->add_byte(L"Modifier", modifier);

	if (modifier & 0x80)
	{
		uipkt->add_dword(L"TargID", consume_DWORD());
	}

	//shouldnt actually do this - the 8 (high bit) is a signal to read another byte. 
	//will wreck things when we get coords that under- or over- flow
	//worry when it happens
	unsigned short startCoord1 = consumeUShort() - 0x8000;
	uipkt->add_word(L"StartCoord1", startCoord1);
	unsigned short startCoord2 = consumeUShort() - 0x8000;
	uipkt->add_word(L"StartCoord2", startCoord2);
	unsigned short targCoord1 = consumeUShort() - 0x8000;
	uipkt->add_word(L"TargCoord1", targCoord1);
	unsigned short targCoord2 = consumeUShort() - 0x8000;
	uipkt->add_word(L"TargCoord2", targCoord2);

	consume_add_word_ntoh(L"SkillID", uipkt);
	consume_add_word_ntoh(L"PkCount", uipkt); //0x1408EF03D
}

//possibly confirm hit? or do animation?
void packet_processor::deserialise_SRV_MOBILE_FINISH_SKILL(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);
}

void packet_processor::deserialise_SRV_MOBILE_UNK_0xee(UIDecodedPkt *uipkt)
{
	/*
	00 EE  
	00 00 01 12    00 00 01 12     50 02  10 byte objid
	81 CD     00    00	    00 00 01 AF 
	42 01   00     60 
	
	00 EB 00 00 01 12 00 00
		01 12 50 02
	*/
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	//2_1_1_4
	consume_add_word_ntoh(L"S1", uipkt);
	consume_add_byte(L"B1", uipkt);
	consume_add_byte(L"B2", uipkt);
	consume_add_dword_ntoh(L"D1", uipkt);

	ushort skillid = consumeUShort();
	uipkt->add_word(L"SkillID", skillid);  //skill id?

	ushort zerobyte = consume_Byte();
	uipkt->add_byte(L"ZeroByte", zerobyte);

	if (skillid & 0x400) //if XX4XX
	{
		ushort skillword2 = consumeUShort();
		uipkt->add_word(L"SkillBit400", skillword2);
	}
	if (skillid >= 0x4000 && skillid < 0x8000)
	{
		ushort skillbyte2 = consume_Byte();
		uipkt->add_byte(L"SkillByte4k8k", skillbyte2);
	}


}

void packet_processor::deserialise_SRV_MOBILE_UNK_0xef(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);


	//2_1_1_4 - SBBD
	consume_add_word_ntoh(L"S1", uipkt);
	consume_add_byte(L"B1", uipkt);
	consume_add_byte(L"B2", uipkt);
	consume_add_dword_ntoh(L"D1", uipkt);

	consume_add_byte(L"UnkEndB", uipkt);
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

	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_dword_ntoh(L"NewValue", uipkt);
	consume_add_dword_ntoh(L"Unk3", uipkt);
	consume_add_byte(L"Stat", uipkt);
	consume_add_byte(L"Unk4", uipkt); //possible more stats here

}

void packet_processor::deserialise_SRV_STAT_CHANGED(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	//same routine in 0x0f - merge into a list getter func
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue pairlist(rapidjson::kArrayType);
	DWORD paircount = customSizeByteGet();
	for (int i = 0; i < paircount; i++)
	{
		WValue pair(rapidjson::kArrayType);

		DWORD first = customSizeByteGet();
		pair.PushBack((UINT32)first, allocator);

		INT32 second = customSizeByteGet_signed();
		pair.PushBack((INT32)second, allocator);

		pairlist.PushBack(pair, allocator);
	}
	uipkt->payload.AddMember(L"PairList", pairlist, allocator);
}

void packet_processor::deserialise_SRV_UNK_0xf2(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);


	consume_add_dword_ntoh(L"DW1", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0xf3(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);


	consume_add_dword_ntoh(L"DW1", uipkt);
	consume_add_dword_ntoh(L"DW2", uipkt);
	consume_add_dword_ntoh(L"DW3", uipkt);
	consume_add_dword_ntoh(L"DW4", uipkt);

}

void packet_processor::deserialise_SRV_START_EFFECT(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word_ntoh(L"BuffID", uipkt);
	consume_add_word_ntoh(L"BuffDefinitionsRow", uipkt);
	consume_add_dword_ntoh(L"UnkDWord3", uipkt);
	consume_add_word_ntoh(L"PotionSlot", uipkt);
	ushort controlByte = consume_Byte();
	uipkt->add_byte(L"ControlByte", controlByte);

	if (controlByte & 0x1)
	{
		consume_add_byte(L"cb_01_1", uipkt);
		consume_add_word_ntoh(L"cb_01_2", uipkt);
		consume_add_byte(L"cb_01_3", uipkt);
	}

	if (controlByte & 0x2)
	{
		consume_add_dword_ntoh(L"cb_02_1", uipkt);
	}

	if (controlByte & 0x4)
	{
		consume_add_word_ntoh(L"cb_04_1", uipkt);
	}

	if (controlByte & 0x8)
	{
		consume_add_word_ntoh(L"cb_08_1", uipkt);
		consume_add_word_ntoh(L"cb_08_2", uipkt);
	}

	if (controlByte & 0x10)
	{
		consume_add_word_ntoh(L"cb_10_1", uipkt);
	}

	if (controlByte & 0x20)
	{
		consume_add_byte(L"cb_20_1", uipkt);
	}

	//there is a list of dwords to get here too
}

void packet_processor::deserialise_SRV_END_EFFECT(UIDecodedPkt *uipkt) {
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word_ntoh(L"BuffID", uipkt);
}


void packet_processor::deserialise_CLI_REQUEST_PLAYERID(UIDecodedPkt *)
{
	//nothing expected
}


void packet_processor::deserialise_SRV_NOTIFY_PLAYERID(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);
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
		consume_DWORD(); //index?

		consume_DWORD(); //hash?

		consume_DWORD();

		consume_DWORD();
		consume_DWORD();
	}

}

void packet_processor::deserialise_SRV_UNKNOWN_0x118(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Index", uipkt);
	consume_add_dword_ntoh(L"Hash", uipkt);
	consume_add_dword_ntoh(L"Unk1", uipkt);
	//todo - 8 byte data type. we have the technology.
	consume_add_dword_ntoh(L"Unk2a", uipkt);
	consume_add_dword_ntoh(L"Unk2b", uipkt);
}



void packet_processor::deserialise_CLI_OPTOUT_TUTORIALS(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_SRV_HEARTBEAT(UIDecodedPkt *uipkt)
{
	//nothing
}

void packet_processor::SRV_ADD_OBJ_decode_character(UIDecodedPkt *uipkt, size_t objBlobDataLen)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	//rewind back to start of blob
	rewind_buffer(objBlobDataLen);

	byte listsize1 = consume_Byte();
	WValue list1(rapidjson::kArrayType);
	for (int i = 0; i < listsize1; i++)
	{
		DWORD unkposshash1 = consume_DWORD(); //hash? 0xb350ac3a
		DWORD unknum2 = consume_DWORD();  //11

		WValue pair(rapidjson::kArrayType);
		pair.PushBack((UINT32)unkposshash1, allocator);
		pair.PushBack((UINT32)unknum2, allocator);
		list1.PushBack(pair, allocator);
	}
	uipkt->payload.AddMember(L"List1", list1, allocator);

	uipkt->add_dword(L"Coord1", consume_DWORD());
	uipkt->add_dword(L"Coord2", consume_DWORD());
	consume_add_dword_ntoh(L"UnkDword1", uipkt);

	consume_add_byte(L"UnkByte1", uipkt);

	byte controlByte1 = consume_Byte();
	uipkt->add_byte(L"ControlByte1", controlByte1);

	if (controlByte1 & 0x20)
	{
		consume_add_dword_ntoh(L"Unk_b20_1", uipkt);
		consume_add_dword_ntoh(L"Unk_b20_2", uipkt);
		consume_add_dword_ntoh(L"Unk_b20_3", uipkt);
	}

	if (controlByte1 & 0x4)
	{
		consume_add_dword_ntoh(L"Unk_b4_1", uipkt);
		consume_add_dword_ntoh(L"Unk_b4_2", uipkt);
	}

	if (controlByte1 & 0x40)
	{
		consume_add_dword_ntoh(L"Unk_b40_1", uipkt);
		consume_add_dword_ntoh(L"Unk_b40_2", uipkt);
	}

	//get objthing.  0x14078c790
	//one byte
	//if 1, 4, 8

	//get objthing 2
	// byte * 3


	WValue statlist(rapidjson::kArrayType);
	byte statcount = customSizeByteGet();
	for (int i = 0; i < statcount; i++)
	{
		DWORD first = customSizeByteGet();
		INT32 second = customSizeByteGet_signed();

		WValue pair(rapidjson::kArrayType);
		pair.PushBack((UINT32)first, allocator);
		pair.PushBack((INT32)second, allocator);
		statlist.PushBack(pair, allocator);
	}
	uipkt->payload.AddMember(L"StatList", statlist, allocator);

	uipkt->add_dword(L"CurrentHealth", (consume_DWORD()));
	uipkt->add_dword(L"ReservedHealth", (consume_DWORD()));
	uipkt->add_byte(L"ReservedPercentHealth", consume_Byte());
	uipkt->add_dword(L"HealthUnk", (consume_DWORD()));

	uipkt->add_dword(L"CurrentMana", (consume_DWORD()));
	uipkt->add_dword(L"ReservedMana", (consume_DWORD()));
	uipkt->add_byte(L"ReservedPercentMana", consume_Byte());
	uipkt->add_dword(L"ManaUnk", (consume_DWORD()));

	uipkt->add_dword(L"CurrentShield", (consume_DWORD()));
	uipkt->add_dword(L"ShieldUnk1", (consume_DWORD()));
	uipkt->add_byte(L"ShieldUnk2", consume_Byte());
	uipkt->add_dword(L"ShieldUnk3", (consume_DWORD()));

	consume_add_dword_ntoh(L"UnkDWORDEndHMS", uipkt);

	uipkt->add_byte(L"UnkByte_PreBuffs", consume_Byte());

	WValue bufflist(rapidjson::kArrayType);
	ushort buffCount = consumeUShort();

	size_t blobRemaining = objBlobDataLen - (restorePoint.savedIndex - decryptedIndex);
	if ((buffCount * 27) > blobRemaining) {
		errorFlag = eErrUnderflow;
	}

	for (int i = 0; i < buffCount; i++)
	{
		WValue buffObj(rapidjson::kObjectType);
		buffObj.AddMember(L"BuffID", consumeUShort(), allocator);
		buffObj.AddMember(L"BuffDefinitionsRow", consumeUShort(), allocator);
		buffObj.AddMember(L"BuffVisualsRow", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkDword1", (UINT32)consume_DWORD(), allocator);
		buffObj.AddMember(L"UnkShort2", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkDword3", (UINT32)consume_DWORD(), allocator);
		buffObj.AddMember(L"UnkShort4", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkShort5", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkShort6", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkShort7", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkShort8", consumeUShort(), allocator);
		buffObj.AddMember(L"UnkByte9", consume_Byte(), allocator);
		bufflist.PushBack(buffObj, allocator);
	}
	uipkt->payload.AddMember(L"BuffList", bufflist, allocator);

	ushort nameLen = ntohs(consumeUShort());

	consume_blob(3); //?????

	blobRemaining = objBlobDataLen - (restorePoint.savedIndex - decryptedIndex);
	if (nameLen > blobRemaining) {
		errorFlag = eErrUnderflow;
	}
	std::wstring msg = consumeWString(nameLen * 2);
	uipkt->add_wstring(L"Name", msg);

	//C: Restore index to start of next packet
	restore_buffer();
}

void packet_processor::deserialise_SRV_ADD_OBJECT(UIDecodedPkt *uipkt)
{
	

	//10 bytes all retrieved at once
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	DWORD objMurmurHash = ntohl(consume_DWORD());
	uipkt->add_dword(L"objHash", objMurmurHash);

	unsigned short objBlobDataLen = ntohs(consumeUShort());
	uipkt->add_word(L"DataLen", objBlobDataLen);



	/*
	add_obj is easy to deserialise but difficult to parse
	deserialise it cleanly and rewind the index to attempt parsing
	even if we mess it up we can restore index to the start of the 
	next message without ruining things
	*/
	vector <byte> payload;
	consume_blob(objBlobDataLen, payload);

	if (errorFlag != eNoErr) return;

	std::string hashResult;
	std::string hashCategory;
	ggpk->lookup_hash(objMurmurHash, hashResult, hashCategory);

	if (hashCategory == "Character")
		SRV_ADD_OBJ_decode_character(uipkt, objBlobDataLen);
	//object
	//npc
	
}

//same as 0x135 but no hash DWORD
void packet_processor::deserialise_SRV_UPDATE_OBJECT(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);
	
	unsigned short dataLen = ntohs(consumeUShort());
	//byte arrayIndex = consume_Byte();
	//ushort controlBits = consumeUShort();
	consume_blob(dataLen); //todo
}

void packet_processor::deserialise_SRV_IDNOTIFY_0x137(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

}