#pragma once
#include "safequeue.h"


enum streamType { eLogin = 'L', eGame = 'G', ePatch = 'P', eNone = 0 };
enum uiMsgType {eMetaLog, eClientEvent, eLoginNote, ePacketHex};

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
	void setData(byte *source, size_t length);


	streamType stream;
	bool incoming;
	DWORD pid;
	time_t createdtime;
	std::vector<byte> pktBytes;
	short startBytes;
};


void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UInotifyClientRunning(DWORD pid, bool running, SafeQueue<UI_MESSAGE> *uiMsgQueue);
void UIrecordLogin(DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue);