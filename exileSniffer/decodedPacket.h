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

	bool failedDecode = false;
	unsigned short messageID;
	//the buffer the decrypted bytes reside in
	byte* pktBytes;
	//index into that buffer where this packets byte start
	unsigned short startIdx;
	//length of this packets bytes in that buffer
	unsigned short length;
};

class pkt_SRV_SKILL_USED :
	public decodedPacket 
{
public:
	pkt_SRV_SKILL_USED(byte *buf, ushort idx) :
		decodedPacket(buf, idx)
	{	messageID = SRVPK_MOBILE_USED_SKILL;	}
};

class pkt_CLI_MOUSE_RELEASE :
	public decodedPacket
{
public:
	pkt_CLI_MOUSE_RELEASE(byte *buf, ushort idx) :
		decodedPacket(buf, idx)
	{ messageID = CLIPK_MOUSE_RELEASE;}

};

class pkt_CLI_CHAT_MSG :
	public decodedPacket
{
public:
	pkt_CLI_CHAT_MSG(byte *buf, ushort idx) :
		decodedPacket(buf, idx)
	{ messageID = CLI_CHAT_MESSAGE; }

	unsigned short msgLen_Words; //words as in 2 bytes
	std::wstring msg;
	byte linkedItemCount;
};