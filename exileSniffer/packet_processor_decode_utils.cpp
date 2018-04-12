#include "stdafx.h"
#include "packet_processor.h"
#include "utilities.h"

void packet_processor::emit_decoding_err_msg(unsigned short msgID, unsigned short lastMsgID)
{
	stringstream errmsg;
	errmsg << "ERROR (DECODING): #" << std::dec << errorCount++ << " - ";

	switch (errorFlag)
	{
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

unsigned char packet_processor::consume_Byte()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;
	if (remainingDecrypted < 1)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		errorCount += 1;
		return 0;
	}

	unsigned char result = decryptedBuffer[decryptedIndex];
	decryptedIndex += 1;
	remainingDecrypted -= 1;

	return result;
}

unsigned short packet_processor::consumeUShort()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;
	if (remainingDecrypted < 2)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		errorCount += 1;
		return 0xf00d;
	}

	unsigned short result = getUshort(decryptedBuffer + decryptedIndex);
	decryptedIndex += 2;
	remainingDecrypted -= 2;

	return result;
}

unsigned long packet_processor::consume_DWORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;
	if (remainingDecrypted < 4)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		errorCount += 1;
		return 0;
	}

	DWORD result = getUlong(decryptedBuffer + decryptedIndex);
	decryptedIndex += 4;
	remainingDecrypted -= 4;
	return result;
}

void packet_processor::discard_data(ushort byteCount)
{
	if (errorFlag != eDecodingErr::eNoErr) return;
	if (remainingDecrypted < byteCount)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		errorCount += 1;
	}

	decryptedIndex += byteCount;
	remainingDecrypted -= byteCount;
}

std::wstring packet_processor::consumeWString(size_t bytesLength)
{

	if (errorFlag != eDecodingErr::eNoErr) return L"<exileSniffer Decoding Error>";
	if (bytesLength == 0)
		return L"";
	if (remainingDecrypted < bytesLength)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		errorCount += 1;
		return L"<exileSniffer Decoding Error>";
	}

	std::string msgmb(decryptedBuffer + decryptedIndex, decryptedBuffer + decryptedIndex + bytesLength);
	std::wstring msg = mb_to_utf8(msgmb);

	decryptedIndex += bytesLength;
	remainingDecrypted -= bytesLength;

	return msg;
}

DWORD packet_processor::customSizeByteGet()
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


DWORD packet_processor::customSizeByteGet_signed()
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