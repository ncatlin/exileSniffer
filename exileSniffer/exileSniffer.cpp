/*

This is the UI thread - try not to hang it

*/

#include "stdafx.h"
#include "exileSniffer.h"
#include "utilities.h"
#include "qtextedit.h"
#include "packetIDs.h"
#include <fstream>

exileSniffer::exileSniffer(QWidget *parent)
	: QMainWindow(parent)
{


	ui.setupUi(this);

	setup_raw_stream_tab();
	setup_decoded_messages_tab();
	initFilters();

	init_DecodedPktActioners();


	start_threads();

	printf("Starting packet processing!\n");
	std::cout << "writing to log " << "N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt" << std::endl;
	outfile = std::ofstream("N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt",
		std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	if (!outfile.is_open())
		outfile = std::ofstream("latestconndump.txt",
			std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	outfile << std::endl << std::endl << "New sniffing session" << std::endl << std::endl;

	for (int i = 0; i < 0; i++)
	{
		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(1234, eGame, PKTBIT_OUTBOUND, ms_since_epoch() + 23432);
		ui_decodedpkt->messageID = SRV_PRELOAD_MONSTER_LIST;
		UI_DECODED_LIST_ENTRY listentry(*ui_decodedpkt);
		listentry.summary = "Player used inventory item";
		addDecodedListEntry(listentry, ui_decodedpkt);

		WValue &payload = ui_decodedpkt->payload;
		rapidjson::Document::AllocatorType& allocator = ui_decodedpkt->jsn.GetAllocator();
		payload.AddMember(L"PreloadList", WValue(rapidjson::kArrayType), allocator);
		WValue &jsarray = payload.FindMember(L"PreloadList")->value;
		for (int i = 0; i < 56; i++)
		{
			WValue pairArray(rapidjson::kArrayType);
			pairArray.PushBack(WValue(1412), allocator);
			pairArray.PushBack(WValue(555), allocator);

			jsarray.PushBack(pairArray, allocator);
		}

		auto it = payload.FindMember(L"PreloadList");
		if (it != payload.MemberEnd())
		{
			std::cout << "%%%%%%%%%%%%%%%%%aa list " << std::dec <<
				it->value.GetArray().Size() << " members in 0x" << std::hex << ui_decodedpkt << std::endl;
		}
	}

}

void exileSniffer::setup_raw_stream_tab()
{
	rawFiltersFormUI.setupUi(&rawFilterForm);
	rawFilterForm.setUI(&rawFiltersFormUI);


	connect(ui.ptHexPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptASCIIPane->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui.ptASCIIPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptHexPane->verticalScrollBar(), SLOT(setValue(int)));
	ui.ptHexPane->verticalScrollBar()->hide();
}

void exileSniffer::add_filter_category(unsigned short pktid, QString description, int fromServer)
{
	unsigned int rowIndex = rawFiltersFormUI.filterTable->rowCount();
	rawFiltersFormUI.filterTable->setRowCount(rowIndex + 1);
	if (ui.decodedAutoscrollCheck->isChecked())
		ui.decodedList->scrollToBottom();

	numericSortTableWidgetItem *pktIDItem = new numericSortTableWidgetItem();
	pktIDItem->setHex(pktid);
	rawFiltersFormUI.filterTable->setItem(rowIndex, FILTER_SECTION_ID, pktIDItem);

	QTableWidgetItem *descriptionItem = new QTableWidgetItem();
	descriptionItem->setData(Qt::DisplayRole, description);
	rawFiltersFormUI.filterTable->setItem(rowIndex, FILTER_SECTION_FUNCTION, descriptionItem);

	QTableWidgetItem *senderItem = new QTableWidgetItem();
	if (fromServer == PACKET_INCOMING)
		senderItem->setData(Qt::DisplayRole, "Server");
	else
		senderItem->setData(Qt::DisplayRole, "Client");
	senderItem->setTextAlignment(Qt::AlignCenter);
	rawFiltersFormUI.filterTable->setItem(rowIndex, FILTER_SECTION_SENDER, senderItem);

	numericSortTableWidgetItem *countItem = new numericSortTableWidgetItem();
	countItem->setData(Qt::DisplayRole, 0);
	rawFiltersFormUI.filterTable->setItem(rowIndex, FILTER_SECTION_COUNT, countItem);

	QTableWidgetItem *statusItem = new QTableWidgetItem();
	statusItem->setData(Qt::DisplayRole, "Included");
	statusItem->setTextAlignment(Qt::AlignCenter);
	rawFiltersFormUI.filterTable->setItem(rowIndex, FILTER_SECTION_STATE, statusItem);
}

void exileSniffer::initFilters()
{
	connect(&rawFilterForm, SIGNAL(applyFilters()), this, SLOT(updateFilters()));
	toggleRawLineWrap(ui.rawLinewrapCheck->isChecked());


	rawFiltersFormUI.filterTable->horizontalHeader()->setSectionResizeMode(FILTER_SECTION_FUNCTION, QHeaderView::Stretch);
	rawFiltersFormUI.filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_ID, 60);
	rawFiltersFormUI.filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_SENDER, 75);
	rawFiltersFormUI.filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_COUNT, 105);
	rawFiltersFormUI.filterTable->horizontalHeader()->resizeSection(FILTER_SECTION_STATE, 75);

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

void exileSniffer::updateFilters()
{ 
	QList<ushort> includedMessageIDs;

	for (int msgid = 0; msgid < rawFiltersFormUI.filterTable->rowCount(); msgid++)
	{
		QTableWidgetItem *item = rawFiltersFormUI.filterTable->item(msgid, FILTER_SECTION_STATE);
		if (item->text() != "Excluded") 
			includedMessageIDs << msgid;
	}

	std::cout << "Todo: include " << includedMessageIDs.size() << " msg types in decoded list" << std::endl;
}




void exileSniffer::setup_decoded_messages_tab()
{
	ui.decodedList->horizontalScrollBar()->setFixedHeight(10);
	ui.decodedList->horizontalHeader()->resizeSection(DECODED_SECTION_TIME, 70);
	ui.decodedList->horizontalHeader()->resizeSection(DECODED_SECTION_SENDER, 50);
	ui.decodedList->horizontalHeader()->resizeSection(DECODED_SECTION_SUMMARY, 450);
	ui.decodedList->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
}

void exileSniffer::start_threads()
{
	//start the packet capture thread to grab streams
	packetSniffer = new packet_capture_thread(&uiMsgQueue);
	std::thread packetSnifferInstance(&packet_capture_thread::ThreadEntry, packetSniffer);
	packetSnifferInstance.detach();

	//start the keyscanner thread to grab keys from clients
	keyGrabber = new key_grabber_thread(&uiMsgQueue);
	std::thread keyGrabberInstance(&key_grabber_thread::ThreadEntry, keyGrabber);
	keyGrabberInstance.detach();


	//start a thread to process streams
	packetProcessor = new packet_processor(keyGrabber, &uiMsgQueue, ggpk);
	std::thread packetProcessorInstance(&packet_processor::ThreadEntry, packetProcessor);
	packetProcessorInstance.detach();

	//start a timer to pull updates into the UI
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(read_UI_Q()));
	timer->start(10);
}

void exileSniffer::read_UI_Q()
{
	clock_t startTicks = clock();
	while (!uiMsgQueue.empty())
	{
		UI_MESSAGE *msg = uiMsgQueue.waitItem();
		action_UI_Msg(msg);

		float secondsElapsed = ((float)clock() - startTicks) / CLOCKS_PER_SEC;
		if (secondsElapsed > 0.15) //todo: season to taste
			break;
	}
}

void exileSniffer::action_UI_Msg(UI_MESSAGE *msg)
{
	bool deleteAfterUse = true;

	switch (msg->msgType)
	{
	case uiMsgType::eMetaLog:
	{
		UI_METALOG_MSG *metalogmsg = (UI_METALOG_MSG *)msg;
		add_metalog_update(metalogmsg->stringData, metalogmsg->pid);
		break;
	}
	case uiMsgType::eClientEvent:
	{
		UI_CLIENTEVENT_MSG *cliEvtMsg = (UI_CLIENTEVENT_MSG *)msg;
		handle_client_event(cliEvtMsg->pid, cliEvtMsg->running);
		break;
	}
	case uiMsgType::eLoginNote:
	{
		UI_LOGIN_NOTE *lgn = (UI_LOGIN_NOTE *)msg;
		auto it = clients.find(lgn->pid);
		if (it != clients.end())
			it->second->isLoggedIn = true;
		break;
	}
	case uiMsgType::ePacketHex:
	{
		deleteAfterUse = false; //archived
		handle_raw_packet_data((UI_RAWHEX_PKT *)msg);
		break;
	}
	case uiMsgType::eDecodedPacket:
	{
		deleteAfterUse = false; //archived
		UIDecodedPkt &uiDecodedMsg = *((UIDecodedPkt *)msg);

		if(!uiDecodedMsg.decodeError())
			action_decoded_packet(uiDecodedMsg); 
		else
		{
			if (uiDecodedMsg.wasAbandoned())
				action_decoded_packet(uiDecodedMsg);
			else
				action_undecoded_packet(uiDecodedMsg);
		}
		break;
	}
	}

	if(deleteAfterUse)
		delete msg;
}

void exileSniffer::add_metalog_update(QString msg, DWORD pid)
{
	std::stringstream ss;
	ss << "[" << timestamp();
	if (pid != 0)
		ss << " - PID:"<<std::dec << pid;
	ss << "]: " << msg.toStdString() << std::endl;

	ui.metaLog->appendPlainText(QString::fromStdString(ss.str()));
}

void exileSniffer::handle_client_event(DWORD pid, bool isRunning)
{
	auto it = clients.find(pid);
	if (isRunning)
	{
		if (it == clients.end())
		{
			clientData *client = new clientData;
			client->processID = pid;
			client->isRunning = true;
			clients.emplace(make_pair(pid,client));

			QString msg = "Client started";
			add_metalog_update(msg, pid);
		}
		else
		{
			//feels like a bad way of doing this. meh.
			QString warnmsg = "WARNING: Found a new client with a PID we have seen before. \
			Deleting previous data. Hope it was saved!";
			add_metalog_update(warnmsg, pid);

			clientData *oldclient = it->second;
			oldclient->cleanup();
			delete oldclient;

			clientData *newClient = new clientData;
			clients[pid]->isRunning = true;
			clients[pid]->processID = pid;
			clients[pid] = newClient;
		}
	}
	else
	{
		if (it != clients.end())
		{
			clientData *oldclient = it->second;
			oldclient->isRunning = false;

			QString msg = "Client terminated";
			add_metalog_update(msg, pid);
		}
		else
		{
			QString warnmsg = "WARNING: A client we have never seen just vanished \
								from the list of clients we have seen. Everything \
								is probably on fire.";
			add_metalog_update(warnmsg, pid);
		}
	}
}

std::string serverString(streamType server, string IP)
{
	switch (server)
	{
	case streamType::eGame:
		return "Server[Game]";
	case streamType::eLogin:
		return "Server[Login]";
	case streamType::ePatch:
		return "Server[Patch]";
	default:
		return "Server[Unknown]";
	}
}

void exileSniffer::insertRawText(std::string hexdump, std::string asciidump)
{
	int oldScrollPos = ui.ptHexPane->verticalScrollBar()->sliderPosition();

	QTextCursor userCursor = ui.ptHexPane->textCursor();
	ui.ptHexPane->moveCursor(QTextCursor::MoveOperation::End);
	ui.ptHexPane->append(QString::fromStdString(hexdump));
	ui.ptHexPane->setTextCursor(userCursor);

	userCursor = ui.ptASCIIPane->textCursor();
	ui.ptASCIIPane->moveCursor(QTextCursor::MoveOperation::End);
	ui.ptASCIIPane->append(QString::fromStdString(asciidump));
	ui.ptASCIIPane->setTextCursor(userCursor);

	if(!ui.rawAutoScrollCheck->isChecked())
		ui.ptASCIIPane->verticalScrollBar()->setSliderPosition(oldScrollPos);
}

//todo: bold first two bytes, may need to add a 'continuationpacket' field
void exileSniffer::print_raw_packet(UI_RAWHEX_PKT *pkt)
{
	std::stringstream hexdump;
	std::stringstream asciidump;

	char timestamp[20];
	struct tm *tm = gmtime(&pkt->createdtime);
	strftime(timestamp, sizeof(timestamp), "%H:%M:%S", tm);

	hexdump << "#" << rawCount_Recorded_Filtered.first << " " << timestamp << " ";

	if (pkt->incoming)
		hexdump << serverString(pkt->stream, "f") << " to PlayerClient";
	else
		hexdump << "PlayerClient to " << serverString(pkt->stream, "f");
	hexdump << "("<<std::dec<<pkt->pktBytes->size()<<" bytes)"<< std::endl;
	asciidump << std::endl;


	stringstream::pos_type bytesStart = hexdump.tellp();

	hexdump << std::setfill('0') << std::uppercase << " ";
	for (int i = 0; i < pkt->pktBytes->size(); ++i)
	{
		byte item = pkt->pktBytes->at(i);

		if (item)
			hexdump << " " << std::hex << std::setw(2) << (int)item ;
		else
			hexdump << " 00";

		if (item >= ' ' && item <= '~')
			asciidump << (char)item;
		else
			asciidump << '.';//replace unprintable with dots

		if ((i + 1) % UIhexPacketsPerRow == 0)
		{
			hexdump << std::endl << "  ";
			asciidump << std::endl;
		}
	}
	hexdump << "\n" << std::endl << std::nouppercase;
	asciidump << "\n" << std::endl;

	std::string hexdumpstring = hexdump.str();
	//todo: work out position from bytes*2 + bytes*space + bytes/bytesperline*space
	//if (pkt->decodeFailed)
	//	hexdumpstring.at()
	outfile << hexdumpstring << std::endl;
	insertRawText(hexdumpstring, asciidump.str());

}

bool exileSniffer::packet_passes_raw_filter(UI_RAWHEX_PKT *pkt, clientData *client)
{
	//todo user specified
	if (pkt->startBytes == CLI_PING_CHALLENGE || 
		pkt->startBytes == SRV_PING_RESPONSE || 
		pkt->startBytes == SRV_HEARTBEAT ||
		pkt->startBytes == SRV_CHAT_MESSAGE)
		return false;

	return true;
}

bool exileSniffer::packet_passes_decoded_filter(UIDecodedPkt& decoded, clientData *client)
{
	//todo user specified
	if (decoded.messageID == CLI_PING_CHALLENGE || 
		decoded.messageID == SRV_PING_RESPONSE || 
		decoded.messageID == SRV_HEARTBEAT || 
		decoded.messageID == SRV_CHAT_MESSAGE)
		return false;
	return true;
}

clientData * exileSniffer::get_client(DWORD pid)
{
	clientData *client = NULL;

	if (pid == 0)
	{
		//until we go down the effort path of associating ports with PIDs
		//we will have to stick with placing unassigned logon packets to the
		//first unauthenticated process we find
		auto it = clients.begin();
		for (; it != clients.end(); it++)
			if (!it->second->isLoggedIn)
			{
				client = it->second;
				break;
			}
	}
	else
	{
		auto it = clients.find(pid);
		if (it != clients.end())
		{
			client = it->second;
		}
	}

	return client;
}

void exileSniffer::handle_raw_packet_data(UI_RAWHEX_PKT *pkt)
{

	clientData *client = get_client(pkt->pid);

	if (!client)
	{
		add_metalog_update("Warning: Dropped packet with no associated PID", 0);
		return;
	}

	if (packet_passes_raw_filter(pkt, client))
		print_raw_packet(pkt);
	else
		++rawCount_Recorded_Filtered.second;
	++rawCount_Recorded_Filtered.first;

	client->rawHexPackets.push_back(pkt);
	updateRawFilterLabel();
}


void exileSniffer::rawBytesRowChanged(QString arg)
{
	//check the entry is all digits
	QRegExp re("\\d*");  
	if (!re.exactMatch(arg))
		return;

	UIhexPacketsPerRow = arg.toInt();

	reprintRawHex();
}

void exileSniffer::reprintRawHex()
{
	std::cout << "reprinting raw" << std::endl;
	ui.ptHexPane->clear();
	ui.ptASCIIPane->clear();



	clientData *exampleclient = clients.begin()->second; //todo: pid for 'active' client
	vector <UI_RAWHEX_PKT *> pkts = exampleclient->rawHexPackets;

	rawCount_Recorded_Filtered.second = 0;

	for (auto pktIt = pkts.begin(); pktIt != pkts.end(); pktIt++)
	{
		UI_RAWHEX_PKT *pkt = *pktIt;

		if (packet_passes_raw_filter(pkt, exampleclient))
			print_raw_packet(pkt);
		else
			++rawCount_Recorded_Filtered.second;
	}
	updateRawFilterLabel();
}

void exileSniffer::updateRawFilterLabel()
{
	std::stringstream filterLabTxt;
	filterLabTxt << std::dec << rawCount_Recorded_Filtered.first << " Packets Recorded";
	if (rawCount_Recorded_Filtered.second)
		filterLabTxt << " / " << rawCount_Recorded_Filtered.second << " Filtered";
	ui.filterLabel->setText(QString::fromStdString(filterLabTxt.str()));
}

void exileSniffer::updateDecodedFilterLabel()
{
	std::stringstream filterLabTxt;
	filterLabTxt << std::dec << "Packets ( Displayed: " << decodedCount_Displayed_Filtered.first <<
	" / Filtered: " << decodedCount_Displayed_Filtered.second <<
	" / Error: "<< decodedErrorPacketCount << " )";
	ui.decodedDisplayedLabel->setText(QString::fromStdString(filterLabTxt.str()));
}

void exileSniffer::toggleRawLineWrap(bool wrap)
{
	if (wrap)
	{
		ui.ptHexPane->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
		ui.ptASCIIPane->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
	}
	else
	{
		ui.ptHexPane->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
		ui.ptASCIIPane->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
	}

}


void exileSniffer::toggleRawAutoScroll(bool enabled)
{
	if (enabled)
	{
		ui.ptASCIIPane->moveCursor(QTextCursor::MoveOperation::End);
		ui.ptHexPane->moveCursor(QTextCursor::MoveOperation::End);
	}
}


void exileSniffer::decodedListClicked()
{
	//todo: user option to disable this
	if (ui.decodedAutoscrollCheck->isChecked())
		ui.decodedAutoscrollCheck->setChecked(false);
}



void exileSniffer::decodedCellActivated(int row, int col)
{
	ui.decodedText->clear();

	QTableWidgetItem *item = ui.decodedList->item(row, 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)item->data(Qt::UserRole).value<UIDecodedPkt*>();

	if (!obj->decodeError())
	{
		auto it = decodedPktActioners.find(obj->messageID);
		if (it != decodedPktActioners.end())
		{
			exileSniffer::actionFunc f = it->second;
			QString detailedAnalysis;
			(this->*f)(*obj, &detailedAnalysis);
			if(!detailedAnalysis.isEmpty())
				ui.decodedText->insertPlainText(detailedAnalysis + "\n\n");
			if (obj->wasAbandoned())
			{
				QString warn = "\tWARNING: Packet not decoded fully - processing abandoned\n\n";
				ui.decodedText->insertPlainText(warn);
			}
		}
		else
		{
			stringstream err;
			err << "ERROR! no action setup for displayed pkt id 0x" << std::hex << obj->messageID;
			add_metalog_update(QString::fromStdString(err.str()), obj->clientProcessID());
		}
	}


	std::wstringstream hexdump;

	char timestamp[20];

	hexdump << epochms_to_timestring(obj->time_processed_ms()) << " ";

	size_t bytessize;
	if (obj->decodeError())
		bytessize = obj->originalbuf->size() - obj->bufferOffsets.first;
	else
		bytessize = obj->bufferOffsets.second - obj->bufferOffsets.first;

	if (obj->streamFlags & PKTBIT_INBOUND)
		hexdump << "server" << " to PlayerClient";
	else
		hexdump << "PlayerClient to " << "server"; //serverString(pkt->stream, "f");
	hexdump << "(" << std::dec << bytessize << " bytes)" << std::endl;

	size_t bufStart = obj->bufferOffsets.first;
	
	hexdump << std::setfill(L'0') << std::uppercase << L" ";
	for (int i = 0; i < bytessize; ++i)
	{
		byte item = obj->originalbuf->at(bufStart + i);

		if (item)
			hexdump << " " << std::hex << std::setw(2) << (int)item;
		else
			hexdump << " 00";

		//if (item >= ' ' && item <= '~')
		//	asciidump << (char)item;
		//else
		//	asciidump << '.';//replace unprintable with dots

		if ((i + 1) % UIhexPacketsPerRow == 0)
		{
			hexdump << std::endl << " ";
			//asciidump << std::endl;
		}
	}
	hexdump << "\n" << std::endl << std::nouppercase;
	
	std::wstring hexdumpstring = hexdump.str();
	ui.decodedText->insertPlainText(QString::fromStdWString(hexdumpstring));
}