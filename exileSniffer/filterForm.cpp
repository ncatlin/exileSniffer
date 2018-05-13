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
	bool incoming, eDisplayState initialState)
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
	if (incoming)
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

void filterForm::populateFiltersList(rapidjson::GenericValue<rapidjson::UTF8<>> &msgInfo)
{
	ui->filterTable->horizontalHeader()->setSectionResizeMode(FILTER_SECTION_FUNCTION, QHeaderView::Stretch);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_ID, 60);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_SENDER, 75);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_COUNT, 105);
	ui->filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_STATE, 75);

	filterTableItems.clear();
	filterStates.clear();

	if (!msgInfo.IsArray())
	{
		UIaddLogMsg("Cannot load filters due to failed messageTypes.json load. Filters will not load.", 0, uiMsgQueue);
		return;
	}

	//add_filter_category(SRV_PKT_ENCAPSULATED, "Should not be shown", true);
	rapidjson::Value::ConstValueIterator it = msgInfo.Begin();
	for (; it != msgInfo.End(); it++)
	{
		UINT32 msgid = it->FindMember("ID")->value.GetUint();

		QString description = it->FindMember("Description")->value.GetString();
		bool incoming = it->FindMember("Inbound")->value.GetBool();

		add_filter_category(msgid, description, incoming);
	}
}



void filterForm::buildBuiltinPresets()
{
	ushort numMsgs = ui->filterTable->rowCount();
	if (numMsgs < 0) return;

	PRESET_LIST allPkts;

	for (int i = 0; i < MSG_IDS_END; i++)
		allPkts.IDs.push_back(i);

	allPkts.name = "All";
	allPkts.description = "The only preset with keep-alives (very noisy)";
	builtinPresets.push_back(allPkts);

	PRESET_LIST mostPkts(allPkts);

	//for remaining lists we remove the noisiest messages
	ERASE_FROM_VECTOR(mostPkts.IDs, CLI_HNC);
	ERASE_FROM_VECTOR(mostPkts.IDs, CLI_HNC);
	ERASE_FROM_VECTOR(mostPkts.IDs, SRV_HNC);
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