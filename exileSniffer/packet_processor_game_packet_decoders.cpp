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
	packetDeserialisers[CLI_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG;
	packetDeserialisers[CLI_CHAT_MSG_ITEMS] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG_ITEMS;
	packetDeserialisers[CLI_PING_CHALLENGE] = (deserialiser)&packet_processor::deserialise_CLI_PING_CHALLENGE;
	packetDeserialisers[CLI_CHAT_COMMAND] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_COMMAND;
	packetDeserialisers[SRV_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_CHAT_MESSAGE;
	packetDeserialisers[SRV_SERVER_MESSAGE] = (deserialiser)&packet_processor::deserialise_SRV_SERVER_MESSAGE;
	packetDeserialisers[CLI_LOGGED_OUT] = (deserialiser)&packet_processor::deserialise_CLI_LOGGED_OUT;
	packetDeserialisers[CLI_ACTION_PREDICTIVE] = (deserialiser)&packet_processor::deserialise_CLI_ACTION_PREDICTIVE;
	packetDeserialisers[CLI_USE_BELT_SLOT] = (deserialiser)&packet_processor::deserialise_CLI_USE_BELT_SLOT;
	packetDeserialisers[CLI_USE_ITEM] = (deserialiser)&packet_processor::deserialise_CLI_USE_ITEM;
	packetDeserialisers[CLI_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
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
	//pkt_CLI_CHAT_MSG_ITEMS decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	//decodedObj.finalise(decryptedIndex);
}

void packet_processor::deserialise_CLI_CHAT_MSG(UIDecodedPkt *uipkt)
{
	ushort msgLenWords = consumeUShort();
	std::wstring msg = consumeWString(msgLenWords * 2);
	uipkt->add_wstring(L"Message", msg);
	uipkt->add_byte(L"NumLinkedItems", consume_Byte());
}

void packet_processor::deserialise_CLI_PING_CHALLENGE(UIDecodedPkt *uipkt)
{
	uipkt->add_dword(L"Challenge", consume_DWORD());
}

void packet_processor::deserialise_CLI_CHAT_COMMAND(UIDecodedPkt *uipkt)
{
	//todo
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
	//no data expected
}

void packet_processor::deserialise_CLI_USE_BELT_SLOT(UIDecodedPkt *uipkt)
{
	//todo
	/*
				//003700000004 = 5th slot
			unsigned long slot = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			std::cout << std::hex << "Player activated potion slot 0x" << slot << std::endl;
	*/
}

void packet_processor::deserialise_CLI_USE_ITEM(UIDecodedPkt *uipkt)
{
	//todo
	/*
				unsigned long unk1 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long item1 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long unk2 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long item2 = getUlong(decryptedBuffer + sIdx); sIdx += 4;

			std::cout << std::hex << "Player activated item 0x" << item1 << " on item 0x" << item2;
			std::cout << "i1unk: 0x" << unk1 << " i2unk: 0x" << unk2 << std::endl;
	*/
}

void packet_processor::deserialise_CLI_ACTION_PREDICTIVE(UIDecodedPkt *uipkt)
{
	uipkt->add_dword(L"TargCoord1", consume_DWORD());
	uipkt->add_dword(L"TargCoord2", consume_DWORD());
	uipkt->add_dword(L"SkillID", consumeUShort());
	uipkt->add_dword(L"PkCount", consumeUShort());
	uipkt->add_byte(L"Modifier", consume_Byte());
}

void packet_processor::deserialise_CLI_MOUSE_RELEASE(UIDecodedPkt *uipkt)
{
	//no data expected
}