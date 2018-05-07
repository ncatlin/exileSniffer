#pragma once

#include <QtWidgets/QMainWindow>


#include "packet_capture_thread.h"
#include "key_grabber_thread.h"
#include "packet_processor.h"
#include "uiMsg.h"
#include "clientData.h"
#include "gameDataStore.h"

#include "ui_exileSniffer.h"

#include "filterForm.h"
#include "ui_rawfilterform.h"
#include <fstream>

#define DECODED_SECTION_TIME 0
#define DECODED_SECTION_SENDER 1
#define DECODED_SECTION_MSGID 2
#define DECODED_SECTION_SUMMARY 3


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
			originalbuf = pktobj.originalbuf;
			bufferOffsets = pktobj.bufferOffsets;
			streamID = pktobj.streamID();
		}

		QString dayMonTime() { return QString::fromStdWString(epochms_to_timestring(msTime)); }
		QString floatSeconds(long long start) { return QString::number((msTime - start) / 1000.0, 'd', 4); }
		QString hexPktID() { return "0x" + QString::number(pktID, 16); }
		QString decPktID() { return QString::number(pktID); }
		QString sender();
		byte pktFlags() { return flags; }
		bool badDecode() { return failedDecode; }
		std::pair<vector<byte> *, ushort> bytesBuf() {
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
		int streamID;
		vector<byte> *originalbuf;
		std::pair <ushort, ushort> bufferOffsets;
};



class exileSniffer : public QMainWindow
{
	Q_OBJECT

	public:
		exileSniffer(QWidget *parent = Q_NULLPTR);

	
	private slots:
		void read_UI_Q();

		void showRawFiltersDLG() { filterFormObj.isHidden() ? filterFormObj.show() : filterFormObj.hide(); }
		void refreshFilters();

		void rawBytesRowChanged(QString arg);
		void toggleRawLineWrap(bool state);
		void toggleRawAutoScroll(bool state);
		void decodedListClicked();
		void decodedCellActivated(int, int);
		void decodedTableMenuRequest(QPoint);
		void copySelected();
		void filterSelected();
		void stopDecrypting();
		void resumeScanningEvent();
		void settingsSelectionChanged(); 
		void hashUtilInput();

	private:
		void setup_settings_tab();
		void save_settings();
		void setup_raw_stream_tab();
		void setup_decoded_messages_tab();
		void setup_decryption_tab();
		void setLabelActive(QLabel *lab, bool state);
		void set_keyEx_scanning_count(int total, int scanning);
		void updateStreamStateWidget();
		void setStateDecrypting(int streamID);
		void setStateNotDecrypting(); 
		void action_ended_stream(int streamID);
		void handle_stream_event(UI_STREAMEVENT_MSG *streamNote);
		void handle_client_event(UI_CLIENTEVENT_MSG *cliEvtMsg);
		void output_hex_to_file(UI_RAWHEX_PKT *pkt, std::ofstream& file);
		void output_hex_to_pane(UI_RAWHEX_PKT *pkt);

		void init_gamePkt_Actioners();
		void init_loginPkt_Actioners();

		void start_threads();
		void initFilters(); 

		void action_UI_Msg(UI_MESSAGE *msg);
		void add_metalog_update(QString msg, DWORD pid);
		void handle_raw_packet_data(UI_RAWHEX_PKT *pkt);
		void action_undecoded_packet(UIDecodedPkt& decoded);
		void action_decoded_packet(UIDecodedPkt& decoded);
		void action_decoded_game_packet(UIDecodedPkt& decoded);
		void action_decoded_login_packet(UIDecodedPkt& decoded);
		

		clientHexData * get_clientdata(DWORD pid);
		void reprintRawHex();
		void insertRawText(std::string hexdump, std::string asciidump);
		void addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry, UIDecodedPkt *obj, bool isNewEntry = true);
		void setRowColor(int row, QColor colour);

		bool packet_passes_decoded_filter(ushort msgID);
		void updateRawFilterLabel();
		void updateDecodedFilterLabel();

		QString stringify_eventslist(WValue &eventlist);
		QString stringify_eventslist_2(WValue &eventlist);
		
		
	private:

		void action_LOGIN_CLI_KEEP_ALIVE(UIDecodedPkt&, QString*);
		void action_LOGIN_EPHERMERAL_PUBKEY(UIDecodedPkt&, QString *);
		void action_LOGIN_CLI_AUTH_DATA(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_UNK0x4(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CHANGE_PASSWORD(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_DELETE_CHARACTER(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CHARACTER_SELECTED(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_NOTIFY_GAMESERVER(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CREATED_CHARACTER(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_CHAR_LIST(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_FINAL_PKT(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_REQUEST_RACE_DATA(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_LEAGUE_LIST(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_REQUEST_LEAGUES(UIDecodedPkt&, QString*);

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
		void action_SRV_UNK_0x13(UIDecodedPkt&, QString *);
		void action_SRV_PLAYER_ITEMS(UIDecodedPkt&, QString*);
		void action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_ACTION_PREDICTIVE(UIDecodedPkt&, QString*);
		void action_SRV_TRANSFER_INSTANCE(UIDecodedPkt& obj, QString *analysis);
		void action_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt&, QString*);
		void action_CLI_PICKUP_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_PLACE_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_DROP_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_REMOVE_SOCKET(UIDecodedPkt&, QString*);
		void action_CLI_INSERT_SOCKET(UIDecodedPkt&, QString*);

		void action_CLI_LEVEL_SKILLGEM(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x20(UIDecodedPkt&, QString*);
		void action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt&, QString*);

		void action_CLI_CHOSE_ASCENDANCY(UIDecodedPkt&, QString*);

		void action_CLI_CANCEL_BUF(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x2c(UIDecodedPkt&, QString*);
		void action_CLI_SELECT_MAPTRAVEL(UIDecodedPkt&, QString*);
		void action_CLI_SET_HOTBARSKILL(UIDecodedPkt&, QString*);
		void action_SRV_SKILL_SLOTS_LIST(UIDecodedPkt&, QString*);
		void action_CLI_REVIVE_CHOICE(UIDecodedPkt&, QString*);
		void action_SRV_YOU_DIED(UIDecodedPkt&, QString*);

		void action_CLI_USE_BELT_SLOT(UIDecodedPkt&, QString*);
		void action_CLI_USE_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x41(UIDecodedPkt&, QString*);

		void action_CLI_SELECT_NPC_DIALOG(UIDecodedPkt&, QString*);
		void action_SRV_SHOW_NPC_DIALOG(UIDecodedPkt&, QString*);
		void action_CLI_CLOSE_NPC_DIALOG(UIDecodedPkt&, QString*);

		void action_SRV_OPEN_UI_PANE(UIDecodedPkt&, QString*);

		void action_CLI_SEND_PARTY_INVITE(UIDecodedPkt&, QString*);

		void action_CLI_TRY_JOIN_PARTY(UIDecodedPkt&, QString*);
		void action_CLI_DISBAND_PUBLIC_PARTY(UIDecodedPkt&, QString*);
		void action_CLI_CREATE_PUBLICPARTY(UIDecodedPkt&, QString*);
		void action_CLI_UNK_x56(UIDecodedPkt&, QString*);
		void action_CLI_GET_PARTY_DETAILS(UIDecodedPkt&, QString*);
		void action_SRV_FRIENDSLIST(UIDecodedPkt&, QString*);

		void action_SRV_PARTY_DETAILS(UIDecodedPkt&, QString*);
		void action_SRV_PARTY_ENDED(UIDecodedPkt&, QString *);
		void action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt&, QString*);
		void action_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt&, QString*);

		void action_CLI_MOVE_ITEM_PANE(UIDecodedPkt&, QString*);

		void action_CLI_CONFIRM_SELL(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x67(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x68(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x6c(UIDecodedPkt&, QString*);
		void action_SRV_CREATE_ITEM(UIDecodedPkt&, QString*);
		void action_SRV_SLOT_ITEMSLIST(UIDecodedPkt&, QString*);
		void action_UNK_MESSAGE_0x70(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x71(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x72(UIDecodedPkt&, QString*);
		void action_UNK_MESSAGE_0x73(UIDecodedPkt&, QString*);
		void action_CLI_SET_STATUS_MESSAGE(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x75(UIDecodedPkt&, QString*);

		void action_CLI_SWAPPED_WEAPONS(UIDecodedPkt&, QString*);

		void action_SRV_PVP_MATCHLIST(UIDecodedPkt&, QString*);
		void action_SRV_EVENTSLIST(UIDecodedPkt&, QString*);

		void action_CLI_SKILLPANE_ACTION(UIDecodedPkt&, QString*);

		void action_SRV_SKILLPANE_DATA(UIDecodedPkt&, QString*);
		void action_SRV_UNK_POSITION_LIST(UIDecodedPkt&, QString*);

		void action_CLI_MICROTRANSACTION_SHOP_ACTION(UIDecodedPkt&, QString*);
		void action_SRV_MICROTRANSACTION_SHOP_DETAILS(UIDecodedPkt&, QString*);
		void action_SRV_UNK_A3(UIDecodedPkt&, QString*);

		void action_SRV_CHAT_CHANNEL_ID(UIDecodedPkt&, QString*);

		void action_SRV_UNK_A5(UIDecodedPkt&, QString*);

		void action_SRV_GUILD_MEMBER_LIST(UIDecodedPkt&, QString*);

		void action_CLI_GUILD_CREATE(UIDecodedPkt&, QString*);


		void action_CLI_PACKET_EXIT(UIDecodedPkt&, QString*);
		void action_SRV_LOGINSRV_CRYPT(UIDecodedPkt&, QString*);
		void action_CLI_DUEL_CHALLENGE(UIDecodedPkt&, QString*);
		void action_SRV_DUEL_RESPONSE(UIDecodedPkt&, QString*);
		void action_SRV_DUEL_CHALLENGE(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0xC6(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0xC7(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xCA(UIDecodedPkt&, QString*);

		void action_SRV_EVENTSLIST_2(UIDecodedPkt&, QString*);

		void action_CLI_USED_SKILL(UIDecodedPkt&, QString*);

		void action_CLI_CLICK_OBJ(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_HELD(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_RELEASE(UIDecodedPkt&, QString*);

		void action_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xE6(UIDecodedPkt&, QString*);	
		void action_SRV_OBJ_REMOVED(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_START_SKILL(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_FINISH_SKILL(UIDecodedPkt&, QString*);

		void action_SRV_MOBILE_UNK_0xee(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_UNK_0xef(UIDecodedPkt&, QString*);

		void action_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt&, QString*);
		void action_SRV_STAT_CHANGED(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf2(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf3(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xf5(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xf7(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf8(UIDecodedPkt&, QString*);

		void action_SRV_START_BUFF(UIDecodedPkt&, QString*);
		void action_SRV_END_EFFECT(UIDecodedPkt&, QString*);

		void action_SRV_EVENT_TRIGGERED(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x106(UIDecodedPkt&, QString*); 
		
		void action_SRV_UNK_0x108(UIDecodedPkt&, QString*);

		void action_CLI_REQUEST_PLAYERID(UIDecodedPkt&, QString *);
		void action_SRV_NOTIFY_PLAYERID(UIDecodedPkt&, QString *);

		void action_SRV_UNKNOWN_0x111(UIDecodedPkt&, QString*);
		void action_SRV_UNKNOWN_0x118(UIDecodedPkt&, QString*);
		void action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt&, QString*);
		void action_SRV_BESTIARY_CAPTIVES(UIDecodedPkt&, QString*);
		void action_CLI_OPEN_BESTIARY(UIDecodedPkt&, QString*);
		void action_SRV_BESTIARY_UNLOCKED_LIST(UIDecodedPkt&, QString*);
		void action_SRV_SHOW_ENTERING_MSG(UIDecodedPkt&, QString*);
		void action_SRV_HEARTBEAT(UIDecodedPkt&, QString*);
		void action_SRV_ADD_OBJECT(UIDecodedPkt&, QString*);
		void action_SRV_UPDATE_OBJECT(UIDecodedPkt&, QString*);
		void action_SRV_IDNOTIFY_0x137(UIDecodedPkt&, QString*);
		
	private:
		std::ofstream outfile;
		Ui::exileSniffer ui;
		Ui::rawFilterForm rawFiltersFormUI;
		filterForm filterFormObj;

		QSettings *settings = new QSettings("ExileSniffer", "Settings");
		bool doLogging = true, doPipe = true;
		QString pipeName;
		QDir logDir;

		std::pair <unsigned long, unsigned long> rawCount_Recorded_Filtered;
		std::pair <int, int> decodedCount_Displayed_Filtered;	 //table row index is int
		int decodedErrorPacketCount = 0;
		bool refreshingFilters = false;
		

		unsigned short UIhexPacketsPerRow = 16;

		SafeQueue<UI_MESSAGE> uiMsgQueue; //read by ui thread, written by all others
		map<DWORD, clientHexData *> clients;
		map<int, eStreamState> streamStates;
		//id of an ending stream if we expect a new one soon
		int transitionStream = -1; 
		int latestDecryptingStream = -1;
		std::pair<int, int> active_total_ClientScanCount = make_pair(0,0);

		typedef void (exileSniffer::*actionFunc)(UIDecodedPkt&, QString*);
		map<unsigned short, actionFunc> gamePktActioners;
		map<unsigned short, actionFunc> loginPktActioners;
		
		std::vector<std::pair<UI_DECODED_LIST_ENTRY, UIDecodedPkt *>> decodedListEntries;

		const long long startMSSinceEpoch = ms_since_epoch();
		bool activeDecryption = false;

private:
	gameDataStore ggpk;
	
private:
	packet_capture_thread* packetSniffer;
	key_grabber_thread* keyGrabber;
	packet_processor* packetProcessor;
};
