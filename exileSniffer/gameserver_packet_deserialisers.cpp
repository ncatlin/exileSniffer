/*
These member functions attempt to reassemble the raw packet bytes 
into meaningful data as the game client/server would interpret it
*/
#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"


void packet_processor::init_gamePkt_deserialisers()
{
	gamePktDeserialisers[SRV_PKT_ENCAPSULATED] = (deserialiser)&packet_processor::deserialise_SRV_PKT_ENCAPSULATED;
	gamePktDeserialisers[CLI_CHAT_MSG_ITEMS] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG_ITEMS;
	//7
	gamePktDeserialisers[CLI_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG;
	gamePktDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	gamePktDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	gamePktDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	gamePktDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;
	gamePktDeserialisers[CLI_HNC] = (deserialiser)&packet_processor::deserialise_CLI_HNC;
	gamePktDeserialisers[SRV_HNC] = (deserialiser)&packet_processor::deserialise_SRV_HNC;
	gamePktDeserialisers[SRV_AREA_INFO] = (deserialiser)&packet_processor::deserialise_SRV_AREA_INFO;
	//10?
	//11?
	gamePktDeserialisers[SRV_PRELOAD_MONSTER_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST;
	gamePktDeserialisers[SRV_UNK_0x13] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x13;
	gamePktDeserialisers[SRV_ITEMS_LIST] = (deserialiser)&packet_processor::deserialise_SRV_ITEMS_LIST;
	gamePktDeserialisers[CLI_CLICKED_GROUND_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM;
	gamePktDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;
	gamePktDeserialisers[SRV_TRANSFER_INSTANCE] = (deserialiser)&packet_processor::deserialise_SRV_TRANSFER_INSTANCE;
	gamePktDeserialisers[SRV_INSTANCE_SERVER_DATA] = (deserialiser)&packet_processor::deserialise_SRV_INSTANCE_SERVER_DATA;
	gamePktDeserialisers[CLI_PICKUP_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PICKUP_ITEM;
	gamePktDeserialisers[CLI_DROP_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_DROP_ITEM;
	gamePktDeserialisers[CLI_PLACE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PLACE_ITEM;
	//1c
	gamePktDeserialisers[CLI_REMOVE_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_REMOVE_SOCKET;
	gamePktDeserialisers[CLI_INSERT_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_INSERT_SOCKET;
	gamePktDeserialisers[CLI_LEVEL_SKILLGEM] = (deserialiser)&packet_processor::deserialise_CLI_LEVEL_SKILLGEM;
	gamePktDeserialisers[SRV_UNK_0x20] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x20;
	gamePktDeserialisers[CLI_SKILLPOINT_CHANGE] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPOINT_CHANGE;
	//22
	//23
	gamePktDeserialisers[CLI_CHOSE_ASCENDANCY] = (deserialiser)&packet_processor::deserialise_CLI_CHOSE_ASCENDANCY;
	//25
	//26
	//27
	//28
	//29
	gamePktDeserialisers[CLI_MERGE_STACK] = (deserialiser)&packet_processor::deserialise_CLI_MERGE_STACK;
	gamePktDeserialisers[CLI_CANCEL_BUF] = (deserialiser)&packet_processor::deserialise_CLI_CANCEL_BUF;
	gamePktDeserialisers[SRV_UNK_0x2c] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x2c;
	gamePktDeserialisers[CLI_SELECT_MAPTRAVEL] = (deserialiser)&packet_processor::deserialise_CLI_SELECT_MAPTRAVEL;
	gamePktDeserialisers[CLI_SET_HOTBARSKILL] = (deserialiser)&packet_processor::deserialise_CLI_SET_HOTBARSKILL;
	gamePktDeserialisers[SRV_SKILL_SLOTS_LIST] = (deserialiser)&packet_processor::deserialise_SRV_SKILL_SLOTS_LIST;
	gamePktDeserialisers[CLI_REVIVE_CHOICE] = (deserialiser)&packet_processor::deserialise_CLI_REVIVE_CHOICE;
	gamePktDeserialisers[SRV_YOU_DIED] = (deserialiser)&packet_processor::deserialise_SRV_YOU_DIED;
	gamePktDeserialisers[CLI_ACTIVATE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_ACTIVATE_ITEM;
	//33
	//34
	//35
	//36
	gamePktDeserialisers[CLI_USE_BELT_SLOT] = (deserialiser)&packet_processor::deserialise_CLI_USE_BELT_SLOT;
	gamePktDeserialisers[CLI_USE_ITEM_ON_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_USE_ITEM_ON_ITEM;
	//39
	//3a
	//3b
	//3c
	//3d
	//3e
	gamePktDeserialisers[SRV_OPEN_UI_PANE] = (deserialiser)&packet_processor::deserialise_SRV_OPEN_UI_PANE;
	gamePktDeserialisers[CLI_SPLIT_STACK] = (deserialiser)&packet_processor::deserialise_CLI_SPLIT_STACK;
	gamePktDeserialisers[CLI_UNK_0x41] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0x41;
	//42
	//43
	//44
	//45
	gamePktDeserialisers[CLI_SELECT_NPC_DIALOG] = (deserialiser)&packet_processor::deserialise_CLI_SELECT_NPC_DIALOG;
	gamePktDeserialisers[SRV_SHOW_NPC_DIALOG] = (deserialiser)&packet_processor::deserialise_SRV_SHOW_NPC_DIALOG;
	gamePktDeserialisers[CLI_CLOSE_NPC_DIALOG] = (deserialiser)&packet_processor::deserialise_CLI_CLOSE_NPC_DIALOG;
	//49
	//4a
	//4b
	//4c
	//4d
	//4e
	gamePktDeserialisers[SRV_LIST_PORTALS] = (deserialiser)&packet_processor::deserialise_SRV_LIST_PORTALS;
	gamePktDeserialisers[CLI_SEND_PARTY_INVITE] = (deserialiser)&packet_processor::deserialise_CLI_SEND_PARTY_INVITE;
	//51
	gamePktDeserialisers[CLI_TRY_JOIN_PARTY] = (deserialiser)&packet_processor::deserialise_CLI_TRY_JOIN_PARTY;
	gamePktDeserialisers[CLI_DISBAND_PUBLIC_PARTY] = (deserialiser)&packet_processor::deserialise_CLI_DISBAND_PUBLIC_PARTY;
	//54
	gamePktDeserialisers[CLI_CREATE_PUBLICPARTY] = (deserialiser)&packet_processor::deserialise_CLI_CREATE_PUBLICPARTY;
	gamePktDeserialisers[CLI_UNK_x56] = (deserialiser)&packet_processor::deserialise_CLI_UNK_x56;
	gamePktDeserialisers[CLI_GET_PARTY_DETAILS] = (deserialiser)&packet_processor::deserialise_CLI_GET_PARTY_DETAILS;
	gamePktDeserialisers[SRV_FRIENDSLIST] = (deserialiser)&packet_processor::deserialise_SRV_FRIENDSLIST;
	//59
	gamePktDeserialisers[SRV_PARTY_DETAILS] = (deserialiser)&packet_processor::deserialise_SRV_PARTY_DETAILS;
	gamePktDeserialisers[SRV_PARTY_ENDED] = (deserialiser)&packet_processor::deserialise_SRV_PARTY_ENDED;
	//5c
	gamePktDeserialisers[CLI_REQUEST_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES;
	gamePktDeserialisers[SRV_PUBLIC_PARTY_LIST] = (deserialiser)&packet_processor::deserialise_SRV_PUBLIC_PARTY_LIST;
	//5f
	//60
	//61
	//62
	gamePktDeserialisers[CLI_MOVE_ITEM_PANE] = (deserialiser)&packet_processor::deserialise_CLI_MOVE_ITEM_PANE;
	//64
	gamePktDeserialisers[CLI_CONFIRM_SELL] = (deserialiser)&packet_processor::deserialise_CLI_CONFIRM_SELL;
	//66
	gamePktDeserialisers[SRV_UNK_0x67] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x67;
	gamePktDeserialisers[SRV_UNK_0x68] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x68;
	//69
	//6a
	//6b
	gamePktDeserialisers[SRV_UNK_0x6c] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x6c;
	gamePktDeserialisers[SRV_CREATE_ITEM] = (deserialiser)&packet_processor::deserialise_SRV_CREATE_ITEM;
	gamePktDeserialisers[SRV_SLOT_ITEMSLIST] = (deserialiser)&packet_processor::deserialise_SRV_SLOT_ITEMSLIST;
	gamePktDeserialisers[SRV_INVENTORY_SET_REMOVE] = (deserialiser)&packet_processor::deserialise_SRV_INVENTORY_SET_REMOVE;
	gamePktDeserialisers[SRV_UNK_0x70] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x70;
	gamePktDeserialisers[CLI_SELECT_STASHTAB] = (deserialiser)&packet_processor::deserialise_CLI_SELECT_STASHTAB;
	gamePktDeserialisers[SRV_STASHTAB_DATA] = (deserialiser)&packet_processor::deserialise_SRV_STASHTAB_DATA;
	gamePktDeserialisers[SRV_UNK_0x73] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0x73;
	gamePktDeserialisers[CLI_SET_STATUS_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_SET_STATUS_MESSAGE;
	gamePktDeserialisers[SRV_MOVE_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_MOVE_OBJECT;
	//76
	//77
	//78
	//79
	//7a
	//7b
	gamePktDeserialisers[CLI_ACTIVATE_MAP] = (deserialiser)&packet_processor::deserialise_CLI_ACTIVATE_MAP;
	//7d
	//7e
	gamePktDeserialisers[CLI_SWAPPED_WEAPONS] = (deserialiser)&packet_processor::deserialise_CLI_SWAPPED_WEAPONS;
	//80
	gamePktDeserialisers[SRV_ADJUST_LIGHTING] = (deserialiser)&packet_processor::deserialise_SRV_ADJUST_LIGHTING;
	//82
	//83
	//84
	//85
	//86
	//87
	//88
	//89
	//8a
	//8b
	//8c
	gamePktDeserialisers[SRV_INVENTORY_FULL] = (deserialiser)&packet_processor::deserialise_SRV_INVENTORY_FULL;
	//8e
	//define 0x8f seen when leaving duel queue
	//define 0x90 seen when leaving duel queue
	gamePktDeserialisers[SRV_PVP_MATCHLIST] = (deserialiser)&packet_processor::deserialise_SRV_PVP_MATCHLIST;
	gamePktDeserialisers[SRV_EVENTSLIST] = (deserialiser)&packet_processor::deserialise_SRV_EVENTSLIST;
	//93
	//94
	//95
	//96
	//97
	gamePktDeserialisers[CLI_SKILLPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPANE_ACTION;
	gamePktDeserialisers[SRV_ACHIEVEMENT_1] = (deserialiser)&packet_processor::deserialise_SRV_ACHIEVEMENT_1;
	gamePktDeserialisers[SRV_ACHIEVEMENT_2] = (deserialiser)&packet_processor::deserialise_SRV_ACHIEVEMENT_2;
	gamePktDeserialisers[SRV_SKILLPANE_DATA] = (deserialiser)&packet_processor::deserialise_SRV_SKILLPANE_DATA;
	gamePktDeserialisers[SRV_UNK_POSITION_LIST] = (deserialiser)&packet_processor::deserialise_SRV_UNK_POSITION_LIST;
	//9d
	//9e
	gamePktDeserialisers[CLI_MICROTRANSACTION_SHOP_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_MICROTRANSACTION_SHOP_ACTION;
	//a0
	gamePktDeserialisers[SRV_MICROTRANSACTION_SHOP_DETAILS] = (deserialiser)&packet_processor::deserialise_SRV_MICROTRANSACTION_SHOP_DETAILS;
	//a2
	gamePktDeserialisers[CLI_UNK_A3] = (deserialiser)&packet_processor::deserialise_CLI_UNK_A3;
	gamePktDeserialisers[SRV_CHAT_CHANNEL_ID] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_CHANNEL_ID;
	gamePktDeserialisers[SRV_UNK_A5] = (deserialiser)&packet_processor::deserialise_SRV_UNK_A5;
	//a6
	//a7
	//a8
	//a9
	//aa
	//ab
	//ac
	gamePktDeserialisers[CLI_GUILD_CREATE] = (deserialiser)&packet_processor::deserialise_CLI_GUILD_CREATE;
	//ae
	//af
	//b0
	//b1
	//b2
	//b3
	//b4
	gamePktDeserialisers[SRV_GUILD_MEMBER_LIST] = (deserialiser)&packet_processor::deserialise_SRV_GUILD_MEMBER_LIST;
	//b6
	//b7
	//b8
	//b9
	//ba
	//bc
	//bd
	//be
	//bf
	gamePktDeserialisers[CLI_EXIT_TO_CHARSCREEN] = (deserialiser)&packet_processor::deserialise_CLI_EXIT_TO_CHARSCREEN;
	gamePktDeserialisers[SRV_LOGINSRV_CRYPT] = (deserialiser)&packet_processor::deserialise_SRV_LOGINSRV_CRYPT;
	gamePktDeserialisers[CLI_DUEL_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_DUEL_CHALLENGE;
	gamePktDeserialisers[SRV_DUEL_RESPONSE] = (deserialiser)&packet_processor::deserialise_SRV_DUEL_RESPONSE;
	gamePktDeserialisers[SRV_DUEL_CHALLENGE] = (deserialiser)&packet_processor::deserialise_SRV_DUEL_CHALLENGE;
	//c5
	gamePktDeserialisers[CLI_UNK_0xC6] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0xC6;
	gamePktDeserialisers[CLI_UNK_0xC7] = (deserialiser)&packet_processor::deserialise_CLI_UNK_0xC7;
	//c8
	//c9
	gamePktDeserialisers[SRV_UNK_0xCA] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xCA;
	//cb
	//cd
	//CLI_VISIT_HIDEOUT
	//cf
	//d0
	//d1
	//d2
	//d3
	//d4
	gamePktDeserialisers[SRV_EVENTSLIST_2] = (deserialiser)&packet_processor::deserialise_SRV_EVENTSLIST_2;
	//d6
	//d7
	gamePktDeserialisers[CLI_USED_SKILL] = (deserialiser)&packet_processor::deserialise_CLI_USED_SKILL;
	gamePktDeserialisers[CLI_CLICK_OBJ] = (deserialiser)&packet_processor::deserialise_CLI_CLICK_OBJ;
	gamePktDeserialisers[CLI_MOUSE_HELD] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_HELD;
	//db
	gamePktDeserialisers[CLI_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
	//dd
	//de
	//df
	gamePktDeserialisers[CLI_OPEN_WORLD_SCREEN] = (deserialiser)&packet_processor::deserialise_CLI_OPEN_WORLD_SCREEN;
	//e1
	//e2
	//e3
	gamePktDeserialisers[SRV_UNK_0xE4] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xE4;
	//e5
	gamePktDeserialisers[SRV_UNK_0xE6] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xE6;
	//e7
	//e8
	gamePktDeserialisers[SRV_OBJ_REMOVED] = (deserialiser)&packet_processor::deserialise_SRV_OBJ_REMOVED;
	gamePktDeserialisers[SRV_MOBILE_START_SKILL] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_START_SKILL;
	gamePktDeserialisers[SRV_MOBILE_FINISH_SKILL] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_FINISH_SKILL;
	gamePktDeserialisers[SRV_MOVE_CHANNELLED] = (deserialiser)&packet_processor::deserialise_SRV_MOVE_CHANNELLED;
	gamePktDeserialisers[SRV_END_CHANNELLED] = (deserialiser)&packet_processor::deserialise_SRV_END_CHANNELLED;
	gamePktDeserialisers[SRV_MOBILE_UNK_0xee] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UNK_0xee;
	gamePktDeserialisers[SRV_MOBILE_UNK_0xef] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UNK_0xef;
	gamePktDeserialisers[SRV_MOBILE_UPDATE_HMS] = (deserialiser)&packet_processor::deserialise_SRV_MOBILE_UPDATE_HMS;
	gamePktDeserialisers[SRV_STAT_CHANGED] = (deserialiser)&packet_processor::deserialise_SRV_STAT_CHANGED;
	gamePktDeserialisers[SRV_UNK_0xf2] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf2;
	gamePktDeserialisers[SRV_UNK_0xf3] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf3;
	//f4
	gamePktDeserialisers[SRV_UNK_0xf5] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf5;
	//f6
	gamePktDeserialisers[SRV_UNK_0xf7] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf7;	
	gamePktDeserialisers[SRV_UNK_0xf8] = (deserialiser)&packet_processor::deserialise_SRV_UNK_0xf8;
	//f9
	gamePktDeserialisers[SRV_START_EFFECT] = (deserialiser)&packet_processor::deserialise_SRV_START_EFFECT;
	gamePktDeserialisers[SRV_END_EFFECT] = (deserialiser)&packet_processor::deserialise_SRV_END_EFFECT;
	//fc
	//fd
	//fe
	gamePktDeserialisers[SRV_EVENT_TRIGGERED] = (deserialiser)&packet_processor::deserialise_SRV_EVENT_TRIGGERED;
	//100
	//101
	//102
	//103
	//104
	//105
	gamePktDeserialisers[SRV_UNKNOWN_0x106] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x106;
	//107
	gamePktDeserialisers[SRV_UNKNOWN_0x108] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x108;
	//109
	//10a
	//10b
	//10c
	//10d
	gamePktDeserialisers[CLI_FINISHED_LOADING] = (deserialiser)&packet_processor::deserialise_CLI_FINISHED_LOADING;
	gamePktDeserialisers[SRV_NOTIFY_PLAYERID] = (deserialiser)&packet_processor::deserialise_SRV_NOTIFY_PLAYERID;
	//0x110 - player pressed add new stash tab +?
	gamePktDeserialisers[SRV_UNKNOWN_0x111] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x111;
	//112
	//113
	//114
	//115
	//116
	//117
	gamePktDeserialisers[SRV_UNKNOWN_0x118] = (deserialiser)&packet_processor::deserialise_SRV_UNKNOWN_0x118;
	//119
	//11a
	//11b
	gamePktDeserialisers[CLI_OPTOUT_TUTORIALS] = (deserialiser)&packet_processor::deserialise_CLI_OPTOUT_TUTORIALS;
	//11d
	//11e
	//11f
	//120
	//121
	//122
	//123
	//124
	//125
	//126
	gamePktDeserialisers[SRV_BESTIARY_CAPTIVES] = (deserialiser)&packet_processor::deserialise_SRV_BESTIARY_CAPTIVES;
	//128
	//129
	gamePktDeserialisers[CLI_OPEN_BESTIARY] = (deserialiser)&packet_processor::deserialise_CLI_OPEN_BESTIARY;
	//12b
	gamePktDeserialisers[SRV_BESTIARY_UNLOCKED_LIST] = (deserialiser)&packet_processor::deserialise_SRV_BESTIARY_UNLOCKED_LIST;
	//12d
	//12e
	gamePktDeserialisers[SRV_SHOW_ENTERING_MSG] = (deserialiser)&packet_processor::deserialise_SRV_SHOW_ENTERING_MSG;
	//130
	//131
	gamePktDeserialisers[SRV_HEARTBEAT] = (deserialiser)&packet_processor::deserialise_SRV_HEARTBEAT;
	//133
	//134
	gamePktDeserialisers[SRV_ADD_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_ADD_OBJECT;
	gamePktDeserialisers[SRV_UPDATE_OBJECT] = (deserialiser)&packet_processor::deserialise_SRV_UPDATE_OBJECT;
	gamePktDeserialisers[SRV_IDNOTIFY_0x137] = (deserialiser)&packet_processor::deserialise_SRV_IDNOTIFY_0x137;
	//138
	//139
}

/*
this is deserialised within the processing loop as part of stream crypt resynchronisation
the packet within is then deserialised and actioned
this function only here for completeness - it should not be used!
*/
void packet_processor::deserialise_SRV_PKT_ENCAPSULATED(UIDecodedPkt *uipkt)
{
	//ignored - see above
}



void packet_processor::deserialise_CLI_CHAT_MSG_ITEMS(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Index", uipkt);
	consume_add_dword_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"ItemID", uipkt);
	consume_add_byte(L"EndByte", uipkt);
}

void packet_processor::deserialise_CLI_CHAT_MSG(UIDecodedPkt *uipkt)
{
	ushort msgLenWords = ntohs(consume_WORD());
	std::wstring msg = consumeWString(msgLenWords * 2);
	uipkt->add_wstring(L"Message", msg);
	consume_add_byte(L"NumLinkedItems", uipkt);

	abandon_processing();
	uipkt->add_byte(L"AbandonedProcessing", 1);
}


void packet_processor::deserialise_CLI_CHAT_COMMAND(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"CommandsDatIndex", uipkt);
	consume_add_word_ntoh(L"Arg", uipkt);

	abandon_processing();
	uipkt->add_byte(L"AbandonedProcessing", 1);
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
	ushort namelen = ntohs(consume_WORD());
	uipkt->add_wstring(L"Name", consumeWString(namelen * 2));
	ushort textlen = ntohs(consume_WORD());
	uipkt->add_wstring(L"Text", consumeWString(textlen * 2));
	ushort taglen = ntohs(consume_WORD());
	uipkt->add_wstring(L"Tag", consumeWString(taglen * 2));
	//guesswork - injection makes a fancy dev tag appear
	consume_add_byte(L"Dev", uipkt);
	consume_add_byte(L"Challenges", uipkt);
	consume_add_byte(L"Hide", uipkt);
	byte itemCount = consume_Byte();


	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	WValue itemArray(rapidjson::kArrayType);
	for (int i = 0; i < itemCount; i++)
	{
		DWORD itemID = ntohs(consume_DWORD());

		ushort modsLen = ntohs(consume_WORD());
		DWORD hash = consume_DWORD();

		std::string hashResult, hashCategory;
		ggpk->lookup_hash(hash, hashResult, hashCategory);
		std::wstring itemString = converter.from_bytes(hashResult);
		std::wstring categoryString = converter.from_bytes(hashCategory);
		consume_blob(modsLen - sizeof(hash));


		WValue itemObj(rapidjson::kObjectType);
		itemObj.AddMember(L"ChatIndex", WValue((UINT32)itemID), allocator);
		itemObj.AddMember(L"ItemHash", WValue((UINT32)hash), allocator);
		itemObj.AddMember(L"ItemType", WValue(itemString.c_str(), allocator), allocator);

		itemArray.PushBack(itemObj, allocator);

	}
	uipkt->payload->AddMember(L"ItemList", itemArray, allocator);
}

//0xb, 0xca, 
WValue packet_processor::get_pairs_strings_blob(UIDecodedPkt *uipkt)
{
	WValue blobPair(rapidjson::kObjectType);

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
	blobPair.AddMember(L"Pairs", pairArray, allocator);

	WValue stringArray(rapidjson::kArrayType);
	for (int i = 0; i < stringCount; i++)
	{
		ushort stringSize = ntohs(consume_WORD());
		std::wstring msgstr = consumeWString(stringSize * 2);
		WValue stringval(msgstr.c_str(), allocator);
		stringArray.PushBack(stringval, allocator);
	}
	blobPair.AddMember(L"Strings", stringArray, allocator);
	
	return blobPair;
}

void packet_processor::deserialise_SRV_SERVER_MESSAGE(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	//outer
	consume_add_word_ntoh(L"BackendErrorsRow", uipkt);
	consume_add_word_ntoh(L"DevID", uipkt);
	consume_add_byte(L"TextModifier", uipkt);
	consume_add_dword_ntoh(L"Unk4", uipkt);

	WValue blobs = get_pairs_strings_blob(uipkt);
	uipkt->payload->AddMember(L"PairList", blobs.FindMember(L"Pairs")->value, allocator);
	uipkt->payload->AddMember(L"StringList", blobs.FindMember(L"Strings")->value, allocator);
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


void packet_processor::deserialise_CLI_HNC(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Challenge", uipkt);
}

void packet_processor::deserialise_SRV_HNC(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Response", uipkt);
}

void packet_processor::deserialise_SRV_AREA_INFO(UIDecodedPkt* uipkt)
{
	DWORD areaCode = ntohl(consume_DWORD());
	std::wstring areaname;
	ggpk->lookup_areaCode(areaCode, areaname);
	uipkt->add_dword(L"AreaCode", areaCode);
	uipkt->add_wstring(L"AreaName", areaname);

	size_t diffLenWords = ntohs(consume_WORD());
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	WValue preloadHashList(rapidjson::kArrayType); 
	WValue preloadHashResults(rapidjson::kArrayType);

	std::string hashResult;
	std::string hashCategory;

	ushort hashCount = ntohs(consume_WORD());
	for (int i = 0; i < hashCount; i++)
	{
		DWORD hash = ntohl(consume_DWORD());
		ggpk->lookup_hash(hash, hashResult, hashCategory);
		std::wstring itemString = converter.from_bytes(hashResult);
		std::wstring categoryString = converter.from_bytes(hashCategory);

		WValue preloadhash(rapidjson::kObjectType);
		preloadhash.AddMember(L"Hash", (UINT32)hash, allocator);
		preloadhash.AddMember(L"Item", WValue(itemString.c_str(), allocator), allocator);
		preloadhash.AddMember(L"Category", WValue(categoryString.c_str(), allocator), allocator);
		preloadHashList.PushBack(preloadhash, allocator);
			
		if (errorFlag != eNoErr) return;
	}
	uipkt->payload->AddMember(L"PreloadHashList", preloadHashList, allocator);

	//no idea what to do with any of these values yet
	ushort countl2 = ntohs(consume_WORD());
	WValue list2(rapidjson::kArrayType);
	for (int i = 0; i < countl2; i++)
	{
		byte b = consume_Byte(); //todo
		list2.PushBack(b, allocator);
	}
	uipkt->payload->AddMember(L"ByteList1", list2, allocator);

	byte countl3 = consume_Byte(); 
	WValue list3(rapidjson::kArrayType);
	for (int i = 0; i < countl3; i++)
	{
		byte b = consume_Byte(); //todo
		list3.PushBack(b, allocator);
	}
	uipkt->payload->AddMember(L"ByteList2", list3, allocator);

	if (control2 & 0x2) //2nd bit set
	{
		WValue list4(rapidjson::kArrayType);
		byte countl4 = consume_Byte();
		for (int i = 0; i < countl4; i++)
		{
			byte b = consume_Byte(); //todo
			list4.PushBack(b, allocator);
		}
		uipkt->payload->AddMember(L"ByteList4", list4, allocator);
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
		uipkt->payload->AddMember(L"ByteList5", list5, allocator);
	}

	if (control2 & 0x1) //1st bit set
	{
		WValue mapstatslist(rapidjson::kArrayType);
		DWORD paircount = customSizeByteGet();
		for (int i = 0; i < paircount; i++)
		{
			WValue statdat(rapidjson::kArrayType);

			DWORD statIndex = customSizeByteGet();
			statdat.PushBack((UINT32)statIndex, allocator);

			std::wstring statname = converter.from_bytes(ggpk->statDescriptions.at(statIndex));
			statdat.PushBack(WValue(statname.c_str(), allocator), allocator);

			DWORD second = customSizeByteGet_signed();
			statdat.PushBack((UINT32)second, allocator);

			mapstatslist.PushBack(statdat, allocator);
		}
		uipkt->payload->AddMember(L"MapStatsList", mapstatslist, allocator);
	}
}

void packet_processor::deserialise_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt* uipkt)
{
	std::vector<std::pair<ushort, byte>> preloadList;

	unsigned short listCount = ntohs(consume_WORD());
	preloadList.resize(listCount);

	//index into data/monstervarieties.dat 
	for (int i = 0; i < listCount; i++)
	{
		preloadList.at(i).first = consume_WORD();
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	WValue preloadJSON(rapidjson::kArrayType);
	for (int i = 0; i < listCount; i++)
	{
		WValue datItem(rapidjson::kArrayType);
		uint varietyIndex = preloadList.at(i).first;
		uint level = preloadList.at(i).second;

		std::wstring ggpkpath;
		if (varietyIndex < ggpk->monsterVarieties.size())
			ggpkpath = converter.from_bytes(ggpk->monsterVarieties.at(varietyIndex));
		else
		{
			std::wstringstream bad;
			bad << "Unknown monstervariety " << std::dec << varietyIndex;
			ggpkpath = bad.str();
		}

		datItem.PushBack(WValue(varietyIndex), allocator);
		datItem.PushBack(WValue(ggpkpath.c_str(), allocator), allocator);
		datItem.PushBack(WValue(level), allocator);
		
		preloadJSON.PushBack(datItem, allocator);
	}
	uipkt->payload->AddMember(L"PreloadList", preloadJSON, allocator);
}

void packet_processor::deserialise_UNK_13_A5_LIST(UIDecodedPkt * uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	WValue blobArray(rapidjson::kArrayType);
	ushort listSize = ntohs(consume_WORD());

	for (int i = 0; i < listSize; i++)
	{
		WValue blobobj(rapidjson::kObjectType);

		blobobj.AddMember(L"DW1", (UINT32)consume_DWORD(), allocator);
		blobobj.AddMember(L"DW2", (UINT32)consume_DWORD(), allocator);

		ushort stringlen_words = ntohs(consume_WORD());
		wstring unkstr = consumeWString(stringlen_words * 2);
		WValue unkstring(unkstr.c_str(), allocator);
		blobobj.AddMember(L"UnkString", unkstring, allocator);

		blobobj.AddMember(L"Short1", consume_WORD(), allocator);
		byte controlByte = consume_Byte();
		blobobj.AddMember(L"ControlByte", controlByte, allocator);
		blobobj.AddMember(L"Short2", consume_WORD(), allocator);
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

	uipkt->payload->AddMember(L"BlobList", blobArray, allocator);
}

void packet_processor::deserialise_SRV_UNK_0x13(UIDecodedPkt * uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	deserialise_UNK_13_A5_LIST(uipkt);

	ushort endstringlen_words = ntohs(consume_WORD());
	wstring endstr = consumeWString(endstringlen_words * 2);
	WValue endstring(endstr.c_str(), allocator);
	uipkt->payload->AddMember(L"EndString", endstring, allocator);
	consume_add_word_ntoh(L"EndShort", uipkt);
	consume_add_dword_ntoh(L"EndDWORD", uipkt);

}

void packet_processor::deserialise_SRV_ITEMS_LIST(UIDecodedPkt* uipkt)
{
	consume_add_dword_ntoh(L"ObjID", uipkt);
}

void packet_processor::deserialise_CLI_LOGGED_OUT(UIDecodedPkt *uipkt)
{
	UInotifyStreamState(currentMsgStreamID, eStreamEnded, uiMsgQueue);
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

	consume_blob(20);


	KEYDATA *key1A = new KEYDATA;
	KEYDATA *key1B = new KEYDATA;
	//todo proper vectors
	memcpy(key1A->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	memcpy(key1B->salsakey, decryptedBuffer->data() + decryptedIndex, 32);
	consume_blob(32);

	if (key1A->salsakey[0] == 0 && key1A->salsakey[3] == 0 && key1A->salsakey[7] == 0)
	{
		UIaddLogMsg("Discarding bad key in area transition", key1A->sourceProcess, uiMsgQueue);
		consume_blob(32);
		return; //probably an old zero-ed out key
	}

	memcpy(key1A->IV, decryptedBuffer->data() + decryptedIndex, 8);
	consume_blob(16);
	memcpy(key1B->IV, decryptedBuffer->data() + decryptedIndex, 8);
	consume_blob(16);

	key1A->sourceProcess = key1B->sourceProcess = uipkt->getClientProcessID();
	key1A->foundAddress = key1B->foundAddress = SENT_BY_SERVER;
	pendingGameserverKeys[nextConnectionID] = make_pair(key1A, key1B);
}

void packet_processor::deserialise_CLI_PICKUP_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"Unk1", uipkt);
	consume_add_word_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"ItemID", uipkt); //odd this is a dword. todo: check
	consume_add_byte(L"Unk", uipkt);
}

void packet_processor::deserialise_CLI_DROP_ITEM(UIDecodedPkt *uipkt)
{
	//no data expected
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

void packet_processor::deserialise_SRV_UNK_0x20(UIDecodedPkt *uipkt)
{
	//todo 
	unsigned short itemCount = ntohs(consume_WORD());
	for (int i = 0; i < itemCount; i++)
	{
		consume_WORD();
	}
	consume_WORD(); 
	consume_WORD(); 
	consume_WORD(); 
	consume_Byte();
	consume_Byte();
	consume_Byte();

}

void packet_processor::deserialise_CLI_SKILLPOINT_CHANGE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"GraphIndex", uipkt);
}

void packet_processor::deserialise_CLI_CHOSE_ASCENDANCY(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Choice", uipkt);
}


void packet_processor::deserialise_CLI_CANCEL_BUF(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"BuffID", uipkt);
}

void packet_processor::deserialise_CLI_MERGE_STACK(UIDecodedPkt *uipkt)
{
	//not checked what the data sizes actually are
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"Unk3", uipkt);
}

//todo
void packet_processor::deserialise_SRV_UNK_0x2c(UIDecodedPkt *uipkt)
{

	unsigned short itemCount = 4; //comes from a member variable, dunno where it's set yet
	for (int i = 0; i < itemCount; i++)
	{
		consume_Byte();
	}
	
	consume_blob(19);

}

void packet_processor::deserialise_CLI_SELECT_MAPTRAVEL(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"AreaCode", uipkt);
	consume_add_dword_ntoh(L"Arg2", uipkt);
	consume_add_byte(L"Arg3", uipkt);
}

void packet_processor::deserialise_CLI_SET_HOTBARSKILL(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Slot", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
}


void packet_processor::deserialise_SRV_SKILL_SLOTS_LIST(UIDecodedPkt *uipkt)
{
	for (int i = 1; i < 9; i++)
	{
		wstring skillName = L"Skill" + to_wstring(i);
		uipkt->add_word(skillName, consume_WORD());
	}
}

void packet_processor::deserialise_CLI_REVIVE_CHOICE(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Choice", uipkt);
}

void packet_processor::deserialise_SRV_YOU_DIED(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"ChoiceBits", uipkt);
	consume_add_dword(L"Unk", uipkt);
}

void packet_processor::deserialise_CLI_ACTIVATE_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Item1", uipkt);
}

void packet_processor::deserialise_CLI_USE_BELT_SLOT(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Slot", uipkt);
}

void packet_processor::deserialise_CLI_USE_ITEM_ON_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Item1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"Item2", uipkt);
}

void packet_processor::deserialise_CLI_UNK_0x41(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
}

void packet_processor::deserialise_CLI_SELECT_NPC_DIALOG(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Option", uipkt);
}

void packet_processor::deserialise_SRV_SHOW_NPC_DIALOG(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_byte(L"Option", uipkt);
}

void packet_processor::deserialise_CLI_CLOSE_NPC_DIALOG(UIDecodedPkt *uipkt)
{
	//no data
}


void packet_processor::deserialise_SRV_OPEN_UI_PANE(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"PaneID", uipkt);
	consume_add_dword_ntoh(L"Arg", uipkt);
}

void packet_processor::deserialise_CLI_SPLIT_STACK(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"ItemID1", uipkt);
	consume_add_dword_ntoh(L"MouseStackSize", uipkt);
	consume_add_byte(L"Unk2", uipkt);
}

void packet_processor::deserialise_SRV_LIST_PORTALS(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue portalList(rapidjson::kArrayType);

	byte portalCount = consume_Byte();
	for (int i = 0; i < portalCount; i++)
	{
		WValue portalDetails(rapidjson::kObjectType);
		portalDetails.AddMember(L"ID", (UINT32)ntohl(consume_DWORD()), allocator);
		portalDetails.AddMember(L"Unk1", (UINT32)ntohl(consume_DWORD()), allocator);

		consume_add_lenprefix_string(L"String", portalDetails, allocator);

		portalDetails.AddMember(L"Unk2", consume_Byte(), allocator);

		portalList.PushBack(portalDetails, allocator);
	}

	uipkt->payload->AddMember(L"PortalList", portalList, allocator);
}

void packet_processor::deserialise_CLI_SEND_PARTY_INVITE(UIDecodedPkt *uipkt)
{
	unsigned short namelen = ntohs(consume_WORD());
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
	unsigned short namelen = ntohs(consume_WORD());
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
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	consume_add_lenprefix_string(L"Name", *(uipkt->payload), allocator);
	consume_add_lenprefix_string(L"String2", *(uipkt->payload), allocator);

	byte controlByte = consume_Byte();

	if (controlByte == 0)
	{
		consume_add_qword(L"0_QWord", uipkt);
	}
	else
	{
		consume_add_lenprefix_string(L"String3", *(uipkt->payload), allocator);
		consume_add_dword_ntoh(L"1_Unk1", uipkt);
		consume_add_byte(L"1_Unk2", uipkt);
		consume_add_dword_ntoh(L"1_Unk3", uipkt);
		consume_add_byte(L"1_Unk4", uipkt);
		consume_add_lenprefix_string(L"String4", *(uipkt->payload), allocator);
		consume_add_byte(L"1_Unk5", uipkt);
		consume_add_byte(L"1_Unk6", uipkt);
		consume_add_byte(L"1_Unk7", uipkt);
	}
}

void packet_processor::deserialise_SRV_PARTY_DETAILS(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	consume_add_dword_ntoh(L"ID", uipkt);

	consume_add_lenprefix_string(L"Description", *(uipkt->payload), uipkt->jsn.GetAllocator());

	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	byte playerCount = consume_Byte();

	WValue playerList(rapidjson::kArrayType);
	for (int i = 0; i < playerCount; i++)
	{

		WValue playerListing(rapidjson::kObjectType);
		consume_add_lenprefix_string(L"Name", playerListing, allocator);

		byte statusByte = consume_Byte();
		std::wstring statusText;
		switch (statusByte) {
		case 0:
			statusText = L"Pending";
			break;
		case 1:
			statusText = L"Member";
			break;
		case 2:
			statusText = L"Leader";
			break;
		default:
			statusText = L"Unknown";
			break;
		}

		playerListing.AddMember(L"StatusByte", statusByte, allocator);
		playerListing.AddMember(L"StatusText", WValue(statusText.c_str(), allocator), allocator);
		playerList.PushBack(playerListing, allocator);
	}

	uipkt->payload->AddMember(L"MemberList", playerList, allocator);

}

void packet_processor::deserialise_SRV_PARTY_ENDED(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue partyArray(rapidjson::kArrayType);

	ushort listingCount = ntohs(consume_WORD());
	for (int i = 0; i < listingCount; i++)
	{
		WValue partyDetails(rapidjson::kObjectType);
		partyDetails.AddMember(L"ID", (UINT32)consume_DWORD(), allocator);

		ushort stringlen = ntohs(consume_WORD());
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

	uipkt->payload->AddMember(L"PartyList", partyArray, allocator);
}

void packet_processor::deserialise_CLI_MOVE_ITEM_PANE(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"PaneID", uipkt);
	consume_add_dword_ntoh(L"ItemID", uipkt);
	consume_add_byte(L"Column", uipkt);
	consume_add_byte(L"Row", uipkt);
}

void packet_processor::deserialise_CLI_CONFIRM_SELL(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0x67(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt); 
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"Unk3", uipkt);
	consume_add_dword(L"Unk4", uipkt);
	consume_add_lenprefix_string(L"UnkString", *(uipkt->payload), uipkt->jsn.GetAllocator());
	consume_add_dword_ntoh(L"Unk5", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0x68(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt); 
	consume_add_byte(L"Unk2", uipkt);
}



void packet_processor::deserialise_SRV_UNK_0x6c(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue entryArray(rapidjson::kArrayType);

	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);

	byte count = consume_Byte();
	for(int i = 0; i < count; i++)
	{
		WValue entry(rapidjson::kObjectType);
		consume_add_lenprefix_string(L"String", entry, allocator);
		entry.AddMember(L"Byte", consume_Byte(), allocator);

		entryArray.PushBack(entry, allocator);
	}
	uipkt->payload->AddMember(L"UnkList", entryArray, allocator);
}


void packet_processor::deserialise_item(UIDecodedPkt *uipkt, WValue& container)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	container.AddMember(L"ItemID", (UINT32)ntohl(consume_DWORD()), allocator);
	container.AddMember(L"Column", consume_Byte(), allocator);
	container.AddMember(L"Row", consume_Byte(), allocator);

	ushort modsLen = ntohs(consume_WORD());
	DWORD hash = consume_DWORD();
	container.AddMember(L"ItemHash", WValue((UINT32)hash), allocator);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string itemname, category;
	ggpk->lookup_hash(hash, itemname, category);
	std::wstring itemWName = converter.from_bytes(itemname);
	std::wstring categoryWstring = converter.from_bytes(category);

	container.AddMember(L"ItemName", WValue(itemWName.c_str(), allocator), allocator);
	container.AddMember(L"Category", WValue(categoryWstring.c_str(), allocator), allocator);

	//skip item data for now, apart from the hash so we at least know item type
	consume_blob(modsLen - sizeof(hash));

	//todo - do something with this
}

void packet_processor::deserialise_SRV_CREATE_ITEM(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	//routine outer
	consume_add_byte(L"B1", uipkt);
	consume_add_dword_ntoh(L"DW1", uipkt);

	//routine inner
	consume_add_dword_ntoh(L"DW2", uipkt);

	DWORD listsize = ntohl(consume_DWORD());
	WValue list1(rapidjson::kArrayType);
	for (int i = 0; i < listsize; i++)
		list1.PushBack((UINT32)ntohl(consume_DWORD()), allocator);
	uipkt->payload->AddMember(L"List1", list1, allocator);

	WValue itemlist(rapidjson::kArrayType);
	DWORD listsize2 = ntohl(consume_DWORD());
	for (int i = 0; i < listsize2; i++)
	{
		WValue item(rapidjson::kObjectType);
		deserialise_item(uipkt, item); //todo
		itemlist.PushBack(item, allocator);
	}
	uipkt->payload->AddMember(L"ItemList", itemlist, allocator);

	byte nextbyte = consume_Byte();
	uipkt->add_byte(L"LastFlag", nextbyte);
	if (nextbyte)
	{
		consume_add_dword(L"End1", uipkt);
		consume_add_dword(L"End2", uipkt);
		consume_add_dword(L"End3", uipkt);
		consume_add_dword(L"End4", uipkt);
	}
}


void packet_processor::deserialise_SRV_SLOT_ITEMSLIST(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Container", uipkt);

	consume_add_byte(L"Slot", uipkt);
	consume_add_byte(L"Unk3", uipkt);
	consume_add_byte(L"Unk4", uipkt);
	consume_add_byte(L"Unk5", uipkt);
	consume_add_byte(L"Unk6", uipkt);

	DWORD itemCount = ntohl(consume_DWORD());
	uipkt->add_dword(L"Count", itemCount);

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	WValue itemArray(rapidjson::kArrayType);
	for (int i = 0; i < itemCount; i++)
	{
		//todo - move this into own func deserialiseItem()
		WValue itemObj(rapidjson::kObjectType);

		itemObj.AddMember(L"ItemID", WValue((UINT32)ntohl(consume_DWORD())), allocator);
		itemObj.AddMember(L"Column", WValue(consume_Byte()), allocator);
		itemObj.AddMember(L"Row", WValue(consume_Byte()), allocator);
		ushort modsLen = ntohs(consume_WORD());
		DWORD hash = consume_DWORD();
		itemObj.AddMember(L"ItemHash", WValue((UINT32)hash), allocator);
		//skip item data for now, apart from the hash so we at least know item type
		consume_blob(modsLen - sizeof(hash));

		std::string hashResult, hashCategory;
		ggpk->lookup_hash(hash, hashResult, hashCategory);
		std::wstring itemString = converter.from_bytes(hashResult);
		std::wstring categoryString = converter.from_bytes(hashCategory);

		itemObj.AddMember(L"ItemType", WValue(itemString.c_str(), allocator), allocator);



		itemArray.PushBack(itemObj, allocator);
	}
	uipkt->payload->AddMember(L"ItemList", itemArray, allocator);

	consume_add_word_ntoh(L"FinalUnk", uipkt);

}

void packet_processor::deserialise_SRV_INVENTORY_SET_REMOVE(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0x70(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Arg", uipkt);
}

void packet_processor::deserialise_CLI_SELECT_STASHTAB(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
}


void packet_processor::deserialise_SRV_STASHTAB_DATA(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0x73(UIDecodedPkt *uipkt)
{
	consume_add_dword(L"Data1", uipkt); //todo - this is not fixed at 4, its just what ive seen it as

	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	consume_add_lenprefix_string(L"String1", *(uipkt->payload), allocator);
	consume_add_lenprefix_string(L"String2", *(uipkt->payload), allocator);
}

void packet_processor::deserialise_CLI_SET_STATUS_MESSAGE(UIDecodedPkt *uipkt)
{
	unsigned short statuslen = ntohs(consume_WORD());
	std::wstring status = consumeWString(statuslen * 2);
	uipkt->add_wstring(L"StatusText", status);
}

void packet_processor::deserialise_SRV_MOVE_OBJECT(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ObjectID", uipkt);
	consume_add_dword_ntoh(L"Coord1", uipkt);
	consume_add_dword_ntoh(L"Coord2", uipkt);
	consume_add_dword_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Unk2", uipkt);

	byte controlByte = consume_Byte();
	uipkt->add_byte(L"Flags", controlByte);

	if (!(controlByte & 0x8))
	{
		consume_add_word_ntoh(L"Unk_cond_a", uipkt);
	}
	if (controlByte & 0x10)
	{
		consume_add_byte(L"Unk_cond_b", uipkt);
	}
}

void packet_processor::deserialise_CLI_ACTIVATE_MAP(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_CLI_SWAPPED_WEAPONS(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Byte", uipkt);
}

void packet_processor::deserialise_SRV_ADJUST_LIGHTING(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"Unk1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"Unk3", uipkt);
}

void packet_processor::deserialise_CLI_TRANSFER_ITEM(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"Container", uipkt);
	consume_add_dword_ntoh(L"Item", uipkt);
	consume_add_byte(L"Unk", uipkt);
}

void packet_processor::deserialise_CLI_SKILLPANE_ACTION(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"State", uipkt);
}

void packet_processor::deserialise_SRV_ACHIEVEMENT_1(UIDecodedPkt *uipkt)
{
	consume_add_word(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_ACHIEVEMENT_2(UIDecodedPkt *uipkt)
{
	consume_add_word(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_SKILLPANE_DATA(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Unk1", uipkt);

	ushort blobsize = ntohs(consume_WORD());
	vector<byte> blob;
	consume_blob(blobsize, blob);
}

void packet_processor::deserialise_SRV_UNK_POSITION_LIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	ushort count = consume_Byte();

	WValue posArray(rapidjson::kArrayType);
	for (int i = 0; i < count; i++)
	{
		WValue eventObj(rapidjson::kArrayType);

		eventObj.PushBack((UINT32)ntohl(consume_DWORD()), allocator);
		eventObj.PushBack((UINT32)ntohl(consume_DWORD()), allocator);
		eventObj.PushBack((UINT32)ntohl(consume_DWORD()), allocator);

		posArray.PushBack(eventObj, allocator);
	}

	uipkt->payload->AddMember(L"CoordArray", posArray, allocator);
}

void packet_processor::deserialise_SRV_INVENTORY_FULL(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_PVP_MATCHLIST(UIDecodedPkt *uipkt)
{
	deserialise_SRV_EVENTSLIST(uipkt);
}


void packet_processor::deserialise_SRV_EVENTSLIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	ushort count = ntohs(consume_WORD());
	uipkt->add_word(L"Count", count);

	WValue eventArray(rapidjson::kArrayType);
	for (int i = 0; i < count; i++)
	{
		WValue eventObj(rapidjson::kObjectType);

		
		consume_add_lenprefix_string(L"StringRef", eventObj, allocator);
		consume_add_lenprefix_string(L"Description", eventObj, allocator);
		consume_add_lenprefix_string(L"Mode1", eventObj, allocator);
		consume_add_lenprefix_string(L"Mode2", eventObj, allocator);

		eventObj.AddMember(L"Unk1", consume_DWORD(), allocator);
		eventObj.AddMember(L"MinLevel", ntohs(consume_WORD()), allocator);
		eventObj.AddMember(L"MaxLevel", ntohs(consume_WORD()), allocator);
		eventObj.AddMember(L"Unk2", consume_Byte(), allocator);

		eventObj.AddMember(L"Unk3_64", consume_QWORD(), allocator);
		eventObj.AddMember(L"Unk4_64", consume_QWORD(), allocator);
		eventObj.AddMember(L"Unk5_64", consume_QWORD(), allocator);
		eventObj.AddMember(L"Unk6", consume_WORD(), allocator);
		eventObj.AddMember(L"Unk7", consume_WORD(), allocator);

		eventArray.PushBack(eventObj, allocator);
	}

	uipkt->payload->AddMember(L"EventList", eventArray, allocator);
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

void packet_processor::deserialise_CLI_UNK_A3(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"fff", uipkt);
	consume_add_dword_ntoh(L"fff3", uipkt);
}

void packet_processor::deserialise_SRV_CHAT_CHANNEL_ID(UIDecodedPkt *uipkt)
{
	consume_add_word_ntoh(L"ChannelID", uipkt);
	consume_add_byte(L"Type", uipkt);
	consume_add_byte(L"Language", uipkt);
}

void packet_processor::deserialise_SRV_UNK_A5(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"GuildPrefix", uipkt);

	deserialise_UNK_13_A5_LIST(uipkt);
}

void packet_processor::deserialise_CLI_EXIT_TO_CHARSCREEN(UIDecodedPkt *uipkt)
{
	UInotifyStreamState(currentMsgStreamID, eStreamTransitionLogin, uiMsgQueue);
}


void packet_processor::deserialise_SRV_LOGINSRV_CRYPT(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	consume_add_dword_ntoh(L"Unk1", uipkt);

	byte listsize = consume_Byte();

	WValue serverList(rapidjson::kArrayType);
	for (int i = 0; i < listsize; i++)
	{
		std::wstring blobstring = consume_hexblob(0x1c);
		WValue blobval(blobstring.c_str(), allocator);
		serverList.PushBack(blobval, allocator);
	}
	uipkt->payload->AddMember(L"ServerList", serverList, allocator);
}
void packet_processor::deserialise_CLI_DUEL_CHALLENGE(UIDecodedPkt *uipkt)
{
	abandon_processing();//todo
}
void packet_processor::deserialise_SRV_DUEL_RESPONSE(UIDecodedPkt *uipkt)
{

	abandon_processing();//todo
}
void packet_processor::deserialise_SRV_DUEL_CHALLENGE(UIDecodedPkt *uipkt)
{

	abandon_processing();//todo
}

void packet_processor::deserialise_CLI_UNK_0xC6(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_CLI_UNK_0xC7(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_UNK_0xCA(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	WValue itemArray(rapidjson::kArrayType);

	consume_add_word(L"UnkWord1", uipkt);
	consume_add_byte(L"UnkByte2", uipkt);

	byte listSize = consume_Byte();
	for (int i = 0; i < listSize; i++)
	{
		WValue item(rapidjson::kObjectType);

		item.AddMember(L"Unk1", consume_WORD(), allocator);
		item.AddMember(L"Unk2", consume_WORD(), allocator);
		item.AddMember(L"Unk3", consume_WORD(), allocator);

		WValue blobPair = get_pairs_strings_blob(uipkt);
		item.AddMember(L"BlobPair", blobPair, allocator);

		itemArray.PushBack(item, allocator);
	}

	uipkt->payload->AddMember(L"ItemArray", itemArray, allocator);
}


void packet_processor::deserialise_SRV_EVENTSLIST_2(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();

	uint count = ntohl(consume_DWORD());

	WValue eventArray(rapidjson::kArrayType);
	for (int i = 0; i < count; i++)
	{
		WValue eventObj(rapidjson::kObjectType);

		consume_add_lenprefix_string(L"Name", eventObj, allocator);
		consume_add_lenprefix_string(L"Label1", eventObj, allocator);
		consume_add_lenprefix_string(L"Label2", eventObj, allocator);

		eventObj.AddMember(L"StartTime", consume_QWORD(), allocator);
		eventObj.AddMember(L"RegisterTime", consume_QWORD(), allocator);
		eventObj.AddMember(L"Unk5_64", consume_QWORD(), allocator);
		eventObj.AddMember(L"Unk6", consume_DWORD(), allocator);
		eventObj.AddMember(L"Unk7", consume_Byte(), allocator);

		eventArray.PushBack(eventObj, allocator);
	}

	uipkt->payload->AddMember(L"EventList", eventArray, allocator);
}


void packet_processor::deserialise_CLI_USED_SKILL(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Coord1", uipkt);
	consume_add_dword_ntoh(L"Coord2", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
	consume_add_byte(L"ControlModifier", uipkt);
}

void packet_processor::deserialise_CLI_CLICK_OBJ(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ObjID", uipkt);
	consume_add_word_ntoh(L"SkillID", uipkt);
	consume_add_byte(L"ControlModifier", uipkt);
}

void packet_processor::deserialise_CLI_MOUSE_HELD(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Coord1", uipkt);
	consume_add_dword_ntoh(L"Coord2", uipkt);
}

void packet_processor::deserialise_CLI_MOUSE_RELEASE(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_GUILD_MEMBER_LIST(UIDecodedPkt *uipkt)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	consume_add_lenprefix_string(L"String1", *(uipkt->payload), allocator);
	consume_add_lenprefix_string(L"String2", *(uipkt->payload), allocator);
	consume_add_lenprefix_string(L"String3", *(uipkt->payload), allocator);
	consume_add_qword(L"Time1", uipkt);

	UINT32 membercount = ntohs(consume_WORD());
	WValue memberlist(rapidjson::kArrayType);

	for (int i = 0; i < membercount; i++)
	{
		WValue member(rapidjson::kObjectType);
		consume_add_lenprefix_string(L"Name", member, allocator);
		member.AddMember(L"Time", consume_QWORD(), allocator);
		member.AddMember(L"State", consume_Byte(), allocator);
		memberlist.PushBack(member, allocator);
	}

	uipkt->payload->AddMember(L"MemberList", memberlist, allocator);
}

void packet_processor::deserialise_CLI_GUILD_CREATE(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_UNK_0xE4(UIDecodedPkt *uipkt)
{
	consume_add_byte(L"Arg", uipkt);
}

//todo - add contents to json
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
		consume_WORD();
		consume_Byte();
	}

	byte list5Len = consume_Byte();
	for (int i = 0; i < list5Len; i++)
	{
		consume_WORD();
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

	consume_WORD();
	consume_Byte();
}

void packet_processor::deserialise_SRV_OBJ_REMOVED(UIDecodedPkt * uipkt)
{
	consume_add_dword_ntoh(L"ItemID", uipkt);
	consume_add_dword_ntoh(L"Receiver", uipkt);
	consume_add_word_ntoh(L"Unk2", uipkt);
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

	
	uipkt->add_word(L"StartCoord1", customSizeByteGet_signed());
	uipkt->add_word(L"StartCoord2", customSizeByteGet_signed());
	uipkt->add_word(L"TargCoord1", customSizeByteGet_signed());
	uipkt->add_word(L"TargCoord2", customSizeByteGet_signed());

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

void packet_processor::deserialise_SRV_MOVE_CHANNELLED(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word_ntoh(L"Unk1", uipkt);
	consume_add_dword_ntoh(L"Coord1", uipkt);
	consume_add_dword_ntoh(L"Coord2", uipkt);
}

void packet_processor::deserialise_SRV_END_CHANNELLED(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"Unk1", uipkt);	
	consume_add_word_ntoh(L"Unk2", uipkt);	
	consume_add_word_ntoh(L"Unk3", uipkt);
	consume_add_dword_ntoh(L"Unk4", uipkt);
	consume_add_byte(L"Unk5", uipkt);
}

void packet_processor::deserialise_SRV_MOBILE_UNK_0xee(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	//2_1_1_4
	consume_add_word_ntoh(L"S1", uipkt);
	consume_add_byte(L"B1", uipkt);
	consume_add_byte(L"B2", uipkt);
	consume_add_dword_ntoh(L"D1", uipkt);

	ushort skillid = ntohs(consume_WORD());
	uipkt->add_word(L"SkillID", skillid);

	ushort zerobyte = consume_Byte();
	uipkt->add_byte(L"ZeroByte", zerobyte);

	if (skillid & 0x400)
	{
		ushort skillword2 = consume_WORD();
		uipkt->add_word(L"SkillBit400", skillword2);
	}

	if (skillid & 0x4000)
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
				0x00, 0x00,	0x00, 0x36, //NewValue
				0x00, 0x00, 0x00, 0x00, //???
				0x01, 
				0x00 
	*/

	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_dword_ntoh(L"NewValue", uipkt);
	consume_add_dword_ntoh(L"Unk3", uipkt);
	consume_add_byte(L"Stat", uipkt);  //0 life/1 mana/2 shield
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
	uipkt->payload->AddMember(L"PairList", pairlist, allocator);
}

void packet_processor::deserialise_SRV_UNK_0xf2(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_byte(L"Arg", uipkt);
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

void packet_processor::deserialise_SRV_UNK_0xf5(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_dword_ntoh(L"Arg1", uipkt);
	consume_add_byte(L"Arg2", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0xf7(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_byte(L"Arg1", uipkt);
	consume_add_byte(L"Arg2", uipkt);
	consume_add_byte(L"Arg3", uipkt);
}

void packet_processor::deserialise_SRV_UNK_0xf8(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_byte(L"Arg", uipkt);
}

void packet_processor::deserialise_SRV_START_EFFECT(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word_ntoh(L"BuffID", uipkt);
	UINT32 buffDefinitionsRow = ntohs(consume_WORD());
	uipkt->add_word(L"BuffDefinitionsRow", buffDefinitionsRow);
	consume_add_dword_ntoh(L"UnkDWord3", uipkt); //an object id
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
		consume_add_byte(L"BufVisualsRow", uipkt);
	}


	WValue statList(rapidjson::kArrayType);
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	if (IS_IN_VECTOR(ggpk->recoveryBuffs, buffDefinitionsRow))
	{
		byte listsize1 = ggpk->buffDefinitions_names_statCounts.at(buffDefinitionsRow).second;

		for (int i = 0; i < listsize1; i++)
		{
			statList.PushBack((UINT32)ntohl(consume_DWORD()), allocator);
		}
	}

	uipkt->payload->AddMember(L"StatList", statList, allocator);
	
}

void packet_processor::deserialise_SRV_END_EFFECT(UIDecodedPkt *uipkt) 
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word_ntoh(L"BuffID", uipkt);
}


void packet_processor::deserialise_SRV_EVENT_TRIGGERED(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_byte(L"State", uipkt);
}

void packet_processor::deserialise_SRV_UNKNOWN_0x106(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_word(L"Unk1", uipkt);
	consume_add_word_ntoh(L"Unk2", uipkt);
	consume_add_dword_ntoh(L"UnkDW1", uipkt);
	consume_add_dword_ntoh(L"UnkDW2", uipkt);
	consume_add_dword_ntoh(L"UnkDW3", uipkt);
	consume_add_byte(L"Unk3", uipkt);
}

void packet_processor::deserialise_SRV_UNKNOWN_0x108(UIDecodedPkt *uipkt)
{
	//10 b objid
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);

	consume_add_dword_ntoh(L"UnkDW1", uipkt);
	consume_add_byte(L"Unk2", uipkt);
	consume_add_byte(L"Unk3", uipkt);
}

void packet_processor::deserialise_CLI_FINISHED_LOADING(UIDecodedPkt *)
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

//recipes and captured beasts
void packet_processor::deserialise_SRV_BESTIARY_CAPTIVES(UIDecodedPkt *uipkt)
{
	byte blobcount = consume_WORD();

	for (int i = 0; i < blobcount; i++)
	{
		byte blobsize = consume_Byte();
		vector<byte>blob;
		consume_blob(blobsize, blob);
	}
}

void packet_processor::deserialise_CLI_OPEN_BESTIARY(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::deserialise_SRV_BESTIARY_UNLOCKED_LIST(UIDecodedPkt *uipkt)
{
	vector <byte> capturedMonsterBits;
	consume_blob(112, //hardcoded size - likely to change in future updates
		capturedMonsterBits);
}


void packet_processor::deserialise_SRV_SHOW_ENTERING_MSG(UIDecodedPkt *uipkt)
{
	UInotifyStreamState(currentMsgStreamID, eStreamTransitionGame, uiMsgQueue);
	consume_add_dword_ntoh(L"AreaCode", uipkt);
}

void packet_processor::deserialise_SRV_HEARTBEAT(UIDecodedPkt *uipkt)
{
	//no data expected
}

void packet_processor::SRV_ADD_OBJ_decode_character(UIDecodedPkt *uipkt, size_t objBlobDataLen)
{
	rapidjson::Document::AllocatorType& allocator = uipkt->jsn.GetAllocator();
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

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
	uipkt->payload->AddMember(L"List1", list1, allocator);

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
		DWORD statIndex = customSizeByteGet();
		INT32 statValue = customSizeByteGet_signed();

		std::wstring statname;
		if (statIndex < ggpk->statDescriptions.size())
			statname = converter.from_bytes(ggpk->statDescriptions.at(statIndex));
		else
			statname = L"Unknown Stat";

		WValue statdat(rapidjson::kArrayType);
		statdat.PushBack((UINT32)statIndex, allocator);
		statdat.PushBack(WValue(statname.c_str(), allocator), allocator);
		statdat.PushBack((INT32)statValue, allocator);
		statlist.PushBack(statdat, allocator);
	}
	uipkt->payload->AddMember(L"StatList", statlist, allocator);

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
	ushort buffCount = consume_WORD();

	size_t blobRemaining = objBlobDataLen - (restorePoint.savedIndex - decryptedIndex);
	if ((buffCount * 27) > blobRemaining) {
		errorFlag = eErrUnderflow;
	}

	for (int i = 0; i < buffCount; i++)
	{
		WValue buffObj(rapidjson::kObjectType);
		buffObj.AddMember(L"BuffID", consume_WORD(), allocator);

		uint buffDefsRow = consume_WORD();
		buffObj.AddMember(L"BuffDefinitionsRow", buffDefsRow, allocator);

		uint buffVisualsRow = consume_WORD();
		buffObj.AddMember(L"BuffVisualsRow", buffVisualsRow, allocator);

		std::wstring buffname;
		if (buffDefsRow < ggpk->buffDefinitions_names_statCounts.size())
			buffname = converter.from_bytes(ggpk->buffDefinitions_names_statCounts.at(buffDefsRow).first);
		else
			buffname = L"Unknown buff definition";
		buffObj.AddMember(L"Buffname", WValue(buffname.c_str(), allocator), allocator);

		std::wstring buffvisualname;
		if (buffVisualsRow < ggpk->buffVisuals.size())
			buffvisualname = converter.from_bytes(ggpk->buffDefinitions_names_statCounts.at(buffDefsRow).first);
		else
			buffvisualname = L"Unknown buff visual";
		buffObj.AddMember(L"BuffVisualName", WValue(buffvisualname.c_str(), allocator), allocator);

		buffObj.AddMember(L"UnkDword1", (UINT32)consume_DWORD(), allocator);
		buffObj.AddMember(L"UnkShort2", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkDword3", (UINT32)consume_DWORD(), allocator);
		buffObj.AddMember(L"UnkShort4", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkShort5", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkShort6", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkShort7", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkShort8", consume_WORD(), allocator);
		buffObj.AddMember(L"UnkByte9", consume_Byte(), allocator);
		bufflist.PushBack(buffObj, allocator);
	}
	uipkt->payload->AddMember(L"BuffList", bufflist, allocator);

	ushort nameLen = ntohs(consume_WORD());

	consume_blob(3); //?????

	blobRemaining = objBlobDataLen - (restorePoint.savedIndex - decryptedIndex);
	if (nameLen > blobRemaining) {
		errorFlag = eErrUnderflow;
	}
	std::wstring msg = consumeWString(nameLen * 2);
	uipkt->add_wstring(L"Name", msg);

	uipkt->add_byte(L"UnkByte_AfterName", consume_Byte()); //bit tested in item rendering
	consume_add_dword(L"XP", uipkt);
	consume_add_dword(L"Unk_AN_3", uipkt);
	consume_add_byte(L"UnkByte_AN4", uipkt);
	consume_add_byte(L"UnkByte_AN5", uipkt);

	vector<byte> questStateBits;
	consume_blob(248, questStateBits);//hardcoded size - likely to change in future updates
	vector<byte> an_blob_2;
	consume_blob(56, an_blob_2);//hardcoded size - likely to change in future updates

	WValue unklist(rapidjson::kArrayType);
	ushort unkcount = 9; //???
	for (int i = 0; i < unkcount; i++)
	{
		WValue unkobj(rapidjson::kObjectType);
		unkobj.AddMember(L"D1",(UINT32)consume_DWORD(), allocator);
		unkobj.AddMember(L"D2", (UINT32)consume_DWORD(), allocator);
		unkobj.AddMember(L"Q3", (UINT64)consume_QWORD(), allocator);
		unklist.PushBack(unkobj, allocator);
	}
	uipkt->payload->AddMember(L"UnkList", unklist, allocator);

	ushort hideoutcode = consume_WORD();
	uipkt->add_word(L"HideoutCode", hideoutcode);

	std::wstring hideoutname;
	auto it = ggpk->hideouts.find(hideoutcode);
	if (it != ggpk->hideouts.end())
		hideoutname = converter.from_bytes(it->second);
	else
		hideoutname = L"Unknown Hideout";

	if (hideoutcode != 0)
	{
		uipkt->add_wstring(L"HideoutName", hideoutname);
		consume_add_byte(L"UnkBHideout", uipkt);

		byte bytescount = consume_Byte();
		if (bytescount)
		{
			std::wstring unkb1 = consume_hexblob(bytescount);
			WValue UnkBytes1(unkb1.c_str(), allocator);
			uipkt->payload->AddMember(L"UnkBytes1", UnkBytes1, allocator);
		}
	}
	else
		uipkt->add_wstring(L"HideoutName", L"None");

	consume_add_byte(L"UnkBAfterHideout", uipkt);

	byte prophecyCount = consume_Byte();
	WValue prophecylist(rapidjson::kArrayType);
	for (int i = 0; i < prophecyCount; i++)
	{
		UINT32 ref = consume_WORD();
		std::wstring prophecyName = ggpk->getProphecy(ref);

		WValue prophecy(rapidjson::kObjectType);
		prophecy.AddMember(L"DatReference", ref, allocator);
		prophecy.AddMember(L"Pos", consume_Byte(), allocator);
		prophecy.AddMember(L"ProphecyName", WValue(prophecyName.c_str(), allocator), allocator);
		prophecylist.PushBack(prophecy, allocator);
	}
	uipkt->payload->AddMember(L"Prophecies", prophecylist, allocator);

	DWORD d1 = consume_DWORD();
	byte b1 = consume_Byte();
	byte b2 = consume_Byte();
	byte b3 = consume_Byte();

	//handle obj worn items
	byte itemCount = consume_Byte();
	WValue wornItemVisuals(rapidjson::kArrayType);

	for (int i = 0; i < itemCount; i++)
	{
		WValue wornItem(rapidjson::kObjectType);
		wornItem.AddMember(L"Slot", consume_Byte(), allocator);
		//not seen any difference changing this either
		wornItem.AddMember(L"Unk2", consume_Byte(), allocator);

		UINT32 visIdentReference1 = consume_WORD();
		UINT32 visIdentReference2 = consume_WORD();
		UINT32 visualEffect = consume_WORD();
		std::wstring visIdentName1 = ggpk->getVisualIdentity(visIdentReference1);
		std::wstring visIdentName2 = ggpk->getVisualIdentity(visIdentReference2);
		std::wstring visEffectName = ggpk->getVisualEffect(visualEffect);

		wornItem.AddMember(L"VisualIdentity1", visIdentReference1, allocator);
		wornItem.AddMember(L"VisualIdentity1Name", WValue(visIdentName1.c_str(), allocator), allocator);
		wornItem.AddMember(L"VisualIdentity2", visIdentReference2, allocator);
		wornItem.AddMember(L"VisualIdentity2Name", WValue(visIdentName2.c_str(), allocator), allocator);
		wornItem.AddMember(L"ItemVisualEffect", visualEffect, allocator);
		wornItem.AddMember(L"ItemVisualEffectName", WValue(visEffectName.c_str(), allocator), allocator);

		//not seen any difference when 1/0 on identical item
		wornItem.AddMember(L"Unk5", consume_Byte(), allocator);
		wornItemVisuals.PushBack(wornItem, allocator);
	}
	uipkt->payload->AddMember(L"WornItems", wornItemVisuals, allocator);

	//other sec - animation?
	consume_add_word(L"UnkX1", uipkt);
	consume_add_byte(L"UnkX2", uipkt);

	//if [something] > 0: 
	//get another byte (animation related)

	//this section may depend on class or something else  1408EE715
	consume_add_word(L"UnkX2", uipkt);

	//skills. horridly big function but worth it to see peoples loadouts
	//expect to see: gem types, gem levels/stats/corruptions, links, passives, microtransactions 

	UINT32 skillflags = consume_WORD();
	uipkt->add_word(L"SkillFlags", skillflags);

	if (skillflags & 0x40)
		consume_add_word(L"Skill0x40", uipkt);
	else if (skillflags & 0x20)
	{
		//lots of stuff
	}

	//even more stuff oh no
	//aintnobodygottimeforthat.jpg

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

	unsigned short objBlobDataLen = ntohs(consume_WORD());
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

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string hashResult;
	std::string hashCategory;
	ggpk->lookup_hash(objMurmurHash, hashResult, hashCategory);

	uipkt->add_wstring(L"HashCategory", converter.from_bytes(hashCategory));
	uipkt->add_wstring(L"HashResult", converter.from_bytes(hashResult));

	if (hashCategory == "Character")
		SRV_ADD_OBJ_decode_character(uipkt, objBlobDataLen);
	//else object
	//else npc, etc
	
}

//same as 0x135 to deserialise but no hash DWORD
//this would be really interesting to decode - probably shares lots of code with 135 too
void packet_processor::deserialise_SRV_UPDATE_OBJECT(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);
	
	unsigned short dataLen = ntohs(consume_WORD());
	uipkt->add_word(L"DataLen", dataLen);
	consume_blob(dataLen); //todo!
}

void packet_processor::deserialise_SRV_IDNOTIFY_0x137(UIDecodedPkt *uipkt)
{
	consume_add_dword_ntoh(L"ID1", uipkt);
	consume_add_dword_ntoh(L"ID2", uipkt);
	consume_add_word_ntoh(L"ID3", uipkt);
}