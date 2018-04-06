#pragma once
#include "safequeue.h"
#include "decodedPacket.h"

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

class UI_DECODED_PKT : public UI_MESSAGE
{
public:
	UI_DECODED_PKT(DWORD processID, streamType streamServer, bool isIncoming);
	void attachDecodedObj(decodedPacket obj) { decodedobj = obj; };

	streamType stream;
	bool incoming;
	DWORD pid;
	time_t createdtime;
	decodedPacket decodedobj;
};

void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UInotifyClientRunning(DWORD pid, bool running, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIrecordLogin(DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);