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


#define HEADER_SECTION_TIME 0
#define HEADER_SECTION_SENDER 1
#define HEADER_SECTION_MSGID 2
#define HEADER_SECTION_SUMMARY 3

struct RAW_FILTERS {
	bool filterIncoming = false;
	bool filterOutgoing = false;
	bool filterGame = false;
	bool filterLogin = false;
	vector <pair<short, streamType>> packets;
};

class UI_DECODED_LIST_ENTRY
{
	public:
		UI_DECODED_LIST_ENTRY(UIDecodedPkt& pktobj) {
			msTime = pktobj.time_processed_ms();
			pktID = pktobj.messageID;
			flags = pktobj.streamFlags;
			failedDecode = pktobj.decodeError();
		}

		QString dayMonTime() { return QString::fromStdWString(epochms_to_timestring(msTime)); }
		QString floatSeconds(long long start) { return QString::number((msTime - start) / 1000.0, 'd', 4); }
		QString hexPktID() { return "0x" + QString::number(pktID, 16); }
		QString decPktID() { return QString::number(pktID); }
		QString sender() { return ((flags & PKTBIT_INBOUND) ? "Server" : "Client"); }
		byte pktFlags() { return flags; }
		bool badDecode() { return failedDecode; }

	public:
		QString summary;
		bool filtered = false;

	private:
		bool failedDecode;
		byte flags;
		long long msTime;
		unsigned short pktID;
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
		void toggleRawAutoScroll(bool state);
		void decodedListClicked();

	private:
		void setup_raw_stream_tab();
		void setup_decoded_messages_tab();
		void init_DecodedPktActioners();
		void start_threads();

		void action_UI_Msg(UI_MESSAGE *msg);
		void add_metalog_update(QString msg, DWORD pid);
		void handle_client_event(DWORD pid, bool isRunning);
		void handle_raw_packet_data(UI_RAWHEX_PKT *pkt);
		void action_undecoded_packet(UIDecodedPkt& decoded);
		void action_decoded_packet(UIDecodedPkt& decoded);

		clientData * get_client(DWORD pid);
		void reprintRawHex();
		void insertRawText(std::string hexdump, std::string asciidump);
		void print_raw_packet(UI_RAWHEX_PKT *pkt);
		bool packet_passes_raw_filter(UI_RAWHEX_PKT *pkt, clientData *client);
		bool packet_passes_decoded_filter(UIDecodedPkt& decoded, clientData *client);
		void updateRawFilterLabel();
		void updateDecodedFilterLabel();
		void addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry);
		void setRowColor(int row, QColor colour);

	private:
		void action_SRV_PKT_ENCAPSULATED(UIDecodedPkt& decobj);
		void action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt& decobj);
		void action_CLI_CHAT_MSG(UIDecodedPkt& decobj);
		void action_CLI_CHAT_COMMAND(UIDecodedPkt& decobj);
		void action_SRV_CHAT_MESSAGE(UIDecodedPkt& decobj);
		void action_SRV_SERVER_MESSAGE(UIDecodedPkt& decobj);
		void action_CLI_LOGGED_OUT(UIDecodedPkt& decobj);
		void action_CLI_PING_CHALLENGE(UIDecodedPkt& decobj);
		void action_CLI_ACTION_PREDICTIVE(UIDecodedPkt& decobj);
		void action_CLI_USE_BELT_SLOT(UIDecodedPkt& decobj);
		void action_CLI_USE_ITEM(UIDecodedPkt& decobj);
		void action_CLI_MOUSE_RELEASE(UIDecodedPkt& decobj);

	private:
		Ui::exileSniffer ui;
		Ui::rawFilterForm rawFiltersFormUI;
		derivedRawFilterForm rawFilterForm;

		unsigned short UIhexPacketsPerRow = 16;

		std::pair <unsigned long, unsigned long> rawCount_Recorded_Filtered;
		std::pair <int, int> decodedCount_Displayed_Filtered;	 //table row index is int
		int decodedErrorPacketCount = 0;

		//RAW_FILTERS rawPacketFilters;

		SafeQueue<UI_MESSAGE> uiMsgQueue; //read by ui thread, written by all others
		map<DWORD, clientData *> clients;


		typedef void (exileSniffer::*actionFunc)(UIDecodedPkt& uiDecodedPktMsg);
		map<unsigned short, actionFunc> decodedPktActioners;

		const long long startMSSinceEpoch = ms_since_epoch();

		packet_capture_thread *packetSniffer;
		key_grabber_thread *keyGrabber;
		packet_processor *packetProcessor;
};
