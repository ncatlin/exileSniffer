#pragma once
#include "safequeue.h"
#include "utilities.h"

#define PKTBIT_OUTBOUND 0x1
#define PKTBIT_INBOUND 0x2
#define PKTBIT_LOGINSERVER 0x4
#define PKTBIT_GAMESERVER 0x8
#define PKTBIT_PATCHSERVER 0x10

enum streamType { eLogin = 'L', eGame = 'G', ePatch = 'P', eNone = 0 };

typedef rapidjson::GenericValue<rapidjson::UTF16<> > WValue;
enum uiMsgType {eMetaLog, eClientEvent, eStreamEvent, eSniffingStarted,
	eLoginNote, ePacketHex, eDecodedPacket, eKeyUpdate, eIVUpdate, eCryptIterUpdate};

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
	int totalClients = 0;
	int totalScanning = 0;
};

enum eStreamState{ eStreamStarted, eStreamEnded, eStreamLoggingIn, eStreamTransitionGame, 
	eStreamTransitionLogin, eStreamFailed, eStreamDecrypting};
class UI_STREAMEVENT_MSG : public UI_MESSAGE
{
public:
	int streamID = -1;
	eStreamState state;
};

class UI_LOGIN_NOTE: public UI_MESSAGE
{
public:
	DWORD pid;
	streamType server;
};

class UI_SNIFF_NOTE : public UI_MESSAGE
{
public:
	QString iface;
	bool state;
};

class UI_KEY : public UI_MESSAGE
{
public:
	std::vector<byte> key;
};

class UI_IV : public UI_MESSAGE
{
public:
	std::vector<byte> sendIV;
	std::vector<byte> recvIV;
};

class UI_CRYPTITER : public UI_MESSAGE
{
public:
	std::vector<byte> sendIter;
	std::vector<byte> recvIter;
};


class UI_RAWHEX_PKT : public UI_MESSAGE
{
public:
	UI_RAWHEX_PKT(DWORD processID, streamType streamServer, bool isIncoming);
	void setData(vector<byte> *source);
	void setErrorIndex(unsigned short idx) {
		decodeFailed = true;
		failLocation = idx;
	}

	time_t createdtime;	
	unsigned long sequenceID;
	DWORD pid;
	streamType stream;
	bool incoming;

	vector<byte>* pktBytes;
	unsigned short startBytes;

	bool decodeFailed = false;
	unsigned short failLocation = 0;
};

class UIDecodedPkt : public UI_MESSAGE
{
public:
	UIDecodedPkt(DWORD processID, streamType streamServerType,int nwkStream, bool isIncoming, long long timeSeen);
	void toggle_payload_operations(bool state) { payloadOperations = state; }

	void add_dword(std::wstring name, DWORD dwordfield);
	void add_word(std::wstring name, ushort ushortfield);
	void add_byte(std::wstring name, byte bytefield);
	void add_wstring(std::wstring name, std::wstring stringfield);
	void add_array(std::wstring name, WValue value);
	rapidjson::GenericDocument<rapidjson::UTF16<> >& getJSON() {	return jsn;	}

	std::wstring get_wstring(std::wstring name);
	UINT32 get_UInt32(std::wstring name);
	UINT64 get_UInt64(std::wstring name);
	
	void setBuffer(vector<byte> *buf) { originalbuf = buf; }
	void setStartOffset(unsigned short off) { bufferOffsets.first = off; }
	void setEndOffset(unsigned short off) { bufferOffsets.second = off; }
	void setFailedDecode() { failedDecode = true; }
	void setAbandoned() { abandoned = true; }
	bool decodeError() { return failedDecode; }
	bool wasAbandoned() { return abandoned; }
	long long time_processed_ms() { return mstime; }
	DWORD getClientProcessID() { return PID; }
	int getStreamID() { return nwkstreamID; }
	ushort getMessageID() { return messageID; }
	void set_validate_MessageID(ushort msgID, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
	streamType getStreamType() { return streamServer; }
	bool isIncoming() { return incoming; }

	static rapidjson::GenericValue<rapidjson::UTF8<>> *loginMessageTypes;
	static rapidjson::GenericValue<rapidjson::UTF8<>> *gameMessageTypes;

public:
	int nwkstreamID;
	vector<byte> *originalbuf = NULL;
	std::pair<ushort, ushort> bufferOffsets;

	rapidjson::GenericDocument<rapidjson::UTF16<> > jsn;
	WValue* payload = NULL;

private:
	ushort messageID;
	DWORD PID;
	streamType streamServer;
	bool incoming;
	bool failedDecode = false;
	bool abandoned = false;
	bool payloadOperations = false;
	long long mstime;
};

Q_DECLARE_METATYPE(UIDecodedPkt *);

void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIsniffingStarted(QString iface, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UInotifyClientRunning(DWORD clientPID, bool running, int activeClients, 
	int scanningClients, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIrecordLogin(DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UInotifyStreamState(int streamID, eStreamState state, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIdisplaySalsaKey(std::vector<byte> key, SafeQueue<UI_MESSAGE *> *uiMsgQueue); 
void UIUpdateSendIV(std::vector<byte> sendIV, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIUpdateRecvIV(std::vector<byte> recvIV, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIUpdateSendIter(std::vector<byte> sendIter, SafeQueue<UI_MESSAGE *> *uiMsgQueue);
void UIUpdateRecvIter(std::vector<byte> recvIter, SafeQueue<UI_MESSAGE *> *uiMsgQueue);