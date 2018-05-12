#include "stdafx.h"
#include "uiMsg.h"
#include "utilities.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\writer.h"


void UIaddLogMsg(QString msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_METALOG_MSG *initmsg = new UI_METALOG_MSG;
	initmsg->msgType = uiMsgType::eMetaLog;
	initmsg->stringData = msg;
	initmsg->pid = clientPID;
	uiMsgQueue->addItem(initmsg);
}

void UIaddLogMsg(std::string msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UIaddLogMsg(QString::fromStdString(msg), clientPID, uiMsgQueue);
}

void UIaddLogMsg(const char* msg, DWORD clientPID, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UIaddLogMsg(QString(msg), clientPID, uiMsgQueue);
}

void UIrecordLogin(DWORD clientPID,  SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_LOGIN_NOTE *loginmsg = new UI_LOGIN_NOTE;
	loginmsg->msgType = uiMsgType::eLoginNote;
	loginmsg->pid = clientPID;
	uiMsgQueue->addItem(loginmsg);
}

void UIsniffingStarted(QString iface, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_SNIFF_NOTE *sniffmsg = new UI_SNIFF_NOTE;
	sniffmsg->msgType = uiMsgType::eSniffingStarted;
	sniffmsg->iface = iface;
	uiMsgQueue->addItem(sniffmsg);
}

void UInotifyClientRunning(DWORD clientPID, bool running, int activeClients, int scanningClients, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_CLIENTEVENT_MSG *initmsg = new UI_CLIENTEVENT_MSG;
	initmsg->msgType = uiMsgType::eClientEvent;
	initmsg->running = running;
	initmsg->pid = clientPID;
	initmsg->totalClients = activeClients;
	initmsg->totalScanning = scanningClients;
	uiMsgQueue->addItem(initmsg);
}

void UInotifyStreamState(int streamID, eStreamState state, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_STREAMEVENT_MSG *initmsg = new UI_STREAMEVENT_MSG;
	initmsg->msgType = uiMsgType::eStreamEvent;
	initmsg->state = state;
	initmsg->streamID = streamID;
	uiMsgQueue->addItem(initmsg);
}

void UIdisplaySalsaKey(std::vector<byte> key, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_KEY *initmsg = new UI_KEY;
	initmsg->msgType = uiMsgType::eKeyUpdate;
	initmsg->key = key;
	uiMsgQueue->addItem(initmsg);
}

void UIUpdateSendIV(std::vector<byte> sendIV, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_IV *initmsg = new UI_IV;
	initmsg->msgType = uiMsgType::eIVUpdate;
	initmsg->sendIV = sendIV;
	uiMsgQueue->addItem(initmsg);
}

void UIUpdateRecvIV(std::vector<byte> recvIV, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_IV *initmsg = new UI_IV;
	initmsg->msgType = uiMsgType::eIVUpdate;
	initmsg->recvIV = recvIV;
	uiMsgQueue->addItem(initmsg);
}


void UIUpdateSendIter(std::vector<byte> sendIter, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_CRYPTITER *initmsg = new UI_CRYPTITER;
	initmsg->msgType = uiMsgType::eCryptIterUpdate;
	initmsg->sendIter = sendIter;
	uiMsgQueue->addItem(initmsg);
}

void UIUpdateRecvIter(std::vector<byte> recvIter, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	UI_CRYPTITER *initmsg = new UI_CRYPTITER;
	initmsg->msgType = uiMsgType::eCryptIterUpdate;
	initmsg->recvIter = recvIter;
	uiMsgQueue->addItem(initmsg);
}


UI_RAWHEX_PKT::UI_RAWHEX_PKT(DWORD processID, streamType streamServer, bool isIncoming) 
{
	createdtime = time(0);
	pid = processID;
	incoming = isIncoming;
	stream = streamServer;
	msgType = uiMsgType::ePacketHex;
}

void UI_RAWHEX_PKT::setData(vector<byte> *source)
{
	pktBytes = source;

	if (source->size() < 2) return;


	startBytes = ntohs(getUshort(source->data()));

}

UIDecodedPkt::UIDecodedPkt(DWORD processID, streamType streamServer,int nwkStream, byte isIncoming, long long timeSeen)
{
	jsn.SetObject();

	jsn.AddMember(L"Payload", WValue(rapidjson::kObjectType), jsn.GetAllocator());
	payload = &jsn.FindMember(L"Payload")->value;

	msgType = uiMsgType::eDecodedPacket;
	PID = processID;
	jsn.AddMember(L"ProcessID", (UINT32)processID, jsn.GetAllocator());

	isIncoming = (streamFlags & PKTBIT_INBOUND);
	streamFlags |= isIncoming;
	
	if ((streamFlags & PKTBIT_INBOUND) != 0)
		jsn.AddMember(L"Direction", L"Inbound", jsn.GetAllocator());
	else
		jsn.AddMember(L"Direction", L"Outbound", jsn.GetAllocator());

	switch (streamServer) 
	{
	case streamType::eGame:
		streamFlags |= PKTBIT_GAMESERVER;
		jsn.AddMember(L"Stream", L"Game", jsn.GetAllocator());
		break;
	case streamType::eLogin:
		streamFlags |= PKTBIT_LOGINSERVER;
		jsn.AddMember(L"Stream", L"Login", jsn.GetAllocator());
		break;
	case streamType::ePatch:
		streamFlags |= PKTBIT_PATCHSERVER;
		jsn.AddMember(L"Stream", L"Patch", jsn.GetAllocator());
		break;
	}

	nwkstreamID = nwkStream;
	mstime = timeSeen;

}

void UIDecodedPkt::add_dword(std::wstring name, DWORD dwordfield)
{
	WValue nameVal (name.c_str(), jsn.GetAllocator());
	if (payloadOperations)
		payload->AddMember(nameVal, (uint64_t)dwordfield, jsn.GetAllocator());
	else
		jsn.AddMember(nameVal, (uint64_t)dwordfield, jsn.GetAllocator());
}

void UIDecodedPkt::add_word(std::wstring name, ushort ushortfield)
{
	WValue nameVal(name.c_str(), jsn.GetAllocator());
	if (payloadOperations)
		payload->AddMember(nameVal, ushortfield, jsn.GetAllocator());
	else
		jsn.AddMember(nameVal, ushortfield, jsn.GetAllocator());
}

void UIDecodedPkt::add_byte(std::wstring name, byte bytefield)
{
	WValue nameVal(name.c_str(), jsn.GetAllocator());
	if (payloadOperations)
		payload->AddMember(nameVal, bytefield, jsn.GetAllocator());
	else
		jsn.AddMember(nameVal, bytefield, jsn.GetAllocator());
}

void UIDecodedPkt::add_wstring(std::wstring name, std::wstring stringfield)
{
	WValue nameVal(name.c_str(), jsn.GetAllocator());
	WValue stringVal(stringfield.c_str(), jsn.GetAllocator());

	if (payloadOperations)
		payload->AddMember(nameVal, stringVal, jsn.GetAllocator());
	else
		jsn.AddMember(nameVal, stringVal, jsn.GetAllocator());
}

void UIDecodedPkt::add_array(std::wstring name, WValue array)
{
	WValue nameVal(name.c_str(), jsn.GetAllocator());

	if (payloadOperations)
		payload->AddMember(nameVal, array, jsn.GetAllocator());
	else
		jsn.AddMember(nameVal, array, jsn.GetAllocator());
}

UINT32 UIDecodedPkt::get_UInt32(std::wstring name)
{
	auto it = payloadOperations ? payload->FindMember(name.c_str())
		: jsn.FindMember(name.c_str());
	if (it != payload->MemberEnd() && it->value.IsUint())
		return it->value.GetUint();

	std::wcerr << "JSON ERROR: No Int32 field named " << name <<
		" in pktID 0x" << std::hex << messageID;
	if (payloadOperations)
		std::wcerr << " payload" << std::endl;
	else
		std::wcerr << " metadata" << std::endl;

	return 0xffffffff;
}

UINT64 UIDecodedPkt::get_UInt64(std::wstring name)
{
	auto it = payloadOperations ? payload->FindMember(name.c_str())
		: jsn.FindMember(name.c_str());
	if (it != payload->MemberEnd() && it->value.IsUint64())
		return it->value.GetUint64();


	std::wstringstream err;
	err << "JSON ERROR: No Int64 field named " << name <<
		" in pktID 0x" << std::hex << messageID;
	if (payloadOperations)
		err << " payload" << std::endl;
	else
		err << " metadata" << std::endl;

	std::wcerr << err.str() <<std::endl;//todo: static ui queue so we can do this
	//add_metalog_update(err.str(), clientProcessID());

	return 0xffffffffffffffff;
}

std::wstring UIDecodedPkt::get_wstring(std::wstring name)
{
	auto it = payloadOperations ? payload->FindMember(name.c_str()) 
								: jsn.FindMember(name.c_str());
	if (it != payload->MemberEnd() && it->value.IsString())
		return it->value.GetString();

	std::wcerr << "JSON ERROR: No string field named " << name <<
		" in pktID 0x" << std::hex << messageID;
	if (payloadOperations)
		std::wcerr << " payload" << std::endl;
	else
		std::wcerr << " metadata" << std::endl;

	return L"<ERROR>";
}


void UIDecodedPkt::setMessageID(ushort msgID)
{
	messageID = msgID;
	jsn.AddMember(L"MsgID", (UINT32)msgID, jsn.GetAllocator());
	jsn.AddMember(L"MsgID", (UINT32)msgID, jsn.GetAllocator());
}