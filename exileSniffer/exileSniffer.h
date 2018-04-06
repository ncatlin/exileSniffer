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
	void start_threads();

private slots:
	void read_UI_Q();
	void showRawFiltersDLG() { rawFilterForm.show(); }
	void updateRawFilters() { std::cout << "yay"<<std::endl; }
	void rawBytesRowChanged(QString arg);
	void toggleRawLineWrap(bool state);
	void toggleRawAutoScroll(bool state);

private:
	void init_DecodedPktActioners();
	void action_UI_Msg(UI_MESSAGE *msg);
	void add_metalog_update(QString msg, DWORD pid);
	void handle_client_event(DWORD pid, bool isRunning);
	void handle_raw_packet_data(UI_RAWHEX_PKT *pkt);
	void action_undecoded_packet(UI_DECODED_PKT& decoded);
	void action_decoded_packet(UI_DECODED_PKT& decoded);

	void reprintRawHex();
	void insertRawText(std::string hexdump, std::string asciidump);
	void print_raw_packet(UI_RAWHEX_PKT *pkt);
	bool packet_passes_raw_filter(UI_RAWHEX_PKT *pkt, clientData *client);
	void updateRawFilterLabel();

private:
	void action_CLI_CHAT_MSG(UI_DECODED_PKT& decobj);
	void action_CLI_MOUSE_RELEASE(UI_DECODED_PKT& decobj);

private:
	Ui::exileSniffer ui;
	Ui::rawFilterForm rawFiltersFormUI;
	derivedRawFilterForm rawFilterForm;

	unsigned short UIhexPacketsPerRow = 16;

	unsigned long packetsRecorded = 0;
	unsigned long packetsFiltered = 0;
	//RAW_FILTERS rawPacketFilters;

	SafeQueue<UI_MESSAGE> uiMsgQueue; //read by ui thread, written by all others
	map<DWORD, clientData *> clients;


	typedef void (exileSniffer::*actionFunc)(UI_DECODED_PKT& uiDecodedPktMsg);
	map<unsigned short, actionFunc> decodedPktActioners;


	packet_capture_thread *packetSniffer;
	key_grabber_thread *keyGrabber;
	packet_processor *packetProcessor;
};
