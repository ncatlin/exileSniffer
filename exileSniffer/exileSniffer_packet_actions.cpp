/*
These member functions take the data produced by the decoders and
present it to the user in a way that is meaningful to them. 

It maintains game state for each client. eg: The names associated 
with object ID's and skill ID's in respective list packets can be 
referred to when those object ID's are seen in future 'object ID 
used skill ID' packets.

These operate in the UI thread and should be primarily low overhead
UI update operations
*/

#include "stdafx.h"
#include "exileSniffer.h"
#include "packetIDs.h"

void exileSniffer::init_DecodedPktActioners()
{
	decodedPktActioners[CLI_CHAT_MSG_ITEMS] = &exileSniffer::action_CLI_CHAT_MSG_ITEMS;
	decodedPktActioners[CLI_CHAT_MESSAGE] = &exileSniffer::action_CLI_CHAT_MSG;
	decodedPktActioners[CLI_PING_CHALLENGE] = &exileSniffer::action_CLI_PING_CHALLENGE;
	decodedPktActioners[CLI_CHAT_COMMAND] = &exileSniffer::action_CLI_CHAT_COMMAND;
	decodedPktActioners[SRV_CHAT_MESSAGE] = &exileSniffer::action_SRV_CHAT_MESSAGE;
	decodedPktActioners[SRV_SERVER_MESSAGE] = &exileSniffer::action_SRV_SERVER_MESSAGE;
	decodedPktActioners[CLI_LOGGED_OUT] = &exileSniffer::action_CLI_LOGGED_OUT;
	decodedPktActioners[CLI_ACTION_PREDICTIVE] = &exileSniffer::action_CLI_ACTION_PREDICTIVE;
	decodedPktActioners[CLI_USE_BELT_SLOT] = &exileSniffer::action_CLI_USE_BELT_SLOT;
	decodedPktActioners[CLI_USE_ITEM] = &exileSniffer::action_CLI_USE_ITEM;

	decodedPktActioners[CLI_MOUSE_RELEASE] = &exileSniffer::action_CLI_MOUSE_RELEASE;
}

void exileSniffer::action_undecoded_packet(UIDecodedPkt& decoded)
{
	std::cout << "ingoring action undecoded pkt" << std::endl;
}

void exileSniffer::action_decoded_packet(UIDecodedPkt& decoded)
{
	auto it = decodedPktActioners.find(decoded.messageID);
	if (it != decodedPktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded);
	}
	else
	{
		std::cerr << "Warning!! no actioner setup for pkt id " << decoded.messageID << std::endl;
	}

}

QString msgIDPrefix(UIDecodedPkt& uipkt)
{
	return "[" + QString::number(uipkt.messageID, 16) + "] ";
}




void exileSniffer::action_SRV_PKT_ENCAPSULATED(UIDecodedPkt& decobj)
{
	/* no action for this, action the packet it encapsulates instead*/
}

void exileSniffer::action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player sent chat message with with linked items");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_CHAT_COMMAND(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used / command");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_SRV_CHAT_MESSAGE(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Chat message from server");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_SRV_SERVER_MESSAGE(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Server sent message ");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_LOGGED_OUT(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Game client logged out");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}


void exileSniffer::action_CLI_CHAT_MSG(UIDecodedPkt& decodedobj)
{
	//summary item
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player spoke in chat");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);

	decodedobj.toggle_payload_operations(true);
	std::wcout << "[You In Chat]:\"" << decodedobj.get_wstring(L"Message") << "\"" << std::endl;

	/*
	if (cliChatObj.linkedItemCount == 0)
		std::wcout << "[You In Chat]:\"" << cliChatObj.msg << "\"" << std::endl;
	else
	{
		int itemPos = cliChatObj.msg.find(0x5f, 0);
		std::wcout << "[You In Chat]:\"" << cliChatObj.msg.substr(0, itemPos);
		std::wcout << "_ITEM";
		std::wcout << cliChatObj.msg.substr(itemPos, cliChatObj.msg.size()) << std::endl;
	}
	*/
}

void exileSniffer::action_CLI_PING_CHALLENGE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UINT64 challenge = decodedobj.get_UInt64(L"Challenge");

	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Game Client sent ping challenge 0x"+QString::number(challenge,16));
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_ACTION_PREDICTIVE(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player performed action");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_USE_BELT_SLOT(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used belt slot");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_USE_ITEM(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used inventory item");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_MOUSE_RELEASE(UIDecodedPkt& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player released mouse");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

