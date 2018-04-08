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

	unsigned short result = getUlong(decryptedBuffer + decryptedIndex);
	decryptedIndex += 4;
	remainingDecrypted -= 4;
	return result;
}

std::wstring packet_processor::consumeWString(size_t bytesLength)
{
	if (errorFlag != eDecodingErr::eNoErr) return L"<exileSniffer Decoding Error>";
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
