/*

This is the UI thread - try not to hang it

*/

#include "stdafx.h"
#include "exileSniffer.h"
#include "utilities.h"
#include "qtextedit.h"


exileSniffer::exileSniffer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setup_raw_stream_tab();
	setup_decoded_messages_tab();

	init_DecodedPktActioners();

	start_threads();

	Sleep(200);
	//testing
	for (int i = 0; i < 0; i++)
	{
		UIDecodedPkt *ui_decodedpkt =
			new UIDecodedPkt(1234, eGame, PKTBIT_OUTBOUND, ms_since_epoch() + 23432);
		ui_decodedpkt->setFailedDecode();
		UI_DECODED_LIST_ENTRY listentry(*ui_decodedpkt);
		listentry.summary = "Player used inventory item";
		addDecodedListEntry(listentry);

		ui_decodedpkt =
			new UIDecodedPkt(1234, eLogin, PKTBIT_OUTBOUND, ms_since_epoch() + 23432);
		UI_DECODED_LIST_ENTRY listentry1(*ui_decodedpkt);
		listentry1.summary = "Player used inventory item";
		addDecodedListEntry(listentry1);

		ui_decodedpkt =
			new UIDecodedPkt(1234, ePatch, PKTBIT_INBOUND, ms_since_epoch() + 23432);
		UI_DECODED_LIST_ENTRY listentry2(*ui_decodedpkt);
		listentry2.summary = "Player used inventory item";
		addDecodedListEntry(listentry2);
	}
}

void exileSniffer::setup_raw_stream_tab()
{
	rawFiltersFormUI.setupUi(&rawFilterForm);
	connect(&rawFilterForm, SIGNAL(newrawFilters()), this, SLOT(updateRawFilters()));
	toggleRawLineWrap(ui.rawLinewrapCheck->isChecked());

	connect(ui.ptHexPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptASCIIPane->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui.ptASCIIPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptHexPane->verticalScrollBar(), SLOT(setValue(int)));
	ui.ptHexPane->verticalScrollBar()->hide();
}

void exileSniffer::setup_decoded_messages_tab()
{
	ui.decodedList->horizontalScrollBar()->setFixedHeight(10);
	ui.decodedList->horizontalHeader()->resizeSection(HEADER_SECTION_TIME, 70);
	ui.decodedList->horizontalHeader()->resizeSection(HEADER_SECTION_SENDER, 50);
	ui.decodedList->horizontalHeader()->resizeSection(HEADER_SECTION_SUMMARY, 800);
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
	packetProcessor = new packet_processor(keyGrabber, &uiMsgQueue);
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
		UIDecodedPkt &uiDecodedMsg = *((UIDecodedPkt *)msg);
		if(!uiDecodedMsg.decodeError())
			action_decoded_packet(uiDecodedMsg); 
		else
			action_undecoded_packet(uiDecodedMsg);
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
		return "GameServer";
	case streamType::eLogin:
		return "LoginServer";
	case streamType::ePatch:
		return "PatchServer";
	default:
		return "UnknownServer";
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
		hexdump << serverString(pkt->stream, "f") << " to POE Client";
	else
		hexdump << "POE Client to " << serverString(pkt->stream, "f");
	hexdump << std::endl;
	asciidump << std::endl;


	stringstream::pos_type bytesStart = hexdump.tellp();

	hexdump << std::setfill('0') << std::uppercase << " ";
	for (int i = 0; i < pkt->pktSize; ++i)
	{
		byte item = pkt->pktBytes[i];

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
	insertRawText(hexdumpstring, asciidump.str());

}

bool exileSniffer::packet_passes_raw_filter(UI_RAWHEX_PKT *pkt, clientData *client)
{
	//todo
	if (pkt->startBytes == 0xd || pkt->startBytes == 0xe)
		return false;
	return true;
}

bool exileSniffer::packet_passes_decoded_filter(UIDecodedPkt& decoded, clientData *client)
{
	//todo
	if (decoded.messageID == 0xd || decoded.messageID == 0xe)
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