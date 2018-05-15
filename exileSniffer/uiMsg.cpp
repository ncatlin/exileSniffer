#include "stdafx.h"
#include "uiMsg.h"
#include "utilities.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\writer.h"

//used to add packet name data when sending to json feed subscribers
rapidjson::GenericValue<rapidjson::UTF8<>> *UIDecodedPkt::loginMessageTypes = NULL;
rapidjson::GenericValue<rapidjson::UTF8<>> *UIDecodedPkt::gameMessageTypes = NULL;


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

UIDecodedPkt::UIDecodedPkt(DWORD processID, streamType streamServerType,int nwkStream, bool isIncoming, long long timeSeen)
{
	jsn.SetObject();

	jsn.AddMember(L"Payload", WValue(rapidjson::kObjectType), jsn.GetAllocator());
	payload = &jsn.FindMember(L"Payload")->value;

	msgType = uiMsgType::eDecodedPacket;
	PID = processID;
	jsn.AddMember(L"ProcessID", (UINT32)processID, jsn.GetAllocator());

	incoming = isIncoming;
	if (incoming)
	{
		jsn.AddMember(L"Direction", L"Inbound", jsn.GetAllocator());
	}
	else
	{
		jsn.AddMember(L"Direction", L"Outbound", jsn.GetAllocator());
	}

	streamServer = streamServerType;
	switch (streamServer) 
	{
	case streamType::eGame:
		jsn.AddMember(L"Stream", L"Game", jsn.GetAllocator());
		break;
	case streamType::eLogin:
		jsn.AddMember(L"Stream", L"Login", jsn.GetAllocator());
		break;
	case streamType::ePatch:
		jsn.AddMember(L"Stream", L"Patch", jsn.GetAllocator());
		break;
	}

	nwkstreamID = nwkStream;
	msTime = timeSeen;
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

//set the message id
//we also have the metadata set as well as the json packet list so
//also do some validation to find inconsistencies between them
void UIDecodedPkt::set_validate_MessageID(ushort msgID, SafeQueue<UI_MESSAGE *> *uiMsgQueue)
{
	messageID = msgID;
	jsn.AddMember(L"MsgID", (UINT32)msgID, jsn.GetAllocator());

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	rapidjson::GenericValue<rapidjson::UTF8<>> *typelist;

	if (streamServer == eLogin && msgID < loginMessageTypes->Size())
	{
		typelist = loginMessageTypes;
	}
	else if(streamServer == eGame && msgID < gameMessageTypes->Size())
	{
		typelist = gameMessageTypes;
	}
	else
	{
		jsn.AddMember(L"MsgType", L"BAD_MESSAGE_TYPE", jsn.GetAllocator());
		return;
	}

	rapidjson::Value &msgInfo = (*typelist)[msgID];
	std::string msgNameString = msgInfo.FindMember("Name")->value.GetString();
	std::wstring msgNameWString = converter.from_bytes(msgNameString);
	WValue namestringVal(msgNameWString.c_str(), jsn.GetAllocator());
	jsn.AddMember(L"MsgType", namestringVal, jsn.GetAllocator());

	bool expectedIncoming = msgInfo.FindMember("Inbound")->value.GetBool();
	if (expectedIncoming != this->incoming)
	{
		if (msgInfo.FindMember("Bidirectional") == msgInfo.MemberEnd())
		{
			std::stringstream msg;
			msg << "Message inconsistency in messageTypes listing for msg ID 0x" << std::hex << msgID;
			msg << ". Expected Incoming == " << expectedIncoming << " but incoming == " << this->incoming << std::endl;
			UIaddLogMsg(msg.str(), this->getClientProcessID(), uiMsgQueue);
		}
	}
}

QString UIDecodedPkt::senderString()
{
	if (!incoming) return "[" + QString::number(nwkstreamID) + "] Client";
	if (streamServer == eGame) return "[" + QString::number(nwkstreamID) + "] GameServer";
	if (streamServer == eLogin) return "[" + QString::number(nwkstreamID) + "] LoginServer";
	return "sender() Error";
}