#pragma once

//login server
#define LOGIN_CLI_KEEP_ALIVE 0x1
#define LOGIN_EPHERMERAL_PUBKEY 0x2
#define LOGIN_CLI_AUTH_DATA 0x3
#define LOGIN_SRV_UNK0x4 0x4
#define LOGIN_CLI_RESYNC 0x6
#define LOGIN_CLI_CHANGE_PASSWORD 0x7
#define LOGIN_CLI_DELETE_CHARACTER 0x9
#define LOGIN_CLI_CHARACTER_SELECTED 0xb
#define LOGIN_CLI_CREATED_CHARACTER 0xd
#define LOGIN_SRV_NOTIFY_GAMESERVER 0xf
#define LOGIN_SRV_CHAR_LIST 0x10
#define LOGIN_SRV_FINAL_PKT 0x11
#define LOGIN_CLI_REQUEST_RACE_DATA 0x12
#define LOGIN_SRV_LEAGUE_LIST 0x13
#define LOGIN_CLI_REQUEST_LEAGUES 0x23
#define LOGIN_CLI_UNK0x24 0x24

//game server
#define SRV_PKT_ENCAPSULATED 0x05
#define CLI_CHAT_MSG_ITEMS (SRV_PKT_ENCAPSULATED+1) //0x6
//7
#define CLI_CHAT_MESSAGE 0x8
#define CLI_CHAT_COMMAND (CLI_CHAT_MESSAGE+1) //0x9
#define SRV_CHAT_MESSAGE (CLI_CHAT_COMMAND+1) //0xa
#define SRV_SERVER_MESSAGE (SRV_CHAT_MESSAGE+1) //0xb
#define CLI_LOGGED_OUT (SRV_SERVER_MESSAGE+1) //0xc
#define CLI_HNC (CLI_LOGGED_OUT+1) //0xd
#define SRV_HNC (CLI_HNC+1) //0xe
#define SRV_AREA_INFO (SRV_HNC+1) //0xf
//10?
//11?
#define SRV_PRELOAD_MONSTER_LIST 0x12
#define SRV_UNK_0x13 (SRV_PRELOAD_MONSTER_LIST+1) //0x13
#define SRV_ITEMS_LIST (SRV_UNK_0x13+1) //0x14
#define CLI_CLICKED_GROUND_ITEM (SRV_ITEMS_LIST+1) //0x15
#define CLI_ACTION_PREDICTIVE (CLI_CLICKED_GROUND_ITEM+1) //0x16
#define SRV_TRANSFER_INSTANCE (CLI_ACTION_PREDICTIVE+1) //0x17
#define SRV_INSTANCE_SERVER_DATA (SRV_TRANSFER_INSTANCE+1) //0x18
#define CLI_PICKUP_ITEM (SRV_INSTANCE_SERVER_DATA+1) //0x19
#define CLI_DROP_ITEM (CLI_PICKUP_ITEM+1)
#define CLI_PLACE_ITEM (CLI_DROP_ITEM+1) 
//1c
#define CLI_REMOVE_SOCKET 0x1d
#define CLI_INSERT_SOCKET (CLI_REMOVE_SOCKET+1) //0x1e
#define CLI_LEVEL_SKILLGEM (CLI_INSERT_SOCKET+1) //0x1f
#define SRV_UNK_0x20 (CLI_LEVEL_SKILLGEM+1) //0x20
#define CLI_SKILLPOINT_CHANGE (SRV_UNK_0x20+1) //0x21
//22
//23
#define CLI_CHOSE_ASCENDANCY 0x24
//25
//26
//27
//28
//29
//2a
#define CLI_MERGE_STACK 0x2b
#define CLI_CANCEL_BUF (CLI_MERGE_STACK+1)
#define SRV_UNK_0x2c (CLI_CANCEL_BUF + 1)
#define CLI_SELECT_MAPTRAVEL (SRV_UNK_0x2c + 1) //2e
#define CLI_SET_HOTBARSKILL (CLI_SELECT_MAPTRAVEL +1) //2f
#define SRV_SKILL_SLOTS_LIST (CLI_SET_HOTBARSKILL+1) //30
#define CLI_REVIVE_CHOICE (SRV_SKILL_SLOTS_LIST+1) //31
#define SRV_YOU_DIED (CLI_REVIVE_CHOICE+1) //"thats dark souls" 0x32
#define CLI_ACTIVATE_ITEM (SRV_YOU_DIED + 1) //0x33
//34
//35
//36
#define CLI_USE_BELT_SLOT 0x0037
#define CLI_USE_ITEM_ON_ITEM (CLI_USE_BELT_SLOT+1) //0x38
//39
//3a
#define CLI_USE_ITEM_ON_OBJ 0x3b
//3c
//3d
//3e
#define SRV_OPEN_UI_PANE 0x3f
#define CLI_SPLIT_STACK (SRV_OPEN_UI_PANE+1)
#define CLI_UNK_0x41 0x41
#define CLI_UNK_0x42 0x42
//43
//44
//45
#define CLI_SELECT_NPC_DIALOG 0x46 
#define SRV_SHOW_NPC_DIALOG (CLI_SELECT_NPC_DIALOG+1)
#define CLI_CLOSE_NPC_DIALOG (SRV_SHOW_NPC_DIALOG+1)
//49
#define CLI_UNK_0x4a  //seen when buying from vendor
//4b
//4c
#define SRV_UNK_0x4d  //seen when buying from vendor
//4e
#define SRV_LIST_PORTALS 0x4f
#define CLI_SEND_PARTY_INVITE (SRV_LIST_PORTALS+1) //0x50
//51
#define CLI_TRY_JOIN_PARTY 0x52
#define CLI_DISBAND_PUBLIC_PARTY (CLI_TRY_JOIN_PARTY+1) //0x53
//54
#define CLI_CREATE_PUBLICPARTY 0x56
#define CLI_UNK_x57 (CLI_CREATE_PUBLICPARTY+1) //0x57
#define CLI_GET_PARTY_DETAILS (CLI_UNK_x57 + 1) //0x58
#define SRV_FRIENDSLIST (CLI_GET_PARTY_DETAILS+1) //0x59
//5a
#define SRV_PARTY_DETAILS 0x5b
#define SRV_PARTY_ENDED 0x5c //one dword party id arg -- unimplemented
//5d
#define CLI_REQUEST_PUBLICPARTIES 0x5e
#define SRV_PUBLIC_PARTY_LIST (CLI_REQUEST_PUBLICPARTIES+1)
//60
//61
//62
#define CLI_UNK_0x62 0x63//seen while selling stuff to vendor
#define CLI_MOVE_ITEM_PANE 0x64
//65
#define CLI_CONFIRM_SELL 0x66
//67
#define SRV_UNK_0x68 0x68//seen while selling stuff to vendor
#define SRV_UNK_0x69 0x69//seen while selling stuff to vendor
//6a
//6b
//6c   CLI_QUEST_DIALOGUE_CHOICE
#define SRV_UNK_0x6d 0x6d
#define SRV_CREATE_ITEM (SRV_UNK_0x6d +1)
#define SRV_SLOT_ITEMSLIST (SRV_CREATE_ITEM+1)
#define SRV_INVENTORY_SET_REMOVE (SRV_SLOT_ITEMSLIST+1)
#define SRV_GRANTED_XP (SRV_INVENTORY_SET_REMOVE+1)
#define CLI_SELECT_STASHTAB (SRV_GRANTED_XP+1)
#define SRV_STASHTAB_DATA (CLI_SELECT_STASHTAB+1)
#define SRV_UNK_0x74 (SRV_STASHTAB_DATA+1)
#define CLI_SET_STATUS_MESSAGE 0x75
#define SRV_MOVE_OBJECT (CLI_SET_STATUS_MESSAGE+1)
//77
//78
//79
//7a
//7b
//7c
#define CLI_ACTIVATE_MAP 0x7d //todo no data
//7e
//7f
#define CLI_SWAPPED_WEAPONS 0x80
//81
#define SRV_ADJUST_LIGHTING 0x82
#define CLI_TRANSFER_ITEM 0x83
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
#define SRV_INVENTORY_FULL 0x8e
//8f
//define 0x90 seen when leaving duel queue
//define 0x91 seen when leaving duel queue
#define SRV_PVP_MATCHLIST 0x92
#define SRV_EVENTSLIST 0x93
//94
//95
//96
//97
//98
#define CLI_SKILLPANE_ACTION 0x99
#define SRV_ACHIEVEMENT_1 (CLI_SKILLPANE_ACTION+1)
#define SRV_ACHIEVEMENT_2 (SRV_ACHIEVEMENT_1+1)
#define SRV_SKILLPANE_DATA (SRV_ACHIEVEMENT_2+1)
#define SRV_UNK_POSITION_LIST (SRV_SKILLPANE_DATA+1)
//9e
//9f
#define CLI_MICROTRANSACTION_SHOP_ACTION 0xa0
//a1
#define SRV_MICROTRANSACTION_SHOP_DETAILS 0xa2
//a3
#define CLI_UNK_A4 0xa4
#define SRV_CHAT_CHANNEL_ID 0xa5
#define SRV_UNK_A6 (SRV_CHAT_CHANNEL_ID+1)
#define SRV_UNK_A7 0xa7
//a8
//a9
//aa
//ab
//ac
//ad
#define CLI_GUILD_CREATE 0xAe
//af
//b0
//b1
//b2
//b3
//b4
//b5
#define SRV_GUILD_MEMBER_LIST 0xb6
//b7
//b8
//b9 
//ba //srv guild status message
//bc //cli set guild status message
//bd
//be
//bf
//c0
#define CLI_EXIT_TO_CHARSCREEN 0xc1
#define SRV_LOGINSRV_CRYPT 0xc2 
#define CLI_DUEL_CHALLENGE 0xc3
#define SRV_DUEL_RESPONSE 0xc4
#define SRV_DUEL_CHALLENGE 0xc5 //namestring, byte. unimplemented
//c6
#define CLI_UNK_0xC7 0xc7 //both sent after clicking join pvp
#define CLI_UNK_0xC8 0xc8
//c9
//ca
#define SRV_UNK_0xCB 0xcb
//cc
//cd
//ce
#define CLI_VISIT_HIDEOUT 0xcf //unimplmented. 00 Cf [namestring] [dword]
//d0
//d1
//d2
//d3
//d4
//d5
#define SRV_EVENTSLIST_2 0xd6
//d7
//d8
#define CLI_USED_SKILL 0xd9
#define CLI_CLICK_OBJ (CLI_USED_SKILL+1) //0xda
#define CLI_MOUSE_HELD (CLI_CLICK_OBJ+1) //0xdb
#define SRV_NOTIFY_AFK (CLI_MOUSE_HELD+1) //0xdc ...seems like kinda weird ordering?
#define CLI_MOUSE_RELEASE (SRV_NOTIFY_AFK+1) //0xdd
//de
//df
//e0
#define CLI_OPEN_WORLD_SCREEN 0xe1
//e2
//e3
//e4
#define SRV_UNK_0xE5 0xe5
//e6
#define SRV_UNK_0xE7 0xe7
//e8
//e9
#define SRV_OBJ_REMOVED 0xea 
#define SRV_MOBILE_START_SKILL (SRV_OBJ_REMOVED+1)
#define SRV_MOBILE_FINISH_SKILL (SRV_MOBILE_START_SKILL+1)
#define SRV_MOVE_CHANNELLED (SRV_MOBILE_FINISH_SKILL+1)
#define SRV_END_CHANNELLED (SRV_MOVE_CHANNELLED+1)
#define SRV_MOBILE_UNK_0xef (SRV_END_CHANNELLED+1)
#define SRV_MOBILE_UNK_0xf0 (SRV_MOBILE_UNK_0xef+1)
#define SRV_MOBILE_UPDATE_HMS (SRV_MOBILE_UNK_0xf0+1)
#define SRV_STAT_CHANGED (SRV_MOBILE_UPDATE_HMS+1)
#define SRV_UNK_0xf3 0xf3
#define SRV_UNK_0xf4 0xf4 //aura?
//f5
#define SRV_UNK_0xf6 0xf6
#define SRV_UNK_0xf7 0xf7 //seem in kaom's dream
#define SRV_UNK_0xf8 0xf8
#define SRV_UNK_0xf9 0xf9
//fa
#define SRV_START_EFFECT 0xfb
#define SRV_END_EFFECT 0xfc
//fd  some sort of moving item/trap. seen in crypt ascendency area
//fe
//ff
#define SRV_EVENT_TRIGGERED 0x100
//101 failed door unlock? fail opening door in crypt ascendency area
//102
//103
//104
//105
//106
#define SRV_UNKNOWN_0x107 0x107
//108
#define SRV_UNKNOWN_0x109 0x109
//10a
//10b
//10c
//10d
//10e
#define CLI_FINISHED_LOADING 0x10f
#define SRV_NOTIFY_PLAYERID 0x110
//0x111 - player pressed add new stash tab +?
#define SRV_UNKNOWN_0x112 0x112
#define CLI_NEW_STASHTAB 0x113
//114
//115
//116
//117
//118
#define SRV_UNKNOWN_0x119 0x119 //effectively pkt 0x111 loop2 deserialiser
//11a
#define SRV_UNKNOWN_0x11B 0x11b
//11c
#define CLI_OPTOUT_TUTORIALS 0x11d //gets 0xff response
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
#define SRV_BESTIARY_CAPTIVES 0x128
//129
//12a
#define CLI_OPEN_BESTIARY 0x12b
//12c
#define SRV_BESTIARY_UNLOCKED_LIST 0x12d
//12e
//12f
#define SRV_SHOW_ENTERING_MSG 0x130
//131
//132
#define SRV_HEARTBEAT 0x133
//134
//135
#define SRV_ADD_OBJECT 0x136
#define SRV_UPDATE_OBJECT 0x137
#define SRV_IDNOTIFY_0x138 0x138
//139
//13a
#define SRV_UNK_13B 0x13b
#define MSG_IDS_END (SRV_UNK_13B+1)