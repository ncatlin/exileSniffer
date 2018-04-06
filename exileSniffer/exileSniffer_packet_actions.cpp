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

void exileSniffer::action_undecoded_packet(UI_DECODED_PKT& decoded)
{
	std::cout << "ingoring action undecoded pkt" << std::endl;
}

void exileSniffer::action_decoded_packet(UI_DECODED_PKT& decoded)
{
	auto it = decodedPktActioners.find(decoded.decodedobj.messageID);
	if (it != decodedPktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded);
	}
	else
	{
		std::cerr << "Warning!! no actioner setup for pkt id " << decoded.decodedobj.messageID << std::endl;
	}

}

QString msgIDPrefix(UI_DECODED_PKT& uipkt)
{
	return "[" + QString::number(uipkt.decodedobj.messageID, 16) + "] ";
}




void exileSniffer::action_SRV_PKT_ENCAPSULATED(UI_DECODED_PKT& decobj)
{
	/* no action for this, action the packet it encapsulates instead*/
}

void exileSniffer::action_CLI_CHAT_MSG_ITEMS(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player sent chat message with with linked items");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_CHAT_COMMAND(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used / command");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_SRV_CHAT_MESSAGE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Chat message from server");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_SRV_SERVER_MESSAGE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Server sent message ");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_LOGGED_OUT(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Game client logged out");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}


void exileSniffer::action_CLI_CHAT_MSG(UI_DECODED_PKT& decodedobj)
{
	//summary item
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player spoke in chat");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);


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

void exileSniffer::action_CLI_PING_CHALLENGE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Game Client sent ping challenge");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_ACTION_PREDICTIVE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player performed action");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_USE_BELT_SLOT(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used belt slot");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_USE_ITEM(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player used inventory item");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

void exileSniffer::action_CLI_MOUSE_RELEASE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player released mouse");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

