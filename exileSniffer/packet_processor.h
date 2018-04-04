#pragma once
#include "stdafx.h"
#include "packet_capture_thread.h"
#include "key_grabber_thread.h"

class STREAMDATA {
public:
	CryptoPP::Salsa20::Encryption toLoginSalsa, fromLoginSalsa;
	CryptoPP::Salsa20::Encryption fromGameSalsa, toGameSalsa;
	unsigned long packetCount = 0;
	KEYDATA *workingRecvKey = NULL;
	KEYDATA *workingSendKey = NULL;
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

	void fillObjCodeMap();
	bool lookup_areaCode(unsigned long code, std::string& result);
	bool lookup_hash(unsigned long hash, std::string& result, std::string& category);

private:
	key_grabber_thread * keyGrabber;
	std::map<networkStreamID, STREAMDATA> streamDatas;
	map<unsigned long, std::pair<KEYDATA *, KEYDATA *> > pendingGameserverKeys;
	map<networkStreamID, unsigned long> connectionIDStreamIDmapping;
	SafeQueue<UI_MESSAGE>* uiMsgQueue;


	HANDLE patchpipe = NULL;
	HANDLE loginpipe = NULL;
	HANDLE gamepipe = NULL;



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

