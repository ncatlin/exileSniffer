/*
These member functions attempt to reassemble the raw packet bytes 
into meaningful data as the game client/server would interpret it
*/
#include "stdafx.h"
#include "packet_processor.h"

#define PKT_ID_LEN 2

void packet_processor::init_packetDeserialisers()
{
	packetDeserialisers[CLI_CHAT_MESSAGE] = (deserialiser)&packet_processor::deserialise_CLI_CHAT_MSG;
	packetDeserialisers[CLIPK_MOUSE_RELEASE] = (deserialiser)&packet_processor::deserialise_CLI_MOUSE_RELEASE;
}


pkt_CLI_CHAT_MSG packet_processor::deserialise_CLI_CHAT_MSG()
{
	std::cout << "3 in clichat decoder" << std::endl;
	pkt_CLI_CHAT_MSG cliChatPkt(decryptedBuffer, decryptedIndex);

	cliChatPkt.msgLen_Words = consumeUShort();
	cliChatPkt.msg = consumeWString(cliChatPkt.msgLen_Words * 2);
	cliChatPkt.linkedItemCount = consumeByte();

	cliChatPkt.length = decryptedIndex - cliChatPkt.startIdx;
	std::cout << "4 return clichat decoder" << std::endl;
	return cliChatPkt;
}


pkt_CLI_MOUSE_RELEASE packet_processor::deserialise_CLI_MOUSE_RELEASE()
{
	std::cout << "in mouserelease decoder" << std::endl;
	pkt_CLI_MOUSE_RELEASE cliMouseReleasePkt(decryptedBuffer, decryptedIndex);
	cliMouseReleasePkt.length = decryptedIndex - cliMouseReleasePkt.startIdx;
	return cliMouseReleasePkt;
}