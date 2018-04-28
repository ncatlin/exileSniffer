#include "stdafx.h"
#include "packet_processor.h"
#include "utilities.h"

void packet_processor::emit_decoding_err_msg(unsigned short msgID, unsigned short lastMsgID)
{
	stringstream errmsg;
	errmsg << "ERROR (DECODING): #" << std::dec << errorCount++ << " - ";

	switch (errorFlag)
	{
	case eDecodingErr::eAbandoned:
		return;

	case eDecodingErr::eErrUnderflow:
		errmsg << "Underflow";
		break;

	case eDecodingErr::eBadPacketID:
		errmsg << "Probably bad packet ID 0x" << std::hex << msgID <<
			". Possible: Decrypt out of sync, bad key/IV," <<
			" missed multi-packet blob or unusual valid packet ID.";
		break;

	case eDecodingErr::eNoErr:
		errmsg << "No error flag set";
		break;

	case eDecodingErr::ePktIDUnimplemented:
		errmsg << "No deserialiser implemented";
		break;

	default:
		errmsg << "Bad error flag '" << errorFlag << "' set";
		break;
	}
	errmsg << " processing msgID 0x" << std::hex << msgID << " at index "
		<< decryptedIndex << " after previous packet ID 0x" << lastMsgID;
	UIaddLogMsg(QString::fromStdString(errmsg.str()), activeClientPID, uiMsgQueue);
}

/*
todo... method of getting stuff from the next packet in the case of underflow
*/
void packet_processor::continue_gamebuffer_next_packet()
{
	std::vector<byte> pkt;
	int attemptsCount = 0;

	pendingPktQueue.pop_front();
	STREAMDATA *streamObj = &streamDatas[currentMsgStreamID];
	streamObj->packetCount++;

	this->currentMsgMultiPacket = true;

	while (true)
	{
		checkPipe(gamepipe, &pendingPktQueue);

		for (auto it = pendingPktQueue.begin(); it != pendingPktQueue.end(); it++)
		{
			pkt = *it;

			char *next_token = (char *)pkt.data();

			char *streamID_s = strtok_s(next_token, ",", &next_token);
			networkStreamID streamID = (networkStreamID)atoi(streamID_s);
			char *incoming = strtok_s(next_token, ",", &next_token);
			bool isIncoming = (*incoming == '1');

			if (streamID == currentMsgStreamID && isIncoming == currentMsgIncoming)
			{
				

				char *timeprocessed = strtok_s(next_token, ",", &next_token);
				char *dLen = strtok_s(next_token, ",", &next_token);
				byte *data = (byte *)next_token;

				unsigned int dataLen = atoi(dLen);
				size_t originalSize = decryptedBuffer->size();
				decryptedBuffer->resize(originalSize + dataLen, 0);

				if (isIncoming)
				{
					streamObj->fromGameSalsa.ProcessData(decryptedBuffer->data()+originalSize,
						data, dataLen);
				}
				else
				{
					streamObj->toGameSalsa.ProcessData(decryptedBuffer->data() + originalSize,
						data, dataLen);
				}

				remainingDecrypted += dataLen;

				//move it to the front to be popped off
				pendingPktQueue.erase(it);
				pendingPktQueue.push_front(pkt); 
				return;
			}
		}
		if (attemptsCount++ > 10)
		{
			stringstream err;
			err << "WARNING: Long wait for continuation data stream " << currentMsgStreamID <<
				" incoming: " << currentMsgIncoming;
			UIaddLogMsg(QString::fromStdString(err.str()), activeClientPID, uiMsgQueue);
		}
		Sleep(50);
	}
}

UINT8 packet_processor::consume_Byte()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 1)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_gamebuffer_next_packet();
	}

	unsigned char result = decryptedBuffer->at(decryptedIndex);
	decryptedIndex += 1;
	remainingDecrypted -= 1;
	return result;
}

UINT16 packet_processor::consumeUShort()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 2)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_gamebuffer_next_packet();
	}

	unsigned short result = getUshort(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 2;
	remainingDecrypted -= 2;
	return result;
}

UINT32 packet_processor::consume_DWORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 4)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_gamebuffer_next_packet();
	}

	DWORD result = getUlong(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 4;
	remainingDecrypted -= 4;
	return result;
}

UINT64 packet_processor::consume_QWORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 8)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_gamebuffer_next_packet();
	}

	UINT64 result = getUlonglong(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 8;
	remainingDecrypted -= 8;
	return result;
}

void packet_processor::consume_blob(ushort byteCount)
{
	if (errorFlag != eDecodingErr::eNoErr) return;
	if (byteCount > 10000)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		return;
	}

	while (remainingDecrypted < byteCount)
	{
		if (errorFlag != eDecodingErr::eNoErr) return;
		continue_gamebuffer_next_packet();
	}

	decryptedIndex += byteCount;
	remainingDecrypted -= byteCount;
}

void packet_processor::consume_blob(ushort byteCount, vector <byte>& blobBuf)
{
	if (errorFlag != eDecodingErr::eNoErr) return;
	if (byteCount > 10000)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		return;
	}

	while (remainingDecrypted < byteCount)
	{
		if (errorFlag != eDecodingErr::eNoErr) return;
		continue_gamebuffer_next_packet();
	}

	blobBuf = vector<byte>(decryptedBuffer->data() + decryptedIndex,
		decryptedBuffer->data() + decryptedIndex + byteCount);

	decryptedIndex += byteCount;
	remainingDecrypted -= byteCount;
}


void packet_processor::consume_add_lenprefix_string(std::wstring name, WValue& container, rapidjson::Document::AllocatorType& allocator)
{
	WValue nameItem(name.c_str(), allocator);

	ushort stringlen = ntohs(consumeUShort());
	std::wstring stringval = consumeWString(stringlen * 2);
	WValue stringItem(stringval.c_str(), allocator);

	container.AddMember(nameItem, stringItem, allocator);
}


void packet_processor::rewind_buffer(size_t countBytes)
{
	assert(!restorePoint.active);
	restorePoint.active = true;

	restorePoint.savedIndex = decryptedIndex;
	restorePoint.savedRemaining = remainingDecrypted;
	decryptedIndex -= countBytes;
	remainingDecrypted += countBytes;
}

void packet_processor::restore_buffer()
{
	assert(restorePoint.active);
	restorePoint.active = false;

	this->decryptedIndex = restorePoint.savedIndex;
	this->remainingDecrypted = restorePoint.savedRemaining;
}

/*
stop processing any more of the packet.
intended for use when we don't know how to process the rest
of the packet
*/
void packet_processor::abandon_processing()
{
	errorFlag = eDecodingErr::eAbandoned;
	errorCount += 1;

	decryptedIndex += remainingDecrypted;
	remainingDecrypted = 0;
}

std::wstring packet_processor::consumeWString(size_t bytesLength)
{

	if (errorFlag != eDecodingErr::eNoErr) return L"<exileSniffer Decoding Error>";
	if (bytesLength == 0)
		return L"";

	while (remainingDecrypted < bytesLength)
	{
		if (bytesLength > 0xff)
		{
			std::stringstream err;
			err << "Warning! Long string " << bytesLength <<" possible bad byte order" << std::endl;
			std::cout << err.str();
			UIaddLogMsg(QString::fromStdString(err.str()), activeClientPID, uiMsgQueue);
		}

		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_gamebuffer_next_packet();
	}

	std::string msgmb(decryptedBuffer->data() + decryptedIndex, 
		decryptedBuffer->data() + decryptedIndex + bytesLength);
	std::wstring msg = mb_to_utf8(msgmb);

	decryptedIndex += bytesLength;
	remainingDecrypted -= bytesLength;

	return msg;
}

UINT32 packet_processor::customSizeByteGet()
{
	unsigned char startByte = consume_Byte();

	if (startByte < 0x80)
		return startByte;

	DWORD result;

	if ((startByte & 0xC0) == 0x80)
	{
		unsigned char byte2 = consume_Byte();

		result = ((startByte & 0x3f) << 8) | byte2;
	}
	else if ((startByte & 0xE0) == 0xC0)
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();

		result = ((startByte & 0x1f) << 16) | 
				(byte2 << 8) | 
				byte3;
	}
	else if ((startByte & 0xf0) == 0xe0)
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();
		unsigned char byte4 = consume_Byte();

		result = ((startByte & 0x1f) << 24) | 
				(byte2 << 16) | 
				(byte3 << 8) | 	
				byte4;
	}
	else
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();
		unsigned char byte4 = consume_Byte();
		unsigned char byte5 = consume_Byte();

		result = (byte2 << 24) |
				(byte3 << 16) | 
				(byte4 << 8) |  
				byte5;
	}

	return result;
}


INT32 packet_processor::customSizeByteGet_signed()
{
	unsigned char startByte = consume_Byte();
	DWORD result;

	if (startByte < 0x80)
	{
		result = startByte;

		if ((startByte & 0x40) != 0) //if highest bit is set treat it as negative?
			result |= 0xffffff80;
	}
	else if ((startByte & 0xC0) == 0x80)
	{
		unsigned char byte2 = consume_Byte();

		result = ((startByte & 0x3f) << 8) | byte2; //takes the lowest 6 bits of the start byte

		if (startByte & 0x20)	//if highest bit is set - treat it as signed?
			result |= 0xffffc000;

	}
	else if ((startByte & 0xE0) == 0xC0)
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();

		result = ((startByte & 0x1f) << 16) | //takes the lowest 5 bits of the start byte
			(byte2 << 8) |
			byte3;

		if ((startByte & 0x10) != 0)
			result |= 0xffe00000;

	}
	else if ((startByte & 0xf0) == 0xe0)
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();
		unsigned char byte4 = consume_Byte();

		result = ((startByte & 0xf) << 24) | //takes the lowest 4 bits of the start byte
			(byte2 << 16) |
			(byte3 << 8) |
			byte4;

		if ((startByte & 0x8) != 0)
			result |= 0xf0000000;
	}
	else
	{
		unsigned char byte2 = consume_Byte();
		unsigned char byte3 = consume_Byte();
		unsigned char byte4 = consume_Byte();
		unsigned char byte5 = consume_Byte();

		result = (byte2 << 24) |
			(byte3 << 16) |
			(byte4 << 8) |
			byte5;
	}

	return result;
}