#include "stdafx.h"

#include "filterForm.h"
#include "packetIDs.h"

#define PACKET_OUTGOING 0
#define PACKET_INCOMING 1

#define NOT_DISPLAYED 0
#define IS_DISPLAYED 1

filterForm::filterForm(QWidget *parent)
	: QWidget(parent)
{
}

void filterForm::add_filter_category(unsigned short pktid, QString description, int fromServer)
{
	unsigned int rowIndex = ui->filterTable->rowCount();
	ui->filterTable->setRowCount(rowIndex + 1);

	numericSortTableWidgetItem *pktIDItem = new numericSortTableWidgetItem();
	pktIDItem->setHex(pktid);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_ID, pktIDItem);

	QTableWidgetItem *descriptionItem = new QTableWidgetItem();
	descriptionItem->setData(Qt::DisplayRole, description);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_FUNCTION, descriptionItem);

	QTableWidgetItem *senderItem = new QTableWidgetItem();
	if (fromServer == PACKET_INCOMING)
		senderItem->setData(Qt::DisplayRole, "Server");
	else
		senderItem->setData(Qt::DisplayRole, "Client");
	senderItem->setTextAlignment(Qt::AlignCenter);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_SENDER, senderItem);

	numericSortTableWidgetItem *countItem = new numericSortTableWidgetItem();
	countItem->setData(Qt::DisplayRole, 0);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_COUNT, countItem);

	QTableWidgetItem *statusItem = new QTableWidgetItem();
	statusItem->setData(Qt::DisplayRole, "Displayed");
	statusItem->setTextAlignment(Qt::AlignCenter);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_STATE, statusItem);

	filterStates[pktid] = IS_DISPLAYED;
	filterItems[pktid] = statusItem;
}

//todo default all minus heartbeats
bool filterForm::isDisplayed(ushort pktID)
{
	if (pktID == CLI_PING_CHALLENGE ||
		pktID == SRV_PING_RESPONSE ||
		pktID == SRV_HEARTBEAT ||
		pktID == SRV_CHAT_MESSAGE)
		return false;


	auto it = filterStates.find(pktID);
	if (it == filterStates.end()) //should add message to alert on this
		return true;

	return (it->second == IS_DISPLAYED);
}

void filterForm::populateFiltersList() 
{
	ui->filterTable->horizontalHeader()->setSectionResizeMode(FILTER_SECTION_FUNCTION, QHeaderView::Stretch);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_ID, 60);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_SENDER, 75);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_COUNT, 105);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_STATE, 75);

	filterItems.clear();
	filterStates.clear();

	//add_filter_category(SRV_PKT_ENCAPSULATED, "Should not be shown", true);
	add_filter_category(CLI_CHAT_MSG_ITEMS, "Sent chat message + item links", PACKET_OUTGOING);
	//7?
	add_filter_category(CLI_CHAT_MESSAGE, "Sent chat message", PACKET_OUTGOING);
	add_filter_category(CLI_CHAT_COMMAND, "Sent chat command", PACKET_OUTGOING);
	add_filter_category(SRV_CHAT_MESSAGE, "Chat message received", PACKET_INCOMING);
	add_filter_category(SRV_SERVER_MESSAGE, "Message from server", PACKET_INCOMING);
	add_filter_category(CLI_LOGGED_OUT, "Client logged out", PACKET_OUTGOING);
	add_filter_category(CLI_PING_CHALLENGE, "Client HNC", PACKET_OUTGOING);
	add_filter_category(SRV_PING_RESPONSE, "Server HNC", PACKET_INCOMING);
	add_filter_category(SRV_AREA_INFO, "Area Info", PACKET_INCOMING);
	//0x10
	//0x11
	add_filter_category(SRV_PRELOAD_MONSTER_LIST, "Area preload list", PACKET_INCOMING);
	add_filter_category(SRV_UNK_0x13, "Unknown", PACKET_INCOMING);
	add_filter_category(SRV_PLAYER_ITEMS, "Container items list", PACKET_INCOMING);
	add_filter_category(CLI_CLICKED_GROUND_ITEM, "Player clicked world object", PACKET_OUTGOING);
	add_filter_category(CLI_ACTION_PREDICTIVE, "Player action (predictive mode)", PACKET_OUTGOING);
	add_filter_category(SRV_TRANSFER_INSTANCE, "Instance change notification", PACKET_INCOMING);
	add_filter_category(SRV_INSTANCE_SERVER_DATA, "Instance server data", PACKET_INCOMING);
	add_filter_category(CLI_PICKUP_ITEM, "Player picked item up", PACKET_OUTGOING);
	//0x1a
	add_filter_category(CLI_PLACE_ITEM, "Player placed item down", PACKET_OUTGOING);
	//1c
	add_filter_category(CLI_REMOVE_SOCKET, "Player removed item from socket", PACKET_OUTGOING);
	add_filter_category(CLI_INSERT_SOCKET, "Player placed item into socket", PACKET_OUTGOING);
	add_filter_category(CLI_LEVEL_SKILLGEM, "Player levelled skill gem", PACKET_OUTGOING);
	add_filter_category(CLI_UNK_0x20, "Unknown", PACKET_OUTGOING);
	add_filter_category(CLI_SKILLPOINT_CHANGE, "Player changed passive skill", PACKET_OUTGOING);
	//22
	//23
	add_filter_category(CLI_CHOSE_ASCENDANCY, "Player selected ascendency", PACKET_OUTGOING);
	//25
	//26
	//27
	//28
	//29
	//2a
	add_filter_category(CLI_CANCEL_BUF, "Player cancelled buff", PACKET_OUTGOING);
	add_filter_category(CLI_UNK_0x2c, "Unknown", PACKET_OUTGOING);
	//2d
	add_filter_category(CLI_SET_HOTBARSKILL, "Player set hotbar skill", PACKET_OUTGOING);
	add_filter_category(SRV_SKILL_SLOTS_LIST, "Server listed hotbar skills", PACKET_INCOMING);
	//30
	//31
	//32
	//33
	//34
	//35
	//36
	add_filter_category(CLI_USE_BELT_SLOT, "Player activated belt slot", PACKET_OUTGOING);
	add_filter_category(CLI_USE_ITEM, "Player used item", PACKET_OUTGOING);
	//39
	//3a
	//3b
	//3c
	//3d
	//3e
	add_filter_category(SRV_OPEN_UI_PANE, "Server opened UI pane", PACKET_INCOMING);
	//40
	add_filter_category(CLI_UNK_0x41, "Unknown", PACKET_OUTGOING);
	//42
	//43
	//44
	//45
	add_filter_category(CLI_SELECT_NPC_DIALOG, "Player selected dialog option", PACKET_OUTGOING);
	add_filter_category(SRV_SHOW_NPC_DIALOG, "Server sent dialog to show", PACKET_INCOMING);
	add_filter_category(CLI_CLOSE_NPC_DIALOG, "Player closed dialog", PACKET_OUTGOING);
	//49
	//4a
	//4b
	//4c
	//4d
	//4e
	//4f
	add_filter_category(CLI_CLOSE_NPC_DIALOG, "Player sent party invite", PACKET_OUTGOING);
	//51
	add_filter_category(CLI_TRY_JOIN_PARTY, "Player joined party", PACKET_OUTGOING);
	add_filter_category(CLI_DISBAND_PUBLIC_PARTY, "Player left party", PACKET_OUTGOING);
	//54
	add_filter_category(CLI_CREATE_PUBLICPARTY, "Player listed public party", PACKET_OUTGOING);
	add_filter_category(CLI_UNK_x56, "Unknown", PACKET_OUTGOING);
	add_filter_category(CLI_GET_PARTY_DETAILS, "Requested details of party", PACKET_OUTGOING);
	add_filter_category(SRV_FRIENDSLIST, "Server sent friends data", PACKET_INCOMING);
	//59
	add_filter_category(SRV_PARTY_DETAILS, "Server sent party details", PACKET_INCOMING);
	add_filter_category(SRV_PARTY_ENDED, "Party ended", PACKET_INCOMING);
	//5c
	add_filter_category(CLI_REQUEST_PUBLICPARTIES, "Client requested list of public parties", PACKET_OUTGOING);
	add_filter_category(SRV_PUBLIC_PARTY_LIST, "List of public parties", PACKET_INCOMING);
	//5f
	//60
	//61
	//62
	add_filter_category(CLI_MOVE_ITEM_PANE, "Player placed item in pane", PACKET_OUTGOING);
	//64
	//65
	//66
	//67
	//68
	//69
	//6a
	//6b
	//6c
	add_filter_category(SRV_CREATE_ITEM, "New item", PACKET_INCOMING);
	add_filter_category(SRV_SLOT_ITEMSLIST, "List of items in container", PACKET_INCOMING);
	//6f
	add_filter_category(UNK_MESSAGE_0x70, "Unknown", PACKET_INCOMING);
	//71
	//72
	add_filter_category(UNK_MESSAGE_0x73, "Unknown", PACKET_INCOMING);
	add_filter_category(CLI_SET_STATUS_MESSAGE, "Player set status message", PACKET_OUTGOING);
	//75
	//76
	//77
	//78
	//79
	//7a
	//7b
	//7c
	//7d
	//7e
	add_filter_category(CLI_SWAPPED_WEAPONS, "Player swapped weaponset", PACKET_OUTGOING);
	//80
	//81
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
	//8d
	//8e
	//define 0x8f seen when leaving duel queue
	//define 0x90 seen when leaving duel queue
	//91
	add_filter_category(SRV_UNK_0x92, "Unknown", PACKET_INCOMING);
	//93
	//94
	//95
	//96
	//97
	add_filter_category(CLI_SKILLPANE_ACTION, "Opened/closed skill tree", PACKET_OUTGOING);
	//99
	//9a
	add_filter_category(SRV_SKILLPANE_DATA, "Skill tree data", PACKET_INCOMING);
	//9c
	//9d
	//9e
	add_filter_category(CLI_MICROTRANSACTION_SHOP_ACTION, "Opened microtransaction shop", PACKET_OUTGOING);
	//a0
	add_filter_category(SRV_MICROTRANSACTION_SHOP_DETAILS, "Micro-transaction shop data", PACKET_INCOMING);
	//a2
	add_filter_category(SRV_UNK_A3, "Unknown", PACKET_INCOMING);
	add_filter_category(SRV_CHAT_CHANNEL_ID, "Chat channel membership", PACKET_INCOMING);
	//a5
	//a6
	//a7
	//a8
	//a9
	//aa
	//ab
	//ac
	add_filter_category(CLI_GUILD_CREATE, "Created guild", PACKET_OUTGOING);
	//ae
	//af
	//b0
	//b1
	//b2
	//b3
	//b4
	//b5
	//b6
	//b7
	//b8
	//b9
	//ba
	//bc
	//bd
	//be
	//bf
	add_filter_category(CLI_PACKET_EXIT, "Client exit 1", PACKET_OUTGOING);
	add_filter_category(CLI_PACKET_EXIT_2, "Client exit 2", PACKET_OUTGOING);
	add_filter_category(CLI_DUEL_CHALLENGE, "Player sent duel challenge", PACKET_OUTGOING);
	add_filter_category(SRV_DUEL_RESPONSE, "Received response to duel challenge", PACKET_INCOMING);
	add_filter_category(SRV_DUEL_CHALLENGE, "Received duel challenge", PACKET_INCOMING);
	//c5
	//c6
	add_filter_category(CLI_UNK_0xC7, "Unknown", PACKET_OUTGOING);
	//c8
	//c9
	add_filter_category(SRV_UNK_0xCA, "Unknown", PACKET_INCOMING);
	//cb
	//cd
	add_filter_category(CLI_VISIT_HIDEOUT, "Visit hideout", PACKET_OUTGOING);
	//cf
	//d0
	//d1
	//d2
	//d3
	//d4
	add_filter_category(SRV_UNK_0xD5, "Unknown", PACKET_INCOMING);
	//d6
	//d7
	add_filter_category(CLI_USED_SKILL, "Player used skill (lockstep)", PACKET_OUTGOING);
	add_filter_category(CLI_CLICK_OBJ, "Player clicked object (lockstep)", PACKET_OUTGOING);
	add_filter_category(CLI_MOUSE_HELD, "Player held button (lockstep)", PACKET_OUTGOING);
	//db
	add_filter_category(CLI_MOUSE_RELEASE, "Player released skill (lockstep)", PACKET_OUTGOING);
	//dd
	//de
	//df
	add_filter_category(CLI_OPEN_WORLD_SCREEN, "Player opened/closed world pane", PACKET_OUTGOING);
	//e1
	//e2
	//e3
	//e4
	//e5
	add_filter_category(SRV_UNK_0xE6, "Unknown", PACKET_INCOMING);
	//e7
	//e8
	add_filter_category(SRV_OBJ_REMOVED, "Object removed", PACKET_INCOMING);
	add_filter_category(SRV_MOBILE_START_SKILL, "Object initiated skill", PACKET_INCOMING);
	add_filter_category(SRV_MOBILE_FINISH_SKILL, "Object activated skill", PACKET_INCOMING);
	//ec
	//ed
	add_filter_category(SRV_MOBILE_UNK_0xee, "Unknown", PACKET_INCOMING);
	add_filter_category(SRV_MOBILE_UNK_0xef, "Unknown", PACKET_INCOMING);
	add_filter_category(SRV_MOBILE_UPDATE_HMS, "Object health/mana/shield update", PACKET_INCOMING);
	add_filter_category(SRV_STAT_CHANGED, "Object stats update", PACKET_INCOMING);
	add_filter_category(SRV_UNK_0xf2, "Unknown", PACKET_INCOMING);
	add_filter_category(SRV_UNK_0xf3, "Unknown", PACKET_INCOMING);
	//f4
	//f5
	//f6
	//f7
	//f8
	//f9
	add_filter_category(SRV_START_EFFECT, "Object effect started", PACKET_INCOMING);
	add_filter_category(SRV_END_EFFECT, "Object effect ended", PACKET_INCOMING);
	//fc
	//fd
	//fe
	//ff
	//100
	//101
	//102
	//103
	//104
	//105
	//106
	//107
	//108
	//109
	//10a
	//10b
	//10c
	//10d
	add_filter_category(CLI_REQUEST_PLAYERID, "Unk playerID request", PACKET_OUTGOING);
	add_filter_category(SRV_NOTIFY_PLAYERID, "Unk playerID response", PACKET_INCOMING);
	//0x110 - player pressed add new stash tab +?
	add_filter_category(SRV_UNKNOWN_0x111, "Unknown", PACKET_INCOMING);
	//112
	//113
	//114
	//115
	//116
	//117
	add_filter_category(SRV_UNKNOWN_0x118, "Unknown", PACKET_INCOMING);
	//119
	//11a
	//11b
	add_filter_category(CLI_OPTOUT_TUTORIALS, "Unk player setting change", PACKET_OUTGOING);
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
	//127
	//128
	//129
	//12a
	//12b
	//12c
	//12d
	//12e
	add_filter_category(SRV_SHOW_ENTERING_MSG, "Entering area message", PACKET_INCOMING);
	//130
	//131
	add_filter_category(SRV_HEARTBEAT, "Server heartbeat", PACKET_INCOMING);
	//133
	//134
	add_filter_category(SRV_ADD_OBJECT, "Object added", PACKET_INCOMING);
	add_filter_category(SRV_UPDATE_OBJECT, "Object updated", PACKET_INCOMING);
	add_filter_category(SRV_IDNOTIFY_0x137, "Unknown ObjID", PACKET_INCOMING);
}

#define ERASE_FROM_VEC(v, x) v.erase(std::remove(v.begin(), v.end(), x), v.end())

void filterForm::buildBuiltinPresets()
{
	ushort numMsgs = ui->filterTable->rowCount();
	assert(numMsgs > 0);

	PRESET_LIST allPkts;

	for (int i = 0; i < MSG_IDS_END; i++)
		allPkts.IDs.push_back(i);

	allPkts.name = "All";
	allPkts.description = "The only preset with keep-alives (very noisy)";
	builtinPresets.push_back(allPkts);

	PRESET_LIST mostPkts(allPkts);

	//for remaining lists we remove the noisiest messages
	ERASE_FROM_VEC(mostPkts.IDs, CLI_PING_CHALLENGE);
	ERASE_FROM_VEC(mostPkts.IDs, CLI_PING_CHALLENGE);
	ERASE_FROM_VEC(mostPkts.IDs, SRV_PING_RESPONSE);
	ERASE_FROM_VEC(mostPkts.IDs, SRV_HEARTBEAT);

	mostPkts.name = "Most";
	mostPkts.description = "Excludes keep-alives (noisy)";
	builtinPresets.push_back(mostPkts);


	PRESET_LIST clientOnlyPackets;
	PRESET_LIST serverOnlyPackets;

	for (auto it = mostPkts.IDs.begin(); it != mostPkts.IDs.end(); it++)
	{
		ushort pktID = *it;
		auto listedFilterIt = filterItems.find(pktID);
		if (listedFilterIt == filterItems.end())
			continue;

		QTableWidgetItem* filterItem = listedFilterIt->second;
		if (filterItem->text() == "Client")
			clientOnlyPackets.IDs.push_back(pktID);
		else
			serverOnlyPackets.IDs.push_back(pktID);
	}

	clientOnlyPackets.name = "Client";
	clientOnlyPackets.description = "Messages sent by the game client";
	builtinPresets.push_back(clientOnlyPackets);

	serverOnlyPackets.name = "Server";
	serverOnlyPackets.description = "Messages sent by the server";
	builtinPresets.push_back(serverOnlyPackets);


	PRESET_LIST ex_VeryCommon(mostPkts);

	ERASE_FROM_VEC(ex_VeryCommon.IDs, SRV_CHAT_MESSAGE);
	ERASE_FROM_VEC(ex_VeryCommon.IDs, CLI_CHAT_MESSAGE);
	ERASE_FROM_VEC(ex_VeryCommon.IDs, CLI_CHAT_MSG_ITEMS);
	ERASE_FROM_VEC(ex_VeryCommon.IDs, SRV_MOBILE_START_SKILL);

	ex_VeryCommon.name = "Exclude chat/skills";
	ex_VeryCommon.description = "Filters out chat, movement and common actions";
	builtinPresets.push_back(ex_VeryCommon);

	PRESET_LIST exclude_Common(ex_VeryCommon);

	ERASE_FROM_VEC(exclude_Common.IDs, SRV_MOBILE_FINISH_SKILL);
	ERASE_FROM_VEC(exclude_Common.IDs, SRV_MOBILE_UPDATE_HMS);
	ERASE_FROM_VEC(exclude_Common.IDs, SRV_STAT_CHANGED);
	ERASE_FROM_VEC(exclude_Common.IDs, SRV_START_EFFECT);
	ERASE_FROM_VEC(exclude_Common.IDs, SRV_END_EFFECT);

	exclude_Common.name = "Exclude chat/skills/combat";
	exclude_Common.description = "Filters out chat, actions and status updates";
	builtinPresets.push_back(exclude_Common);

	PRESET_LIST new_objects;
	new_objects.name = "Show all objects";
	new_objects.description = "Show new objects, items, monsters, etc";
	builtinPresets.push_back(new_objects);

	PRESET_LIST drops;
	drops.name = "Show item drops";
	drops.description = "Show only item drops";
	builtinPresets.push_back(drops);
}

void filterForm::populatePresetsList()
{

	ui->presetsTree->header()->resizeSection(0, 200);

	buildBuiltinPresets();

	QTreeWidgetItem *builtinsItem = ui->presetsTree->topLevelItem(0);
	for (int i = 0; i < builtinPresets.size(); i++)
	{
		PRESET_LIST& pl = builtinPresets.at(i);
		QTreeWidgetItem * preset = new QTreeWidgetItem();
		preset->setText(0, pl.name);
		preset->setText(1, pl.description);
		preset->setData(2, Qt::UserRole, 0);
		preset->setData(3, Qt::UserRole, i);
		builtinsItem->addChild(preset);
	}

	if (!customPresets.empty())
	{
		QTreeWidgetItem * customPresetsItem = new QTreeWidgetItem();

		ui->presetsTree->addTopLevelItem(customPresetsItem);

		for (int i = 0; i < customPresets.size(); i++)
		{
			PRESET_LIST& pl = customPresets.at(i);
			QTreeWidgetItem * preset = new QTreeWidgetItem();
			preset->setText(0, pl.name);
			preset->setText(1, pl.description);
			preset->setData(2, Qt::UserRole, 1);
			preset->setData(3, Qt::UserRole, i);
			customPresetsItem->addChild(preset);
		}
	}


	ui->presetsTree->expandAll();
}

void filterForm::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui->filterTable->columnCount(); tablecolumn++)
	{
		QTableWidgetItem *item = ui->filterTable->item(tablerow, tablecolumn);
		if (item)
			item->setBackgroundColor(colour);
	}
}

void filterForm::includeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		ui->filterTable->item(index.row(), FILTER_SECTION_STATE)->setText("Displayed");
		setRowColor(index.row(), QColor(230, 250, 180, 255));
	}
}

void filterForm::excludeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		ui->filterTable->item(index.row(), FILTER_SECTION_STATE)->setText("Hidden");
		setRowColor(index.row(), QColor(255, 220, 220, 255));
	}
}

void filterForm::saveCustom()
{
	//get text
	//add item
	//save
}

void filterForm::deletePreset()
{
	//get selected
	//remove
}

void filterForm::loadPreset()
{
	QTreeWidgetItem *item = ui->presetsTree->selectedItems().front();
	int category = item->data(2, Qt::UserRole).toInt();
	int index = item->data(3, Qt::UserRole).toInt();
	if (category == 0)
		std::cout << "loading builtin preset " << index << std::endl;
	else
		std::cout << "loading custom preset " << index << std::endl;

	PRESET_LIST& filters = (category == 0) ? 
			builtinPresets.at(index) : 	customPresets.at(index);

	//default to hidden
	for (auto it = filterStates.begin(); it != filterStates.end(); it++)
	{
		ushort pktID = it->first;
		auto item = filterItems.find(pktID)->second;
		item->setText("Hidden");
		filterStates[pktID] = false;
	}

	//items in list get shown
	for (auto it = filters.IDs.begin(); it != filters.IDs.end(); it++)
	{
		ushort pktID = *it;
		auto item = filterItems.find(pktID);
		if (item == filterItems.end()) continue;
		item->second->setText("Displayed");
		filterStates[pktID] = true;
	}
}

void filterForm::showPresetContextMenu(const QPoint& pos)
{

	QMenu contextMenu(tr("Context menu"), this);

	QAction action1("Load", this);
	connect(&action1, SIGNAL(triggered()), this, SLOT(loadPreset()));
	contextMenu.addAction(&action1);

	QAction action2("Delete", this);
	connect(&action2, SIGNAL(triggered()), this, SLOT(deletePreset()));
	contextMenu.addAction(&action2);

	contextMenu.exec(mapToGlobal(pos));

}