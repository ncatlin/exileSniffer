#pragma once
#include "base_thread.h"

typedef unsigned int networkStreamID;

using Tins::Packet;
using Tins::Sniffer;
using Tins::SnifferConfiguration;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

#include "uiMsg.h"

#define PACKET_OUTGOING 0
#define PACKET_INCOMING 1

struct STREAM_NETWORK_DATA {
	std::string serverIP;
	int serverPort;
};

class GAMEPACKET {
public:
	bool incoming = false;
	int streamID;
	vector<byte> data;
	long long time;
};

bool checkQueue(SafeQueue<GAMEPACKET > *q, std::deque< GAMEPACKET  > &pendingPktQueue);


class packet_capture_thread :
	public base_thread
{
public:
	packet_capture_thread(SafeQueue<UI_MESSAGE *>* uiq, SafeQueue<GAMEPACKET > *gameP, SafeQueue<GAMEPACKET > *loginP);
	~packet_capture_thread();
	STREAM_NETWORK_DATA *get_stream_data(int streamID);
	void stop_sniffing();

	bool ded = false;
private:

	void main_loop();

	unsigned int packet_capture_thread::getStreamID(Tins::TCPIP::Stream& stream);
	void on_stream_terminated(Tins::TCPIP::Stream& stream, Tins::TCPIP::StreamFollower::TerminationReason reason);

	void on_new_stream(Tins::TCPIP::Stream& stream);
	/*
	void on_patchclient_data(Tins::TCPIP::Stream& stream);
	void on_patchserver_data(Tins::TCPIP::Stream& stream);
	*/
	void on_loginclient_data(Tins::TCPIP::Stream& stream);
	void on_loginserver_data(Tins::TCPIP::Stream& stream);

	void on_gameclient_data(Tins::TCPIP::Stream& stream);
	void on_gameserver_data(Tins::TCPIP::Stream& stream);

private:
	Tins::Sniffer *sniffer = NULL;

	CRITICAL_SECTION streamDataCritsec;
	map<int, STREAM_NETWORK_DATA> streamRecords;

	SafeQueue<UI_MESSAGE *> *uiMsgQueue;
	SafeQueue<GAMEPACKET> *gameQueue, *loginQueue;

	std::map<std::chrono::microseconds, networkStreamID> streamList;
	int connectionCount = 0;
};

