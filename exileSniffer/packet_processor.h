#pragma once
#include "stdafx.h"
#include "packet_capture_thread.h"
#include "key_grabber_thread.h"
#include "gameDataStore.h"

enum eDecodingErr{ eNoErr, eErrUnderflow, 
	eBadPacketID, ePktIDUnimplemented, eAbandoned};


class STREAMDATA {
public:
	CryptoPP::Salsa20::Encryption toLoginSalsa, fromLoginSalsa;
	CryptoPP::Salsa20::Encryption fromGameSalsa, toGameSalsa;
	unsigned long packetCount = 0;
	KEYDATA *workingRecvKey = NULL;
	KEYDATA *workingSendKey = NULL;
	unsigned short lastPktID = 0;
};

class packet_processor :
	public base_thread
{
public:

	packet_processor(key_grabber_thread *keyGrabPtr, SafeQueue<UI_MESSAGE>* uiq, gameDataStore& ggpkRef)
	{
		keyGrabber = keyGrabPtr; uiMsgQueue = uiq; ggpk = &ggpkRef;
	}
	~packet_processor() {};

private:
	UIDecodedPkt * testpk;

	void main_loop();

	void init_packetDeserialisers();

	bool process_packet_loop();
	void handle_patch_data(byte* data);
	void handle_login_data(byte* data);
	bool handle_game_data(byte* data);

	void handle_packet_from_loginserver(byte* data, unsigned int dataLen);
	void handle_packet_to_loginserver(byte* data, unsigned int dataLen);
	void handle_packet_from_patchserver(byte* data, unsigned int dataLen);
	void handle_packet_to_patchserver(byte* data, unsigned int dataLen);
	void handle_packet_from_gameserver(byte* data, unsigned int dataLen, long long timems);
	void handle_packet_to_gameserver(byte* data, unsigned int dataLen, long long timems);


	inline void consume_add_byte(std::wstring name, UIDecodedPkt *uipkt) {	uipkt->add_byte(name, consume_Byte());}
	inline void consume_add_word(std::wstring name, UIDecodedPkt *uipkt) { uipkt->add_word(name, consumeUShort()); }
	inline void consume_add_dword(std::wstring name, UIDecodedPkt *uipkt) { uipkt->add_dword(name, consume_DWORD()); }
	inline void consume_add_word_ntoh(std::wstring name, UIDecodedPkt *uipkt) { uipkt->add_word(name, ntohs(consumeUShort())); }
	inline void consume_add_dword_ntoh(std::wstring name, UIDecodedPkt *uipkt) { uipkt->add_dword(name, ntohl(consume_DWORD())); }

	void deserialise_SRV_PKT_ENCAPSULATED(UIDecodedPkt *);
	void deserialise_CLI_CHAT_MSG_ITEMS(UIDecodedPkt *);
	void deserialise_CLI_CHAT_MSG(UIDecodedPkt *);
	void deserialise_CLI_CHAT_COMMAND(UIDecodedPkt *);
	void deserialise_SRV_CHAT_MESSAGE(UIDecodedPkt *);
	void deserialise_SRV_SERVER_MESSAGE(UIDecodedPkt *);
	void deserialise_CLI_LOGGED_OUT(UIDecodedPkt *);
	void deserialise_CLI_PING_CHALLENGE(UIDecodedPkt *);
	void deserialise_SRV_PING_RESPONSE(UIDecodedPkt *);		
	void deserialise_SRV_AREA_INFO(UIDecodedPkt*);

	void deserialise_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt*);
	void deserialise_SRV_UNK_0x13(UIDecodedPkt *);
	void deserialise_SRV_PLAYER_ITEMS(UIDecodedPkt*);
	void deserialise_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt *);
	void deserialise_CLI_ACTION_PREDICTIVE(UIDecodedPkt *);
	void deserialise_SRV_TRANSFER_INSTANCE(UIDecodedPkt *);
	void deserialise_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt *);
	void deserialise_CLI_PICKUP_ITEM(UIDecodedPkt *);
	void deserialise_CLI_PLACE_ITEM(UIDecodedPkt *);
	void deserialise_CLI_REMOVE_SOCKET(UIDecodedPkt *);
	void deserialise_CLI_INSERT_SOCKET(UIDecodedPkt *);

	void deserialise_CLI_LEVEL_SKILLGEM(UIDecodedPkt *);
	void deserialise_CLI_UNK_0x20(UIDecodedPkt *);
	void deserialise_CLI_SKILLPOINT_CHANGE(UIDecodedPkt *); 
	void deserialise_CLI_CHOSE_ASCENDANCY(UIDecodedPkt *);

	void deserialise_CLI_CANCEL_BUF(UIDecodedPkt *);
	void deserialise_CLI_UNK_0x2c(UIDecodedPkt *);
	void deserialise_CLI_SET_HOTBARSKILL(UIDecodedPkt *);
	void deserialise_SRV_SKILL_SLOTS_LIST(UIDecodedPkt *);
	
	void deserialise_CLI_USE_BELT_SLOT(UIDecodedPkt *);
	void deserialise_CLI_USE_ITEM(UIDecodedPkt *);
	void deserialise_CLI_UNK_0x41(UIDecodedPkt *);

	void deserialise_CLI_SELECT_NPC_DIALOG(UIDecodedPkt *uipkt);
	void deserialise_SRV_SHOW_NPC_DIALOG(UIDecodedPkt *uipkt);
	void deserialise_CLI_CLOSE_NPC_DIALOG(UIDecodedPkt *uipkt);

	void deserialise_SRV_OPEN_UI_PANE(UIDecodedPkt *);

	void deserialise_CLI_SEND_PARTY_INVITE(UIDecodedPkt *);

	void deserialise_CLI_TRY_JOIN_PARTY(UIDecodedPkt *);
	void deserialise_CLI_DISBAND_PUBLIC_PARTY(UIDecodedPkt *);
	void deserialise_CLI_CREATE_PUBLICPARTY(UIDecodedPkt *);
	void deserialise_CLI_UNK_x56(UIDecodedPkt *);
	void deserialise_CLI_GET_PARTY_DETAILS(UIDecodedPkt*);
	void deserialise_SRV_FRIENDSLIST(UIDecodedPkt *);

	void deserialise_SRV_PARTY_DETAILS(UIDecodedPkt *);
	void deserialise_SRV_PARTY_ENDED(UIDecodedPkt *uipkt);
	void deserialise_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt *);
	void deserialise_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt *);

	void deserialise_CLI_MOVE_ITEM_PANE(UIDecodedPkt *);

	void deserialise_SRV_CREATE_ITEM(UIDecodedPkt *);
	void deserialise_SRV_SLOT_ITEMSLIST(UIDecodedPkt *);
	void deserialise_UNK_MESSAGE_0x70(UIDecodedPkt *);
	void deserialise_UNK_MESSAGE_0x73(UIDecodedPkt *);
	void deserialise_CLI_SET_STATUS_MESSAGE(UIDecodedPkt *);

	void deserialise_CLI_SWAPPED_WEAPONS(UIDecodedPkt *);

	void deserialise_CLI_SKILLPANE_ACTION(UIDecodedPkt *);

	void deserialise_SRV_SKILLPANE_DATA(UIDecodedPkt *);

	void deserialise_SRV_UNK_0x92(UIDecodedPkt *uipkt);

	void deserialise_CLI_MICROTRANSACTION_SHOP_ACTION(UIDecodedPkt *);
	void deserialise_SRV_MICROTRANSACTION_SHOP_DETAILS(UIDecodedPkt *);
	void deserialise_SRV_UNK_A3(UIDecodedPkt *);
	void deserialise_SRV_CHAT_CHANNEL_ID(UIDecodedPkt *);

	void deserialise_CLI_GUILD_CREATE(UIDecodedPkt *);

	void deserialise_CLI_PACKET_EXIT(UIDecodedPkt *);
	void deserialise_CLI_PACKET_EXIT_2(UIDecodedPkt *);
	void deserialise_CLI_DUEL_CHALLENGE(UIDecodedPkt *);
	void deserialise_SRV_DUEL_RESPONSE(UIDecodedPkt *);
	void deserialise_SRV_DUEL_CHALLENGE(UIDecodedPkt *);

	void deserialise_CLI_UNK_0xC7(UIDecodedPkt *);

	void deserialise_SRV_UNK_0xCA(UIDecodedPkt *);

	void deserialise_SRV_UNK_0xD5(UIDecodedPkt *);

	void deserialise_CLI_USED_SKILL(UIDecodedPkt *);

	void deserialise_CLI_CLICK_OBJ(UIDecodedPkt *);
	void deserialise_CLI_MOUSE_HELD(UIDecodedPkt *);
	void deserialise_CLI_MOUSE_RELEASE(UIDecodedPkt *);

	void deserialise_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt *);

	void deserialise_SRV_UNK_0xE6(UIDecodedPkt *);

	void deserialise_SRV_OBJ_REMOVED(UIDecodedPkt *);
	void deserialise_SRV_MOBILE_START_SKILL(UIDecodedPkt *);
	void deserialise_SRV_MOBILE_FINISH_SKILL(UIDecodedPkt *);

	void deserialise_SRV_MOBILE_UNK_0xee(UIDecodedPkt *);
	void deserialise_SRV_MOBILE_UNK_0xef(UIDecodedPkt *);

	void deserialise_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt *);

	void deserialise_SRV_STAT_CHANGED(UIDecodedPkt *);
	void deserialise_SRV_UNK_0xf2(UIDecodedPkt *);
	void deserialise_SRV_UNK_0xf3(UIDecodedPkt *);
	void deserialise_SRV_START_EFFECT(UIDecodedPkt *);
	void deserialise_SRV_END_EFFECT(UIDecodedPkt *);

	void deserialise_CLI_REQUEST_PLAYERID(UIDecodedPkt *);
	void deserialise_SRV_NOTIFY_PLAYERID(UIDecodedPkt *);
	void deserialise_SRV_UNKNOWN_0x111(UIDecodedPkt *);
	void deserialise_SRV_UNKNOWN_0x118(UIDecodedPkt *);
	void deserialise_CLI_OPTOUT_TUTORIALS(UIDecodedPkt *); 
	void deserialise_SRV_SHOW_ENTERING_MSG(UIDecodedPkt *uipkt);
	void deserialise_SRV_HEARTBEAT(UIDecodedPkt *uipkt);
	void deserialise_SRV_ADD_OBJECT(UIDecodedPkt *uipkt);

	void SRV_ADD_OBJ_decode_character(UIDecodedPkt *uipkt, size_t objBlobDataLen);

	void deserialise_SRV_UPDATE_OBJECT(UIDecodedPkt *uipkt);
	void deserialise_SRV_IDNOTIFY_0x137(UIDecodedPkt *uipkt);
	

	UINT8 consume_Byte();
	UINT16 consumeUShort();
	UINT32 consume_DWORD();
	std::wstring consumeWString(size_t bytesLength);
	void consume_blob(ushort byteCount);
	void consume_blob(ushort byteCount, vector <byte>& blobBuf);
	void abandon_processing();
	UINT32 customSizeByteGet();
	INT32 customSizeByteGet_signed();
	void rewind_buffer(size_t countBytes);
	void restore_buffer();

	WValue get_pairs_strings_blob(UIDecodedPkt *uipkt);

	bool sanityCheckPacketID(unsigned short pktID);
	void emit_decoding_err_msg(unsigned short msgID, unsigned short lastMsgID);
	void continue_gamebuffer_next_packet();


private:
	vector<UIDecodedPkt *> deserialisedPkts;
	std::deque< std::vector<byte>> pendingPktQueue;
	gameDataStore* ggpk = NULL;

	key_grabber_thread * keyGrabber;

	std::map<networkStreamID, STREAMDATA> streamDatas;
	map<unsigned long, std::pair<KEYDATA *, KEYDATA *> > pendingGameserverKeys;
	map<networkStreamID, unsigned long> connectionIDStreamIDmapping;
	SafeQueue<UI_MESSAGE>* uiMsgQueue;

	typedef void (packet_processor::*deserialiser)(UIDecodedPkt *);
	map<unsigned short, deserialiser> packetDeserialisers;

	//used for continuing multi-packet messages
	networkStreamID currentMsgStreamID;
	bool currentMsgIncoming;

	HANDLE patchpipe = NULL;
	HANDLE loginpipe = NULL;
	HANDLE gamepipe = NULL;

	DWORD activeClientPID = 0;
	vector<byte> *decryptedBuffer = NULL;
	size_t remainingDecrypted = 0, decryptedIndex = 0;

	eDecodingErr errorFlag = eDecodingErr::eNoErr;
	unsigned long errorCount = 0;

	bool currentMsgMultiPacket = false;
	struct {
		bool active = false;
		size_t savedIndex;
		size_t savedRemaining;
	} restorePoint;
};

