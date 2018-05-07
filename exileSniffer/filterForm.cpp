#include "stdafx.h"
#include "utilities.h"
#include "filterForm.h"
#include "packetIDs.h"

enum ePktDirection {outgoing, incoming};
enum ePresetCategory { builtin, user };

filterForm::filterForm(QWidget *parent)
	: QWidget(parent)
{
	savedPresetLists = new QSettings("ExileSniffer", "Filters");
}

void filterForm::add_filter_category(unsigned short pktid, QString description, 
	int fromServer, eDisplayState initialState)
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
	if (fromServer == ePktDirection::incoming)
		senderItem->setData(Qt::DisplayRole, "Server");
	else
		senderItem->setData(Qt::DisplayRole, "Client");
	senderItem->setTextAlignment(Qt::AlignCenter);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_SENDER, senderItem);

	numericSortTableWidgetItem *countItem = new numericSortTableWidgetItem();
	countItem->setData(Qt::DisplayRole, 0);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_COUNT, countItem);

	QTableWidgetItem *statusItem = new QTableWidgetItem();
	statusItem->setTextAlignment(Qt::AlignCenter);
	ui->filterTable->setItem(rowIndex, FILTER_SECTION_STATE, statusItem);
	filterTableItems[pktid] = statusItem;

	setFilterRowState(statusItem->row(), initialState);
}

bool filterForm::isDisplayed(ushort pktID)
{
	auto it = filterStates.find(pktID);
	if (it == filterStates.end()) //should add message to alert on this
		return true;

	return (it->second == eDisplayState::displayed);
}

void filterForm::populateFiltersList() 
{
	ui->filterTable->horizontalHeader()->setSectionResizeMode(FILTER_SECTION_FUNCTION, QHeaderView::Stretch);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_ID, 60);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_SENDER, 75);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_COUNT, 105);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_STATE, 75);

	filterTableItems.clear();
	filterStates.clear();

	//add_filter_category(SRV_PKT_ENCAPSULATED, "Should not be shown", true);
	add_filter_category(CLI_CHAT_MSG_ITEMS, "Sent chat message + item links", ePktDirection::outgoing);
	//7?
	add_filter_category(CLI_CHAT_MESSAGE, "Sent chat message", ePktDirection::outgoing);
	add_filter_category(CLI_CHAT_COMMAND, "Sent chat command", ePktDirection::outgoing);
	add_filter_category(SRV_CHAT_MESSAGE, "Chat message received", ePktDirection::incoming);
	add_filter_category(SRV_SERVER_MESSAGE, "Message from server", ePktDirection::incoming);
	add_filter_category(CLI_LOGGED_OUT, "Client logged out", ePktDirection::outgoing);
	add_filter_category(CLI_PING_CHALLENGE, "Client HNC", ePktDirection::outgoing);
	add_filter_category(SRV_PING_RESPONSE, "Server HNC", ePktDirection::incoming);
	add_filter_category(SRV_AREA_INFO, "Area Info", ePktDirection::incoming);
	//0x10
	//0x11
	add_filter_category(SRV_PRELOAD_MONSTER_LIST, "Area preload list", ePktDirection::incoming);
	add_filter_category(SRV_UNK_0x13, "Unknown", ePktDirection::incoming);
	add_filter_category(SRV_PLAYER_ITEMS, "Container items list", ePktDirection::incoming);
	add_filter_category(CLI_CLICKED_GROUND_ITEM, "Player clicked world object", ePktDirection::outgoing);
	add_filter_category(CLI_ACTION_PREDICTIVE, "Player action (predictive mode)", ePktDirection::outgoing);
	add_filter_category(SRV_TRANSFER_INSTANCE, "Instance change notification", ePktDirection::incoming);
	add_filter_category(SRV_INSTANCE_SERVER_DATA, "Instance server data", ePktDirection::incoming);
	add_filter_category(CLI_PICKUP_ITEM, "Player picked item up", ePktDirection::outgoing);
	//0x1a
	add_filter_category(CLI_PLACE_ITEM, "Player placed item down", ePktDirection::outgoing);
	//1c
	add_filter_category(CLI_REMOVE_SOCKET, "Player removed item from socket", ePktDirection::outgoing);
	add_filter_category(CLI_INSERT_SOCKET, "Player placed item into socket", ePktDirection::outgoing);
	add_filter_category(CLI_LEVEL_SKILLGEM, "Player levelled skill gem", ePktDirection::outgoing);
	add_filter_category(CLI_UNK_0x20, "Unknown", ePktDirection::outgoing);
	add_filter_category(CLI_SKILLPOINT_CHANGE, "Player changed passive skill", ePktDirection::outgoing);
	//22
	//23
	add_filter_category(CLI_CHOSE_ASCENDANCY, "Player selected ascendency", ePktDirection::outgoing);
	//25
	//26
	//27
	//28
	//29
	//2a
	add_filter_category(CLI_CANCEL_BUF, "Player cancelled buff", ePktDirection::outgoing);
	add_filter_category(CLI_UNK_0x2c, "Unknown", ePktDirection::outgoing);
	//2d
	add_filter_category(CLI_SET_HOTBARSKILL, "Player set hotbar skill", ePktDirection::outgoing);
	add_filter_category(SRV_SKILL_SLOTS_LIST, "Server listed hotbar skills", ePktDirection::incoming);
	//30
	//31
	//32
	//33
	//34
	//35
	//36
	add_filter_category(CLI_USE_BELT_SLOT, "Player activated belt slot", ePktDirection::outgoing);
	add_filter_category(CLI_USE_ITEM, "Player used item", ePktDirection::outgoing);
	//39
	//3a
	//3b
	//3c
	//3d
	//3e
	add_filter_category(SRV_OPEN_UI_PANE, "Server opened UI pane", ePktDirection::incoming);
	//40
	add_filter_category(CLI_UNK_0x41, "Unknown", ePktDirection::outgoing);
	//42
	//43
	//44
	//45
	add_filter_category(CLI_SELECT_NPC_DIALOG, "Player selected dialog option", ePktDirection::outgoing);
	add_filter_category(SRV_SHOW_NPC_DIALOG, "Server sent dialog to show", ePktDirection::incoming);
	add_filter_category(CLI_CLOSE_NPC_DIALOG, "Player closed dialog", ePktDirection::outgoing);
	//49
	//4a
	//4b
	//4c
	//4d
	//4e
	//4f
	add_filter_category(CLI_CLOSE_NPC_DIALOG, "Player sent party invite", ePktDirection::outgoing);
	//51
	add_filter_category(CLI_TRY_JOIN_PARTY, "Player joined party", ePktDirection::outgoing);
	add_filter_category(CLI_DISBAND_PUBLIC_PARTY, "Player left party", ePktDirection::outgoing);
	//54
	add_filter_category(CLI_CREATE_PUBLICPARTY, "Player listed public party", ePktDirection::outgoing);
	add_filter_category(CLI_UNK_x56, "Unknown", ePktDirection::outgoing);
	add_filter_category(CLI_GET_PARTY_DETAILS, "Requested details of party", ePktDirection::outgoing);
	add_filter_category(SRV_FRIENDSLIST, "Server sent friends data", ePktDirection::incoming);
	//59
	add_filter_category(SRV_PARTY_DETAILS, "Server sent party details", ePktDirection::incoming);
	add_filter_category(SRV_PARTY_ENDED, "Party ended", ePktDirection::incoming);
	//5c
	add_filter_category(CLI_REQUEST_PUBLICPARTIES, "Client requested list of public parties", ePktDirection::outgoing);
	add_filter_category(SRV_PUBLIC_PARTY_LIST, "List of public parties", ePktDirection::incoming);
	//5f
	//60
	//61
	//62
	add_filter_category(CLI_MOVE_ITEM_PANE, "Player placed item in pane", ePktDirection::outgoing);
	//64
	//65
	//66
	//67
	//68
	//69
	//6a
	//6b
	//6c
	add_filter_category(SRV_CREATE_ITEM, "New item", ePktDirection::incoming);
	add_filter_category(SRV_SLOT_ITEMSLIST, "List of items in container", ePktDirection::incoming);
	//6f
	add_filter_category(UNK_MESSAGE_0x70, "Unknown", ePktDirection::incoming);
	//71
	//72
	add_filter_category(UNK_MESSAGE_0x73, "Unknown", ePktDirection::incoming);
	add_filter_category(CLI_SET_STATUS_MESSAGE, "Player set status message", ePktDirection::outgoing);
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
	add_filter_category(CLI_SWAPPED_WEAPONS, "Player swapped weaponset", ePktDirection::outgoing);
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
	add_filter_category(SRV_PVP_MATCHLIST, "PVP Match list", ePktDirection::incoming);
	add_filter_category(SRV_EVENTSLIST, "Events List", ePktDirection::incoming);
	//93
	//94
	//95
	//96
	//97
	add_filter_category(CLI_SKILLPANE_ACTION, "Opened/closed skill tree", ePktDirection::outgoing);
	//99
	//9a
	add_filter_category(SRV_SKILLPANE_DATA, "Skill tree data", ePktDirection::incoming);
	//9c
	//9d
	//9e
	add_filter_category(CLI_MICROTRANSACTION_SHOP_ACTION, "Opened microtransaction shop", ePktDirection::outgoing);
	//a0
	add_filter_category(SRV_MICROTRANSACTION_SHOP_DETAILS, "Micro-transaction shop data", ePktDirection::incoming);
	//a2
	add_filter_category(SRV_UNK_A3, "Unknown", ePktDirection::incoming);
	add_filter_category(SRV_CHAT_CHANNEL_ID, "Chat channel membership", ePktDirection::incoming);
	//a5
	//a6
	//a7
	//a8
	//a9
	//aa
	//ab
	//ac
	add_filter_category(CLI_GUILD_CREATE, "Created guild", ePktDirection::outgoing);
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
	add_filter_category(CLI_PACKET_EXIT, "Client exit 1", ePktDirection::outgoing);
	add_filter_category(SRV_LOGINSRV_CRYPT, "Client exit 2", ePktDirection::outgoing);
	add_filter_category(CLI_DUEL_CHALLENGE, "Player sent duel challenge", ePktDirection::outgoing);
	add_filter_category(SRV_DUEL_RESPONSE, "Received response to duel challenge", ePktDirection::incoming);
	add_filter_category(SRV_DUEL_CHALLENGE, "Received duel challenge", ePktDirection::incoming);
	//c5
	//c6
	add_filter_category(CLI_UNK_0xC7, "Unknown", ePktDirection::outgoing);
	//c8
	//c9
	add_filter_category(SRV_UNK_0xCA, "Unknown", ePktDirection::incoming);
	//cb
	//cd
	add_filter_category(CLI_VISIT_HIDEOUT, "Visit hideout", ePktDirection::outgoing);
	//cf
	//d0
	//d1
	//d2
	//d3
	//d4
	add_filter_category(SRV_EVENTSLIST, "Unknown", ePktDirection::incoming);
	//d6
	//d7
	add_filter_category(CLI_USED_SKILL, "Player used skill (lockstep)", ePktDirection::outgoing);
	add_filter_category(CLI_CLICK_OBJ, "Player clicked object (lockstep)", ePktDirection::outgoing);
	add_filter_category(CLI_MOUSE_HELD, "Player held button (lockstep)", ePktDirection::outgoing);
	//db
	add_filter_category(CLI_MOUSE_RELEASE, "Player released skill (lockstep)", ePktDirection::outgoing);
	//dd
	//de
	//df
	add_filter_category(CLI_OPEN_WORLD_SCREEN, "Player opened/closed world pane", ePktDirection::outgoing);
	//e1
	//e2
	//e3
	//e4
	//e5
	add_filter_category(SRV_UNK_0xE6, "Unknown", ePktDirection::incoming);
	//e7
	//e8
	add_filter_category(SRV_OBJ_REMOVED, "Object removed", ePktDirection::incoming);
	add_filter_category(SRV_MOBILE_START_SKILL, "Object initiated skill", ePktDirection::incoming);
	add_filter_category(SRV_MOBILE_FINISH_SKILL, "Object activated skill", ePktDirection::incoming);
	//ec
	//ed
	add_filter_category(SRV_MOBILE_UNK_0xee, "Unknown", ePktDirection::incoming);
	add_filter_category(SRV_MOBILE_UNK_0xef, "Unknown", ePktDirection::incoming);
	add_filter_category(SRV_MOBILE_UPDATE_HMS, "Object health/mana/shield update", ePktDirection::incoming);
	add_filter_category(SRV_STAT_CHANGED, "Object stats update", ePktDirection::incoming);
	add_filter_category(SRV_UNK_0xf2, "Unknown", ePktDirection::incoming);
	add_filter_category(SRV_UNK_0xf3, "Unknown", ePktDirection::incoming);
	//f4
	//f5
	//f6
	//f7
	//f8
	//f9
	add_filter_category(SRV_START_EFFECT, "Object effect started", ePktDirection::incoming);
	add_filter_category(SRV_END_EFFECT, "Object effect ended", ePktDirection::incoming);
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
	add_filter_category(CLI_REQUEST_PLAYERID, "Unk playerID request", ePktDirection::outgoing);
	add_filter_category(SRV_NOTIFY_PLAYERID, "Unk playerID response", ePktDirection::incoming);
	//0x110 - player pressed add new stash tab +?
	add_filter_category(SRV_UNKNOWN_0x111, "Unknown", ePktDirection::incoming);
	//112
	//113
	//114
	//115
	//116
	//117
	add_filter_category(SRV_UNKNOWN_0x118, "Unknown", ePktDirection::incoming);
	//119
	//11a
	//11b
	add_filter_category(CLI_OPTOUT_TUTORIALS, "Unk player setting change", ePktDirection::outgoing);
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
	add_filter_category(SRV_SHOW_ENTERING_MSG, "Entering area message", ePktDirection::incoming);
	//130
	//131
	add_filter_category(SRV_HEARTBEAT, "Server heartbeat", ePktDirection::incoming);
	//133
	//134
	add_filter_category(SRV_ADD_OBJECT, "Object added", ePktDirection::incoming);
	add_filter_category(SRV_UPDATE_OBJECT, "Object updated", ePktDirection::incoming);
	add_filter_category(SRV_IDNOTIFY_0x137, "Unknown ObjID", ePktDirection::incoming);
}



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
	ERASE_FROM_VECTOR(mostPkts.IDs, CLI_PING_CHALLENGE);
	ERASE_FROM_VECTOR(mostPkts.IDs, CLI_PING_CHALLENGE);
	ERASE_FROM_VECTOR(mostPkts.IDs, SRV_PING_RESPONSE);
	ERASE_FROM_VECTOR(mostPkts.IDs, SRV_HEARTBEAT);

	mostPkts.name = "Most";
	mostPkts.description = "Excludes keep-alives (noisy)";
	builtinPresets.push_back(mostPkts);

	//set this as default - shouldn't be here but trying to get this code done
	activatePresetList(mostPkts);

	PRESET_LIST clientOnlyPackets;
	PRESET_LIST serverOnlyPackets;

	for (auto it = mostPkts.IDs.begin(); it != mostPkts.IDs.end(); it++)
	{
		ushort pktID = *it;
		auto listedFilterIt = filterTableItems.find(pktID);
		if (listedFilterIt == filterTableItems.end())
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
	//usually don't care about chat - can see it in client
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, SRV_CHAT_MESSAGE);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_CHAT_MESSAGE);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_CHAT_MSG_ITEMS);
	//don't care about things moving - quite spammy
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, SRV_MOBILE_START_SKILL);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_ACTION_PREDICTIVE);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_MOUSE_HELD);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_CLICK_OBJ);
	ERASE_FROM_VECTOR(ex_VeryCommon.IDs, CLI_MOUSE_RELEASE);
	

	ex_VeryCommon.name = "Exclude chat/skills";
	ex_VeryCommon.description = "Filters out chat, movement and common actions";
	builtinPresets.push_back(ex_VeryCommon);

	PRESET_LIST exclude_Common(ex_VeryCommon);

	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_MOBILE_FINISH_SKILL);
	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_MOBILE_UPDATE_HMS);
	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_STAT_CHANGED);
	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_START_EFFECT);
	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_END_EFFECT);
	ERASE_FROM_VECTOR(exclude_Common.IDs, SRV_IDNOTIFY_0x137);	//135 more useful

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

PRESET_LIST filterForm::load_saved_preset(QString groupName)
{
	PRESET_LIST plist;
	plist.name = savedPresetLists->value(groupName + "//name").toString();
	plist.description = savedPresetLists->value(groupName + "//info").toString();

	QString listString = savedPresetLists->value(groupName + "//list").toString();

	std::vector<std::string> tokens;
	std::istringstream iss(listString.toStdString());
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
		back_inserter(tokens));

	for (auto it = tokens.begin(); it != tokens.end(); it++)
		plist.IDs.push_back(std::stoi(*it, 0, 16));

	return plist;
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
		preset->setData(2, Qt::UserRole, ePresetCategory::builtin);
		preset->setData(3, Qt::UserRole, i);
		builtinsItem->addChild(preset);
	}

	QTreeWidgetItem * customPresetsItem = new QTreeWidgetItem();
	ui->presetsTree->addTopLevelItem(customPresetsItem);

	QStringList groups = savedPresetLists->childGroups();
	for (auto groupit = groups.begin(); groupit != groups.end(); groupit++)
	{
		PRESET_LIST plist = load_saved_preset(*groupit);

		customPresets.push_back(plist);

		QTreeWidgetItem * preset = new QTreeWidgetItem();
		preset->setText(0, plist.name);
		preset->setText(1, plist.description);
		preset->setData(2, Qt::UserRole, ePresetCategory::user);
		preset->setData(3, Qt::UserRole, customPresets.size() - 1);
		customPresetsItem->addChild(preset);
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

void filterForm::setFilterRowState(int row, eDisplayState newState)
{
	if (newState == eDisplayState::displayed)
	{
		ui->filterTable->item(row, FILTER_SECTION_STATE)->setText("Displayed");
		setRowColor(row, QColor(230, 250, 180, 255));
	}
	else
	{
		ui->filterTable->item(row, FILTER_SECTION_STATE)->setText("Hidden");
		setRowColor(row, QColor(255, 220, 220, 255));
	}

	ushort pktID = ui->filterTable->item(row, 0)->data(Qt::UserRole).toUInt();
	filterStates[pktID] = newState;
}

void filterForm::setPktIDFilterState(ushort pktID, eDisplayState newState)
{
	auto item = filterTableItems.find(pktID);
	if (item == filterTableItems.end()) return;
	setFilterRowState(item->second->row(), newState);
}


void filterForm::includeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		setFilterRowState(index.row(), eDisplayState::displayed);
	}
}

void filterForm::excludeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		setFilterRowState(index.row(), eDisplayState::hidden);
	}
}

void filterForm::toggleSelectedFilter()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		ushort pktID = ui->filterTable->item(index.row(), 0)->data(Qt::UserRole).toUInt();
		auto item = filterStates.find(pktID);
		if (item == filterStates.end()) continue;

		eDisplayState newState = (item->second == eDisplayState::hidden) ?
			eDisplayState::displayed :
			eDisplayState::hidden;
		setFilterRowState(index.row(), newState);
	}
}

void filterForm::savePresetLists()
{
	savedPresetLists->clear();

	int idx = 0;
	for (auto it = customPresets.begin(); it != customPresets.end(); it++)
	{
		PRESET_LIST& plist = *it;

		QString spaceSepList;
		for (auto strit = plist.IDs.begin(); strit != plist.IDs.end(); strit++)
			spaceSepList += (QString::number(*strit, 16) + " ");

		savedPresetLists->beginGroup(QString::number(idx++)+ " "+plist.name);
		savedPresetLists->setValue("name", plist.name);
		savedPresetLists->setValue("info", plist.description);
		savedPresetLists->setValue("list", spaceSepList);
		savedPresetLists->endGroup();
	}

	savedPresetLists->sync();
}

void filterForm::addPresetListToTree(PRESET_LIST& newList)
{
	QTreeWidgetItem *customPresetsItem;
	if (ui->presetsTree->topLevelItemCount() == 2)
		customPresetsItem = ui->presetsTree->topLevelItem(1);
	else
	{
		customPresetsItem = new QTreeWidgetItem();
		customPresetsItem->setText(0, "Saved Presets");
		ui->presetsTree->addTopLevelItem(customPresetsItem);
		ui->presetsTree->expandAll();
	}

	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setText(0, newList.name);
	item->setText(1, newList.description);
	item->setData(2, Qt::UserRole, ePresetCategory::user);
	item->setData(3, Qt::UserRole, customPresets.size() - 1);
	customPresetsItem->addChild(item);
}

void filterForm::saveCustom()
{
	PRESET_LIST newList;
	newList.name = ui->saveName->text();

	for (auto it = filterStates.begin(); it != filterStates.end(); it++)
		if (it->second != 0)
			newList.IDs.push_back(it->first);

	newList.description = QString::number(newList.IDs.size()) + " filters";

	customPresets.push_back(newList);

	addPresetListToTree(newList);
	savePresetLists();
}

void filterForm::deletePreset()
{
	QTreeWidgetItem *item = ui->presetsTree->selectedItems().front();
	int category = item->data(2, Qt::UserRole).toInt();
	int index = item->data(3, Qt::UserRole).toInt();

	if (category == ePresetCategory::user)
	{
		delete item;
		customPresets.erase(customPresets.begin() + index);
	}

	savePresetLists();
}

void filterForm::activateBuiltInPresetList(int index)
{
	PRESET_LIST& filters = builtinPresets.at(index);

	//reset all to hidden initially
	for (auto it = filterStates.begin(); it != filterStates.end(); it++)
	{
		ushort pktID = it->first;
		setPktIDFilterState(pktID, eDisplayState::hidden);
	}

	//items in preset list get set to displayed
	for (auto it = filters.IDs.begin(); it != filters.IDs.end(); it++)
	{
		ushort pktID = *it;
		setPktIDFilterState(pktID, eDisplayState::displayed);
	}

	ui->tabWidget->setCurrentIndex(0); //show the filters
}

void filterForm::activatePresetListClicked()
{
	QTreeWidgetItem *item = ui->presetsTree->selectedItems().front();
	ePresetCategory category = (ePresetCategory)item->data(2, Qt::UserRole).toInt();
	int index = item->data(3, Qt::UserRole).toInt();

	PRESET_LIST& filters = (category == ePresetCategory::builtin) ?
		builtinPresets.at(index) :
		customPresets.at(index);

	activatePresetList(filters);
}

void filterForm::activatePresetList(PRESET_LIST& filters)
{
	//reset all to hidden initially
	for (auto it = filterStates.begin(); it != filterStates.end(); it++)
	{
		ushort pktID = it->first;
		setPktIDFilterState(pktID, eDisplayState::hidden);
	}

	//items in preset list get set to displayed
	for (auto it = filters.IDs.begin(); it != filters.IDs.end(); it++)
	{
		ushort pktID = *it;
		setPktIDFilterState(pktID, eDisplayState::displayed);
	}

	ui->tabWidget->setCurrentIndex(0); //show the filters
}

void filterForm::showPresetContextMenu(const QPoint& pos)
{
	QMenu contextMenu(tr("Context menu"), this);

	QAction action1("Load", this);
	connect(&action1, SIGNAL(triggered()), this, SLOT(activatePresetListClicked()));
	contextMenu.addAction(&action1);

	//doesnt appear if nested in the if statements?
	QAction action2("Delete", this);
	connect(&action2, SIGNAL(&QAction::triggered()), this, SLOT(deletePreset()));

	QTreeWidgetItem *selectedItem = ui->presetsTree->selectedItems().front();
	if (selectedItem)
	{
		ePresetCategory category = (ePresetCategory)selectedItem->data(2, Qt::UserRole).toInt();
		if (category == ePresetCategory::user)
		{
			contextMenu.addAction(&action2);
		}
	}

	contextMenu.exec(mapToGlobal(pos));
}