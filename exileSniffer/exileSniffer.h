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
			if ((flags & PKTBIT_INBOUND) && (flags & PKTBIT_OUTBOUND))
				std::cout << "errrrrrrr" << std::endl;
			failedDecode = pktobj.decodeError();
			originalbuf = pktobj.originalbuf;
			bufferOffsets = pktobj.bufferOffsets;
		}

		QString dayMonTime() { return QString::fromStdWString(epochms_to_timestring(msTime)); }
		QString floatSeconds(long long start) { return QString::number((msTime - start) / 1000.0, 'd', 4); }
		QString hexPktID() { return "0x" + QString::number(pktID, 16); }
		QString decPktID() { return QString::number(pktID); }
		QString sender() { return ((flags & PKTBIT_INBOUND) ? "Server" : "Client"); }
		byte pktFlags() { return flags; }
		bool badDecode() { return failedDecode; }
		std::pair<byte *, ushort> bytesBuf() { 
			return make_pair(originalbuf + bufferOffsets.first, 
				bufferOffsets.second - bufferOffsets.first);
		}

	public:
		QString summary;
		QString fulltext;
		bool filtered = false;

	private:
		bool failedDecode;
		byte flags;
		long long msTime;
		unsigned short pktID;
		byte *originalbuf;
		std::pair <ushort, ushort> bufferOffsets;
};

class exileSniffer : public QMainWindow
{
	Q_OBJECT

	public:
		exileSniffer(QWidget *parent = Q_NULLPTR);

	private slots:
		void read_UI_Q();
		void showRawFiltersDLG() { rawFilterForm.show(); }
		void updateRawFilters() { std::cout << "y ay"<<std::endl; }
		void rawBytesRowChanged(QString arg);
		void toggleRawLineWrap(bool state);
		void toggleRawAutoScroll(bool state);
		void decodedListClicked();
		void decodedCellActivated(int, int);

	private:
		void setup_raw_stream_tab();
		void setup_decoded_messages_tab();
		void init_DecodedPktActioners();
		void start_threads();
		void fill_gamedata_lists();
		bool lookup_areaCode(unsigned long code, std::string& result);
		bool lookup_hash(unsigned long hash, std::string& result, std::string& category);

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
		void addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry, UIDecodedPkt *obj);
		void setRowColor(int row, QColor colour);

	private:
		void action_SRV_PKT_ENCAPSULATED(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_MSG(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_COMMAND(UIDecodedPkt&, QString*);
		void action_SRV_CHAT_MESSAGE(UIDecodedPkt&, QString*);
		void action_SRV_SERVER_MESSAGE(UIDecodedPkt&, QString*);
		void action_CLI_LOGGED_OUT(UIDecodedPkt&, QString*);
		void action_CLI_PING_CHALLENGE(UIDecodedPkt&, QString*);
		void action_SRV_PING_RESPONSE(UIDecodedPkt&, QString*);
		void action_SRV_AREA_INFO(UIDecodedPkt&, QString*);
		void action_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt&, QString*);
		void action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_ACTION_PREDICTIVE(UIDecodedPkt&, QString*);
		void action_SRV_PLAYER_ITEMS_DATA(UIDecodedPkt&, QString*);
		void action_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt&, QString*);
		void action_CLI_PICKUP_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_PLACE_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_REMOVE_SOCKET(UIDecodedPkt&, QString*);
		void action_CLI_INSERT_SOCKET(UIDecodedPkt&, QString*);
		void action_CLI_LEVEL_SKILLGEM(UIDecodedPkt&, QString*);
		void action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt&, QString*);
		void action_CLI_CANCEL_BUF(UIDecodedPkt&, QString*);
		void action_CLI_SET_HOTBARSKILL(UIDecodedPkt&, QString*);
		void action_CLI_USE_BELT_SLOT(UIDecodedPkt&, QString*);
		void action_CLI_USE_ITEM(UIDecodedPkt&, QString*);

		void action_CLI_UNK_x56(UIDecodedPkt&, QString*);
		void action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt&, QString*);
		void action_CLI_SKILLPANE_ACTION(UIDecodedPkt&, QString*);
		void action_CLI_MICROSTRANSACTIONPANE_ACTION(UIDecodedPkt&, QString*);
		void action_CLI_PACKET_EXIT(UIDecodedPkt&, QString*);
		void action_CLI_USED_SKILL(UIDecodedPkt&, QString*);
		void action_CLI_CLICK_OBJ(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_HELD(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_RELEASE(UIDecodedPkt&, QString*);
		void action_SRV_DISPLAY_BUILTIN_MSG(UIDecodedPkt&, QString*);
		void action_CLI_GUILD_CREATE(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_USED_SKILL(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt&, QString*);
		void action_SRV_HEARTBEAT(UIDecodedPkt&, QString*);
		void action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt&, QString*);

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

		typedef void (exileSniffer::*actionFunc)(UIDecodedPkt&, QString*);
		map<unsigned short, actionFunc> decodedPktActioners;

		const long long startMSSinceEpoch = ms_since_epoch();

private:
	std::map <unsigned long, std::string> gameObjHashes;
	std::map <unsigned long, std::string> monsterHashes;
	std::map <unsigned long, std::string> chestHashes;
	std::map <unsigned long, std::string> characterHashes;
	std::map <unsigned long, std::string> NPCHashes;
	std::map <unsigned long, std::string> petHashes;
	std::map <unsigned long, std::string> itemHashes;
	std::map <unsigned long, std::string> areaCodes;
	std::vector <std::string> monsterVarieties;

private:
	packet_capture_thread * packetSniffer;
	key_grabber_thread *keyGrabber;
	packet_processor *packetProcessor;
};
