#pragma once
#include "packetIDs.h"

enum streamType { eLogin = 'L', eGame = 'G', ePatch = 'P', eNone = 0 };

class decodedPacket
{
public:
	decodedPacket() {};
	decodedPacket(byte * buf, unsigned short idx) : pktBytes(buf),
		startIdx(idx) {}
	~decodedPacket() {};
	void markFailedDecode() { failedDecode = true; }
	void finalise(unsigned short endOffset) { 	length = endOffset - startIdx; }

	bool failedDecode = false;
	unsigned short messageID;
	//the buffer the decrypted bytes reside in
	byte* pktBytes;
	//index into that buffer where this packets byte start
	unsigned short startIdx;
	//length of this packets bytes in that buffer
	unsigned short length;
};

//used to send its first packet - know first bytes help synchronise crypt stream
//this object only here for completeness - it should not be used!
class pkt_SRV_PKT_ENCAPSULATED : public decodedPacket
{
public:
	pkt_SRV_PKT_ENCAPSULATED(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{	assert(false); messageID = SRV_PKT_ENCAPSULATED; }
};

class pkt_CLI_CHAT_MSG_ITEMS : public decodedPacket
{
public:
	pkt_CLI_CHAT_MSG_ITEMS(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_CHAT_MSG_ITEMS; }

	unsigned short msgLen_Words; //words as in 2 bytes
	std::wstring msg;
	byte linkedItemCount;
};


class pkt_CLI_CHAT_MSG : public decodedPacket
{
public:
	pkt_CLI_CHAT_MSG(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_CHAT_MESSAGE; }

	unsigned short msgLen_Words; //words as in 2 bytes
	std::wstring msg;
	byte linkedItemCount;
};

class pkt_CLI_CHAT_COMMAND : public decodedPacket
{
public:
	pkt_CLI_CHAT_COMMAND(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_CHAT_COMMAND; }
};

class pkt_SRV_CHAT_MESSAGE : public decodedPacket
{
public:
	pkt_SRV_CHAT_MESSAGE(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = SRV_CHAT_MESSAGE;	}
};


class pkt_SRV_SERVER_MESSAGE : public decodedPacket
{
public:
	pkt_SRV_SERVER_MESSAGE(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = SRV_SERVER_MESSAGE; }
};


class pkt_CLI_LOGGED_OUT : public decodedPacket
{
public:
	pkt_CLI_LOGGED_OUT(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_LOGGED_OUT; }
};


class pkt_CLI_PING_CHALLENGE : public decodedPacket
{
public:
	pkt_CLI_PING_CHALLENGE(byte *buf, ushort idx) :	decodedPacket(buf, idx)
	{ messageID = CLI_PING_CHALLENGE; }

	DWORD challenge;
};

class pkt_CLI_ACTION_PREDICTIVE : public decodedPacket
{
public:
	pkt_CLI_ACTION_PREDICTIVE(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_ACTION_PREDICTIVE; }
};


class pkt_CLI_USE_BELT_SLOT : public decodedPacket
{
public:
	pkt_CLI_USE_BELT_SLOT(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_USE_BELT_SLOT; }
};

class pkt_CLI_USE_ITEM : public decodedPacket
{
public:
	pkt_CLI_USE_ITEM(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_USE_ITEM;	}
};

class pkt_SRV_SKILL_USED : public decodedPacket
{
public:
	pkt_SRV_SKILL_USED(byte *buf, ushort idx) :	decodedPacket(buf, idx)
	{ messageID = SRV_MOBILE_USED_SKILL; }
};

class pkt_CLI_MOUSE_RELEASE : public decodedPacket
{
public:
	pkt_CLI_MOUSE_RELEASE(byte *buf, ushort idx) : decodedPacket(buf, idx)
	{ messageID = CLI_MOUSE_RELEASE; }

};