#pragma once

//login server
#define LOGIN_CLI_KEEP_ALIVE 0x1
#define LOGIN_EPHERMERAL_PUBKEY 0x2
#define LOGIN_CLI_AUTH_DATA 0x3
#define LOGIN_SRV_UNK0x4 0x4
#define LOGIN_CLI_CHANGE_PASSWORD 0x7
#define LOGIN_CLI_DELETE_CHARACTER 0x9
#define LOGIN_CLI_CHARACTER_SELECTED_SELECTED 0xb
#define LOGIN_SRV_NOTIFY_GAMESERVER 0xf
#define LOGIN_CLI_CREATED_CHARACTER 0xd
#define LOGIN_SRV_CHAR_LIST 0x10
#define LOGIN_SRV_FINAL_PKT 0x11
#define LOGIN_CLI_REQUEST_RACE_DATA 0x12
#define LOGIN_SRV_LEAGUE_LIST 0x13
#define LOGIN_CLI_REQUEST_LEAGUES 0x23

//game server
#define SRV_PKT_ENCAPSULATED 0x05
#define CLI_CHAT_MSG_ITEMS (SRV_PKT_ENCAPSULATED+1) //0x6
//7
#define CLI_CHAT_MESSAGE 0x8
#define CLI_CHAT_COMMAND (CLI_CHAT_MESSAGE+1) //0x9
#define SRV_CHAT_MESSAGE (CLI_CHAT_COMMAND+1) //0xa
#define SRV_SERVER_MESSAGE (SRV_CHAT_MESSAGE+1) //0xb
#define CLI_LOGGED_OUT (SRV_SERVER_MESSAGE+1) //0xc
#define CLI_PING_CHALLENGE (CLI_LOGGED_OUT+1) //0xd
#define SRV_PING_RESPONSE (CLI_PING_CHALLENGE+1) //0xe
#define SRV_AREA_INFO (SRV_PING_RESPONSE+1) //0xf
//10?
//11?
#define SRV_PRELOAD_MONSTER_LIST 0x12
#define SRV_UNK_0x13 (SRV_PRELOAD_MONSTER_LIST+1) //0x13
#define SRV_PLAYER_ITEMS (SRV_UNK_0x13+1) //0x14
#define CLI_CLICKED_GROUND_ITEM (SRV_PLAYER_ITEMS+1) //0x15
#define CLI_ACTION_PREDICTIVE (CLI_CLICKED_GROUND_ITEM+1) //0x16
#define SRV_TRANSFER_INSTANCE (CLI_ACTION_PREDICTIVE+1) //0x17
#define SRV_INSTANCE_SERVER_DATA (SRV_TRANSFER_INSTANCE+1) //0x18
#define CLI_PICKUP_ITEM (SRV_INSTANCE_SERVER_DATA+1) //0x19
//1a
#define CLI_PLACE_ITEM 0x1b
//1c
#define CLI_REMOVE_SOCKET 0x1d
#define CLI_INSERT_SOCKET (CLI_REMOVE_SOCKET+1) //0x1e
#define CLI_LEVEL_SKILLGEM (CLI_INSERT_SOCKET+1) //0x1f
#define CLI_UNK_0x20 (CLI_LEVEL_SKILLGEM+1) //0x20
#define CLI_SKILLPOINT_CHANGE (CLI_UNK_0x20+1) //0x21
//22
//23
#define CLI_CHOSE_ASCENDANCY 0x24
//25
//26
//27
//28
//29
//2a
#define CLI_CANCEL_BUF 0x2b
#define CLI_UNK_0x2c 0x2c
//2d
#define CLI_SET_HOTBARSKILL 0x2e
#define SRV_SKILL_SLOTS_LIST (CLI_SET_HOTBARSKILL+1)
//30
//31
//32
//33
//34
//35
//36
/*
player dies:
S->C UnkPkID: 0x31 size: 7 bytes
00310c00000000
[f1] Server sent stat update
00f1000002080000017550010189cb010132013600000208ffffffff000000020301013600000208ffffffff0000000705010000000000
S->C UnkPkID: 0xef size: 23 bytes
00ef0000017300000173500081ef000000000208010132
*/
#define CLI_USE_BELT_SLOT 0x0037
#define CLI_USE_ITEM 0x0038
//39
//3a
//3b
//3c
//3d
//3e
#define SRV_OPEN_UI_PANE 0x3f
//40
#define CLI_UNK_0x41 0x41
//42
//43
//44
//45
#define CLI_SELECT_NPC_DIALOG 0x46 
#define SRV_SHOW_NPC_DIALOG 0x47 
#define CLI_CLOSE_NPC_DIALOG 0x48 
//49
//4a
//4b
//4c
//4d
//4e
//4f
#define CLI_SEND_PARTY_INVITE 0x50
//51
#define CLI_TRY_JOIN_PARTY 0x52
#define CLI_DISBAND_PUBLIC_PARTY (CLI_TRY_JOIN_PARTY+1) //0x53
//54
#define CLI_CREATE_PUBLICPARTY 0x55
#define CLI_UNK_x56 (CLI_CREATE_PUBLICPARTY+1) //0x56
#define CLI_GET_PARTY_DETAILS (CLI_UNK_x56 + 1) //0x57
#define SRV_FRIENDSLIST (CLI_GET_PARTY_DETAILS+1) //0x58
//59
#define SRV_PARTY_DETAILS 0x5a
#define SRV_PARTY_ENDED 0x5b //one dword party id arg -- unimplemented
//5c
#define CLI_REQUEST_PUBLICPARTIES 0x5d
#define SRV_PUBLIC_PARTY_LIST (CLI_REQUEST_PUBLICPARTIES+1)
//5f
//60
//61
//62
#define CLI_MOVE_ITEM_PANE 0x63
//64
//65
//66
//67
//68
//69
//6a
//6b
//6c
#define SRV_CREATE_ITEM 0x6d
#define SRV_SLOT_ITEMSLIST (SRV_CREATE_ITEM+1)
//6f
#define UNK_MESSAGE_0x70 0x70
#define CLI_UNK_0x71 0x71
#define SRV_UNK_0x72 0x72
#define UNK_MESSAGE_0x73 0x73
#define CLI_SET_STATUS_MESSAGE 0x74
//75
//76
//77
//78
//79
//7a
//7b
//7c
//7d
//7e
#define CLI_SWAPPED_WEAPONS 0x7f
//80
//81
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
//8d
//8e
//define 0x8f seen when leaving duel queue
//define 0x90 seen when leaving duel queue
#define SRV_PVP_MATCHLIST 0x91
#define SRV_EVENTSLIST 0x92
//93
//94
//95
//96
//97
#define CLI_SKILLPANE_ACTION 0x98
//99
//9a
#define SRV_SKILLPANE_DATA 0x9b
//9c
//9d
//9e
#define CLI_MICROTRANSACTION_SHOP_ACTION 0x9f
//a0
#define SRV_MICROTRANSACTION_SHOP_DETAILS 0xa1
//a2
#define SRV_UNK_A3 0xa3
#define SRV_CHAT_CHANNEL_ID 0xa4
//a5
//a6
//a7
//a8
//a9
//aa
//ab
//ac
#define CLI_GUILD_CREATE 0xAD
//ae
//af
//b0
//b1
//b2
//b3
//b4
//b5
//b6
//b7
//b8
//b9
//ba
//bc
//bd
//be
//bf
#define CLI_PACKET_EXIT 0xc0
#define SRV_LOGINSRV_CRYPT 0xc1 
#define CLI_DUEL_CHALLENGE 0xc2
#define SRV_DUEL_RESPONSE 0xc3
#define SRV_DUEL_CHALLENGE 0xc4 //namestring, byte. unimplemented
//c5
#define CLI_UNK_0xC6 0xc6 //both sent after clickign join pvp
#define CLI_UNK_0xC7 0xc7
//c8
//c9
#define SRV_UNK_0xCA 0xca
//cb
//cd
#define CLI_VISIT_HIDEOUT 0xce //unimplmented. 00 CE [namestring] [dword]
//cf
//d0
//d1
//d2
//d3
//d4
#define SRV_UNK_0xD5 0xd5
//d6
//d7
#define CLI_USED_SKILL 0xd8
#define CLI_CLICK_OBJ (CLI_USED_SKILL+1) //0xd9
#define CLI_MOUSE_HELD (CLI_CLICK_OBJ+1) //0xda
//db
#define CLI_MOUSE_RELEASE 0xdc
//dd
//de
//df
#define CLI_OPEN_WORLD_SCREEN 0xe0
//e1
//e2
//e3
//e4
//e5
#define SRV_UNK_0xE6 0xe6
//e7
//e8
#define SRV_OBJ_REMOVED 0xe9 
#define SRV_MOBILE_START_SKILL 0xea
#define SRV_MOBILE_FINISH_SKILL 0xeb
//ec
//ed
#define SRV_MOBILE_UNK_0xee 0xee
#define SRV_MOBILE_UNK_0xef 0xef
#define SRV_MOBILE_UPDATE_HMS 0xf0
#define SRV_STAT_CHANGED 0xf1
#define SRV_UNK_0xf2 0xf2
#define SRV_UNK_0xf3 0xf3
//f4
//f5
//f6
//f7
//f8
//f9
#define SRV_START_EFFECT 0xfa
#define SRV_END_EFFECT 0xfb
//fc
//fd
//fe
//ff
//100
//101
//102
//103
//104
//105
//106
//107
//108
//109
//10a
//10b
//10c
//10d
#define CLI_REQUEST_PLAYERID 0x10e
#define SRV_NOTIFY_PLAYERID 0x10f
//0x110 - player pressed add new stash tab +?
#define SRV_UNKNOWN_0x111 0x111
#define CLI_NEW_STASHTAB 0x112
//113
//114
//115
//116
//117
#define SRV_UNKNOWN_0x118 0x118 //effectively pkt 0x111 loop2 deserialiser
//119
//11a
//11b
#define CLI_OPTOUT_TUTORIALS 0x11c //gets 0xff response
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
//127
//128
//129
//12a
//12b
//12c
//12d
//12e
#define SRV_SHOW_ENTERING_MSG 0x12f
//130
//131
#define SRV_HEARTBEAT 0x132
//133
//134
#define SRV_ADD_OBJECT 0x135
#define SRV_UPDATE_OBJECT 0x136
#define SRV_IDNOTIFY_0x137 0x137
//138
//139
#define SRV_UNK_13A 0x13a
#define MSG_IDS_END (SRV_UNK_13A+1)