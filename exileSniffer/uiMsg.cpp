#include "stdafx.h"
#include "uiMsg.h"
#include "utilities.h"

void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue)
{
	UI_METALOG_MSG *initmsg = new UI_METALOG_MSG;
	initmsg->msgType = uiMsgType::eMetaLog;
	initmsg->stringData = msg;
	initmsg->pid = clientPID;
	uiMsgQueue->addItem(initmsg);
}

void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue)
{
	UIaddLogMsg(QString::fromStdString(msg), clientPID, uiMsgQueue);
}

void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE> *uiMsgQueue)
{
	UIaddLogMsg(QString(msg), clientPID, uiMsgQueue);
}

void UIrecordLogin(DWORD clientPID,  SafeQueue<UI_MESSAGE> *uiMsgQueue)
{
	UI_LOGIN_NOTE *loginmsg = new UI_LOGIN_NOTE;
	loginmsg->msgType = uiMsgType::eLoginNote;
	loginmsg->pid = clientPID;
	uiMsgQueue->addItem(loginmsg);
}


void UInotifyClientRunning(DWORD clientPID, bool running, SafeQueue<UI_MESSAGE> *uiMsgQueue)
{
	UI_CLIENTEVENT_MSG *initmsg = new UI_CLIENTEVENT_MSG;
	initmsg->msgType = uiMsgType::eClientEvent;
	initmsg->running = running;
	initmsg->pid = clientPID;
	uiMsgQueue->addItem(initmsg);
}

UI_RAWHEX_PKT::UI_RAWHEX_PKT(DWORD processID, streamType streamServer, bool isIncoming) 
{
	createdtime = time(0);
	pid = processID;
	incoming = isIncoming;
	stream = streamServer;
	msgType = uiMsgType::ePacketHex;
	pktBytes.clear();
}

void UI_RAWHEX_PKT::setData(byte *source, size_t length) 
{
	if (!length) return;

	pktBytes.insert(pktBytes.end(), &source[0], &source[length]);
	assert(pktBytes.size() == length);

	if (length >= 2)
		startBytes = getUshort(source);
	else 
		startBytes = source[0];
}

