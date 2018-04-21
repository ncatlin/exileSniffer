#include "stdafx.h"
#include "utilities.h"


std::string timestamp()
{
	char tstamp[9];
	time_t t = time(0);
	struct tm *tm;

	tm = gmtime(&t);
	strftime(tstamp, sizeof(tstamp), "%H:%M:%S", tm);

	return std::string(tstamp);
}

unsigned int getUlong(void *ptr)
{
	return *(DWORD*)(ptr);
}

unsigned int getUshort(void *ptr)
{
	return *(unsigned short*)(ptr);
}

std::wstring mb_to_utf8(std::string utf16_string)
{
	int size = utf16_string.size();
	std::wstring url1(reinterpret_cast<wchar_t*>((byte *)utf16_string.data()), (size) / sizeof(wchar_t));
	return url1;
}

HANDLE connectPipe(std::wstring pipename)
{
	const wchar_t* szName = pipename.c_str();
	HANDLE sniffpipe = 0;

	while (true)
	{
		sniffpipe = CreateFile(
			szName,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 

							// Break if the pipe handle is valid. 

		if (sniffpipe != INVALID_HANDLE_VALUE)
			break;

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			//_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			return false;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(szName, 20000))
		{
			//printf("Could not open pipe: 20 second wait timed out.");
			return false;
		}
	}

	BOOL   fSuccess = FALSE;
	DWORD  cbRead, cbToWrite, cbWritten, dwMode;
	dwMode = PIPE_READMODE_MESSAGE;
	fSuccess = SetNamedPipeHandleState(
		sniffpipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess)
	{
		printf("SetNamedPipeHandleState failed. GLE=%d\n", GetLastError());
		return false;
	}

	return sniffpipe;
}

bool checkPipe(HANDLE pipe, std::queue< std::vector<byte>> *pktQueue)
{
	DWORD available, remainingSize;
	if (!PeekNamedPipe(pipe, NULL, NULL, NULL, &available, &remainingSize) || !available)
	{
		if (GetLastError() == ERROR_BROKEN_PIPE) {
			return false;
		}
	}
	if (!available) return false;

	while (true)
	{
		if (!PeekNamedPipe(pipe, NULL, NULL, 0, &available, &remainingSize) || !available)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE) {
				return true;
			}
		}

		if (!available) return true;

		std::vector<byte> pkt;
		pkt.resize(remainingSize);

		DWORD dataRead = 1;

		if (!ReadFile(pipe, (byte *)(pkt.data()), remainingSize, &dataRead, NULL))
		{
			int err = GetLastError();
			if (err == ERROR_MORE_DATA)
			{
				printf(" MORE DATA|?\n");
			}
			else
			{
				if (err != ERROR_BROKEN_PIPE)
					std::cerr << "Error: pipe read ERROR: " << err << "." << std::endl;
				return false;
			}
		}
		if (dataRead != pkt.size())
			pkt.resize(dataRead);
		pktQueue->emplace(pkt);
	}
}

std::wstring epochms_to_timestring(long long epochms)
{
	std::chrono::milliseconds dur(epochms);
	std::chrono::time_point<std::chrono::system_clock> dt(dur);
	std::time_t rawtime = std::chrono::system_clock::to_time_t(dt);

	struct tm * timeinfo;
	timeinfo = localtime(&rawtime);

	wchar_t buf[100];
	wcsftime(buf, 100, L"%b%d %H:%M:%S:", timeinfo);
	std::wstring result = std::wstring(buf) + std::to_wstring((epochms % 1000));
	return result;
}

long long ms_since_epoch()
{
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast< std::chrono::milliseconds>(now);
	auto sinceEpoch = now_ms.time_since_epoch();
	return sinceEpoch.count();
}
