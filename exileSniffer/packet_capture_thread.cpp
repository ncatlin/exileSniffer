#include "stdafx.h"
#include "packet_capture_thread.h"
#include "uiMsg.h" 
#include "utilities.h"

#define PATCHSERVER_PORT 12995
#define LOGINSERVER_PORT 20481
#define GAMESERVER_PORT 6112


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

bool checkQueue(SafeQueue<GAMEPACKET > *q, std::deque< GAMEPACKET  > &pendingPktQueue)
{
	while (!q->empty())
	{
		GAMEPACKET pkt = q->waitItem();
		pendingPktQueue.push_back(pkt);
	}
	return !pendingPktQueue.empty();
}

/*
void packet_capture_thread::on_patchclient_data(Tins::TCPIP::Stream& stream) 
{
	//printf("patch client data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();
	std::stringstream pktstringstr;
	pktstringstr << getStreamID(stream) << "," << PACKET_OUTGOING << "," << ms_since_epoch() << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	std::string pktstr = pktstringstr.str();
	WriteFile(patchPipe, pktstr.c_str(), pktstr.size(), 0, 0);
}
*/

/*
// This will be called when there's new server data
void packet_capture_thread::on_patchserver_data(Tins::TCPIP::Stream& stream) 
{
	//printf("patch server data\n");
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();
	std::ostringstream pktstringstr;

	pktstringstr << getStreamID(stream) << "," << PACKET_INCOMING << "," << ms_since_epoch() << "," <<
		payload.size() << "," << std::string(payload.begin(), payload.end());
	
	std::string pktstr = pktstringstr.str();
	WriteFile(patchPipe, pktstr.c_str(), pktstr.size(), 0, 0);
}
*/

void packet_capture_thread::on_loginclient_data(Tins::TCPIP::Stream& stream) 
{
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();
	
	GAMEPACKET pktobj;
	pktobj.incoming = false;
	pktobj.streamID = getStreamID(stream);
	pktobj.data = std::vector<byte>(payload.begin(), payload.end());
	pktobj.time = ms_since_epoch();

	loginQueue->addItem(pktobj);
}

// This will be called when there's new server data
void packet_capture_thread::on_loginserver_data(Tins::TCPIP::Stream& stream) 
{
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();

	GAMEPACKET pktobj;
	pktobj.incoming = true;
	pktobj.streamID = getStreamID(stream);
	pktobj.data = std::vector<byte>(payload.begin(), payload.end());
	pktobj.time = ms_since_epoch();

	loginQueue->addItem(pktobj);
}


void packet_capture_thread::on_gameclient_data(Tins::TCPIP::Stream& stream) 
{
	const Tins::TCPIP::Stream::payload_type& payload = stream.client_payload();

	GAMEPACKET pktobj;
	pktobj.incoming = false;
	pktobj.streamID = getStreamID(stream);
	pktobj.data = std::vector<byte>(payload.begin(), payload.end());
	pktobj.time = ms_since_epoch();

	gameQueue->addItem(pktobj);
}

// This will be called when there's new server data
void packet_capture_thread::on_gameserver_data(Tins::TCPIP::Stream& stream) 
{
	const Tins::TCPIP::Stream::payload_type& payload = stream.server_payload();

	GAMEPACKET pktobj;
	pktobj.incoming = true;
	pktobj.streamID = getStreamID(stream);
	pktobj.data = std::vector<byte>(payload.begin(), payload.end());
	pktobj.time = ms_since_epoch();

	gameQueue->addItem(pktobj);
}


void packet_capture_thread::on_new_stream(Tins::TCPIP::Stream& stream)
{
	int streamID = connectionCount++;

	streamList[stream.create_time()] = streamID;

	EnterCriticalSection(&streamDataCritsec);
	streamRecords[streamID].serverPort = stream.server_port();
	streamRecords[streamID].serverIP = stream.server_addr_v4().to_string(); //ipv6 anyone? no? no.
	LeaveCriticalSection(&streamDataCritsec);

	char serverType = portStreamType(stream.server_port());

	using std::placeholders::_1;
	switch (serverType)
	{
	case ePatch:
		//stream.client_data_callback(std::bind(&packet_capture_thread::on_patchclient_data, this, _1));
		//stream.server_data_callback(std::bind(&packet_capture_thread::on_patchserver_data, this, _1));
		assert(false);
		break;

	case eLogin:
		stream.client_data_callback(std::bind(&packet_capture_thread::on_loginclient_data, this, _1));
		stream.server_data_callback(std::bind(&packet_capture_thread::on_loginserver_data, this, _1));
		break;

	case eGame:
		stream.client_data_callback(std::bind(&packet_capture_thread::on_gameclient_data, this, _1));
		stream.server_data_callback(std::bind(&packet_capture_thread::on_gameserver_data, this, _1));
		break;
	default:
		std::cout << "Ignoring unknown server port: " << stream.server_port() << std::endl;
	}

	std::stringstream newStreamMsg;
	newStreamMsg << "New stream[#" << std::dec << streamID << "]: Client:" << stream.client_port() <<
		" -> " << stream.server_addr_v4().to_string() << ":" << stream.server_port();

	UIaddLogMsg(newStreamMsg.str().c_str(), 0, uiMsgQueue);

	UInotifyStreamState(streamID, eStreamState::eStreamStarted, uiMsgQueue);
}

/*
These are rare. From the headers:

	*A stream is terminated when either :
	*
	* * It contains too much buffered data.
	* * No packets have been seen for some time interval.

This is not a reliable way of detecting logout
Have to infer it from the data (exit messages)
*/
void packet_capture_thread::on_stream_terminated(Tins::TCPIP::Stream& stream, Tins::TCPIP::StreamFollower::TerminationReason reason)
{
	std::stringstream newStreamMsg;
	newStreamMsg << "Stream "<< std::dec << getStreamID(stream) <<" ended ("<<reason<<". Client:" << stream.client_port() <<
		" -> " << stream.server_addr_v4().to_string() << ":" << stream.server_port();

	std::cout << newStreamMsg.str() << std::endl;

	UIaddLogMsg(newStreamMsg.str().c_str(), 0, uiMsgQueue);
	UInotifyStreamState(getStreamID(stream), eStreamState::eStreamEnded, uiMsgQueue);
	
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
	//filterString.append(" or");
	//filterString.append(" tcp port " + std::to_string(PATCHSERVER_PORT));
	filterString.append(" )");

	std::stringstream listenStartMsg;
	listenStartMsg << "Sniffing on interface address: " << hostAddr.to_string() <<
		", ID: " << iface.name() << " using filter \"" << filterString << "\"";
	UIaddLogMsg(listenStartMsg.str(), 0, uiMsgQueue);

	Tins::SnifferConfiguration config;
	config.set_promisc_mode(true);
	config.set_filter(filterString);
	sniffer = new Tins::Sniffer(iface.name(), config);

	UIsniffingStarted(QString::fromStdString(hostAddr.to_string()), uiMsgQueue);

	sniffer->sniff_loop([&](Tins::PDU& pdu) { follower.process_packet(pdu); return true; });
}

packet_capture_thread::packet_capture_thread(SafeQueue<UI_MESSAGE *>* uiq, 
	SafeQueue<GAMEPACKET > *gameP, SafeQueue<GAMEPACKET > *loginP)
{
	uiMsgQueue = uiq;
	gameQueue = gameP;
	loginQueue = loginP;
}


packet_capture_thread::~packet_capture_thread()
{
}


STREAM_NETWORK_DATA* packet_capture_thread::get_stream_data(int streamID)
{
	STREAM_NETWORK_DATA* result = NULL;

	EnterCriticalSection(&streamDataCritsec);
	auto it = streamRecords.find(streamID);
	if (it == streamRecords.end())
	{
		LeaveCriticalSection(&streamDataCritsec);
		UIaddLogMsg("Error: Tried to retrieve streamdata for nonexistant stream", 0, uiMsgQueue);
	}
	else
	{
		result = &it->second;
		LeaveCriticalSection(&streamDataCritsec);

	}
	return result;
}

void packet_capture_thread::stop_sniffing()
{
	if(sniffer)
		sniffer->stop_sniff();
	ded = true;
}