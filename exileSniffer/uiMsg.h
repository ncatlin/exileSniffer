#pragma once
#include "safequeue.h"

#define PKTBIT_OUTBOUND 0
#define PKTBIT_INBOUND 0x1
#define PKTBIT_LOGINSERVER 0x2
#define PKTBIT_GAMESERVER 0x4
#define PKTBIT_PATCHSERVER 0x8

enum streamType { eLogin = 'L', eGame = 'G', ePatch = 'P', eNone = 0 };

typedef rapidjson::GenericValue<rapidjson::UTF16<> > WValue;
enum uiMsgType {eMetaLog, eClientEvent, eLoginNote, ePacketHex, eDecodedPacket};

class UI_MESSAGE
{
public:
	uiMsgType msgType;
};

class UI_METALOG_MSG : public UI_MESSAGE
{
public:
	QString stringData;
	DWORD pid;
};

class UI_CLIENTEVENT_MSG : public UI_MESSAGE
{
public:
	bool running = true;
	DWORD pid;
};

class UI_LOGIN_NOTE: public UI_MESSAGE
{
public:
	DWORD pid;
	streamType server;
};

class UI_RAWHEX_PKT : public UI_MESSAGE
{
public:
	UI_RAWHEX_PKT(DWORD processID, streamType streamServer, bool isIncoming);
	void setData(byte *source, unsigned short length);
	void setErrorIndex(unsigned short idx) {
		decodeFailed = true;
		failLocation = idx;
	}

	streamType stream;
	bool incoming;
	DWORD pid;
	time_t createdtime;
	byte* pktBytes;
	unsigned short pktSize = 0;
	short startBytes;
	bool decodeFailed = false;
	unsigned short failLocation = 0;
};

class UIDecodedPkt : public UI_MESSAGE
{
public:
	UIDecodedPkt(DWORD processID, streamType streamServer, byte isIncoming);
	//void attachDecodedObj(decodedPacket obj) { decodedobj = obj; };
	void toggle_payload_operations(bool state) { payloadOperations = state; }

	void add_dword(std::wstring name, DWORD dwordfield);
	void add_word(std::wstring name, ushort ushortfield);
	void add_byte(std::wstring name, byte bytefield);
	void add_wstring(std::wstring name, std::wstring stringfield);

	std::wstring get_wstring(std::wstring name);
	UINT32 get_UInt32(std::wstring name);
	UINT64 get_UInt64(std::wstring name);
	

	void setBuffer(byte *buf) { originalbuf = buf; }
	void setStartOffset(unsigned short off) { bufferOffsets.first = off; }
	void setEndOffset(unsigned short off) { bufferOffsets.second = off; }
	void setFailedDecode() { failedDecode = true; }
	bool decodeError() { return failedDecode; }

	ushort messageID;
	streamType serverStream;
	bool incoming;

private:
	byte *originalbuf = NULL;
	std::pair<ushort, short> bufferOffsets;
	time_t createdtime;
	bool failedDecode = false;
	bool payloadOperations = false;

	rapidjson::GenericDocument<rapidjson::UTF16<> > jsn;
	WValue payload;
};

void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UInotifyClientRunning(DWORD pid, bool running, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIrecordLogin(DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);