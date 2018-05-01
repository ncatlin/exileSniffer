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

	init_loginPkt_Actioners();
	init_gamePkt_Actioners();

	start_threads();

	setup_decryption_tab();

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



void exileSniffer::setLabelActive(QLabel *lab, bool state)
{
	if (state)
	{
		lab->setGraphicsEffect(Q_NULLPTR);
	}
	else
	{
		QGraphicsColorizeEffect *effect;
		effect = new QGraphicsColorizeEffect;
		effect->setColor(QColor(225, 225, 225, 255));

		lab->setGraphicsEffect(effect);
	}
}

void exileSniffer::setStateNotDecrypting()
{
	activeDecryption = false;
	packetProcessor->requestIters(false);
	setLabelActive(ui.yes_decrypt_label, false);
	setLabelActive(ui.no_decrypt_label, true);

	ui.decrypt_details_stack->setCurrentIndex(0);
}

void exileSniffer::setup_decryption_tab()
{
	ui.keyExStatusWidget->setTitle("Client Key Extraction");
	ui.keyExStatusWidget->setText("Waiting for game processes");

	ui.sniffStatusWidget->setTitle("Network Stream Sniffing");
	ui.sniffStatusWidget->setText("Waiting for game packets");

	ui.no_decrypt_label->setPixmap(QPixmap(":/icons/padlock-red-locked.png"));
	ui.yes_decrypt_label->setPixmap(QPixmap(":/icons/padlock-green.png"));

	setStateNotDecrypting();

}

void exileSniffer::setup_raw_stream_tab()
{
	rawFiltersFormUI.setupUi(&filterFormObj);
	filterFormObj.setUI(&rawFiltersFormUI);

	toggleRawLineWrap(ui.rawLinewrapCheck->isChecked());

	connect(ui.ptHexPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptASCIIPane->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui.ptASCIIPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptHexPane->verticalScrollBar(), SLOT(setValue(int)));
	ui.ptHexPane->verticalScrollBar()->hide();
}

//full clear and reload of displayed packets
void exileSniffer::refreshFilters()
{
	if (decodedListEntries.empty()) return;

	ui.decodedListTable->clear();

	for (auto it = decodedListEntries.begin(); it != decodedListEntries.end(); it++)
	{
		if (packet_passes_decoded_filter(it->second->messageID))
		{
			addDecodedListEntry(it->first, it->second, false);
		}
	}
}

void exileSniffer::initFilters()
{
	filterFormObj.populateFiltersList();
	filterFormObj.populatePresetsList();

	connect(&filterFormObj, SIGNAL(applyFilters()), this, SLOT(refreshFilters()));
}

void exileSniffer::setup_decoded_messages_tab()
{
	ui.decodedListTable->horizontalScrollBar()->setFixedHeight(10);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_TIME, 70);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_SENDER, 75);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_MSGID, 45);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_SUMMARY, 450);
	ui.decodedListTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
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

void exileSniffer::set_keyEx_scanning_count(int total, int scanning)
{

	if (total == 0)
	{
		ui.keyExStatusWidget->setState(statusWidgetState::eBad);
		ui.keyExStatusWidget->setText("No running game clients detected");
	}
	else
	{
		if (scanning != total)
		{
			stringstream msg;
			if (total == 0)
				msg << "No active clients found but ";
			else if (total == 1)
				msg << "1 active client found but ";
			else
				msg << total << " active clients found but ";

			msg << scanning << " being scanned";

			if (scanning > 0)
				ui.keyExStatusWidget->setState(statusWidgetState::ePending);
			else
				ui.keyExStatusWidget->setState(statusWidgetState::eBad);

			ui.keyExStatusWidget->setText(QString::fromStdString(msg.str()));
		}
		else
		{
			ui.keyExStatusWidget->setState(statusWidgetState::ePending);
			QString stateString = "Scanning " + QString::number(total) + " clients for stream keys";
			ui.keyExStatusWidget->setText(stateString);
		}
	}
}

void exileSniffer::setStateDecrypting(int streamID)
{
	activeDecryption = true;

	STREAM_NETWORK_DATA *streamData = packetSniffer->get_stream_data(streamID);
	if (streamData)
	{
		std::stringstream streamWidgetMsg;
		streamWidgetMsg << "Decrypting connection to " << streamData->serverIP << ":" << streamData->serverPort << std::endl;
		ui.sniffStatusWidget->setState(statusWidgetState::eGood);
		ui.sniffStatusWidget->setText(QString::fromStdString(streamWidgetMsg.str()));

		std::stringstream keyexWidgetMsg;
		keyexWidgetMsg << "Decrypting stream of game process " << std::dec << packetProcessor->getLatestDecryptProcess() << std::endl;
		ui.keyExStatusWidget->setState(statusWidgetState::eGood);
		ui.keyExStatusWidget->setText(QString::fromStdString(keyexWidgetMsg.str()));
	}
	else
	{
		ui.sniffStatusWidget->setState(statusWidgetState::eBad);
		ui.sniffStatusWidget->setText("ERROR: Decrypting unknown stream. Voices from beyond?");
	}

	setLabelActive(ui.yes_decrypt_label, true);
	setLabelActive(ui.no_decrypt_label, false);
	ui.decrypt_details_stack->setCurrentIndex(1);
	packetProcessor->requestIters(true);
}

void exileSniffer::updateStreamStateWidget()
{
	int active = 0;
	int failed = 0;
	
	int decryptingStream = -1;

	for (auto it = streamStates.begin(); it != streamStates.end(); it++)
	{
		if (it->second == eStreamDecrypting)
		{
			decryptingStream = it->first;
			break;
		}
		if (it->second == eStreamFailed) failed++;
		active++;
	}

	if (decryptingStream != -1)
	{
		if (!activeDecryption)
		{
			setStateDecrypting(decryptingStream);
		}
	}
	else
	{
		if (active == 0)
		{
			ui.sniffStatusWidget->setState(statusWidgetState::eBad);
			ui.sniffStatusWidget->setText("No streams being sniffed");
		}
		else
		{
			std::stringstream msg;
			int actualActive = active - failed;
			if (actualActive > 0)
			{
				msg << "Sniffing " << actualActive << " stream";
				if (actualActive != 1)
					msg << "s";
				msg << " for logon packets";

				if (failed > 0)
					msg << " (" << failed << " abandoned)";

				ui.sniffStatusWidget->setState(statusWidgetState::ePending);
			}
			else
			{
				msg << "Abandoned decryption of " << failed << " stream";
				if (failed != 1)
					msg << "s";
				msg << ". Must start before logon.";

				ui.sniffStatusWidget->setState(statusWidgetState::eBad);
			}

			ui.sniffStatusWidget->setText(QString::fromStdString(msg.str()));
		}
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

			if (cliEvtMsg->pid && !activeDecryption)
				set_keyEx_scanning_count(cliEvtMsg->totalClients, cliEvtMsg->totalScanning);

			break;
		}

		case uiMsgType::eStreamEvent:
		{
			UI_STREAMEVENT_MSG *streamNote = (UI_STREAMEVENT_MSG *)msg;
			if (streamNote->state == eStreamState::eStreamEnded)
			{
				auto streamIt = streamStates.find(streamNote->streamID);
				if (streamIt->second == eStreamDecrypting)
					activeDecryption = false;
				streamStates.erase(streamIt);
			}
			else
				streamStates[streamNote->streamID] = streamNote->state;

			updateStreamStateWidget();
			break;
		}

		case uiMsgType::eSniffNote:
		{
			UI_SNIFF_NOTE *sniffnote = (UI_SNIFF_NOTE *)msg;
			ui.sniffStatusWidget->setState(statusWidgetState::ePending);
			ui.sniffStatusWidget->setText("Sniffing for new game streams on interface "+ sniffnote->iface);
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

		case uiMsgType::eKeyUpdate:
		{
			UI_KEY *keymsg = (UI_KEY *)msg;
			ui.keyHexText->clear();
			QString keys = byteVecToHex(keymsg->key);
			keys.insert(48, '\n');
			ui.keyHexText->appendPlainText(keys);
			break;
		}

		case uiMsgType::eIVUpdate:
		{
			UI_IV *ivmsg = (UI_IV *)msg;
			if(!ivmsg->sendIV.empty())
				ui.sendIVText->setText(byteVecToHex(ivmsg->sendIV));
			if (!ivmsg->recvIV.empty())
				ui.recvIVText->setText(byteVecToHex(ivmsg->recvIV));
			break;
		}

		case uiMsgType::eCryptIterUpdate:
		{
			UI_CRYPTITER *ivmsg = (UI_CRYPTITER *)msg;
			if (!ivmsg->sendIter.empty())
				ui.sendIterText->setText(byteVecToHex(ivmsg->sendIter));
			if (!ivmsg->recvIter.empty())
				ui.recvIterText->setText(byteVecToHex(ivmsg->recvIter));
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

bool exileSniffer::packet_passes_raw_filter(UI_RAWHEX_PKT *pkt)
{
	//todo user specified
	if (pkt->startBytes == CLI_PING_CHALLENGE || 
		pkt->startBytes == SRV_PING_RESPONSE || 
		pkt->startBytes == SRV_HEARTBEAT ||
		pkt->startBytes == SRV_CHAT_MESSAGE)
		return false;

	return true;
}

bool exileSniffer::packet_passes_decoded_filter(ushort msgID)
{
	return (filterFormObj.isDisplayed(msgID));
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

	if (packet_passes_raw_filter(pkt))
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

		if (packet_passes_raw_filter(pkt))
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

QString UI_DECODED_LIST_ENTRY::sender()
{
	if (flags & PKTBIT_OUTBOUND) return "Client";
	if (flags & PKTBIT_GAMESERVER) return "GameServer";
	if (flags & PKTBIT_LOGINSERVER) return "LoginServer";
	return "ErrorB";
}

void exileSniffer::decodedCellActivated(int row, int col)
{
	ui.decodedText->clear();

	QTableWidgetItem *item = ui.decodedListTable->item(row, 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)item->data(Qt::UserRole).value<UIDecodedPkt*>();

	if (!obj->decodeError())
	{
		map<unsigned short, actionFunc>* actionerList;
		if (obj->streamFlags & PKTBIT_GAMESERVER)
			actionerList = &gamePktActioners;
		else
			actionerList = &loginPktActioners;

		auto it = actionerList->find(obj->messageID);
		if (it != actionerList->end())
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
	hexdump << "----Hex Dump----" << std::endl;
	char timestamp[20];
	hexdump << epochms_to_timestring(obj->time_processed_ms()) << " ";

	if (!obj->originalbuf)
	{
		wstringstream err;
		err << "ERROR! Decodedcell item has no buffer set. pkt time: " << epochms_to_timestring(obj->time_processed_ms());
		add_metalog_update(QString::fromStdWString(err.str()), 0);
		return;
	}



	size_t bytessize;
	if (obj->decodeError())
		bytessize = obj->originalbuf->size() - obj->bufferOffsets.first;
	else
		bytessize = obj->bufferOffsets.second - obj->bufferOffsets.first;
	
	std::wstring serverName  = (obj->streamFlags & PKTBIT_GAMESERVER) ? L"GameServer" : L"LoginServer";

	if (obj->streamFlags & PKTBIT_INBOUND)
		hexdump << serverName << " to PlayerClient";
	else
		hexdump << "PlayerClient to " << serverName;

	hexdump << " (" << std::dec << bytessize << " bytes)" << std::endl;

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


void exileSniffer::copySelected()
{
	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty()) return;
	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);

	//todo - mush stuff on this row together on keyboard
}

void exileSniffer::filterSelected()
{
	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty()) return;
	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)rowitem->data(Qt::UserRole).value<UIDecodedPkt*>();

	//todo filter
}

void exileSniffer::decodedTableMenuRequest(QPoint pos)
{
	QMenu contextMenu(tr("Context menu"), this);

	QAction action1("Copy Contents", this);
	//connect(&action1, SIGNAL(triggered()), this, SLOT(copySelected()));
	contextMenu.addAction(&action1);

	//doesnt appear if nested in the if statements?
	QAction action2("", this);
	//connect(&action2, SIGNAL(triggered()), this, SLOT(filterSelected()));

	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty())
	{
		contextMenu.exec(mapToGlobal(pos));
		return;
	}

	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)rowitem->data(Qt::UserRole).value<UIDecodedPkt*>();

	QString labeltext = "Filter PktID 0x" + QString::number(obj->messageID, 16);
	action2.setText(labeltext);
	contextMenu.addAction(&action2);
	contextMenu.exec(mapToGlobal(pos));
	return;
}