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
	rawFiltersFormUI.setupUi(&rawFilterForm);
	connect(&rawFilterForm, SIGNAL(newrawFilters()), this, SLOT(updateRawFilters()));

	toggleRawLineWrap(ui.rawLinewrapCheck->isChecked());

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
	timer->start(20);
}

void exileSniffer::read_UI_Q()
{
	clock_t startTicks = clock();
	while (!uiMsgQueue.empty())
	{
		UI_MESSAGE *msg = uiMsgQueue.waitItem();
		action_UI_Msg(msg);

		float secondsSinceStart = ((float)clock() - startTicks) / CLOCKS_PER_SEC;
		if (secondsSinceStart > 0.15) //todo: season to taste
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
	return "serverrrr";
}

void exileSniffer::handle_raw_packet_data(UI_RAWHEX_PKT *pkt)
{
	std::stringstream hexdump;

	char timestamp[20];
	struct tm *tm = gmtime(&pkt->createdtime);
	strftime(timestamp, sizeof(timestamp), "%H:%M:%S-%e/%d/%g", tm);

	if (pkt->incoming)
		hexdump << serverString(pkt->stream, "f") << " to POE Client <324324234>";
	else
		hexdump << "POE Client <324324234> to " << serverString(pkt->stream,"f");
	hexdump << " [" << timestamp << "]" <<std::endl;

	hexdump << std::setfill('0') << std::uppercase;
	for (int i = 0; i < pkt->pktBytes.size(); ++i)
	{
	byte item = pkt->pktBytes.at(i);
	if (item)
		hexdump << std::hex << std::setw(2) << (int)item << " ";
	else
		hexdump << "00 ";
	if ((i + 1) % UIhexPacketsPerRow == 0) hexdump << std::endl;
	}
	hexdump << "\n\n" <<  std::nouppercase;

	ui.ptHexPane->insertPlainText(QString::fromStdString(hexdump.str()));

	if (pkt->pid == 0)
	{
		//until we go down the effort path of associating ports with PIDs
		//we will have to stick with placing unassigned logon packets to the
		//first unauthenticated process we find
		auto it = clients.begin();
		for(; it != clients.end(); it++)
			if (!it->second->isLoggedIn)
			{
				it->second->rawHexPackets.push_back(pkt);
				return;
			}

		add_metalog_update("Warning: Dropped packet with no associated PID", 0);
	
	}
	else
	{
		auto it = clients.find(pkt->pid);
		if (it != clients.end())
		{
			it->second->rawHexPackets.push_back(pkt);
		}
	}
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
	ui.ptHexPane->clear();

	vector <UI_RAWHEX_PKT *> examplepkts = clients.begin()->second->rawHexPackets;
	for (auto pktIt = examplepkts.begin(); pktIt != examplepkts.end(); pktIt++)
	{
		UI_RAWHEX_PKT *pkt = *pktIt;
		handle_raw_packet_data(pkt);
	}
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