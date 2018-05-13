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
		errmsg << "[Probably bad packet ID 0x" << std::hex << msgID <<
			"]. Possible: Bad decoding, Decrypt out of sync, Bad key/IV," <<
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
	errmsg << " while processing msgID 0x" << std::hex << msgID << " at index " <<
		std::dec << decryptedIndex << " after previous packet ID 0x" << std::hex << lastMsgID;
	UIaddLogMsg(QString::fromStdString(errmsg.str()), activeClientPID, uiMsgQueue);
}

/*
Sometimes a message takes up more than a single packet (> ~1400 bytes).
This transparently fetches data from the next packet outside the 
normal workflow and appends it to the remaining decrypted buffer so the decoder can
 continue

 Unfortunately if the decoding is bad and we interpret a large number as a length field
 then decoding will hang as this keeps getting called to fill the requested data requirement
*/
void packet_processor::continue_buffer_next_packet()
{
	GAMEPACKET pkt;
	int attemptsCount = 0;

	pendingPktQueue.pop_front();
	STREAMDATA *streamObj = &streamDatas[currentMsgStreamID];
	streamObj->packetCount++;

	while (true)
	{
		checkQueue(streamObj->queue, pendingPktQueue);

		for (auto it = pendingPktQueue.begin(); it != pendingPktQueue.end(); it++)
		{
			pkt = *it;

			networkStreamID streamID = pkt.streamID;

			if (streamID == currentMsgStreamID && pkt.incoming == currentMsgIncoming)
			{
				size_t dataLen = pkt.data.size();
				size_t originalSize = decryptedBuffer->size();
				decryptedBuffer->resize(originalSize + dataLen, 0);

				CryptoPP::Salsa20::Encryption& keyObj = pkt.incoming ?
					streamObj->recvSalsa : 
					streamObj->sendSalsa;

				//i don't know if exceptions get thrown here but can't hurt to try
				try {
					keyObj.ProcessData(decryptedBuffer->data()+originalSize, pkt.data.data(), dataLen);
				}
				catch (const CryptoPP::Exception& exception) {
					QString msg = "An exception was caught during salsa decrypt of multipacket data.";
					msg = msg + " This is usually due to incorrect deserialisation";
					UIaddLogMsg(msg, getLatestDecryptProcess(), uiMsgQueue);
					currentStreamObj->failed = true;
					UInotifyStreamState(currentMsgStreamID, eStreamState::eStreamFailed, uiMsgQueue);
					return;
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

//get 1 byte from decrypted buffer
UINT8 packet_processor::consume_Byte()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 1)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_buffer_next_packet();
	}

	if (decryptedIndex >= decryptedBuffer->size()) {
		errorFlag = eDecodingErr::eErrUnderflow;
		return 0;
	}

	unsigned char result = decryptedBuffer->at(decryptedIndex);
	decryptedIndex += 1;
	remainingDecrypted -= 1;
	return result;
}

//get 2 bytes from decrypted buffer
UINT16 packet_processor::consume_WORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 2)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_buffer_next_packet();
	}

	if (decryptedIndex >= decryptedBuffer->size() - 1) {
		errorFlag = eDecodingErr::eErrUnderflow;
		return 0;
	}

	unsigned short result = getUshort(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 2;
	remainingDecrypted -= 2;
	return result;
}

//get 4 bytes from decrypted buffer
UINT32 packet_processor::consume_DWORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 4)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_buffer_next_packet();
	}

	if (decryptedIndex >= decryptedBuffer->size() - 3) {
		errorFlag = eDecodingErr::eErrUnderflow;
		return 0;
	}

	DWORD result = getUlong(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 4;
	remainingDecrypted -= 4;
	return result;
}

//get 8 bytes from decrypted buffer
UINT64 packet_processor::consume_QWORD()
{
	if (errorFlag != eDecodingErr::eNoErr) return 0;

	while (remainingDecrypted < 8)
	{
		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_buffer_next_packet();
	}
	if (decryptedIndex >= decryptedBuffer->size() - 7) {
		errorFlag = eDecodingErr::eErrUnderflow;
		return 0;
	}
	UINT64 result = getUlonglong(&decryptedBuffer->at(decryptedIndex));
	decryptedIndex += 8;
	remainingDecrypted -= 8;
	return result;
}

//consume and discard byteCount bytes from decrypted buffer
void packet_processor::consume_blob(ushort byteCount)
{
	if (errorFlag != eDecodingErr::eNoErr) return;
	if (byteCount > 10000) //smoke test - may need adjusting if game ever sends a blob this big
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		return;
	}

	while (remainingDecrypted < byteCount)
	{
		if (errorFlag != eDecodingErr::eNoErr) return;
		continue_buffer_next_packet();
	}

	decryptedIndex += byteCount;
	remainingDecrypted -= byteCount;
}

//consume byteCount bytes from decrypted buffer and store in blobBuf
void packet_processor::consume_blob(ushort requiredBytes, vector <byte>& blobBuf)
{
	if (errorFlag != eDecodingErr::eNoErr) return;
	/*
	last ditch "something is awful here" check
	for bad decoding intepreting inappropriate things as length fields
	*/
	if (requiredBytes > 10000)
	{
		errorFlag = eDecodingErr::eErrUnderflow;
		return;
	}

	while (remainingDecrypted < requiredBytes)
	{
		if (errorFlag != eDecodingErr::eNoErr) return;
		continue_buffer_next_packet();
	}

	blobBuf = vector<byte>(decryptedBuffer->data() + decryptedIndex,
		decryptedBuffer->data() + decryptedIndex + requiredBytes);

	decryptedIndex += requiredBytes;
	remainingDecrypted -= requiredBytes;
}

//read a wstring of size 'bytesLength' from decrypted buffer
std::wstring packet_processor::consumeWString(size_t bytesLength)
{

	if (errorFlag != eDecodingErr::eNoErr) return L"<exileSniffer Decoding Error>";
	if (bytesLength == 0)
		return L"";

	while (remainingDecrypted < bytesLength)
	{
		if (bytesLength > 500)
		{
			std::stringstream err;
			err << "Warning! Long string " << bytesLength << " possible bad byte order" << std::endl;
			UIaddLogMsg(QString::fromStdString(err.str()), activeClientPID, uiMsgQueue);
		}

		if (errorFlag != eDecodingErr::eNoErr) return 0;
		continue_buffer_next_packet();
	}

	std::string msgmb(decryptedBuffer->data() + decryptedIndex,
		decryptedBuffer->data() + decryptedIndex + bytesLength);
	std::wstring msg = mb_to_utf8(msgmb);

	decryptedIndex += bytesLength;
	remainingDecrypted -= bytesLength;

	return msg;
}

/*
consume from decryption buffer a 2 byte length field 
and get a wstring of that length
place result in the 'container' json object with name 'name'
*/
void packet_processor::consume_add_lenprefix_string(std::wstring name, WValue& container, rapidjson::Document::AllocatorType& allocator)
{
	WValue nameItem(name.c_str(), allocator);

	ushort stringlen = ntohs(consume_WORD());
	if (stringlen > 0)
	{
		std::wstring stringval = consumeWString(stringlen * 2);
		WValue stringItem(stringval.c_str(), allocator);
		container.AddMember(nameItem, stringItem, allocator);
	}
	else
	{
		container.AddMember(nameItem, L"", allocator);
	}
	
}

//rewind time to before we read 'countBytes' bytes
void packet_processor::rewind_buffer(size_t countBytes)
{
	assert(!restorePoint.active);
	restorePoint.active = true;

	restorePoint.savedIndex = decryptedIndex;
	restorePoint.savedRemaining = remainingDecrypted;
	decryptedIndex -= countBytes;
	remainingDecrypted += countBytes;
}

//revert forward to before we called rewind_buffer
void packet_processor::restore_buffer()
{
	assert(restorePoint.active);
	restorePoint.active = false;

	this->decryptedIndex = restorePoint.savedIndex;
	this->remainingDecrypted = restorePoint.savedRemaining;
}

/*
stop processing any more of the packet - abandoning its message(s).
intended for use when we don't know how to process the rest
of a message
*/
void packet_processor::abandon_processing()
{
	errorFlag = eDecodingErr::eAbandoned;
	errorCount += 1;

	decryptedIndex += remainingDecrypted;
	remainingDecrypted = 0;
}

//retrives the variable sized multibyte encoded values POE uses
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

//retrives the variable sized multibyte encoded values POE uses - with negatives
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

//consume 'size' bytes, return them as a hex encoded string
std::wstring packet_processor::consume_hexblob(unsigned int size)
{
	vector <byte> blob;
	consume_blob(size, blob);

	std::wstringstream keyhexss;
	keyhexss << std::setfill(L'0') << std::uppercase << " ";
	for (int i = 0; i < blob.size(); ++i)
	{
		byte item = blob.at(i);
		if (item)
			keyhexss << " " << std::hex << std::setw(2) << (int)item;
		else
			keyhexss << " 00";
	}

	std::wstring keyhex(keyhexss.str());
	return keyhex;
}