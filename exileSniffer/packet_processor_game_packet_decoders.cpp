/*
These member functions attempt to reassemble the raw packet bytes 
into meaningful data as the game client/server would interpret it
*/
#include "stdafx.h"
#include "packet_processor.h"

#define PKT_ID_LEN 2

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
pkt_SRV_PKT_ENCAPSULATED packet_processor::deserialise_SRV_PKT_ENCAPSULATED()
{
	assert(false);
	pkt_SRV_PKT_ENCAPSULATED decodedObj(decryptedBuffer, decryptedIndex);
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_CHAT_MSG_ITEMS packet_processor::deserialise_CLI_CHAT_MSG_ITEMS()
{
	pkt_CLI_CHAT_MSG_ITEMS decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_CHAT_MSG packet_processor::deserialise_CLI_CHAT_MSG()
{
	pkt_CLI_CHAT_MSG decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	decodedObj.msgLen_Words = consumeUShort();
	decodedObj.msg = consumeWString(decodedObj.msgLen_Words * 2);
	decodedObj.linkedItemCount = consumeByte();

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_PING_CHALLENGE packet_processor::deserialise_CLI_PING_CHALLENGE()
{
	pkt_CLI_PING_CHALLENGE decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	decodedObj.challenge = consumeUShort();

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}





pkt_CLI_CHAT_COMMAND packet_processor::deserialise_CLI_CHAT_COMMAND()
{
	pkt_CLI_CHAT_COMMAND decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//todo

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_SRV_CHAT_MESSAGE packet_processor::deserialise_SRV_CHAT_MESSAGE()
{
	pkt_SRV_CHAT_MESSAGE decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_SRV_SERVER_MESSAGE packet_processor::deserialise_SRV_SERVER_MESSAGE()
{
	pkt_SRV_SERVER_MESSAGE decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_LOGGED_OUT packet_processor::deserialise_CLI_LOGGED_OUT()
{
	pkt_CLI_LOGGED_OUT decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_USE_BELT_SLOT packet_processor::deserialise_CLI_USE_BELT_SLOT()
{
	pkt_CLI_USE_BELT_SLOT decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//todo
	/*
				//003700000004 = 5th slot
			unsigned long slot = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			std::cout << std::hex << "Player activated potion slot 0x" << slot << std::endl;
	*/

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_USE_ITEM packet_processor::deserialise_CLI_USE_ITEM()
{
	pkt_CLI_USE_ITEM decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//todo
	/*
				unsigned long unk1 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long item1 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long unk2 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long item2 = getUlong(decryptedBuffer + sIdx); sIdx += 4;

			std::cout << std::hex << "Player activated item 0x" << item1 << " on item 0x" << item2;
			std::cout << "i1unk: 0x" << unk1 << " i2unk: 0x" << unk2 << std::endl;
	*/

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_ACTION_PREDICTIVE packet_processor::deserialise_CLI_ACTION_PREDICTIVE()
{
	pkt_CLI_ACTION_PREDICTIVE decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/
	/*
				unsigned long targcoord1 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned long targcoord2 = getUlong(decryptedBuffer + sIdx); sIdx += 4;
			unsigned short skill = getUshort(decryptedBuffer + sIdx); sIdx += 2;
			unsigned short pcount = getUshort(decryptedBuffer + sIdx); sIdx += 2;
			char controlStatus = decryptedBuffer[sIdx]; sIdx += 1;

			std::cout << std::hex << "Player used" << explainMouseLastByte(controlStatus)
				<< " skill 0x" << skill << " on coord (" <<
				targcoord1 << "," << targcoord2 << ") " << std::endl;

			if (controlStatus > 0xf || !(controlStatus & 0x8))
				std::cout << "\t!Unusual controlStatus " << (int)controlStatus << " - window open?>" << std::endl;
	*/

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}

pkt_CLI_MOUSE_RELEASE packet_processor::deserialise_CLI_MOUSE_RELEASE()
{
	pkt_CLI_MOUSE_RELEASE decodedObj(decryptedBuffer, decryptedIndex);
	/*---deserialise contents here---*/

	//no data expected

	/*---deserialising done---*/
	decodedObj.finalise(decryptedIndex);
	return decodedObj;
}