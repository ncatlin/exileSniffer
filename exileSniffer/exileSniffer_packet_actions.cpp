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
	decodedPktActioners[CLI_CHAT_MESSAGE] = &exileSniffer::action_CLI_CHAT_MSG;
	decodedPktActioners[CLIPK_MOUSE_RELEASE] = &exileSniffer::action_CLI_MOUSE_RELEASE;
}

void exileSniffer::action_undecoded_packet(UI_DECODED_PKT& decoded)
{
	std::cout << "ingoring action undecoded pkt" << std::endl;
}

void exileSniffer::action_decoded_packet(UI_DECODED_PKT& decoded)
{
	std::cout << "8 callaction pk" << std::endl;
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


void exileSniffer::action_CLI_MOUSE_RELEASE(UI_DECODED_PKT& decodedobj)
{
	QListWidgetItem *listitem = new QListWidgetItem;
	QString summaryText(msgIDPrefix(decodedobj) + "Player released mouse");
	listitem->setText(summaryText);
	ui.decodedList->addItem(listitem);
}

