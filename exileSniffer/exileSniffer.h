#pragma once

#include <QtWidgets/QMainWindow>


#include "packet_capture_thread.h"
#include "key_grabber_thread.h"
#include "packet_processor.h"
#include "uiMsg.h"
#include "clientData.h"

#include "ui_exileSniffer.h"

#include "rawFilterForm.h"
#include "ui_rawfilterform.h"


struct RAW_FILTERS {
	bool filterIncoming = false;
	bool filterOutgoing = false;
	bool filterGame = false;
	bool filterLogin = false;
	vector <pair<short, streamType>> packets;
};

class exileSniffer : public QMainWindow
{
	Q_OBJECT

public:
	exileSniffer(QWidget *parent = Q_NULLPTR);

private slots:
	void read_UI_Q();
	void showRawFiltersDLG() { rawFilterForm.show(); }
	void updateRawFilters() { std::cout << "yay"<<std::endl; }
	void rawBytesRowChanged(QString arg);
	void toggleRawLineWrap(bool state);

private:
	void action_UI_Msg(UI_MESSAGE *msg);
	void add_metalog_update(QString msg, DWORD pid);
	void handle_client_event(DWORD pid, bool isRunning);
	void handle_raw_packet_data(UI_RAWHEX_PKT *pkt);
	void reprintRawHex();

private:
	Ui::exileSniffer ui;
	Ui::rawFilterForm rawFiltersFormUI;
	derivedRawFilterForm rawFilterForm;

	unsigned short UIhexPacketsPerRow = 16;
	//RAW_FILTERS rawPacketFilters;

	SafeQueue<UI_MESSAGE> uiMsgQueue; //read by ui thread, written by all others
	map<DWORD, clientData *> clients;

	packet_capture_thread *packetSniffer;
	key_grabber_thread *keyGrabber;
	packet_processor *packetProcessor;
};
