#pragma once

//login server
#define LSRV_GAMESERVER_INFO (SRV_PING_RESPONSE+1) //0xf - loginserver


#define SRV_PKT_ENCAPSULATED 0x05
#define CLI_CHAT_MSG_ITEMS 0x06
#define CLI_CHAT_MESSAGE 0x8
#define CLI_CHAT_COMMAND 0x9
#define SRV_CHAT_MESSAGE 0x0a
#define SRV_SERVER_MESSAGE 0xb
#define CLI_LOGGED_OUT 0xc
#define CLI_PING_CHALLENGE 0xd
#define SRV_PING_RESPONSE (CLI_PING_CHALLENGE+1) //0xe
#define SRV_AREA_INFO 0xf //gameserver

#define SRV_PRELOAD_MONSTER_LIST 0x12

#define SRV_PLAYER_ITEMS 0x14
#define CLI_CLICKED_GROUND_ITEM 0x15
#define CLI_ACTION_PREDICTIVE (CLI_CLICKED_GROUND_ITEM+1) //0x16

#define SRV_INSTANCE_SERVER_DATA (0x18)
#define CLI_PICKUP_ITEM (SRV_INSTANCE_SERVER_DATA+1)

#define CLI_PLACE_ITEM 0x1b

#define CLI_REMOVE_SOCKET 0x1d
#define CLI_INSERT_SOCKET (CLI_REMOVE_SOCKET+1)

#define CLI_LEVEL_SKILLGEM 0x1f

#define CLI_SKILLPOINT_CHANGE 0x21

#define CLI_CANCEL_BUF 0x2b

#define CLI_SET_HOTBARSKILL 0x2e
#define SRV_SKILL_SLOTS_LIST (CLI_SET_HOTBARSKILL+1)


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

#define SRVPK_STASH_INFO 0x3f

#define CLI_UNK_x56 0x5d

#define CLI_REQUEST_PUBLICPARTIES 0x5d
#define SRV_RESPOND_PUBLICPARTIES (CLI_REQUEST_PUBLICPARTIES+1)

#define SRV_CREATE_ITEM 0x6d
#define SRV_SLOT_ITEMSLIST 0x6e

#define CLI_SWAPPED_WEAPONS 0x7f

#define CLI_SKILLPANE_ACTION 0x98
#define SRV_SKILLPANE_DATA 0x9b
#define CLI_MICROSTRANSACTIONPANE_ACTION 0x9f

#define CLI_PACKET_EXIT 0xc0

#define CLI_USED_SKILL 0xd8
#define CLI_CLICK_OBJ 0xd9
#define CLI_MOUSE_HELD 0xda
#define CLI_MOUSE_RELEASE 0xdc

#define SRV_MICROSTRANSACTIONSPANE_RESP 0xa1
#define SRV_DISPLAY_BUILTIN_MSG 0xa4

#define CLI_GUILD_CREATE 0xAD

#define SRV_MOBILE_USED_SKILL 0xea
#define SRV_MOBILE_UPDATE_HMS 0xf0
#define SRV_STAT_CHANGED 0xf1
#define SRV_CRITTER_MOVEMENT 0xf3
#define SRV_START_EFFECT 0xfa
#define SRV_END_EFFECT 0xfb

#define SRV_UNKNOWN_0x111 0x111

#define CLI_OPTOUT_TUTORIALS 0x11c //gets 0xff response
#define SRV_HEARTBEAT 0x132
#define SRV_ADD_OBJECT 0x135
#define SRV_UNK_13A 0x13a