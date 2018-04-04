#include "stdafx.h"
#include "packet_capture_thread.h"
#include "uiMsg.h" 

#define PATCHSERVER_PORT 12995
#define LOGINSERVER_PORT 20481
#define GAMESERVER_PORT 6112
#define PACKET_OUTGOING 0
#define PACKET_INCOMING 1

struct GAMEPACKET {
	char serverType;
	bool incoming = false;
	unsigned int size;
	std::vector<byte> contents;
};

streamType portStreamType(unsigned int port)
{
	return (port == LOGINSERVER_PORT) ? eLogin : 
				((port == PATCHSERVER_PORT) ? ePatch 
					: ((port == GAMESERVER_PORT) ? eGame : 
						eNone));
}

unsigned int packet_capture_thread::getStreamID(Tins::TCPIP::Stream& stream)
{
	return streamList[stream.create_time()];
}



void packet_capture_thread::on_patchclient_data(Tins::TCPIP::Stream& stream) 
{
	//printf("patch client data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_OUTGOING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	WriteFile(patchPipe, pktstr.c_str(), pktstr.size(), 0, 0);
}

// This will be called when there's new server data
void packet_capture_thread::on_patchserver_data(Tins::TCPIP::Stream& stream) 
{
	//printf("patch server data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();
	std::ostringstream pktstringstr;

	pktstringstr << getStreamID(stream) << "," << PACKET_INCOMING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	
	std::string pktstr = pktstringstr.str();
	WriteFile(patchPipe, pktstr.c_str(), pktstr.size(), 0, 0);
}

void packet_capture_thread::on_loginclient_data(Tins::TCPIP::Stream& stream) 
{
	//printf("login client data, getting clientpayload of stream %lx\n",&stream);
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_OUTGOING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	DWORD writtens = 0;
	WriteFile(loginPipe, pktstr.c_str(), pktstr.size(), &writtens, 0);
}

// This will be called when there's new server data
void packet_capture_thread::on_loginserver_data(Tins::TCPIP::Stream& stream) 
{
	//printf("login server data\n"); 
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_INCOMING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	DWORD writtens = 0;
	WriteFile(loginPipe, pktstr.c_str(), pktstr.size(), &writtens, 0);
}

void packet_capture_thread::on_gameclient_data(Tins::TCPIP::Stream& stream) 
{
	//printf("game client data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_OUTGOING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	DWORD writtens = 0;
	WriteFile(gamePipe, pktstr.c_str(), pktstr.size(), &writtens, 0);
}

// This will be called when there's new server data
void packet_capture_thread::on_gameserver_data(Tins::TCPIP::Stream& stream) 
{
	//printf("game server data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_INCOMING << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	DWORD writtens = 0;
	WriteFile(gamePipe, pktstr.c_str(), pktstr.size(), &writtens, 0);
}


void packet_capture_thread::on_new_stream(Tins::TCPIP::Stream& stream)
{
	printf("New stream [#%d]: client:%d -> %s:%d ", connectionCount, stream.client_port(), stream.server_addr_v4().to_string().c_str(), stream.server_port());
	char serverType = portStreamType(stream.server_port());

	streamList[stream.create_time()] = connectionCount++;
	using std::placeholders::_1;
	switch (serverType)
	{
	case ePatch:
		printf(" (Patch server)\n");
		stream.client_data_callback(std::bind(&packet_capture_thread::on_patchclient_data, this, _1));
		stream.server_data_callback(std::bind(&packet_capture_thread::on_patchserver_data, this, _1));
		break;

	case eLogin:
		printf(" (Login server)\n");
		stream.client_data_callback(std::bind(&packet_capture_thread::on_loginclient_data, this, _1));
		stream.server_data_callback(std::bind(&packet_capture_thread::on_loginserver_data, this, _1));
		break;

	case eGame:
		printf(" (Game server)\n");
		stream.client_data_callback(std::bind(&packet_capture_thread::on_gameclient_data, this, _1));
		stream.server_data_callback(std::bind(&packet_capture_thread::on_gameserver_data, this, _1));
		break;
	default:
		std::cout << "Ignoring unknown port: " << stream.server_port() << std::endl;
	}
}


void packet_capture_thread::on_stream_terminated(Tins::TCPIP::Stream& stream, Tins::TCPIP::StreamFollower::TerminationReason reason)
{

	char serverType = portStreamType(stream.server_port());
	switch (serverType) 
	{
	case ePatch:
		std::cout << "Patchserver Stream Ended -";
		break;

	case eLogin:
		std::cout << "Loginserver Stream Ended -" ;
		break;

	case eGame:
		std::cout << "Gameserver Stream Ended -";
		break;
	default:
		break;
	}

	printf("[#%d]: client:%d -> %s:%d ", connectionCount, stream.client_port(), stream.server_addr_v4().to_string().c_str(), stream.server_port());

}

HANDLE createPipe(std::wstring pipename)
{
	const wchar_t* szName = pipename.c_str();
	HANDLE newhandle = CreateNamedPipe(szName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE,
		50, //max instances
		1024 * 1024 * 10, //outbuffer
		1024 * 1024, //inbuffermax
		20, //timeout?
		NULL);

	if ((int)newhandle == -1)
	{
		std::cerr << "Error: Could not create sniff pipe. error:" << GetLastError() << std::endl;
		return 0;
	}
	return newhandle;
}

void packet_capture_thread::main_loop()
{
	std::vector<Tins::NetworkInterface> interfaces = Tins::NetworkInterface::all();

	Tins::TCPIP::StreamFollower follower;
	follower.new_stream_callback(std::bind(&packet_capture_thread::on_new_stream,
		this,
		std::placeholders::_1));
	follower.stream_termination_callback(std::bind(&packet_capture_thread::on_stream_terminated,
		this,
		std::placeholders::_1, std::placeholders::_2));

	Tins::NetworkInterface& iface = Tins::NetworkInterface::default_interface();
	Tins::IPv4Address hostAddr = iface.ipv4_address();

	std::string filterString = "ip host " + hostAddr.to_string();
	filterString.append(" and (");
	filterString.append(" tcp port " + std::to_string(LOGINSERVER_PORT));
	filterString.append(" or");
	filterString.append(" tcp port " + std::to_string(GAMESERVER_PORT));
	filterString.append(" or");
	filterString.append(" tcp port " + std::to_string(PATCHSERVER_PORT));
	filterString.append(" )");

	std::stringstream listenStartMsg;
	listenStartMsg << "Sniffing on interface address: " << hostAddr.to_string() <<
		", ID: " << iface.name() << " using filter \"" << filterString << "\"";
	UIaddLogMsg(listenStartMsg.str(), 0, uiMsgQueue);

	Tins::SnifferConfiguration config;
	config.set_promisc_mode(true);
	config.set_filter(filterString);
	Tins::Sniffer sniffer(iface.name(), config);

	sniffer.sniff_loop([&](Tins::PDU& pdu) { follower.process_packet(pdu); return true; });
}

packet_capture_thread::packet_capture_thread(SafeQueue<UI_MESSAGE>* uiq)
{
	patchPipe = createPipe(L"\\\\.\\pipe\\patchpipe");
	loginPipe = createPipe(L"\\\\.\\pipe\\loginpipe");
	gamePipe = createPipe(L"\\\\.\\pipe\\gamepipe");
	uiMsgQueue = uiq;
}


packet_capture_thread::~packet_capture_thread()
{
}
