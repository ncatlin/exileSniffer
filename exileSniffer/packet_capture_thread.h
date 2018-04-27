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

class packet_capture_thread :
	public base_thread
{
public:
	packet_capture_thread(SafeQueue<UI_MESSAGE>* uiq);
	~packet_capture_thread();

private:

	void main_loop();

	unsigned int packet_capture_thread::getStreamID(Tins::TCPIP::Stream& stream);
	void on_stream_terminated(Tins::TCPIP::Stream& stream, Tins::TCPIP::StreamFollower::TerminationReason reason);

	void on_new_stream(Tins::TCPIP::Stream& stream);

	void on_patchclient_data(Tins::TCPIP::Stream& stream);
	void on_patchserver_data(Tins::TCPIP::Stream& stream);

	void on_loginclient_data(Tins::TCPIP::Stream& stream);
	void on_loginserver_data(Tins::TCPIP::Stream& stream);

	void on_gameclient_data(Tins::TCPIP::Stream& stream);
	void on_gameserver_data(Tins::TCPIP::Stream& stream);


	SafeQueue<UI_MESSAGE> *uiMsgQueue;

	std::map<std::chrono::microseconds, networkStreamID> streamList;
	int connectionCount = 0;

	HANDLE patchPipe = 0;
	HANDLE loginPipe = 0;
	HANDLE gamePipe = 0;
};

