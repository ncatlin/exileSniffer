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

void exileSniffer::init_gamePkt_Actioners()
{
	//encapsulated ignored
	gamePktActioners[CLI_CHAT_MSG_ITEMS] = &exileSniffer::action_CLI_CHAT_MSG_ITEMS;
	//7
	gamePktActioners[CLI_CHAT_MESSAGE] = &exileSniffer::action_CLI_CHAT_MSG;	
	gamePktActioners[CLI_CHAT_COMMAND] = &exileSniffer::action_CLI_CHAT_COMMAND;
	gamePktActioners[SRV_CHAT_MESSAGE] = &exileSniffer::action_SRV_CHAT_MESSAGE;
	gamePktActioners[SRV_SERVER_MESSAGE] = &exileSniffer::action_SRV_SERVER_MESSAGE;
	gamePktActioners[CLI_LOGGED_OUT] = &exileSniffer::action_CLI_LOGGED_OUT;
	gamePktActioners[CLI_HNC] = &exileSniffer::action_CLI_HNC;
	gamePktActioners[SRV_HNC] = &exileSniffer::action_SRV_HNC;
	gamePktActioners[SRV_AREA_INFO] = &exileSniffer::action_SRV_AREA_INFO;
	//10?
	//11?
	gamePktActioners[SRV_PRELOAD_MONSTER_LIST] = &exileSniffer::action_SRV_PRELOAD_MONSTER_LIST;
	gamePktActioners[SRV_UNK_0x13] = &exileSniffer::action_SRV_UNK_0x13;
	gamePktActioners[SRV_ITEMS_LIST] = &exileSniffer::action_SRV_ITEMS_LIST;
	gamePktActioners[CLI_CLICKED_GROUND_ITEM] = &exileSniffer::action_CLI_CLICKED_GROUND_ITEM;
	gamePktActioners[CLI_ACTION_PREDICTIVE] = &exileSniffer::action_CLI_ACTION_PREDICTIVE;
	gamePktActioners[SRV_TRANSFER_INSTANCE] = &exileSniffer::action_SRV_TRANSFER_INSTANCE;
	gamePktActioners[SRV_INSTANCE_SERVER_DATA] = &exileSniffer::action_SRV_INSTANCE_SERVER_DATA;
	gamePktActioners[CLI_PICKUP_ITEM] = &exileSniffer::action_CLI_PICKUP_ITEM;
	//1a
	gamePktActioners[CLI_PLACE_ITEM] = &exileSniffer::action_CLI_PLACE_ITEM;
	gamePktActioners[CLI_DROP_ITEM] = &exileSniffer::action_CLI_PLACE_ITEM;
	gamePktActioners[CLI_REMOVE_SOCKET] = &exileSniffer::action_CLI_REMOVE_SOCKET;
	gamePktActioners[CLI_INSERT_SOCKET] = &exileSniffer::action_CLI_INSERT_SOCKET;
	gamePktActioners[CLI_LEVEL_SKILLGEM] = &exileSniffer::action_CLI_LEVEL_SKILLGEM;
	gamePktActioners[SRV_UNK_0x20] = &exileSniffer::action_SRV_UNK_0x20;
	gamePktActioners[CLI_SKILLPOINT_CHANGE] = &exileSniffer::action_CLI_SKILLPOINT_CHANGE;
	//22
	//23
	gamePktActioners[CLI_CHOSE_ASCENDANCY] = &exileSniffer::action_CLI_CHOSE_ASCENDANCY;
	//25
	//26
	//27
	//28
	//29
	gamePktActioners[CLI_MERGE_STACK] = &exileSniffer::action_CLI_MERGE_STACK;
	gamePktActioners[CLI_CANCEL_BUF] = &exileSniffer::action_CLI_CANCEL_BUF;
	gamePktActioners[SRV_UNK_0x2c] = &exileSniffer::action_SRV_UNK_0x2c;
	gamePktActioners[CLI_SELECT_MAPTRAVEL] = &exileSniffer::action_CLI_SELECT_MAPTRAVEL;
	gamePktActioners[CLI_SET_HOTBARSKILL] = &exileSniffer::action_CLI_SET_HOTBARSKILL;
	gamePktActioners[SRV_SKILL_SLOTS_LIST] = &exileSniffer::action_SRV_SKILL_SLOTS_LIST;
	gamePktActioners[CLI_REVIVE_CHOICE] = &exileSniffer::action_CLI_REVIVE_CHOICE;
	gamePktActioners[SRV_YOU_DIED] = &exileSniffer::action_SRV_YOU_DIED;
	gamePktActioners[CLI_ACTIVATE_ITEM] = &exileSniffer::action_CLI_ACTIVATE_ITEM;
	//33
	//34
	//35
	//36
	gamePktActioners[CLI_USE_BELT_SLOT] = &exileSniffer::action_CLI_USE_BELT_SLOT;
	gamePktActioners[CLI_USE_ITEM_ON_ITEM] = &exileSniffer::action_CLI_USE_ITEM_ON_ITEM;
	//39
	//3a
	//3b
	//3c
	//3d
	//3e
	gamePktActioners[SRV_OPEN_UI_PANE] = &exileSniffer::action_SRV_OPEN_UI_PANE;
	gamePktActioners[CLI_SPLIT_STACK] = &exileSniffer::action_CLI_SPLIT_STACK;
	gamePktActioners[CLI_UNK_0x41] = &exileSniffer::action_CLI_UNK_0x41;
	//42
	//43
	//44
	//45
	gamePktActioners[CLI_SELECT_NPC_DIALOG] = &exileSniffer::action_CLI_SELECT_NPC_DIALOG;
	gamePktActioners[SRV_SHOW_NPC_DIALOG] = &exileSniffer::action_SRV_SHOW_NPC_DIALOG;
	gamePktActioners[CLI_CLOSE_NPC_DIALOG] = &exileSniffer::action_CLI_CLOSE_NPC_DIALOG;
	//49
	//4a
	//4b
	//4c
	//4d
	//4e
	gamePktActioners[SRV_LIST_PORTALS] = &exileSniffer::action_SRV_LIST_PORTALS;
	gamePktActioners[CLI_SEND_PARTY_INVITE] = &exileSniffer::action_CLI_SEND_PARTY_INVITE;
	//51
	gamePktActioners[CLI_TRY_JOIN_PARTY] = &exileSniffer::action_CLI_TRY_JOIN_PARTY;
	gamePktActioners[CLI_DISBAND_PUBLIC_PARTY] = &exileSniffer::action_CLI_DISBAND_PUBLIC_PARTY;
	//54
	gamePktActioners[CLI_CREATE_PUBLICPARTY] = &exileSniffer::action_CLI_CREATE_PUBLICPARTY;
	gamePktActioners[CLI_UNK_x56] = &exileSniffer::action_CLI_UNK_x56;
	gamePktActioners[CLI_GET_PARTY_DETAILS] = &exileSniffer::action_CLI_GET_PARTY_DETAILS;
	gamePktActioners[SRV_FRIENDSLIST] = &exileSniffer::action_SRV_FRIENDSLIST;
	//59
	gamePktActioners[SRV_PARTY_DETAILS] = &exileSniffer::action_SRV_PARTY_DETAILS;
	gamePktActioners[SRV_PARTY_ENDED] = &exileSniffer::action_SRV_PARTY_ENDED;
	//5c
	gamePktActioners[CLI_REQUEST_PUBLICPARTIES] = &exileSniffer::action_CLI_REQUEST_PUBLICPARTIES;
	gamePktActioners[SRV_PUBLIC_PARTY_LIST] = &exileSniffer::action_SRV_PUBLIC_PARTY_LIST;
	//5f
	//60
	//61
	//62
	gamePktActioners[CLI_MOVE_ITEM_PANE] = &exileSniffer::action_CLI_MOVE_ITEM_PANE;
	//64
	gamePktActioners[CLI_CONFIRM_SELL] = &exileSniffer::action_CLI_CONFIRM_SELL;
	//66
	gamePktActioners[SRV_UNK_0x67] = &exileSniffer::action_SRV_UNK_0x67;
	gamePktActioners[SRV_UNK_0x68] = &exileSniffer::action_SRV_UNK_0x68;
	//69
	//6a
	//6b
	gamePktActioners[SRV_UNK_0x6c] = &exileSniffer::action_SRV_UNK_0x6c;
	gamePktActioners[SRV_CREATE_ITEM] = &exileSniffer::action_SRV_CREATE_ITEM;
	gamePktActioners[SRV_SLOT_ITEMSLIST] = &exileSniffer::action_SRV_SLOT_ITEMSLIST;
	gamePktActioners[SRV_INVENTORY_SET_REMOVE] = &exileSniffer::action_SRV_INVENTORY_SET_REMOVE;
	gamePktActioners[SRV_UNK_0x70] = &exileSniffer::action_SRV_UNK_0x70;
	gamePktActioners[CLI_SELECT_STASHTAB] = &exileSniffer::action_CLI_SELECT_STASHTAB;
	gamePktActioners[SRV_STASHTAB_DATA] = &exileSniffer::action_SRV_STASHTAB_DATA;
	gamePktActioners[SRV_UNK_0x73] = &exileSniffer::action_SRV_UNK_0x73;
	gamePktActioners[CLI_SET_STATUS_MESSAGE] = &exileSniffer::action_CLI_SET_STATUS_MESSAGE;
	gamePktActioners[SRV_MOVE_OBJECT] = &exileSniffer::action_SRV_MOVE_OBJECT;
	//76
	//77
	//78
	//79
	//7a
	//7b
	gamePktActioners[CLI_ACTIVATE_MAP] = &exileSniffer::action_CLI_ACTIVATE_MAP;
	//7d
	//7e
	gamePktActioners[CLI_SWAPPED_WEAPONS] = &exileSniffer::action_CLI_SWAPPED_WEAPONS;
	//80
	gamePktActioners[SRV_ADJUST_LIGHTING] = &exileSniffer::action_SRV_ADJUST_LIGHTING;
	//82
	//83
	//84
	//85
	//86
	//87
	//88
	//89
	//8a
	//8b
	//8c
	gamePktActioners[SRV_INVENTORY_FULL] = &exileSniffer::action_SRV_INVENTORY_FULL;
	//8e
	//define 0x8f seen when leaving duel queue
	//define 0x90 seen when leaving duel queue
	gamePktActioners[SRV_PVP_MATCHLIST] = &exileSniffer::action_SRV_PVP_MATCHLIST;
	gamePktActioners[SRV_EVENTSLIST] = &exileSniffer::action_SRV_EVENTSLIST;
	//93
	//94
	//95
	//96
	//97
	gamePktActioners[CLI_SKILLPANE_ACTION] = &exileSniffer::action_CLI_SKILLPANE_ACTION;
	gamePktActioners[SRV_ACHIEVEMENT_1] = &exileSniffer::action_SRV_ACHIEVEMENT_1;
	gamePktActioners[SRV_ACHIEVEMENT_2] = &exileSniffer::action_SRV_ACHIEVEMENT_2;
	gamePktActioners[SRV_SKILLPANE_DATA] = &exileSniffer::action_SRV_SKILLPANE_DATA;
	gamePktActioners[SRV_UNK_POSITION_LIST] = &exileSniffer::action_SRV_UNK_POSITION_LIST;
	//9d
	//9e
	gamePktActioners[CLI_MICROTRANSACTION_SHOP_ACTION] = &exileSniffer::action_CLI_MICROTRANSACTION_SHOP_ACTION;
	//a0
	gamePktActioners[SRV_MICROTRANSACTION_SHOP_DETAILS] = &exileSniffer::action_SRV_MICROTRANSACTION_SHOP_DETAILS;
	//a2
	gamePktActioners[CLI_UNK_A3] = &exileSniffer::action_CLI_UNK_A3;
	gamePktActioners[SRV_CHAT_CHANNEL_ID] = &exileSniffer::action_SRV_CHAT_CHANNEL_ID;
	gamePktActioners[SRV_UNK_A5] = &exileSniffer::action_SRV_UNK_A5;
	//a6
	//a7
	//a8
	//a9
	//aa
	//ab
	//ac
	gamePktActioners[CLI_GUILD_CREATE] = &exileSniffer::action_CLI_GUILD_CREATE;
	//ae
	//af
	//b0
	//b1
	//b2
	//b3
	//b4
	gamePktActioners[SRV_GUILD_MEMBER_LIST] = &exileSniffer::action_SRV_GUILD_MEMBER_LIST;
	//b6
	//b7
	//b8
	//b9
	//ba
	//bc
	//bd
	//be
	//bf
	gamePktActioners[CLI_EXIT_TO_CHARSCREEN] = &exileSniffer::action_CLI_EXIT_TO_CHARSCREEN;
	gamePktActioners[SRV_LOGINSRV_CRYPT] = &exileSniffer::action_SRV_LOGINSRV_CRYPT;
	gamePktActioners[CLI_DUEL_CHALLENGE] = &exileSniffer::action_CLI_DUEL_CHALLENGE;
	gamePktActioners[SRV_DUEL_RESPONSE] = &exileSniffer::action_SRV_DUEL_RESPONSE;
	gamePktActioners[SRV_DUEL_CHALLENGE] = &exileSniffer::action_SRV_DUEL_CHALLENGE;
	//c5
	gamePktActioners[CLI_UNK_0xC6] = &exileSniffer::action_CLI_UNK_0xC6; 
	gamePktActioners[CLI_UNK_0xC7] = &exileSniffer::action_CLI_UNK_0xC7;
	//c8
	//c9
	gamePktActioners[SRV_UNK_0xCA] = &exileSniffer::action_SRV_UNK_0xCA;
	//cb
	//cd
	//CLI_VISIT_HIDEOUT
	//cf
	//d0
	//d1
	//d2
	//d3
	//d4
	gamePktActioners[SRV_EVENTSLIST_2] = &exileSniffer::action_SRV_EVENTSLIST_2;
	//d6
	//d7
	gamePktActioners[CLI_USED_SKILL] = &exileSniffer::action_CLI_USED_SKILL;
	gamePktActioners[CLI_CLICK_OBJ] = &exileSniffer::action_CLI_CLICK_OBJ;
	gamePktActioners[CLI_MOUSE_HELD] = &exileSniffer::action_CLI_MOUSE_HELD;
	//db
	gamePktActioners[CLI_MOUSE_RELEASE] = &exileSniffer::action_CLI_MOUSE_RELEASE;
	//dd
	//de
	//df
	gamePktActioners[CLI_OPEN_WORLD_SCREEN] = &exileSniffer::action_CLI_OPEN_WORLD_SCREEN;
	//e1
	//e2
	//e3
	gamePktActioners[SRV_UNK_0xE4] = &exileSniffer::action_SRV_UNK_0xE4;
	//e5
	gamePktActioners[SRV_UNK_0xE6] = &exileSniffer::action_SRV_UNK_0xE6;
	//e7
	//e8
	gamePktActioners[SRV_OBJ_REMOVED] = &exileSniffer::action_SRV_OBJ_REMOVED;
	gamePktActioners[SRV_MOBILE_START_SKILL] = &exileSniffer::action_SRV_MOBILE_START_SKILL;
	gamePktActioners[SRV_MOBILE_FINISH_SKILL] = &exileSniffer::action_SRV_MOBILE_FINISH_SKILL;
	gamePktActioners[SRV_MOVE_CHANNELLED] = &exileSniffer::action_SRV_MOVE_CHANNELLED;
	gamePktActioners[SRV_END_CHANNELLED] = &exileSniffer::action_SRV_END_CHANNELLED;
	gamePktActioners[SRV_MOBILE_UNK_0xee] = &exileSniffer::action_SRV_MOBILE_UNK_0xee;
	gamePktActioners[SRV_MOBILE_UNK_0xef] = &exileSniffer::action_SRV_MOBILE_UNK_0xef;
	gamePktActioners[SRV_MOBILE_UPDATE_HMS] = &exileSniffer::action_SRV_MOBILE_UPDATE_HMS;
	gamePktActioners[SRV_STAT_CHANGED] = &exileSniffer::action_SRV_STAT_CHANGED;
	gamePktActioners[SRV_UNK_0xf2] = &exileSniffer::action_SRV_UNK_0xf2;
	gamePktActioners[SRV_UNK_0xf3] = &exileSniffer::action_SRV_UNK_0xf3;
	//f4
	gamePktActioners[SRV_UNK_0xf5] = &exileSniffer::action_SRV_UNK_0xf5;
	//f6
	gamePktActioners[SRV_UNK_0xf7] = &exileSniffer::action_SRV_UNK_0xf7;
	gamePktActioners[SRV_UNK_0xf8] = &exileSniffer::action_SRV_UNK_0xf8;
	//f9
	gamePktActioners[SRV_START_EFFECT] = &exileSniffer::action_SRV_START_BUFF;
	gamePktActioners[SRV_END_EFFECT] = &exileSniffer::action_SRV_END_EFFECT;
	//fc
	//fd
	//fe
	gamePktActioners[SRV_EVENT_TRIGGERED] = &exileSniffer::action_SRV_EVENT_TRIGGERED;
	//100
	//101
	//102
	//103
	//104
	//105
	gamePktActioners[SRV_UNKNOWN_0x106] = &exileSniffer::action_SRV_UNK_0x106;
	//107
	gamePktActioners[SRV_UNKNOWN_0x108] = &exileSniffer::action_SRV_UNK_0x108;
	//109
	//10a
	//10b
	//10c
	//10d
	gamePktActioners[CLI_FINISHED_LOADING] = &exileSniffer::action_CLI_FINISHED_LOADING;
	gamePktActioners[SRV_NOTIFY_PLAYERID] = &exileSniffer::action_SRV_NOTIFY_PLAYERID;
	//0x110 - player pressed add new stash tab +?
	gamePktActioners[SRV_UNKNOWN_0x111] = &exileSniffer::action_SRV_UNKNOWN_0x111;
	//112
	//113
	//114
	//115
	//116
	//117
	gamePktActioners[SRV_UNKNOWN_0x118] = &exileSniffer::action_SRV_UNKNOWN_0x118;
	//119
	//11a
	//11b
	gamePktActioners[CLI_OPTOUT_TUTORIALS] = &exileSniffer::action_CLI_OPTOUT_TUTORIALS;
	//11d
	//11e
	//11f
	//120
	//121
	//122
	//123
	//124
	//125
	//126
	gamePktActioners[SRV_BESTIARY_CAPTIVES] = &exileSniffer::action_SRV_BESTIARY_CAPTIVES;
	//128
	//129
	gamePktActioners[CLI_OPEN_BESTIARY] = &exileSniffer::action_CLI_OPEN_BESTIARY;
	//12b
	gamePktActioners[SRV_BESTIARY_UNLOCKED_LIST] = &exileSniffer::action_SRV_BESTIARY_UNLOCKED_LIST;
	//12d
	//12e
	gamePktActioners[SRV_SHOW_ENTERING_MSG] = &exileSniffer::action_SRV_SHOW_ENTERING_MSG;
	//130
	//131
	gamePktActioners[SRV_HEARTBEAT] = &exileSniffer::action_SRV_HEARTBEAT;
	//133
	//134
	gamePktActioners[SRV_ADD_OBJECT] = &exileSniffer::action_SRV_ADD_OBJECT;
	gamePktActioners[SRV_UPDATE_OBJECT] = &exileSniffer::action_SRV_UPDATE_OBJECT;
	gamePktActioners[SRV_IDNOTIFY_0x137] = &exileSniffer::action_SRV_IDNOTIFY_0x137;
	//138
	//139

}

void exileSniffer::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui.decodedListTable->columnCount(); tablecolumn++)
	{
		QTableWidgetItem *item = ui.decodedListTable->item(tablerow, tablecolumn);
		if(item)
			item->setBackgroundColor(colour);
	}
}

void exileSniffer::addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry, UIDecodedPkt *obj, bool isNewEntry)
{
	if (isNewEntry)
		decodedListEntries.push_back(make_pair(entry, obj));

	unsigned int rowIndex = ui.decodedListTable->rowCount();
	ui.decodedListTable->setRowCount(rowIndex + 1);
	if(ui.decodedAutoscrollCheck->isChecked())
		ui.decodedListTable->scrollToBottom();

	QTableWidgetItem *time = new QTableWidgetItem(entry.floatSeconds(startMSSinceEpoch));
	time->setData(Qt::UserRole, QVariant::fromValue<UIDecodedPkt *>(obj)); //add object pointer to first column
	ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_TIME, time);

	QTableWidgetItem *sender = new QTableWidgetItem(entry.sender());
	ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_SENDER, sender);

	QTableWidgetItem *pktIDItem = new QTableWidgetItem(entry.hexPktID());
	ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_MSGID, pktIDItem);

	if (entry.badDecode())
	{
		entry.summary = "<!BAD!>" + entry.summary;

		QTableWidgetItem *summary = new QTableWidgetItem(entry.summary);
		ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_SUMMARY, summary);

		setRowColor(rowIndex, QColor(255, 150, 150, 255));
		return;
	}

	if (obj->wasAbandoned())
	{
		entry.summary = "<!ABAND!>" + entry.summary;

		QTableWidgetItem *summary = new QTableWidgetItem(entry.summary);
		ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_SUMMARY, summary);

		setRowColor(rowIndex, QColor(255, 175, 175, 255));
		return;
	}

	QTableWidgetItem *summary = new QTableWidgetItem(entry.summary);
	ui.decodedListTable->setItem(rowIndex, DECODED_SECTION_SUMMARY, summary);


	streamType streamServer = obj->getStreamType();
	ushort msgid = obj->getMessageID();

	if (streamServer == eGame)
	{
		if (obj->isIncoming())
			setRowColor(rowIndex, Qt::white);
		else
			setRowColor(rowIndex, QColor(235, 235, 235, 255)); //grey
	}
	else
	{
		if (streamServer == eLogin)
		{
			if (obj->isIncoming())
				setRowColor(rowIndex, QColor(255, 255, 230, 255));  //yellowy
			else
				setRowColor(rowIndex, QColor(255, 255, 200, 255));	//dark yellowy	
		}
		else
			setRowColor(rowIndex, Qt::red);
		//else if (flags & PKTBIT_PATCHSERVER)
		//	setRowColor(rowIndex, QColor(153, 217, 234, 255));
	}
}

void exileSniffer::action_undecoded_packet(UIDecodedPkt& obj)
{
	obj.toggle_payload_operations(true);

	//will only work for packets in the good range. 0x9F02 is still gonna show up
	ushort pktID = obj.getMessageID();
	if (pktID < rawFiltersFormUI.filterTable->rowCount() && !packet_passes_decoded_filter(pktID))
	{
		++decodedCount_Displayed_Filtered.second;
		updateDecodedFilterLabel();
		return;
	}

	if (!obj.originalbuf) 
	{
		stringstream err;
		err << "ERROR! Undecoded packet has no buffer set";
		add_metalog_update(QString::fromStdString(err.str()), 0);
		return;
	}

	size_t sizeAfterID;
	if (obj.bufferOffsets.first <= obj.originalbuf->size())
		sizeAfterID = obj.originalbuf->size() - obj.bufferOffsets.first;
	else
		sizeAfterID = obj.originalbuf->size();

	wstringstream summary;
	summary << "Undecoded packet or poorly decoded previous packet (~ "
		<< std::dec << sizeAfterID << " byte";
	summary << ((sizeAfterID == 1) ? ")" : "s)");

	UI_DECODED_LIST_ENTRY listentry(obj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry, &obj);

	++decodedErrorPacketCount;
	updateDecodedFilterLabel();
}

void exileSniffer::action_decoded_packet(UIDecodedPkt& decoded)
{
	if (decoded.getStreamType() == eGame)
		action_decoded_game_packet(decoded);
	else if (decoded.getStreamType() == eLogin)
		action_decoded_login_packet(decoded);
}

void exileSniffer::action_decoded_game_packet(UIDecodedPkt& decoded)
{
	if (!packet_passes_decoded_filter(decoded.getMessageID()))
	{
		++decodedCount_Displayed_Filtered.second;
		updateDecodedFilterLabel();
		return;
	}

	auto it = gamePktActioners.find(decoded.getMessageID());
	if (it != gamePktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded, NULL);

		++decodedCount_Displayed_Filtered.first;
		updateDecodedFilterLabel();
	}
	else
	{
		stringstream err;
		err << "ERROR! no action setup for known game msg id 0x" << std::hex << decoded.getMessageID();
		add_metalog_update(QString::fromStdString(err.str()), decoded.getClientProcessID());
	}

}


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


void exileSniffer::action_SRV_PKT_ENCAPSULATED(UIDecodedPkt& obj, QString *analysis)
{
	/* no action for this, action the packet it encapsulates instead*/
	//silently dropped
}

void exileSniffer::action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD itemID = obj.get_UInt32(L"ItemID");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) sent chat message with with linked item ";
		addDecodedListEntry(listentry, &obj);
		return;
	}
	
	wstringstream analysisStream;
	analysisStream << std::dec;
	analysisStream << "Index: " << obj.get_UInt32(L"Index") << std::endl;
	analysisStream << "Container: " << slotToString(obj.get_UInt32(L"Container")) << std::endl;
	analysisStream << "Item: " << itemID << std::endl;
	analysisStream << "EndByte: " << obj.get_UInt32(L"EndByte") << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_CHAT_COMMAND(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	/*
	todo - load into presupplied data blob or lookup in ggpk
	0x04 = /remaining, 0x06=/pvp, 0x08=/oos, 0x0d=/fixmyhelmet, etc
	*/
	UINT32 commandsDatIndex = obj.get_UInt32(L"CommandsDatIndex");
	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Used builtin command at commands.dat index: " << std::dec << commandsDatIndex <<
			" [Arg 0x: " << std::hex << arg << "]";
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

std::wstring wchar_to_channel(wchar_t firstbyte)
{
	switch (firstbyte)
	{
	case L'#':
		return L"Global";
	case L'%':
		return L"Party";
	case L'@':
		return L"Whisper";
	case L'$':
		return L"Trade";
	case L'&':
		return L"Guild";
	default:
		return L"Local";
	}
}


void exileSniffer::action_SRV_CHAT_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	std::wstring name = obj.get_wstring(L"Name");
	std::wstring tag = obj.get_wstring(L"Tag");
	std::wstring text = obj.get_wstring(L"Text");
	wstring channel;
	if (!text.empty())
		channel = wchar_to_channel(text.front());

	ushort devFlag = obj.get_UInt32(L"Dev");

	if (!analysis)
	{
		
		wstringstream summary;
		//if (devFlag)
		//	summary << "{-DEV-} ";
		summary << "Chat <" << channel << "> " << name;
		if (tag.size() > 0)
			summary << "[" << tag << "]";
		summary << ": " << text;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SERVER_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	//this is the row in the ggpk->dat file "BackendErrors.dat"
	UINT32 ggpkDatRow = obj.get_UInt32(L"BackendErrorsRow") - 1;
	UINT32 devID = obj.get_UInt32(L"DevID");
	UINT32 TextModifier = obj.get_UInt32(L"TextModifier");

	if (!analysis)
	{
		wstringstream summary;
		if (devID == 0xffff)
		{
			if (TextModifier) //todo: this is not boolean
				summary << "Server displayed pinned";
			else
				summary << "Server displayed standard";
		}
		else
		{
			if (TextModifier)
				summary << "Dev " << devID << " displayed fancy";
			else
				summary << "Dev " << devID << "displayed standard";
		}

		summary << "msgID " << ggpkDatRow;


		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::dec;
	analysisStream << "GGPK row: " << ggpkDatRow << std::endl;
	analysisStream << "Dev ID: " << devID << std::endl;
	analysisStream << std::hex;
	analysisStream << "Modifier: " <<TextModifier << std::endl;
	analysisStream << "UnkDWORD: " << obj.get_UInt32(L"Unk4") << std::endl;

	WValue &preloadList = obj.payload->FindMember(L"PairList")->value;
	if (preloadList.Size() == 0)
		analysisStream << "No argument pairs supplied" << std::endl;
	else
	{
		analysisStream << "Argument pairs:" << std::endl;
		for (auto pairit = preloadList.Begin(); pairit != preloadList.End(); pairit++)
		{
			WValue &pair = *pairit;
			//signedness may depend on type
			//all sorts of types which need dealing with
			analysisStream << "\tType " << 
				pair[0].GetUint() << ": " << pair[1].GetUint() << std::endl;
		}
	}

	analysisStream << std::endl;

	auto stringlist = obj.payload->FindMember(L"StringList");
	if (stringlist->value.Size() == 0)
		analysisStream << "No strings supplied" << std::endl;
	else
	{
		analysisStream << "String pairs:" << std::endl;
		for (auto stringit = stringlist->value.Begin(); stringit != stringlist->value.End(); stringit++)
		{
			//signedness may depend on type
			analysisStream << "\t" << stringit->GetString() << std::endl;
		}
	}
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_LOGGED_OUT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Game client logged out. [Arg: 0x"+QString::number((byte)arg, 16)+"]";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_CHAT_MSG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	//todo - item or not
	//todo - channel decode
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) spoke in chat: "+ QString::fromStdWString(obj.get_wstring(L"Message"));
		addDecodedListEntry(listentry, &obj);
		return;
	}

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

void exileSniffer::action_CLI_HNC(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 challenge = obj.get_UInt32(L"Challenge");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Game Client sent ping challenge 0x" + QString::number(challenge, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_HNC(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 response = obj.get_UInt32(L"Response");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent HNC response 0x" + QString::number(response, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_AREA_INFO(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD areaCode = obj.get_UInt32(L"AreaCode");
	std::wstring areaname = obj.get_wstring(L"AreaName");

	auto it = obj.payload->FindMember(L"PreloadHashList");
	if (it == obj.payload->MemberEnd())
	{
		add_metalog_update("Warning: No list found in payload of SRV_AREA_INFO", obj.getClientProcessID());
		return;
	}
	WValue &preloadList = it->value;
	unsigned short listSize = preloadList.Size();

	if (!analysis)
	{
		wstringstream summary;
		summary << "<Loading Area: " << areaname
			<< "> - Server sent environment and objects preload data (" << std::dec << listSize << " items)";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	DWORD variant = obj.get_UInt32(L"AreaVariant");
	analysisStream << "Animation preload information" << std::hex << std::endl;
	analysisStream << "Area " << areaname << "<" << std::dec << areaCode << "from worldareas.dat>" << std::endl;
	analysisStream <<  "Area variant 0x" << std::hex << variant << std::endl;
	analysisStream << "Difficulty name: " << obj.get_wstring(L"Difficulty") << std::endl;
	analysisStream << std::endl;

	analysisStream << std::hex;
	analysisStream << "Unknown values: A: 0x" << obj.get_UInt32(L"Unk1") <<
		" B: 0x" << obj.get_UInt32(L"Unk2") <<
		" C: 0x" << obj.get_UInt32(L"Unk3") <<
		" D: 0x" << obj.get_UInt32(L"Unk4") << std::endl << std::endl;

	it = obj.payload->FindMember(L"Unk5_b4_1");
	if (it != obj.payload->MemberEnd())
	{
		analysisStream << "Control bit 4 set. Data:" << std::endl;
		analysisStream << "\t1: 0x" << obj.get_UInt32(L"Unk5_b4_1") << std::endl;
		analysisStream << "\t2: 0x" << obj.get_UInt32(L"Unk5_b4_2") << std::endl;
		analysisStream << "\t3: 0x" << obj.get_UInt32(L"Unk5_b4_3") << std::endl << std::endl;
	}

	it = obj.payload->FindMember(L"Unk5_b5_1");
	if (it != obj.payload->MemberEnd())
	{
		analysisStream << "Control bit 5 set. Data:" << std::endl;
		analysisStream << "\t1: 0x" << obj.get_UInt32(L"Unk5_b5_1") << std::endl << std::endl;
	}



	vector<std::pair<std::wstring, std::pair<std::wstring, DWORD>>> preloadVec;
	for (auto it = preloadList.Begin(); it != preloadList.End(); it++)
	{
		DWORD hash = it->FindMember(L"Hash")->value.GetUint();
		std::wstring hashResult = it->FindMember(L"Item")->value.GetString();
		std::wstring hashCategory = it->FindMember(L"Category")->value.GetString();
		preloadVec.push_back(make_pair(hashCategory, make_pair(hashResult, hash)));
	}
	sort(preloadVec.begin(), preloadVec.end());

	analysisStream << "List of object hashes to preload" << std::endl;

	WValue preloadHashResults(rapidjson::kArrayType);

	std::wstring activeCategory = L"";
	for (auto it = preloadVec.begin(); it != preloadVec.end(); it++)
	{
		std::wstring hashCategory = it->first;
		std::pair<std::wstring, DWORD> result_hash = it->second;
		if (hashCategory != activeCategory)
		{
			activeCategory = hashCategory;
			analysisStream << hashCategory << "s:" << std::endl;
			activeCategory = hashCategory;
		}

		analysisStream << "\t\"" << result_hash.first << "\"" << std::endl;
	}
	analysisStream << std::endl;



	analysisStream << "Byte list 1:" << std::endl;
	WValue &blist1 = obj.payload->FindMember(L"ByteList1")->value;
	for (auto it = blist1.Begin(); it != blist1.End(); it++)
	{
		analysisStream << "\t0x" << it->GetUint() << ", ";
	}
	analysisStream << std::endl << std::endl;

	analysisStream << "Byte list 2:" << std::endl;
	WValue &blist2 = obj.payload->FindMember(L"ByteList2")->value;
	for (auto it = blist2.Begin(); it != blist2.End(); it++)
	{
		analysisStream << "\t0x" << it->GetUint() << ", ";
	}
	analysisStream << std::endl << std::endl;


	auto plit = obj.payload->FindMember(L"ByteList4");
	if (plit != obj.payload->MemberEnd())
	{
		analysisStream << "Byte list 4:" << std::endl;
		WValue &blist4 = plit->value;
		for (auto it = blist4.Begin(); it != blist4.End(); it++)
		{
			analysisStream << "\t0x" << it->GetUint() << ", ";
		}
		analysisStream << std::endl << std::endl;
	}

	
	plit = obj.payload->FindMember(L"ByteList5");
	if (plit != obj.payload->MemberEnd())
	{
		analysisStream << "Byte list 5:" << std::endl;
		WValue &blist5 = plit->value;
		for (auto it = blist5.Begin(); it != blist5.End(); it++)
		{
			analysisStream << "\t0x" << it->GetUint() << ", ";
		}
		analysisStream << std::endl << std::endl;
	}


	
	plit = obj.payload->FindMember(L"MapStatsList");
	if (plit != obj.payload->MemberEnd())
	{
		analysisStream << "Area Stats:" << std::endl;
		WValue &statlist = plit->value;
		for (auto statit = statlist.Begin(); statit != statlist.End(); statit++)
		{
			WValue &statdat = *statit;
			analysisStream << "\t" <<
					statdat[1].GetString()
					<< ": " << statdat[2].GetInt() << std::endl;
		}
		analysisStream << std::endl;
	}


	*analysis = QString::fromStdWString(analysisStream.str());

}

void exileSniffer::action_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt& obj, QString *analysis)
{

	obj.toggle_payload_operations(true);

	auto it = obj.payload->FindMember(L"PreloadList");
	if (it == obj.payload->MemberEnd())
	{
		add_metalog_update("Warning: No list found in payload of SRV_PRELOAD_MONSTER_LIST", obj.getClientProcessID());
		return;
	}
	
	WValue &monsterList = it->value;
	unsigned short listSize = monsterList.Size();

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent monster preload list with " << std::dec << listSize << " entries";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}


	std::vector<std::pair<unsigned short, std::wstring>> pairVec;
	for (auto it = monsterList.Begin(); it != monsterList.End(); it++)
	{
		auto dayArray = it->GetArray();
		if (dayArray.Size() != 3)
		{
			add_metalog_update("Warning: Bad pair dat array in SRV_PRELOAD_MONSTER_LIST", obj.getClientProcessID());
			return;
		}
		std::wstring varietyName = dayArray[1].GetString();
		unsigned short level = dayArray[2].GetUint();
		pairVec.push_back(make_pair(level, varietyName));
	}

	std::sort(pairVec.rbegin(), pairVec.rend());

	wstringstream analysisStream;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	analysisStream << "Monster preload list sent by server <Indexes into MonsterVarieties.dat> " << std::endl;

	unsigned int monsterLevel = pairVec.front().first + 1;
	for (auto it = pairVec.begin(); it != pairVec.end(); it++)
	{
		unsigned short level = it->first;
		std::wstring monstername = it->second;

		if (level < monsterLevel)
		{
			analysisStream << "Level: " << std::dec << level << std::endl;
			monsterLevel = level;
		}

		wstring idstring;
		analysisStream << "\t" << monstername << std::endl;

	}
	*analysis = QString::fromStdWString(analysisStream.str());


}

void exileSniffer::action_SRV_UNK_0x13(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &bloblist = obj.payload->FindMember(L"BlobList")->value;
	size_t listSize = bloblist.Size();


	std::wstring endString = obj.payload->FindMember(L"EndString")->value.GetString();
	DWORD endShort = obj.payload->FindMember(L"EndShort")->value.GetUint();
	DWORD endDWORD = obj.payload->FindMember(L"EndDWORD")->value.GetUint();


	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent pck 0x13 with " << std::dec << listSize << 
			" entries. Endstring: "<<endString<<", EndVal1: 0x"<<std::hex<< endShort<<
			", EndVal2: 0x"<<endDWORD;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	int i = 0;
	for (auto listit = bloblist.Begin(); listit != bloblist.End(); listit++)
	{
		analysisStream << "Blob: " << std::dec << i << std::hex <<std::endl;
		analysisStream << "-------" << std::endl;
		analysisStream << "DW1: 0x" << listit->FindMember(L"DW1")->value.GetUint() << std::endl;
		analysisStream << "DW2: 0x" << listit->FindMember(L"DW2")->value.GetUint() << std::endl;
		analysisStream << "String: "<< listit->FindMember(L"UnkString")->value.GetString() << std::endl;
		analysisStream << "Short1: 0x" << listit->FindMember(L"Short1")->value.GetUint() << std::endl;
		analysisStream << "Short2: 0x" << listit->FindMember(L"Short2")->value.GetUint() << std::endl;
		analysisStream << "DW3: 0x" << listit->FindMember(L"DW3")->value.GetUint() << std::endl;
		analysisStream << "DW4: 0x" << listit->FindMember(L"DW4")->value.GetUint() << std::endl;
		analysisStream << "Byte2: 0x" << listit->FindMember(L"Byte2")->value.GetUint() << std::endl;
		analysisStream << "ControlByte: 0x" << listit->FindMember(L"ControlByte")->value.GetUint() << std::endl;

		auto CB_GT_0x80it = listit->FindMember(L"DW_8_1");
		if (CB_GT_0x80it != listit->MemberEnd())//controlByte > 0x80)
		{
			analysisStream << "DW_8_1: 0x" << listit->FindMember(L"DW_8_1")->value.GetUint() << std::endl;
			analysisStream << "DW_8_2: 0x" << listit->FindMember(L"DW_8_2")->value.GetUint() << std::endl;
		}

		auto CB_GTE_0x40it = listit->FindMember(L"Byte_b7");
		if (CB_GTE_0x40it != listit->MemberEnd())//controlByte & 0x40
		{
			analysisStream << "Byte_b7: 0x" << listit->FindMember(L"Byte_b7")->value.GetUint() << std::endl;
		}
		analysisStream << std::endl << std::endl;
		i += 1;
	}

	analysisStream << "Endstring: " << endString << std::endl;
	analysisStream << "EndShort : 0x" << std::hex << endShort << std::endl;
	analysisStream << "EndDWORD : 0x" << std::hex << endDWORD << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_ITEMS_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD objID = obj.get_UInt32(L"ObjID");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server listing items held by obj ID: 0x"+QString::number(objID,16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 targID = obj.get_UInt32(L"TargID");
	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 seq = obj.get_UInt32(L"Sequence");
	UINT32 modifier = obj.get_UInt32(L"Modifier");
	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Player(You) clicked itemID 0x" << std::hex << targID << " Skill: 0x" << skillID;

		if (modifier)
			summary << " [" << explainModifier(modifier) << "]";

		if (modifier > 0xf || !(modifier & 0x8))
			summary << " <!Unusual modifier 0x" << std::hex << modifier << " - what are you doing?>";

		summary << " seq: 0x" << seq;
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_ACTION_PREDICTIVE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 coord1 = obj.get_UInt32(L"TargCoord1");
	UINT32 coord2 = obj.get_UInt32(L"TargCoord2");
	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 PkCount = obj.get_UInt32(L"PkCount");
	UINT32 modifier = obj.get_UInt32(L"Modifier");
	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Player(You) used skillID 0x" << std::hex << skillID <<
			" on coord " << std::dec << coord1 << "," << coord2;
		if (modifier != 0x08) //standard mouse click
			summary << "[" << explainModifier(modifier) << "]";

		if (modifier > 0xf || !(modifier & 0x8))
			summary << " <!Unusual modifier 0x" << std::hex<< modifier << " - what are you doing?>";
	

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_TRANSFER_INSTANCE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server transferred account to another instance. Arg 0x" + QString::number(arg, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(L"Server sent instance server data");
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_PICKUP_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 container = obj.get_UInt32(L"Container");
	UINT32 itemID = obj.get_UInt32(L"ItemID");
	UINT32 unk = obj.get_UInt32(L"Unk");

	std::wstringstream summary;
	summary << "Player(You) picked up itemID 0x" << std::hex << itemID 
		<< " in container: " << slotToString(container) <<". UnkByte: 0x"<<unk;

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_PLACE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 container = obj.get_UInt32(L"Container");
	UINT32 col = obj.get_UInt32(L"Column");
	UINT32 row = obj.get_UInt32(L"Row");
	UINT32 unk1 = obj.get_UInt32(L"Row");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Placed item down in container " << slotToString(container) << " at (" << std::dec << col << "," << row << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_DROP_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);


	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Dropped held item on ground";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_REMOVE_SOCKET(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) emptied socket";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_INSERT_SOCKET(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) inserted into socket";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_LEVEL_SKILLGEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) levelled a skillgem";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0x20(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Unknown packet 0x20 (skill maybe)";
		//summary << "Unknown social/account name " << obj.get_wstring(L"Name") << std::hex;
		//summary << "  -  Other data: 0x" << obj.get_UInt32(L"Unk1") << ", 0x" << obj.get_UInt32(L"Unk2")
		//	<< ", 0x" << obj.get_UInt32(L"Unk3") << ", 0x" << obj.get_UInt32(L"Unk4");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) added a skillpoint";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CHOSE_ASCENDANCY(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	ushort choice = obj.get_UInt32(L"Choice");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player chose ascendancy "+QString::number(choice);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_MERGE_STACK(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	//not reversed the payload, dunno if these are the right size
	int unk1 = obj.get_UInt32(L"Unk1");
	int unk2 = obj.get_UInt32(L"Unk2");
	int unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Player merged item stacks. Data: 0x" << unk1 << ", 0x" << unk2 << ", 0x" << unk3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CANCEL_BUF(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	int buffID = obj.get_UInt32(L"BuffID");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Attempted to cancel buff "+QString::number(buffID,10);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0x2c(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Unknown packet 0x2c. Unk size bytes read (4 seen) + 13 bytes at end";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SELECT_MAPTRAVEL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD areaCode = obj.get_UInt32(L"AreaCode");
	std::wstring areaname;
	ggpk->lookup_areaCode(areaCode, areaname);

	DWORD unk2 = obj.get_UInt32(L"Arg2");
	byte byte = obj.get_UInt32(L"Arg3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Player selected waypoint in area " << areaname <<
			std::hex<< ", Arg2: 0x"<<unk2<<", Arg3: 0x"<<byte;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SET_HOTBARSKILL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	byte slot = obj.get_UInt32(L"Slot");
	byte skillID = obj.get_UInt32(L"SkillID");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Set hotbar slot "+QString::number(slot)+" to 0x"+QString::number(skillID, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SKILL_SLOTS_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent hotbar skill ID list";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//todo - lookup the id and match with the associated skillgem or action
	std::wstringstream analysisStream;

	analysisStream << std::hex;
	analysisStream << "Primary skill bar:" << std::endl;
	analysisStream << "\tSkill 1 ID: 0x" << obj.get_UInt32(L"Skill1") << std::endl;
	analysisStream << "\tSkill 2 ID: 0x" << obj.get_UInt32(L"Skill2") << std::endl;
	analysisStream << "\tSkill 3 ID: 0x" << obj.get_UInt32(L"Skill3") << std::endl;

	analysisStream << "Secondary skill bar:" << std::endl;
	analysisStream << "\tSkill 4 ID: 0x" << obj.get_UInt32(L"Skill4") << std::endl;
	analysisStream << "\tSkill 5 ID: 0x" << obj.get_UInt32(L"Skill5") << std::endl;
	analysisStream << "\tSkill 6 ID: 0x" << obj.get_UInt32(L"Skill6") << std::endl;
	analysisStream << "\tSkill 7 ID: 0x" << obj.get_UInt32(L"Skill7") << std::endl;
	analysisStream << "\tSkill 8 ID: 0x" << obj.get_UInt32(L"Skill8") << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_REVIVE_CHOICE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 choice = obj.get_UInt32(L"Choice");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player chose revive option " + QString::number(choice);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_YOU_DIED(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	QString summary;
	UINT32 choices = obj.get_UInt32(L"Slot");
	UINT32 unk1 = obj.get_UInt32(L"Unk");
	
	if (choices & 0x2)
	{
		summary = "Resurrection dialog removed";
	}
	else if (choices & 0x1)
	{
		summary = "Resurrection dialog: Exit";
	}
	else
	{
		switch (choices)
		{
		case 0:
			summary = "Resurrection dialog: Resurrect";
			break;
		case 4:
			summary = "Resurrection dialog: Checkpoint";
			break;
		case 8:
			summary = "Resurrection dialog: Town";
			break;
		case 0xc:
			summary = "Resurrection dialog: Town + Checkpoint";
			break;
		default:
			summary = "Resurrection dialog: Unknown options 0x"+QString::number(choices,16);
			break;
		}
	}

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = summary + " Arg: 0x"+QString::number(unk1, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_ACTIVATE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	//total guess that this is quantity
	UINT32 q1 = obj.get_UInt32(L"Unk1");
	UINT32 item1 = obj.get_UInt32(L"Item1");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Used (" << std::dec << q1 << ") item 0x" << std::hex << item1;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_USE_BELT_SLOT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 slot = obj.get_UInt32(L"Slot");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Activated belt slot "+QString::number(slot);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_USE_ITEM_ON_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	//total guess that this is quantity
	UINT32 q1 = obj.get_UInt32(L"Unk1");
	UINT32 item1 = obj.get_UInt32(L"Item1");
	UINT32 q2 = obj.get_UInt32(L"Unk2");
	UINT32 item2 = obj.get_UInt32(L"Item2");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Used (" << std::dec<< q1 << ") item 0x" << std::hex << item1;
		summary << " on (" << std::dec << q2 << ") item 0x" << std::hex << item2;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_UNK_0x41(UIDecodedPkt& obj, QString* analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Unk pkt 0x41";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SELECT_NPC_DIALOG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 option = obj.get_UInt32(L"Option");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client selected dialog option "+QString::number(option);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}
void exileSniffer::action_SRV_SHOW_NPC_DIALOG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	//seen 1 while going from town to riverways, maybe declares area as fightable/droppable items?

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");
	UINT32 dialogIdx = obj.get_UInt32(L"Option");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Dialog item " << std::dec << dialogIdx << " shown for object (0x" << 
			std::hex << ID1 << "," << ID2 << "," << ID3 << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;

	analysisStream << "Object ID: (0x" << std::hex << ID1 << ", " << ID2 << ", " << ID3 << ")" << std::endl;
	analysisStream << "Dialog option: " << std::dec << dialogIdx << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}
void exileSniffer::action_CLI_CLOSE_NPC_DIALOG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player closed dialog";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_OPEN_UI_PANE(UIDecodedPkt& obj, QString* analysis)
{
	obj.toggle_payload_operations(true);

	std::string paneName;
	UINT32 paneID = obj.get_UInt32(L"PaneID");

	auto it = ggpk->UIPaneIDs.find(paneID);
	if (it != ggpk->UIPaneIDs.end())
		paneName = ggpk->UIPaneIDs.at(paneID);
	else
		paneName = "<Unkown Pane. Where did this happen?>";

	UINT32 arg = obj.get_UInt32(L"Arg");

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Server opened Client UI pane "<<converter.from_bytes(paneName)<<std::hex<<", Arg: 0x" << arg;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SPLIT_STACK(UIDecodedPkt& obj, QString* analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");

	UINT32 iid = obj.get_UInt32(L"ItemID1");
	UINT32 stacksize = obj.get_UInt32(L"MouseStackSize");

	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Player split inventory stack. Mouse stack size: " << std::dec << stacksize;
		summary << std::hex;
		summary << "ItemID1: 0x" << iid;
		summary << ", Unk32: 0x" << unk1 << ", Unk8: 0x" << unk2;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_LIST_PORTALS(UIDecodedPkt& obj, QString* analysis)
{
	obj.toggle_payload_operations(true);

	WValue &portallist = obj.payload->FindMember(L"PortalList")->value;
	size_t listSize = portallist.Size();

	if (!analysis)
	{
		wstringstream summary;
		summary << "List of "<< std::dec << listSize <<" portals";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << "Portal list:" << std::dec << std::endl;

	for (auto it = portallist.Begin(); it != portallist.End(); it++)
	{
		UINT32 ID = it->FindMember(L"ID")->value.GetUint();
		UINT32 unk1 = it->FindMember(L"Unk1")->value.GetUint();
		std::wstring unkstring = it->FindMember(L"String")->value.GetString();
		UINT32 unk2 = it->FindMember(L"Unk2")->value.GetUint();

		analysisStream << "ID 0x" << std::hex << ID << std::endl;
		analysisStream << "Unk1 0x" << std::hex << unk1 << std::endl;
		analysisStream << "String: " << unkstring << std::endl;
		analysisStream << "Unk2 0x" << std::hex << unk2 << std::endl;
		analysisStream << std::endl;
	}

	analysisStream << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_SEND_PARTY_INVITE(UIDecodedPkt& obj, QString* analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Invited other player \"" << obj.get_wstring(L"Name") << "\" to party";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_TRY_JOIN_PARTY(UIDecodedPkt& obj, QString*analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Sent request to join public party ID 0x" << std::hex << obj.get_UInt32(L"ID");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_DISBAND_PUBLIC_PARTY(UIDecodedPkt& obj, QString*analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Disbanded public party ID 0x" << std::hex << obj.get_UInt32(L"ID");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CREATE_PUBLICPARTY(UIDecodedPkt& obj, QString*analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Created public party called: \"" 
			<< obj.get_wstring(L"Name") << "\" - arg 0x" << std::hex << obj.get_UInt32(L"Arg");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_UNK_x56(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	//seen 1 while going from town to riverways, maybe declares area as fightable/droppable items?

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		if (arg != 1)
			listentry.summary = "Sent packet 0x56 - (usual 1 as argument)";
		else
			listentry.summary = "!Client packet 0x56 has new argument!: " + QString::number(arg);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_GET_PARTY_DETAILS(UIDecodedPkt& obj, QString*analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Send joined request for public party 0x" << std::hex << obj.get_UInt32(L"ID");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_FRIENDSLIST(UIDecodedPkt& obj, QString *analysis)
{

	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Character socialpane " << obj.get_wstring(L"Name") << ", " << obj.get_wstring(L"String2");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}


	std::wstringstream analysisStream;

	analysisStream << "String1: " << obj.get_wstring(L"Name") << std::endl;
	analysisStream << "String2: " << obj.get_wstring(L"String2") << std::endl;

	auto it = obj.payload->FindMember(L"0_QWord");
	if (it != obj.payload->MemberEnd())
	{
		analysisStream << "QWord1: " <<std::hex<< it->value.GetUint64() << std::endl;
	}
	else
	{
		analysisStream << "String3: " << obj.get_wstring(L"String3") << std::endl;
		analysisStream << "Unk1: 0x" << obj.get_UInt32(L"1_Unk1") << std::endl;
		analysisStream << "Unk2: 0x" << obj.get_UInt32(L"1_Unk2") << std::endl;
		analysisStream << "Unk3: 0x" << obj.get_UInt32(L"1_Unk3") << std::endl;
		analysisStream << "Unk4: 0x" << obj.get_UInt32(L"1_Unk4") << std::endl;

		analysisStream << "String4: " << obj.get_wstring(L"String4") << std::endl;
		analysisStream << "Unk5: 0x" << obj.get_UInt32(L"1_Unk5") << std::endl;
		analysisStream << "Unk6: 0x" << obj.get_UInt32(L"1_Unk6") << std::endl;
		analysisStream << "Unk7: 0x" << obj.get_UInt32(L"1_Unk7") << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_PARTY_DETAILS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID = obj.get_UInt32(L"ID");
	std::wstring description = obj.get_wstring(L"Description");

	WValue &memberlist = obj.payload->FindMember(L"MemberList")->value;
	size_t listSize = memberlist.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent details for public party (" + QString::number(listSize) + " members)";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");

	std::wstringstream analysisStream;
	analysisStream << std::hex;
	analysisStream << "Party ID: 0x" << ID << std::endl;
	analysisStream << "Unk byte 1: 0x" << unk1 << std::endl;
	analysisStream << "Unk byte 2: 0x" << unk2 << std::endl;

	analysisStream << std::dec << listSize << " members:" << std::endl;
	for (auto it = memberlist.Begin(); it != memberlist.End(); it++)
	{
		analysisStream << "\t" << it->FindMember(L"Name")->value.GetString();
		analysisStream << " (" << it->FindMember(L"StatusText")->value.GetString() << ")"<< std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_PARTY_ENDED(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Party ended";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested latest public parties - arg " + obj.get_UInt32(L"Arg");
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent list of public parties";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_MOVE_ITEM_PANE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD paneID = obj.get_UInt32(L"PaneID");
	DWORD itemID = obj.get_UInt32(L"ItemID");
	DWORD column = obj.get_UInt32(L"Column");
	DWORD row = obj.get_UInt32(L"Row");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Client placed item 0x" << itemID << " in pane 0x" << paneID 
			<< " at " << std::dec << column << "," << row;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}



void exileSniffer::action_CLI_CONFIRM_SELL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Player confirmed sale. Arg: 0x"<<std::hex<<arg;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}


	std::wstringstream analysisStream;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_UNK_0x67(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	std::wstring unkstring = obj.get_wstring(L"UnkString");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Unk (vendor related msg) 0x67: " << unkstring;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;

	analysisStream << "Unk1: 0x" << obj.get_UInt32(L"Unk1") << std::endl;
	analysisStream << "Unk2: 0x" << obj.get_UInt32(L"Unk2") << std::endl;
	analysisStream << "Unk3: 0x" << obj.get_UInt32(L"Unk3") << std::endl;
	analysisStream << "Unk4: 0x" << obj.get_UInt32(L"Unk4") << std::endl;
	analysisStream << "String: " << unkstring << std::endl;
	analysisStream << "Unk5: 0x" << obj.get_UInt32(L"Unk5") << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_UNK_0x68(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	if (!analysis)
	{
		wstringstream summary;
		summary << std::hex << "Unk (vendor related msg) 0x68. Unk1: 0x" << obj.get_UInt32(L"Unk1")
			<< ", Unk2: 0x" << obj.get_UInt32(L"Unk2");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;

	*analysis = QString::fromStdWString(analysisStream.str());
}


//todo this and the pkt below share a lot of item handling code
//create a common itemlist analysis function
void exileSniffer::action_SRV_UNK_0x6c(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &bloblist = obj.payload->FindMember(L"UnkList")->value;
	size_t listSize = bloblist.Size();

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent unknown string/byte pair list with "<< bloblist.Size() << " entries";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << "String/Byte list:" << std::dec << std::endl;

	for (auto it = bloblist.Begin(); it != bloblist.End(); it++)
	{
		analysisStream << "\t" << it->FindMember(L"String")->value.GetString() << ": " <<
			it->FindMember(L"Byte")->value.GetUint() << std::endl;
	}

	analysisStream << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());

}

void exileSniffer::action_SRV_CREATE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		wstringstream summary;
		summary << "Server updated items in inventory";
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	byte unk1 = obj.get_UInt32(L"B1");
	DWORD slot = obj.get_UInt32(L"Slot");
	DWORD unk3 = obj.get_UInt32(L"DW2");

	analysisStream << std::hex;
	analysisStream << "Unk1: 0x" << unk1 << std::endl;
	analysisStream << "Slot: 0x" << slot<< std::endl;
	analysisStream << "Unk3: 0x" << unk3 << std::endl;

	analysisStream << "List1: " << std::endl;

	WValue& list1 = obj.payload->FindMember(L"List1")->value;
	for (auto it = list1.Begin(); it != list1.End(); it++)
	{
		analysisStream << "\t0x" << it->GetUint() << std::endl;
	}

	analysisStream << "ItemList: " << std::endl;
	WValue& itemList = obj.payload->FindMember(L"ItemList")->value;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	analysisStream << "\nItem List (Location):Name (Hash) ServerID" << std::endl;

	for (auto it = itemList.Begin(); it != itemList.End(); it++)
	{
		DWORD instanceID = it->FindMember(L"ItemID")->value.GetUint();
		ushort posX = it->FindMember(L"Column")->value.GetUint();
		ushort posY = it->FindMember(L"Row")->value.GetUint();
		DWORD hash = it->FindMember(L"ItemHash")->value.GetUint();
		std::string itemname, category;
		ggpk->lookup_hash(hash, itemname, category);

		analysisStream << "   (" << std::dec << (ushort)posX << "," << (ushort)posY << "): " <<
				converter.from_bytes(itemname) << std::hex << " (0x" << hash << ") ID: 0x" << instanceID << std::endl;
	}


	byte lflag = obj.get_UInt32(L"LastFlag");
	if (lflag)
	{
		analysisStream << "lflag: 0x" << lflag << std::endl;
		analysisStream << "end1: 0x" << obj.get_UInt32(L"End1") << std::endl;
		analysisStream << "end2: 0x" << obj.get_UInt32(L"End2") << std::endl;
		analysisStream << "end3: 0x" << obj.get_UInt32(L"End3") << std::endl;
		analysisStream << "end4: 0x" << obj.get_UInt32(L"End4") << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_SRV_SLOT_ITEMSLIST(UIDecodedPkt& obj, QString *analysis)
{

	obj.toggle_payload_operations(true);

	//this is wrong when opening vendor things
	//unk or previous packet describes obj listing is for
	DWORD containerCode = obj.get_UInt32(L"Container");
	std::wstring container = slotToString(containerCode);

	DWORD itemCount = obj.get_UInt32(L"Count");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent list of " << std::dec << itemCount << " items in slot " << container;
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	auto it = obj.payload->FindMember(L"ItemList");
	if (it == obj.payload->MemberEnd())
	{
		add_metalog_update("Warning: No itemlist found in payload of action_SRV_SLOT_ITEMSLIST", obj.getClientProcessID());
		return;
	}
	WValue &itemList = it->value;
	unsigned short listSize = itemList.Size();

	wstringstream analysisStream;
	analysisStream << "Listing requires significant reversing of object/modifier parsing" << std::hex<< std::endl;
	analysisStream << "Unknown bytes before actual item list:" << std::endl;
	analysisStream << "\tUnk1: 0x"<< obj.get_UInt32(L"Unk1") << std::endl;
	analysisStream << "\t---\n\tUnk2: 0x" << obj.get_UInt32(L"Unk2") << std::endl;
	analysisStream << "\tUnk3: 0x" << obj.get_UInt32(L"Unk3") << std::endl;
	analysisStream << "\tUnk4: 0x" << obj.get_UInt32(L"Unk4") << std::endl;
	analysisStream << "\tUnk5: 0x" << obj.get_UInt32(L"Unk5") << std::endl;
	analysisStream << "\tUnk6: 0x" << obj.get_UInt32(L"Unk6") << std::endl;

	
	if (itemList.Size() == 0)
		analysisStream << "\nItem List: (empty)"<<std::endl;
	else
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		analysisStream << "\nItem List (Location):Name (Hash) ServerID" << std::endl;

		for (auto it = itemList.Begin(); it != itemList.End(); it++)
		{
			DWORD instanceID = it->FindMember(L"InstanceID")->value.GetUint();
			ushort posX = it->FindMember(L"PosX")->value.GetUint();
			ushort posY = it->FindMember(L"PosY")->value.GetUint();
			DWORD hash = it->FindMember(L"ItemHash")->value.GetUint();
			std::string itemname, category;
			ggpk->lookup_hash(hash, itemname, category);

			analysisStream << "   (" << std::dec << (ushort)posX << "," << (ushort)posY << "): " <<
				converter.from_bytes(itemname) << std::hex << " (0x" << hash << ") ID: 0x" << instanceID << std::endl;
		}
		analysisStream << std::endl;
		analysisStream << "These can be looked up by their hash in BaseItemTypes.dat" << std::endl;
	}

	analysisStream << "\nFinal(?) unknown: 0x" << std::hex << obj.get_UInt32(L"FinalUnk") << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_INVENTORY_SET_REMOVE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD unk1 = obj.get_UInt32(L"Unk1");
	DWORD unk2 = obj.get_UInt32(L"Unk2");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Inventory set remove. Unk1: 0x" << std::hex << unk1 << ", Unk2: 0x"<< unk2;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_UNK_0x70(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD data1 = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server msg 0x70. Data: 0x" << std::hex << data1;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SELECT_STASHTAB(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Client changed stash tab. Data: 0x" << std::hex << unk1 << ", 0x"<<unk2<<", 0x"<<unk3;
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_STASHTAB_DATA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Stash tab data: 0x" << std::hex << unk1 << ", 0x" << unk2 << ", 0x" << unk3;
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0x73(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 data1 = obj.get_UInt32(L"Data1");
	std::wstring string1 = obj.get_wstring(L"String1");
	std::wstring string2 = obj.get_wstring(L"String2");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server msg 0x73. Data: 0x" << std::hex << data1 << ". Str1: " << string1 
			<< ", String2: "<<string2 <<" (bad strings? Different length data...)";
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SET_STATUS_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Set status text: \"" << obj.get_wstring(L"StatusText") << "\"";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_MOVE_OBJECT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 objectID = obj.get_UInt32(L"ObjectID");
	UINT32 coord1 = obj.get_UInt32(L"Coord1");
	UINT32 coord2 = obj.get_UInt32(L"Coord2");
	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 flags = obj.get_UInt32(L"Flags");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Object 0x" << std::hex << objectID << " moved to coord (" << std::dec << coord1 << "," << coord2 << ").";
		summary << std::hex << "Unk1: 0x"<< unk1 <<", Unk2: 0x" << unk2;
		if (flags)
			summary << " +Flags 0x" << flags;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::hex;
	analysisStream << "ObjectID: 0x" << objectID << std::endl;
	analysisStream << "Coords: (" << std::dec << obj.get_UInt32(L"Coord1") << "," << obj.get_UInt32(L"Coord2") << ")" << std::endl;
	analysisStream << "Unk1: 0x" << obj.get_UInt32(L"Unk1") << std::endl;
	analysisStream << "Unk2: 0x" << obj.get_UInt32(L"Unk2") << std::endl;
	analysisStream << std::endl;

	analysisStream << "Flags: 0x" << flags << std::endl;
	if (flags & 0x8)
	{
		analysisStream << "Flag 0x8 val: 0x" << obj.get_UInt32(L"Unk_cond_a") << std::endl;
	}
	if (flags & 0x10)
	{
		analysisStream << "Flag 0x10 val: 0x" << obj.get_UInt32(L"Unk_cond_b") << std::endl;
	}



	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_ACTIVATE_MAP(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	byte arg = obj.get_UInt32(L"Byte");
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player activate map device";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = "No extra data expected";
}


void exileSniffer::action_CLI_SWAPPED_WEAPONS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	byte arg = obj.get_UInt32(L"Byte");
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Swapped to weapon slot "+QString::number(arg,10);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_ADJUST_LIGHTING(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex;
		summary << "Unk msg 0x81. Arg1: 0x "<< unk1 << ", Arg2: 0x"<<unk2 << ", Arg3: 0x" << unk3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	analysisStream << "Unknown short Unk1: 0x" << unk1 << std::endl;
	analysisStream << "Unknown byte Unk2: 0x" << unk2 << std::endl;
	analysisStream << "Unknown dword Unk3: 0x" << unk3 << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_TRANSFER_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 container = obj.get_UInt32(L"Container");
	UINT32 item = obj.get_UInt32(L"Item");
	UINT32 unk = obj.get_UInt32(L"Unk");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex;
		summary << "Player moved item 0x" << std::hex << " to container 0x" << container << ". Unk byte: 0x" << unk;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	analysisStream << "Container: 0x" << container << std::endl;
	analysisStream << "Item ID: 0x" << item << std::endl;
	analysisStream << "Unknown byte: 0x" << unk << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_INVENTORY_FULL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "'Inventory Full' notice";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = "No further data expected";
}


QString exileSniffer::stringify_eventslist(WValue &eventlist)
{
	wstringstream analysisStream;

	for (auto evIt = eventlist.Begin(); evIt != eventlist.End(); evIt++)
	{
		analysisStream << "Name: " << evIt->FindMember(L"StringRef")->value.GetString() << std::endl;
		analysisStream << "\tDescription: " << evIt->FindMember(L"Description")->value.GetString() << std::endl;
		analysisStream << "\tMode1: " << evIt->FindMember(L"Mode1")->value.GetString() << std::endl;
		analysisStream << "\tMode2: " << evIt->FindMember(L"Mode2")->value.GetString() << std::endl;
		analysisStream << "\tUnk1: 0x" << std::hex << evIt->FindMember(L"Unk1")->value.GetUint() << std::endl;

		unsigned short minlevel = evIt->FindMember(L"MinLevel")->value.GetUint();
		if(minlevel)
			analysisStream << "\tMinLevel: " << std::dec << minlevel << std::endl;
		else
			analysisStream << "\tMinLevel: " << "-" << std::endl;

		unsigned short maxlevel = evIt->FindMember(L"MaxLevel")->value.GetUint();
		if (maxlevel)
			analysisStream << "\tMaxLevel: " << std::dec << maxlevel << std::endl;
		else
			analysisStream << "\tMaxLevel: " << "-" << std::endl;

		analysisStream << "\tUnk2: 0x" << std::hex << evIt->FindMember(L"Unk2")->value.GetUint() << std::endl;
		analysisStream << "\tUnk3_64 (Time?): 0x" << evIt->FindMember(L"Unk3_64")->value.GetUint64() << std::endl;
		analysisStream << "\tUnk4_64 (Time?): 0x" << evIt->FindMember(L"Unk4_64")->value.GetUint64() << std::endl;
		analysisStream << "\tUnk5_64 (Time?): 0x" << evIt->FindMember(L"Unk5_64")->value.GetUint64() << std::endl;
		analysisStream << "\tUnk6: 0x" << evIt->FindMember(L"Unk6")->value.GetUint() << std::endl;
		analysisStream << "\tUnk7: 0x" << evIt->FindMember(L"Unk7")->value.GetUint() << std::endl;
		analysisStream << std::endl;
	}
	analysisStream << std::endl;

	return QString::fromStdWString(analysisStream.str());
}

QString exileSniffer::stringify_eventslist_2(WValue &eventlist)
{
	wstringstream analysisStream;

	

	for (auto it = eventlist.Begin(); it != eventlist.End(); it++)
	{
		analysisStream << "Name: " << it->FindMember(L"Name")->value.GetString() << std::endl;
		analysisStream << "Label1: " << it->FindMember(L"Label1")->value.GetString() << std::endl;
		analysisStream << "Label2: " << it->FindMember(L"Label2")->value.GetString() << std::endl;
		analysisStream << std::dec;
		analysisStream << "StartTime: " << it->FindMember(L"StartTime")->value.GetUint64() << std::endl;
		analysisStream << "RegisterTime: " << it->FindMember(L"RegisterTime")->value.GetUint64() << std::endl;
		analysisStream << "Time3: " << it->FindMember(L"Unk5_64")->value.GetUint64() << std::endl;
		analysisStream << std::hex;
		analysisStream << "Unk6: 0x" << it->FindMember(L"Unk6")->value.GetUint() << std::endl;
		analysisStream << "Unk7: 0x" << it->FindMember(L"Unk7")->value.GetUint() << std::endl;

		analysisStream << std::endl;
	}

	return QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_SRV_PVP_MATCHLIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &eventlist = obj.payload->FindMember(L"EventList")->value;
	size_t listSize = eventlist.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "List of "+ QString::number(listSize)+" available PVP match types";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = stringify_eventslist(eventlist);
}

void exileSniffer::action_SRV_EVENTSLIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &eventlist = obj.payload->FindMember(L"EventList")->value;
	size_t listSize = eventlist.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "List of " + QString::number(listSize) + " available events to join";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = stringify_eventslist(eventlist);
}



void exileSniffer::action_CLI_SKILLPANE_ACTION(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Used skillpane";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_ACHIEVEMENT_1(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Achievement_1 arg: 0x" + QString::number(arg,16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_ACHIEVEMENT_2(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Achievement_2 arg: 0x" + QString::number(arg, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SKILLPANE_DATA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Skillpane data from server";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_POSITION_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);


	auto it = obj.payload->FindMember(L"CoordArray");
	WValue &itemList = it->value;

	unsigned short listSize = itemList.Size();
	if (!analysis)
	{
		WValue &first = itemList[0];
		UINT32 item1 = first[0].GetUint();
		UINT32 item2 = first[1].GetUint();
		UINT32 item3 = first[2].GetUint();

		wstringstream summary;
		summary << "Srv positionlist with " <<std::dec << itemList.Size() << " entries beginning (" <<
			item1 << "," << item2 << "," << item3 << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << "List entries: " << std::endl;
	for (auto it = itemList.Begin(); it != itemList.End(); it++)
	{
		WValue &item = *it;
		analysisStream << "\t(" << item[0].GetUint() << "," <<
			item[1].GetUint() << ","
			<< item[2].GetUint() << ")" << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_MICROTRANSACTION_SHOP_ACTION(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) opened microtransaction pane";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_MICROTRANSACTION_SHOP_DETAILS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Transaction pane details from server";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_UNK_A3(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Unk message A3 from client";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_A5(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &bloblist = obj.payload->FindMember(L"BlobList")->value;
	size_t listSize = bloblist.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Unknown list A5";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << "Prefix byte: " << std::dec << obj.get_UInt32(L"Prefix")<<std::endl;
	analysisStream << "Members: " << std::endl;

	int i = 0;
	for (auto listit = bloblist.Begin(); listit != bloblist.End(); listit++)
	{
		analysisStream << "Blob: " << std::dec << i << std::hex << std::endl;
		analysisStream << "-------" << std::endl;
		analysisStream << "DW1: 0x" << listit->FindMember(L"DW1")->value.GetUint() << std::endl;
		analysisStream << "DW2: 0x" << listit->FindMember(L"DW2")->value.GetUint() << std::endl;
		analysisStream << "String: " << listit->FindMember(L"UnkString")->value.GetString() << std::endl;
		analysisStream << "Short1: 0x" << listit->FindMember(L"Short1")->value.GetUint() << std::endl;
		analysisStream << "Short2: 0x" << listit->FindMember(L"Short2")->value.GetUint() << std::endl;
		analysisStream << "DW3: 0x" << listit->FindMember(L"DW3")->value.GetUint() << std::endl;
		analysisStream << "DW4: 0x" << listit->FindMember(L"DW4")->value.GetUint() << std::endl;
		analysisStream << "Byte2: 0x" << listit->FindMember(L"Byte2")->value.GetUint() << std::endl;
		analysisStream << "ControlByte: 0x" << listit->FindMember(L"ControlByte")->value.GetUint() << std::endl;

		auto CB_GT_0x80it = listit->FindMember(L"DW_8_1");
		if (CB_GT_0x80it != listit->MemberEnd())//controlByte > 0x80)
		{
			analysisStream << "DW_8_1: 0x" << listit->FindMember(L"DW_8_1")->value.GetUint() << std::endl;
			analysisStream << "DW_8_2: 0x" << listit->FindMember(L"DW_8_2")->value.GetUint() << std::endl;
		}

		auto CB_GTE_0x40it = listit->FindMember(L"Byte_b7");
		if (CB_GTE_0x40it != listit->MemberEnd())//controlByte & 0x40
		{
			analysisStream << "Byte_b7: 0x" << listit->FindMember(L"Byte_b7")->value.GetUint() << std::endl;
		}
		analysisStream << std::endl << std::endl;
		i += 1;
	}

	*analysis = QString::fromStdWString(analysisStream.str());

}


//sent when clicking join pvp
void exileSniffer::action_CLI_UNK_0xC6(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client sent dataless message ID 0xC6";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

//sent when clicking join pvp
void exileSniffer::action_CLI_UNK_0xC7(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client sent dataless message ID 0xC7";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xCA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);


	UINT32 unk1 = obj.get_UInt32(L"UnkWord1"); 
	UINT32 unk2 = obj.get_UInt32(L"UnkByte2");
	
	auto it = obj.payload->FindMember(L"ItemArray");
	if (it == obj.payload->MemberEnd())
	{
		add_metalog_update("Warning: No itemlist found in payload of action_SRV_UNK_0xCA", obj.getClientProcessID());
		return;
	}
	WValue &itemList = it->value;

	unsigned short listSize = itemList.Size();
	if (!analysis)
	{
		wstringstream summary;
		summary << "Srv msg 0xCA. Unk1: 0x" << std::hex << unk1 << std::endl;
		summary << "Unk2: 0x" << unk2 << std::endl;
		summary << "Listcount: 0x" << listSize << std::endl;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//todo, list the lists
}

void exileSniffer::action_SRV_EVENTSLIST_2(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &eventlist = obj.payload->FindMember(L"EventList")->value;
	size_t listSize = eventlist.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "List of " + QString::number(listSize) + " available events to join";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = stringify_eventslist_2(eventlist);
}

void exileSniffer::action_CLI_USED_SKILL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UINT32 coord1 = obj.get_UInt32(L"Coord1");
		UINT32 coord2 = obj.get_UInt32(L"Coord2");
		UINT32 modifier = obj.get_UInt32(L"ControlModifier");

		wstringstream summary;
		summary << "[Lockstep]Used skill " << std::hex << obj.get_UInt32(L"SkillID") << " -> ";
		summary << std::dec << "(" << coord1 << "," << coord2 << ")";

		std::wstring modDetails = explainModifier(modifier);
		if (!modDetails.empty())
			summary << " [" << modDetails << "]";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CLICK_OBJ(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 objID = obj.get_UInt32(L"ObjID");
	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 modifier = obj.get_UInt32(L"ControlModifier");

	if (!analysis)
	{
		wstringstream summary;
		summary << "[Lockstep]Clicked obj 0x" << std::hex << objID << " using skill: 0x" << skillID;

		std::wstring modDetails = explainModifier(modifier);
		if (!modDetails.empty())
			summary << " [" << modDetails << "]";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_MOUSE_HELD(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		wstringstream summary;
		summary << "[Lockstep]Mouse Held (" << obj.get_UInt32(L"Coord1") 
			<< "," << obj.get_UInt32(L"Coord2") << ")";
		
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_MOUSE_RELEASE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Released mouse";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player opened world screen";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_CHAT_CHANNEL_ID(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 channelID = obj.get_UInt32(L"ChannelID");
	UINT32 type = obj.get_UInt32(L"Type");
	UINT32 language = obj.get_UInt32(L"Language");
	if (!analysis)
	{
		wstringstream summary;
		summary << "Joined chat channel ID 0x" << std::dec << channelID <<
			", Type: 0x" << std::hex << type <<
			", Language: " << std::dec << language << std::endl;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_GUILD_MEMBER_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	std::wstring string1 = obj.get_wstring(L"String1");
	std::wstring string2 = obj.get_wstring(L"String2");
	std::wstring string3 = obj.get_wstring(L"String3");

	UINT64 time = obj.get_UInt64(L"Time1");

	WValue& memberlist = obj.payload->FindMember(L"MemberList")->value;

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Guild member listing";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::hex;

	for (auto it = memberlist.Begin(); it != memberlist.End(); it++)
	{
		std::wstring name = it->FindMember(L"Name")->value.GetString();
		UINT64 time = it->FindMember(L"Time")->value.GetUint64();
		UINT32 state = it->FindMember(L"State")->value.GetUint();

		analysisStream << "\tName: " << name << " Time: 0x"<< time << " State: 0x" << state << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_GUILD_CREATE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) created guild";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xE4(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Unk msg 0xE4. Arg: 0x" << std::hex << arg << std::dec << "("<<arg<<")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xE6(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 list1Len = obj.get_UInt32(L"List1Len");
	UINT32 list2Len = obj.get_UInt32(L"List2Len");
	UINT32 list3Len = obj.get_UInt32(L"List3Len");
	UINT32 list4Len = obj.get_UInt32(L"List4Len");
	UINT32 list5Len = obj.get_UInt32(L"List5Len");
	UINT32 list6Len = obj.get_UInt32(L"List6Len");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Unk item packet 0xe6. List lengths: " << std::dec <<
			"1: " << list1Len << ", "
			"2: " << list2Len << ", "
			"3: " << list3Len << ", "
			"4: " << list4Len << ", "
			"5: " << list5Len << ", "
			"6 (items - not decoded!): " << list6Len << std::endl;


		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_EXIT_TO_CHARSCREEN(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client exited";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_LOGINSRV_CRYPT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent loginserver data for character screen display";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;

	analysisStream << "Unk1: 0x" << std::hex << obj.get_UInt32(L"Unk1") << std::endl;

	analysisStream << "Data [byte][port][ip][zeros?]:" << std::endl;
	WValue &bloblist = obj.payload->FindMember(L"BlobList")->value;
	for (auto listit = bloblist.Begin(); listit != bloblist.End(); listit++)
	{
		analysisStream << listit->GetString() << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_DUEL_CHALLENGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player initiated duel challenge";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_DUEL_RESPONSE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player responded to duel challenge";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_DUEL_CHALLENGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Duel challenge from server";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_SRV_OBJ_REMOVED(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 ID = obj.get_UInt32(L"ItemID");
	UINT32 receiver = obj.get_UInt32(L"Receiver");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");

	if (!analysis)
	{

		wstringstream summary;
		summary << std::hex << "Object removed from map. ID: 0x" << ID;
		if (receiver)
			summary << " by 0x" << receiver;
		if (unk2)
			summary << " unk2: 0x" << unk2;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_MOBILE_START_SKILL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");
	UINT32 modifier = obj.get_UInt32(L"Modifier"); 

	UINT32 startCoord1 = obj.get_UInt32(L"StartCoord1");
	UINT32 startCoord2 = obj.get_UInt32(L"StartCoord2");
	UINT32 targCoord1 = obj.get_UInt32(L"TargCoord1");
	UINT32 targCoord2 = obj.get_UInt32(L"TargCoord2");

	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 PkCount = obj.get_UInt32(L"PkCount");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Entity ID (0x" << std::hex << ID1 << "," << ID2 << "," << ID3 << ") @(" <<
			std::dec << startCoord1 << "," << startCoord2 << ")" << std::hex <<
			" started skill 0x" << skillID<< " activation";

		std::wstring modDetails = explainModifier(modifier);
		if (!modDetails.empty())
			summary << " [" << modDetails << "]";

		summary <<"	-> ("<< std::dec << targCoord1 << "," << targCoord2 << ")" << std::hex;
		if (modifier & 0x80)
		{
			UINT32 targID = obj.get_UInt32(L"TargID");
			summary << " [ TargetID: 0x" << targID << "]";
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_MOBILE_FINISH_SKILL(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");
	if (!analysis)
	{

		wstringstream summary;
		summary << std::hex << "ObjID (0x" << std::hex << ID1 << "," << ID2 << "," << ID3 << ") finished skill activation";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_MOVE_CHANNELLED(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 coord1 = obj.get_UInt32(L"Coord1");
	UINT32 coord2 = obj.get_UInt32(L"Coord2");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Object 0x(" << std::hex << ID1 << "," << ID2 << "," << ID3 <<
			") shifted channelled skill to ";
		summary << std::dec << "(" << coord1 << "," << coord2 << ")";
	    summary << std::hex << " UnkCount: 0x" << unk1;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());

}

void exileSniffer::action_SRV_END_CHANNELLED(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");
	UINT32 unk4 = obj.get_UInt32(L"Unk4");
	UINT32 unk5 = obj.get_UInt32(L"Unk5");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Channelled skill ended. dUnk1: 0x" << unk1 << 
			", Unk2: 0x" << unk2 << 
			", Unk3: 0x" << unk3 <<
			", UnkCount: 0x" << unk4 << 
			", Unk5: 0x" << unk5;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_MOBILE_UNK_0xee(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 s1 = obj.get_UInt32(L"S1");
	UINT32 b1 = obj.get_UInt32(L"B1");
	UINT32 b2 = obj.get_UInt32(L"B2");
	UINT32 d1 = obj.get_UInt32(L"D1");

	UINT32 skillid = obj.get_UInt32(L"SkillID");

	UINT32 zerobyte = obj.get_UInt32(L"ZeroByte");
	
	wstringstream summary;
	summary << std::hex << "Unk 0xee. objID (0x" << std::hex << ID1 << "," << ID2 << "," << ID3 << ") " <<
		", SBBD: 0x" << s1 << "," << b1 << "," << b2 << "," << d1 << ". SkillID: 0x" << skillid;


	if (skillid & 0x400) //if XX4XX
	{
		summary << ", SkillID_4XX- 0x" << obj.get_UInt32(L"SkillBit400");
	}

	if (skillid >= 0x4000 && skillid < 0x8000)
	{
		summary << ", SkillID_4-8k- 0x" << obj.get_UInt32(L"SkillByte4k8k");
	}

	//todo add the other bits
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = QString::fromStdWString(summary.str());
}

void exileSniffer::action_SRV_MOBILE_UNK_0xef(UIDecodedPkt& obj, QString *analysis)
{
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 s1 = obj.get_UInt32(L"S1");
	UINT32 b1 = obj.get_UInt32(L"B1");
	UINT32 b2 = obj.get_UInt32(L"B2");
	UINT32 d1 = obj.get_UInt32(L"D1");

	UINT32 UnkEndB = obj.get_UInt32(L"UnkEndB");
	if (!analysis)
	{

		wstringstream summary;
		summary << std::hex << "Unk 0xef. objID (0x" << std::hex << ID1 << "," << ID2 << "," << ID3 << ") "
			", SBBD: 0x" << s1<<","<<b1<<","<<b2<<","<<d1<<". EndByte: 0x"<<UnkEndB;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 val = obj.get_UInt32(L"NewValue");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");
	UINT32 stat = obj.get_UInt32(L"Stat");
	UINT32 unk4 = obj.get_UInt32(L"Unk4");

	if (!analysis)
	{

		wstringstream summary;
		summary << "Stat update - objID (0x" << std::hex << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") - "<<
			" - [";
		switch (stat) {
		case 0x0:
			summary << L"Health";
			break;
		case 0x1:
			summary << L"Mana";
			break;
		case 0x2:
			summary << L"Shield";
			break;
		default:
			summary << L"<Unknown stat 0x" << stat << ">";
		}
		summary << "] is now " << std::dec << val << " Unk4(more?): 0x"<<unk4<< std::endl;


		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_STAT_CHANGED(UIDecodedPkt& obj, QString *analysis)//0xf1
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	size_t listSize = 0;
	auto plit = obj.payload->FindMember(L"PairList");
	if (plit != obj.payload->MemberEnd())
	{
		listSize = plit->value.Size();
	}

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Stat change for object ID (0x" << std::hex << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") - " <<
			std::dec<<listSize<<" stats changed";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << "Stat change for object ID (0x" << std::hex << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ")" << std::endl;

	if (plit != obj.payload->MemberEnd())
	{

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

		analysisStream << "Stat Pairs:" << std::dec<< std::endl;
		WValue &blist5 = plit->value;
		for (auto pairlistit = blist5.Begin(); pairlistit != blist5.End(); pairlistit++)
		{

			WValue &pair = *pairlistit;

			UINT32 statIndex = pair[0].GetUint() - 1;
			analysisStream << "\t" <<
				converter.from_bytes(ggpk->statDescriptions.at(statIndex))
				<< ": " << pair[1].GetInt() << std::endl;
		}
		analysisStream << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_UNK_0xf2(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	ushort arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Pkt 0xf2. ID (0x" << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") Arg 0x" << arg ;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}



void exileSniffer::action_SRV_UNK_0xf3(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	DWORD DW1 = obj.get_UInt32(L"DW1");
	DWORD DW2 = obj.get_UInt32(L"DW2");
	DWORD DW3 = obj.get_UInt32(L"DW3");
	DWORD DW4 = obj.get_UInt32(L"DW4");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Pkt 0xf3. ID (0x"<< ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") DWORDS- 0x"<<DW1<<", 0x"<<DW2<<", 0x"<<DW3<<", 0x"<<DW4;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xf5(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	byte arg1 = obj.get_UInt32(L"Arg1");
	byte arg2 = obj.get_UInt32(L"Arg2");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Pkt 0xf5. ID (0x" << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") Args: 0x"
			<< arg1 << ", 0x" << arg2;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xf7(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	byte arg1 = obj.get_UInt32(L"Arg1");
	byte arg2 = obj.get_UInt32(L"Arg2");
	byte arg3 = obj.get_UInt32(L"Arg3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Pkt 0xf7. ID (0x" << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") Args: 0x"
			<< arg1 << ", 0x" << arg2 << ", arg3: 0x"<<arg3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0xf8(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	byte arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Pkt 0xf8. ID (0x" << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ") Arg: 0x"<<arg;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_START_BUFF(UIDecodedPkt& obj, QString *analysis) //0xfa
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 buffID = obj.get_UInt32(L"BuffID");
	UINT32 buffDefinitionsRow = obj.get_UInt32(L"BuffDefinitionsRow");
	std::string buffname = ggpk->buffDefinitions_names_statCounts.at(buffDefinitionsRow).first;
	UINT32 UnkDWord3 = obj.get_UInt32(L"ID2");
	UINT32 PotionSlot = obj.get_UInt32(L"PotionSlot");
	UINT32 controlByte = obj.get_UInt32(L"ID2");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Buff "<< converter.from_bytes(buffname)
			<<" started on obj ID (0x" << ID1 << "," << ID2 << "," << ID3 
			<< ") ControlBits: 0x" << controlByte <<
			" Unk: 0x" << UnkDWord3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::hex;
	analysisStream << "ID (0x" << ID1 << ", 0x" << ID2 << ", 0x" << ID3 << ")";
	analysisStream << "BuffId: 0x" << buffID << std::endl;
	analysisStream << "ControlBits: 0x" << controlByte << std::endl;
	analysisStream << "Index into buffDefinitions.dat: " <<std::dec<< buffDefinitionsRow << std::endl;
	analysisStream << "Other args: 0x" << UnkDWord3 << ", Potion 0x" << PotionSlot << std::endl;

	auto it = obj.payload->FindMember(L"BufVisualsRow");
	if (it != obj.payload->MemberEnd())
	{
		analysisStream << "Buff Visuals row " << std::dec << it->value.GetUint() << std::endl;
	}

	WValue &statkeylist = obj.payload->FindMember(L"StatList")->value;

	analysisStream << std::dec << "Statkey assignment list:" << std::endl;

	for (auto listit = statkeylist.Begin(); listit != statkeylist.End(); listit++)
	{
		analysisStream << "\t"<<std::dec<< listit->GetUint() << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_END_EFFECT(UIDecodedPkt& obj, QString *analysis) //0xfb
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 BuffID = obj.get_UInt32(L"BuffID");
	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Buff 0x"<<BuffID<<" ended on obj ID (0x"<< ID1 << "," << ID2 << "," << ID3 << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_EVENT_TRIGGERED(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	//10 b objid
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 state = obj.get_UInt32(L"State");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Event triggered: ObjID (0x" << ID1 << "," << ID2 << "," << ID3 << ") State: 0x" << state;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_UNK_0x106(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unkd1 = obj.get_UInt32(L"UnkDW1");
	UINT32 unkd2 = obj.get_UInt32(L"UnkDW2");
	UINT32 unkd3 = obj.get_UInt32(L"UnkDW3");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Unk msg 0x106 " << std::hex;
		summary << "ID (0x" << ID1 << "," << ID2 << "," << ID3 << ")"; 
		summary << "u1: x" << unk1 << ", u2: x" << unk2
			<< ", ( d1: x" << unkd1 << ", d2: x" << unkd2 << ", d3: 0x" << unkd3 << "), u3: x" << unk3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisss;

	analysisss << "Unk msg 0x106 " << std::hex << std::endl;
	analysisss << "\t1: 0x" << unk1 << std::endl; 
	analysisss << "\t2: 0x" << unk2 << std::endl;
	analysisss << "\t\td1: 0x" << unkd1 << std::endl;
	analysisss << "\t\td2: 0x" << unkd2 << std::endl;
	analysisss << "\t\td3: 0x" << unkd3 << std::endl;
	analysisss << "\t3: 0x" << unk3 << std::endl; ;

	*analysis = QString::fromStdWString(analysisss.str());
}

void exileSniffer::action_SRV_UNK_0x108(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");


	UINT32 unkd1 = obj.get_UInt32(L"UnkDW1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");
	UINT32 unk3 = obj.get_UInt32(L"Unk3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex;
		summary << "Unk msg 0x108. ID (0x" << ID1 << "," << ID2 << "," << ID3 << ")";
		summary << " Unk1: 0x" << unkd1 << ", 2: 0x" << unk2 << "3: 0x" << unk3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstringstream analysisss;

	analysisss << "Unk msg 0x106 " << std::hex << std::endl;
	analysisss << "\t1: 0x" << unkd1 << std::endl;
	analysisss << "\t2: 0x" << unk2 << std::endl;
	analysisss << "\t3: 0x" << unk3 << std::endl;

	*analysis = QString::fromStdWString(analysisss.str());
}

void exileSniffer::action_CLI_FINISHED_LOADING(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client finished loading the zone";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = "No additional data expected";
}

void exileSniffer::action_SRV_NOTIFY_PLAYERID(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Server notified client of playerID. (ID1 0x"<< ID1 << "," << ID2 << "," << ID3 << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::hex << "Server notified client of playerID. ID1 0x"
		<< ID1 << ", ID2: 0x" << ID2 << " ID3: 0x" << ID3;
	QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_UNKNOWN_0x111(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 count1 = obj.get_UInt32(L"Count1"); 

	UINT32 count2 = obj.get_UInt32(L"Count2");

	//second list is pkt 0x118 entries

	if (!analysis)
	{
		std::wstringstream summary;
		 
		if (count1 == 0 && count2 == 0)
			summary << "0x111 packet <item/gem/skill data?> with empty lists";
		else
		{
			summary << std::dec<<"!![Alert]!! 0x111 packet with lists! List 1 has "
				<< count1 << ", list 2 (see 0x118) has " << count2;
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}


}

void exileSniffer::action_SRV_UNKNOWN_0x118(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 index = obj.get_UInt32(L"Index");
	UINT32 hash = obj.get_UInt32(L"Hash");
	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 unk2a = obj.get_UInt32(L"Unk2a");
	UINT32 unk2b = obj.get_UInt32(L"Unk2b");

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string hashResult;
	std::string hashCategory;
	ggpk->lookup_hash(hash, hashResult, hashCategory);

	if (!analysis)
	{
		std::wstringstream summary;

		UI_DECODED_LIST_ENTRY listentry(obj);
		summary << "pkt 0x118 <item/gem/skill data> ";
		summary << std::dec << index << ": " << converter.from_bytes(hashResult) << ". 0x" << unk1 << " 0x" << unk2a << unk2b;
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << "This is an item as it would appear on the second list of an 0x111 pkt" << std::endl;
	analysisStream << std::hex;
	analysisStream << "Index: 0x" << index << std::endl;
	analysisStream << "Hash: 0x" << hash << " - " << converter.from_bytes(hashCategory) << 
		" - " << converter.from_bytes(hashResult) << std::endl;
	analysisStream << "Unk1: 0x" << unk1 << std::endl;
	analysisStream << "Unk2: 0x" << unk2a <<"," << unk2b << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) opted out of tutorials";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_BESTIARY_CAPTIVES(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent list of menagerie captives";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_OPEN_BESTIARY(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested bestiary data";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_BESTIARY_UNLOCKED_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent updated list of unlocked bestiary monsters";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SHOW_ENTERING_MSG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD areaCode = obj.get_UInt32(L"AreaCode");
	std::wstring areaname;
	ggpk->lookup_areaCode(areaCode, areaname);

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Starting transtion to area " + QString::fromStdWString(areaname);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_HEARTBEAT(UIDecodedPkt& obj, QString *analysis)
{
	//maybe increment a counter or something
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server Heartbeat";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

/*
The summary is left until the end so the json readers can benefit from the analysis

Analysis needs splitting into the various types of object category
*/
void exileSniffer::action_SRV_ADD_OBJECT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	DWORD objHash = obj.get_UInt32(L"objHash");
	DWORD dataLen = obj.get_UInt32(L"DataLen");

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::wstring hashCategoryWS = obj.get_wstring(L"HashCategory");
	std::wstring hashResultWS = obj.get_wstring(L"HashResult");

	if (!analysis)
	{
		wstringstream summary;
		summary << std::hex << hashCategoryWS << " added ";
		if (hashCategoryWS == L"Character")
		{
			summary << " - " << obj.get_wstring(L"Name");
		}
		else
		{
			summary << "<" << hashResultWS <<
				"> ID (0x" << ID1 << "," << ID2 << "," << ID3 << ") - " << dataLen << " bytes>";
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << std::hex << "ID (0x" << ID1 << "," << ID2 << "," << ID3 << ")" << std::endl;
	analysisStream << "Hash: 0x" << objHash << " - " << hashCategoryWS << "-"<< hashResultWS << std::endl;
	analysisStream << "Datalen: " << std::dec << dataLen << std::endl;

	if (hashCategoryWS != L"Character")
	{
		analysisStream << "\n !- Not character, can't decode yet -! " << std::endl;
		*analysis = QString::fromStdWString(analysisStream.str());

		return;
	}


	DWORD coord1 = obj.get_UInt32(L"Coord1");
	DWORD coord2 = obj.get_UInt32(L"Coord2");

	auto it = obj.payload->FindMember(L"List1");
	if (it != obj.payload->MemberEnd())
	{
		WValue &list1 = it->value;
		analysisStream << std::dec << list1.Size() << std::hex << " List1:" << std::endl;

		for (auto listit = list1.Begin(); listit != list1.End(); listit++)
		{
			WValue &pair = *listit;
			DWORD possHash = pair[0].GetUint();
			DWORD val2 = pair[1].GetUint();
			analysisStream << "\t 0x" << possHash << ": 0x" << val2 << std::endl;
		}
	}

	analysisStream << "Coords: " << std::dec << coord1 << "," << coord2 << std::endl;

	analysisStream << std::hex;
	DWORD unkdword1 = ntohl(obj.get_UInt32(L"UnkDword1"));
	if (unkdword1 != 0)
	{
		analysisStream << "Unk DWORD After Coords: 0x" << unkdword1 << std::endl;
	}
	analysisStream << "Unk byte 1: 0x" << obj.get_UInt32(L"UnkByte1") << std::endl;
	byte controlByte1 = obj.get_UInt32(L"ControlByte1");
	analysisStream << "Control byte 1: 0x" << controlByte1 << std::endl;

	if (controlByte1 & 0x20)
	{
		analysisStream << "\tcontrolByte1 bit 0x20 set!" << std::endl;
		analysisStream << "\t  Arg 1: 0x" << obj.get_UInt32(L"Unk_b20_1");
			analysisStream << ", 2: 0x" << obj.get_UInt32(L"Unk_b20_2");
			analysisStream << ", 3: 0x" << obj.get_UInt32(L"Unk_b20_3") << std::endl;
	}

	if (controlByte1 & 0x4)
	{
		analysisStream << "\tcontrolByte1 bit 0x4 set!" << std::endl;
		analysisStream << "\t  Arg 1: 0x" << obj.get_UInt32(L"Unk_b4_1");
		analysisStream << ", 2: 0x" << obj.get_UInt32(L"Unk_b4_2") << std::endl;
	}

	if (controlByte1 & 0x40)
	{
		analysisStream << "\tcontrolByte1 bit 0x40 set!" << std::endl;
		analysisStream << "\t  Arg 1: 0x" << obj.get_UInt32(L"Unk_b40_1");
		analysisStream << ", 2: 0x" << obj.get_UInt32(L"Unk_b40_2") << std::endl;
	}

	analysisStream << std::endl;

	it = obj.payload->FindMember(L"StatList");
	if (it != obj.payload->MemberEnd())
	{
		WValue &statList = it->value;
		analysisStream << std::dec << statList.Size() << " Stats:" << std::endl;
		for (auto statit = statList.Begin(); statit != statList.End(); statit++)
		{
			WValue &pair = *statit;
			DWORD statIndex = pair[0].GetUint() - 1;
			std::wstring statType = pair[1].GetString();
			analysisStream << "\t" << statType << ": " << pair[2].GetInt() << std::endl;
		}
	}
	else
		analysisStream << "No stat list";

	analysisStream << std::dec << std::endl;
	analysisStream << "Current Health: " << obj.get_UInt32(L"CurrentHealth") << std::endl;
	analysisStream << "Reserved Health (absolute): " << obj.get_UInt32(L"ReservedHealth") << std::endl;
	analysisStream << "Reserved Health (%): " << obj.get_UInt32(L"ReservedPercentHealth") << std::endl;
	analysisStream << "Unk Health: " << obj.get_UInt32(L"HealthUnk") << std::endl;

	analysisStream << "Current Mana: " << obj.get_UInt32(L"CurrentMana") << std::endl;
	analysisStream << "Reserved Mana (absolute): " << obj.get_UInt32(L"ReservedMana") << std::endl;
	analysisStream << "Reserved Mana (%): " << obj.get_UInt32(L"ReservedPercentMana") << std::endl;
	analysisStream << "Unk Mana: " << obj.get_UInt32(L"ManaUnk") << std::endl;

	analysisStream << "Current Shield: " << obj.get_UInt32(L"CurrentShield") << std::endl;
	analysisStream << "[?]Reserved Shield (absolute): " << obj.get_UInt32(L"ShieldUnk1") << std::endl;
	analysisStream << "[?]Reserved Shield (%): " << obj.get_UInt32(L"ShieldUnk2") << std::endl;
	analysisStream << "[?]Unk Shield: " << obj.get_UInt32(L"ShieldUnk3") << std::endl;
	analysisStream << "Unk Value after HMS: " << obj.get_UInt32(L"UnkDWORDEndHMS") << std::endl;
	analysisStream << "Unk Value before buffs: " << obj.get_UInt32(L"UnkByte_PreBuffs") << std::endl;

	analysisStream << std::dec << std::endl;

	it = obj.payload->FindMember(L"BuffList");
	if (it != obj.payload->MemberEnd())
	{
		WValue &buffList = it->value;
		if (buffList.Size() == 1)
			analysisStream << "1 Buff:" << std::endl;
		else
			analysisStream << buffList.Size() << " Buffs:" << std::endl;

		for (auto buffit = buffList.Begin(); buffit != buffList.End(); buffit++)
		{
			WValue &buff = *buffit;
			uint buffID = buff.FindMember(L"BuffID")->value.GetUint();
			analysisStream << "Buff Slot/ID: " << buffID << std::endl;

			ushort defsrow = buff.FindMember(L"BuffDefinitionsRow")->value.GetUint();
			std::wstring buffname = buff.FindMember(L"Buffname")->value.GetString();
			analysisStream << "\tBuffDefinitions.dat row " << defsrow << " - \"" <<  buffname << "\"" << std::endl;

			ushort visualsrow = buff.FindMember(L"BuffVisualsRow")->value.GetUint();
			std::wstring buffvisualname = buff.FindMember(L"BuffVisualName")->value.GetString();
			analysisStream << "\tBuffVisuals.dat row " << visualsrow << " - \"" << buffvisualname	<< "\"" << std::endl;

			analysisStream << std::hex;
			analysisStream << "\tUnkDword1 0x:" << buff.FindMember(L"UnkDword1")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort2 0x:" << buff.FindMember(L"UnkShort2")->value.GetUint() << std::endl;
			analysisStream << "\tUnkDword3 0x:" << buff.FindMember(L"UnkDword3")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort4 0x:" << buff.FindMember(L"UnkShort4")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort5 0x:" << buff.FindMember(L"UnkShort5")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort6 0x:" << buff.FindMember(L"UnkShort6")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort7 0x:" << buff.FindMember(L"UnkShort7")->value.GetUint() << std::endl;
			analysisStream << "\tUnkShort8 0x:" << buff.FindMember(L"UnkShort8")->value.GetUint() << std::endl;
			analysisStream << "\tUnkByte9 0x:" << buff.FindMember(L"UnkByte9")->value.GetUint() << std::endl;
			analysisStream << std::endl;
		}
	}
	else
		analysisStream << "No stat list";

	analysisStream << "Name: " << obj.get_wstring(L"Name") << std::endl;
	analysisStream << "Byte: 0x" << std::hex << obj.get_UInt32(L"UnkByte_AfterName") << std::endl;
	analysisStream << "XP: " << std::dec << obj.get_UInt32(L"XP") << std::endl;
	analysisStream << "Unk_AN_3: 0x" << std::hex << obj.get_UInt32(L"Unk_AN_3") << std::endl;
	analysisStream << "UnkByte_AN4: 0x" << std::hex << obj.get_UInt32(L"UnkByte_AN4") << std::endl;
	analysisStream << "UnkByte_AN5: 0x" << std::hex << obj.get_UInt32(L"UnkByte_AN5") << std::endl;

	analysisStream << "[Quest/Achievment bits] skipped" << std::endl;

	WValue &unklist1 = obj.payload->FindMember(L"UnkList")->value;
	analysisStream << "Unknown list:" << std::hex << std::endl;
	int i = 0;
	for (auto it = unklist1.Begin(); it != unklist1.End(); it++)
	{
		analysisStream << i++ << std::endl;
		analysisStream << "\tD1: 0x "<<it->FindMember(L"D1")->value.GetUint() << std::endl;
		analysisStream << "\tD2: 0x " << it->FindMember(L"D2")->value.GetUint() << std::endl;
		analysisStream << "\tQ3: 0x " << it->FindMember(L"Q3")->value.GetUint64() << std::endl;
	}

	std::wstring hideoutname = obj.get_wstring(L"HideoutName");
	analysisStream << "Hideout: " << hideoutname << std::endl;

	analysisStream << "UnkBytes:" << obj.get_wstring(L"UnkBytes1") << std::endl;

	WValue &prophsList = obj.payload->FindMember(L"Prophecies")->value;
	analysisStream << "Prophecies:" << std::hex << std::endl;
	for (auto it = prophsList.Begin(); it != prophsList.End(); it++)
	{
		uint ref = it->FindMember(L"DatReference")->value.GetUint();
		std::wstring prophecyName = ggpk->getProphecy(ref);
		analysisStream << "Position: 0x" << it->FindMember(L"Pos")->value.GetUint() << std::endl;
		analysisStream << "\tID: " << prophecyName << std::endl;
		analysisStream << std::endl;
	}

	WValue &wornItems = obj.payload->FindMember(L"WornItems")->value;
	analysisStream << "Worn Items List:" << std::hex << std::endl;
	for (auto it = wornItems.Begin(); it != wornItems.End(); it++)
	{
		UINT32 visIdentReference1 = it->FindMember(L"VisualIdentity1")->value.GetUint();
		std::wstring visIdentName1 = ggpk->getVisualIdentity(visIdentReference1);
		UINT32 visIdentReference2 = it->FindMember(L"VisualIdentity2")->value.GetUint();
		std::wstring visIdentName2 = ggpk->getVisualIdentity(visIdentReference2);
		UINT32 visualEffect = it->FindMember(L"ItemVisualEffect")->value.GetUint();
		std::wstring visEffectName = ggpk->getVisualEffect(visualEffect);

		analysisStream << "Slot: " << std::dec << it->FindMember(L"Slot")->value.GetUint() << std::endl;
		analysisStream << "\tVisualIdentity: " << visIdentName1 << std::endl;
		analysisStream << "\tExtraVisualIdentity: " << visIdentName2 << std::endl;
		analysisStream << "\tVisualEffect: " << visEffectName << std::endl;
		analysisStream << "\tUnk2: " << std::dec << it->FindMember(L"Unk2")->value.GetUint() << std::endl;
		analysisStream << "\tUnk5: " << std::dec << it->FindMember(L"Unk5")->value.GetUint() << std::endl;
		analysisStream << std::endl;
	}


	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_UPDATE_OBJECT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	DWORD dataLen = obj.get_UInt32(L"DataLen");

	if (!analysis)
	{
		wstringstream summary;
		summary << std::hex <<"Update obj ID(0x" << ID1 << "," << ID2 << ","<< ID3 <<") -<"<<std::dec<<dataLen<<" bytes>";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_IDNOTIFY_0x137(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 ID1 = obj.get_UInt32(L"ID1");
	UINT32 ID2 = obj.get_UInt32(L"ID2");
	UINT32 ID3 = obj.get_UInt32(L"ID3");

	if (!analysis)
	{
		wstringstream summary;
		summary << std::hex << "ObjID notify 0x137. ID- (0x" << ID1 << "," << ID2 << "," << ID3 << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}
