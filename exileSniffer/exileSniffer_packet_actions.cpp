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
#include "inventory.h"

std::wstring explainModifier(byte lastByte)
{
	/*
	00001000 click       0x8
	00001001 +shift		 0x9
	00001010 +windowOpen 0xa
	00001100 +ctrl		 0xc

	8 = inventory/etc open
	9 = shift held
	c = control held
	*/

	std::wstring result = L"";

	if (lastByte & 0x1)
		result += L"+shift ";
	if (lastByte & 0x2)
		result += L"+openPane ";
	if (lastByte & 0x4)
		result += L"+ctrl ";
	return result;
}


void exileSniffer::init_DecodedPktActioners()
{
	decodedPktActioners[CLI_CHAT_MSG_ITEMS] = &exileSniffer::action_CLI_CHAT_MSG_ITEMS;
	decodedPktActioners[CLI_CHAT_MESSAGE] = &exileSniffer::action_CLI_CHAT_MSG;
	decodedPktActioners[CLI_PING_CHALLENGE] = &exileSniffer::action_CLI_PING_CHALLENGE;
	decodedPktActioners[CLI_CHAT_COMMAND] = &exileSniffer::action_CLI_CHAT_COMMAND;
	decodedPktActioners[SRV_CHAT_MESSAGE] = &exileSniffer::action_SRV_CHAT_MESSAGE;
	decodedPktActioners[SRV_SERVER_MESSAGE] = &exileSniffer::action_SRV_SERVER_MESSAGE;
	decodedPktActioners[CLI_LOGGED_OUT] = &exileSniffer::action_CLI_LOGGED_OUT;

	decodedPktActioners[CLI_CLICKED_GROUND_ITEM] = &exileSniffer::action_CLI_CLICKED_GROUND_ITEM;
	decodedPktActioners[CLI_ACTION_PREDICTIVE] = &exileSniffer::action_CLI_ACTION_PREDICTIVE;

	decodedPktActioners[CLI_PICKUP_ITEM] = &exileSniffer::action_CLI_PICKUP_ITEM;
	decodedPktActioners[CLI_PLACE_ITEM] = &exileSniffer::action_CLI_PLACE_ITEM;
	decodedPktActioners[CLI_REMOVE_SOCKET] = &exileSniffer::action_CLI_REMOVE_SOCKET;
	decodedPktActioners[CLI_INSERT_SOCKET] = &exileSniffer::action_CLI_INSERT_SOCKET;

	decodedPktActioners[CLI_LEVEL_SKILLGEM] = &exileSniffer::action_CLI_LEVEL_SKILLGEM;
	decodedPktActioners[CLI_SKILLPOINT_CHANGE] = &exileSniffer::action_CLI_SKILLPOINT_CHANGE;
	decodedPktActioners[CLI_CANCEL_BUF] = &exileSniffer::action_CLI_CANCEL_BUF;
	decodedPktActioners[CLI_SET_HOTBARSKILL] = &exileSniffer::action_CLI_SET_HOTBARSKILL;

	decodedPktActioners[CLI_USE_BELT_SLOT] = &exileSniffer::action_CLI_USE_BELT_SLOT;
	decodedPktActioners[CLI_USE_ITEM] = &exileSniffer::action_CLI_USE_ITEM;


	decodedPktActioners[CLI_REQUEST_PUBLICPARTIES] = &exileSniffer::action_CLI_REQUEST_PUBLICPARTIES;
	decodedPktActioners[CLI_SKILLPANE_ACTION] = &exileSniffer::action_CLI_SKILLPANE_ACTION;
	decodedPktActioners[CLI_MICROSTRANSACTIONPANE_ACTION] = &exileSniffer::action_CLI_MICROSTRANSACTIONPANE_ACTION;
	decodedPktActioners[CLI_USED_SKILL] = &exileSniffer::action_CLI_USED_SKILL;
	decodedPktActioners[CLI_CLICK_OBJ] = &exileSniffer::action_CLI_CLICK_OBJ;
	decodedPktActioners[CLI_MOUSE_HELD] = &exileSniffer::action_CLI_MOUSE_HELD;
	decodedPktActioners[CLI_MOUSE_RELEASE] = &exileSniffer::action_CLI_MOUSE_RELEASE;
	decodedPktActioners[CLI_OPTOUT_TUTORIALS] = &exileSniffer::action_CLI_OPTOUT_TUTORIALS;



}

void exileSniffer::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui.decodedList->columnCount(); tablecolumn++)
	{
		ui.decodedList->item(tablerow, tablecolumn)->setBackgroundColor(colour);
	}
}

void exileSniffer::addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry)
{
	unsigned int rowIndex = ui.decodedList->rowCount();
	ui.decodedList->setRowCount(rowIndex + 1);
	if(ui.decodedAutoscrollCheck->isChecked())
		ui.decodedList->scrollToBottom();

	QTableWidgetItem *time = new QTableWidgetItem(entry.floatSeconds(startMSSinceEpoch));
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_TIME, time);

	QTableWidgetItem *sender = new QTableWidgetItem(entry.sender());
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_SENDER, sender);

	QTableWidgetItem *pktID = new QTableWidgetItem(entry.hexPktID());
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_MSGID, pktID);

	QTableWidgetItem *summary = new QTableWidgetItem(entry.summary);
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_SUMMARY, summary);

	if (entry.badDecode())
	{
		setRowColor(rowIndex, QColor(255, 150, 150, 255));
		return;
	}

	byte flags = entry.pktFlags();
	if (!(flags & PKTBIT_GAMESERVER))
	{
		if (flags & PKTBIT_LOGINSERVER)
			setRowColor(rowIndex, QColor(232, 226, 155, 255));
		else if (flags & PKTBIT_PATCHSERVER)
			setRowColor(rowIndex, QColor(153, 217, 234, 255));
		else
			setRowColor(rowIndex, QColor(255, 0, 0, 0));
	}
}

void exileSniffer::action_undecoded_packet(UIDecodedPkt& obj)
{
	obj.toggle_payload_operations(true);

	size_t sizeAfterID = obj.bufferOffsets.second - obj.bufferOffsets.first;
	wstringstream summary;
	summary << "Undecoded packet or multipacket blob ("
		<< std::dec << sizeAfterID << " byte";
	summary << ((sizeAfterID == 1) ? ")" : "s)");

	UI_DECODED_LIST_ENTRY listentry(obj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry);

	++decodedErrorPacketCount;
	updateDecodedFilterLabel();
}

void exileSniffer::action_decoded_packet(UIDecodedPkt& decoded)
{
	clientData *client = get_client(decoded.clientProcessID());
	if (!client) {
		std::cerr << "Error: Client had PID 0 when decoding pkt id 0x" << std::hex << decoded.messageID << std::endl;
		return;
	}

	if (!packet_passes_decoded_filter(decoded, client))
	{
		++decodedCount_Displayed_Filtered.second;
		updateDecodedFilterLabel();
		return;
	}

	auto it = decodedPktActioners.find(decoded.messageID);
	if (it != decodedPktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded);

		++decodedCount_Displayed_Filtered.first;
		updateDecodedFilterLabel();
	}
	else
	{
		stringstream err;
		err << "ERROR! no action setup for known pkt id 0x" << std::hex << decoded.messageID;
		add_metalog_update(QString::fromStdString(err.str()), decoded.clientProcessID());
	}

}


void exileSniffer::action_SRV_PKT_ENCAPSULATED(UIDecodedPkt& decobj)
{
	/* no action for this, action the packet it encapsulates instead*/
	//silently dropped
}

void exileSniffer::action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt& obj)
{
	obj.toggle_payload_operations(true);

	UI_DECODED_LIST_ENTRY listentry(obj);
	listentry.summary = "Player sent chat message with with linked items";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_CHAT_COMMAND(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);

	/*
	todo - load into presupplied data blob or lookup in ggpk
	0x04 = /remaining, 0x06=/pvp, 0x08=/oos, 0x0d=/fixmyhelmet, etc
	*/
	UINT32 commandsDatIndex = decodedobj.get_UInt32(L"CommandID");
	UINT32 unk1 = decodedobj.get_UInt32(L"Unk1");

	wstringstream summary;
	summary << "Player used command at commands.dat index: " << std::dec << commandsDatIndex <<
		" [unkVal 0x: " << std::hex << unk1 << "]";
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry);
}

void exileSniffer::action_SRV_CHAT_MESSAGE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Chat message from server";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_SRV_SERVER_MESSAGE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Server sent message";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_LOGGED_OUT(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);

	UINT32 arg = decodedobj.get_UInt32(L"Unk1");

	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Game client logged out. [Arg: "+QString::number(arg)+"]";
	addDecodedListEntry(listentry);
}


void exileSniffer::action_CLI_CHAT_MSG(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	//todo - item or not
	//todo - channel decode
	listentry.summary = "Player spoke in chat: "+ QString::fromStdWString(decodedobj.get_wstring(L"Message"));
	addDecodedListEntry(listentry);

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

	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Game Client sent ping challenge 0x" + QString::number(challenge, 16);
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);

	UINT64 targID = decodedobj.get_UInt64(L"TargID");
	UINT64 Unk1 = decodedobj.get_UInt64(L"Unk1");
	UINT32 modifier = decodedobj.get_UInt32(L"Modifier");

	std::wstringstream summary;
	summary << "Player clicked ground itemID 0x" << std::hex << targID << " Arg1: 0x" << Unk1;

	if (modifier)
		summary << " [" << explainModifier(modifier) << "]";

	if (modifier > 0xf || !(modifier & 0x8))
		summary << " <!Unusual modifier 0x" << std::hex << modifier << " - what are you doing?>";
}

void exileSniffer::action_CLI_ACTION_PREDICTIVE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UINT64 coord1 = decodedobj.get_UInt64(L"TargCoord1");
	UINT64 coord2 = decodedobj.get_UInt64(L"TargCoord2");
	UINT32 skillID = decodedobj.get_UInt32(L"SkillID");
	UINT32 PkCount = decodedobj.get_UInt32(L"PkCount");
	UINT32 modifier = decodedobj.get_UInt32(L"Modifier");

	std::wstringstream summary;
	summary << "Player used skillID 0x" << std::hex << skillID <<
		" on coord " << std::dec << coord1 << "," << coord2;
	if (modifier)
		summary << "[" << explainModifier(modifier) << "]";

	if (modifier > 0xf || !(modifier & 0x8))
		summary << " <!Unusual modifier 0x" << std::hex<< modifier << " - what are you doing?>";
	

	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry);
}


void exileSniffer::action_CLI_PICKUP_ITEM(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UINT64 container = decodedobj.get_UInt64(L"Container");
	UINT64 itemID = decodedobj.get_UInt32(L"ItemID");
	UINT32 unk2 = decodedobj.get_UInt32(L"Unk2");

	std::wstringstream summary;
	summary << "Player picked up itemID 0x" << std::hex << itemID 
		<< "in container " << slotToString(container) <<" < unk2: 0x"<<unk2<<">";

	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_PLACE_ITEM(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player placed item down";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_REMOVE_SOCKET(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player removed from socket";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_INSERT_SOCKET(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player inserted into socket";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_LEVEL_SKILLGEM(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player levelled a skillgem";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player added a skillpoint";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_CANCEL_BUF(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player cancelled a buff";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_SET_HOTBARSKILL(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player changed a hotbar skill";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_USE_BELT_SLOT(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);

	UINT64 slot = decodedobj.get_UInt32(L"Slot");

	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player activated belt slot "+slot;
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_USE_ITEM(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player used inventory item X on item Y";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Client requested latest public parties";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_SKILLPANE_ACTION(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player used skillpane";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_MICROSTRANSACTIONPANE_ACTION(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player opened microtransaction pane";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_USED_SKILL(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player used skill (lockstep)";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_CLICK_OBJ(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player clicked object x";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_MOUSE_HELD(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player is holding mouse";
	addDecodedListEntry(listentry);
}

void exileSniffer::action_CLI_MOUSE_RELEASE(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player released mouse";
	addDecodedListEntry(listentry);
}


void exileSniffer::action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt& decodedobj)
{
	decodedobj.toggle_payload_operations(true);
	UI_DECODED_LIST_ENTRY listentry(decodedobj);
	listentry.summary = "Player opted out of tutorials";
	addDecodedListEntry(listentry);
}
