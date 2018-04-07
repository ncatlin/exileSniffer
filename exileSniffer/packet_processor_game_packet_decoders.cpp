/*
These member functions attempt to reassemble the raw packet bytes 
into meaningful data as the game client/server would interpret it
*/
#include "stdafx.h"
#include "packet_processor.h"
#include "packetIDs.h"


void packet_processor::init_packetDeserialisers()
{
	//packetDeserialisers[pkt_SRV_PKT_ENCAPSULATED] //see packet_processor::handle_packet_from_gameserver
	packetDeserialisers[CLI_CHAT_MSG_ITEMS] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG_ITEMS;
	packetDeserialisers[CLI_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG;
	packetDeserialisers[CLI_PING_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_PING_CHALLENGE;
	packetDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	packetDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	packetDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	packetDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;

	packetDeserialisers[CLI_CLICKED_GROUND_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_CLICKED_GROUND_ITEM;
	packetDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;

	packetDeserialisers[CLI_PICKUP_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PICKUP_ITEM;
	packetDeserialisers[CLI_PLACE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_PLACE_ITEM;
	packetDeserialisers[CLI_REMOVE_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_REMOVE_SOCKET;
	packetDeserialisers[CLI_INSERT_SOCKET] = (deserialiser)&packet_processor::deserialise_CLI_INSERT_SOCKET;

	packetDeserialisers[CLI_LEVEL_SKILLGEM] = (deserialiser)&packet_processor::deserialise_CLI_LEVEL_SKILLGEM;
	packetDeserialisers[CLI_SKILLPOINT_CHANGE] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPOINT_CHANGE;
	packetDeserialisers[CLI_CANCEL_BUF] = (deserialiser)&packet_processor::deserialise_CLI_CANCEL_BUF;
	packetDeserialisers[CLI_SET_HOTBARSKILL] = (deserialiser)&packet_processor::deserialise_CLI_SET_HOTBARSKILL;

	packetDeserialisers[CLI_USE_BELT_SLOT] = (deserialiser)&packet_processor::deserialise_CLI_USE_BELT_SLOT;
	packetDeserialisers[CLI_USE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_USE_ITEM;

	packetDeserialisers[CLI_REQUEST_PUBLICPARTIES] = (deserialiser)&packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES;
	packetDeserialisers[CLI_SKILLPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_SKILLPANE_ACTION;
	packetDeserialisers[CLI_MICROSTRANSACTIONPANE_ACTION] = (deserialiser)&packet_processor::deserialise_CLI_MICROSTRANSACTIONPANE_ACTION;
	packetDeserialisers[CLI_USED_SKILL] = (deserialiser)&packet_processor::deserialise_CLI_USED_SKILL;
	packetDeserialisers[CLI_CLICK_OBJ] = (deserialiser)&packet_processor::deserialise_CLI_CLICK_OBJ;
	packetDeserialisers[CLI_MOUSE_HELD] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_HELD;
	packetDeserialisers[CLI_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
	packetDeserialisers[CLI_OPTOUT_TUTORIALS] = (deserialiser)&packet_processor::deserialise_CLI_OPTOUT_TUTORIALS;
}

/*
pkt_CLI_CHAT_COMMAND packet_processor::deserialise_CLI_CHAT_COMMAND()
{
pkt_CLI_CHAT_COMMAND cliChatCmd(decryptedBuffer, decryptedIndex);
/*---deserialise contents here---*/

//todo

/*---deserialising done---*/
/*
cliChatCmd.length = decryptedIndex - cliChatCmd.startIdx;
return cliChatCmd;
}

*/

/*
this is deserialised within the processing loop as part of stream crypt resynchronisation
the packet within is then deserialised and actioned
this function only here for completeness - it should not be used!
*/
void packet_processor::deserialise_SRV_PKT_ENCAPSULATED(UIDecodedPkt *uipkt)
{
	assert(false);
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


void packet_processor::deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_SKILLPANE_ACTION(UIDecodedPkt *uipkt)
{
	//todo
}

void packet_processor::deserialise_CLI_MICROSTRANSACTIONPANE_ACTION(UIDecodedPkt *uipkt)
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

void packet_processor::deserialise_CLI_OPTOUT_TUTORIALS(UIDecodedPkt *uipkt)
{
	//todo
}