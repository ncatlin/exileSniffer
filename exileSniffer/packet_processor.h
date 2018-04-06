#pragma once
#include "stdafx.h"
#include "packet_capture_thread.h"
#include "key_grabber_thread.h"

enum eDecodingErr{ eNoErr, eErrUnderflow, eBadPacketID};


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

	packet_processor(key_grabber_thread *keyGrabPtr, SafeQueue<UI_MESSAGE>* uiq) 
	{ keyGrabber = keyGrabPtr; uiMsgQueue = uiq;}
	~packet_processor() {};

private:
	void main_loop();

	void init_packetDeserialisers();

	bool process_packet_loop();
	void handle_patch_data(std::vector<byte> pkt);
	void handle_login_data(std::vector<byte> pkt);
	void handle_game_data(std::vector<byte> pkt);

	void handle_packet_from_loginserver(networkStreamID streamID, byte* data, unsigned int dataLen);
	void handle_packet_to_loginserver(networkStreamID streamID, byte* data, unsigned int dataLen);
	void handle_packet_from_patchserver(byte* data, unsigned int dataLen);
	void handle_packet_to_patchserver(byte* data, unsigned int dataLen);
	void handle_packet_from_gameserver(networkStreamID streamID, byte* data, unsigned int dataLen);
	void handle_packet_to_gameserver(networkStreamID streamID, byte* data, unsigned int dataLen);

	pkt_SRV_PKT_ENCAPSULATED deserialise_SRV_PKT_ENCAPSULATED();
	pkt_CLI_CHAT_MSG_ITEMS deserialise_CLI_CHAT_MSG_ITEMS();
	pkt_CLI_CHAT_MSG deserialise_CLI_CHAT_MSG();
	pkt_CLI_CHAT_COMMAND deserialise_CLI_CHAT_COMMAND();
	pkt_SRV_CHAT_MESSAGE deserialise_SRV_CHAT_MESSAGE();
	pkt_SRV_SERVER_MESSAGE deserialise_SRV_SERVER_MESSAGE();
	pkt_CLI_LOGGED_OUT deserialise_CLI_LOGGED_OUT();
	pkt_CLI_PING_CHALLENGE deserialise_CLI_PING_CHALLENGE();
	pkt_CLI_ACTION_PREDICTIVE deserialise_CLI_ACTION_PREDICTIVE();
	pkt_CLI_USE_BELT_SLOT deserialise_CLI_USE_BELT_SLOT();
	pkt_CLI_USE_ITEM deserialise_CLI_USE_ITEM();
	pkt_CLI_MOUSE_RELEASE deserialise_CLI_MOUSE_RELEASE();


	byte consumeByte();
	unsigned short consumeUShort();
	unsigned long consumeULong();
	std::wstring consumeWString(size_t bytesLength);

	bool sanityCheckPacketID(unsigned short pktID);
	void emit_decoding_err_msg(unsigned short msgID, unsigned short lastMsgID);

	
	void fillObjCodeMap();
	bool lookup_areaCode(unsigned long code, std::string& result);
	bool lookup_hash(unsigned long hash, std::string& result, std::string& category);

private:
	key_grabber_thread * keyGrabber;
	std::map<networkStreamID, STREAMDATA> streamDatas;
	map<unsigned long, std::pair<KEYDATA *, KEYDATA *> > pendingGameserverKeys;
	map<networkStreamID, unsigned long> connectionIDStreamIDmapping;
	SafeQueue<UI_MESSAGE>* uiMsgQueue;

	typedef decodedPacket (packet_processor::*deserialiser)();
	map<unsigned short, deserialiser> packetDeserialisers;

	HANDLE patchpipe = NULL;
	HANDLE loginpipe = NULL;
	HANDLE gamepipe = NULL;

	DWORD activeClientPID = 0;
	byte *decryptedBuffer = NULL;
	size_t remainingDecrypted = 0, decryptedIndex = 0;
	eDecodingErr errorFlag = eDecodingErr::eNoErr;
	unsigned long errorCount = 0;

	bool unfinishedPacket = false;

	std::map <unsigned long, std::string> gameObjHashes;
	std::map <unsigned long, std::string> monsterHashes;
	std::map <unsigned long, std::string> chestHashes;
	std::map <unsigned long, std::string> characterHashes;
	std::map <unsigned long, std::string> NPCHashes;
	std::map <unsigned long, std::string> petHashes;
	std::map <unsigned long, std::string> itemHashes;

	std::map <unsigned long, std::string> areaCodes;
	std::vector <std::string> monsterVarieties;
};

