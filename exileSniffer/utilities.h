#pragma once

std::string timestamp();

UINT64 getUlonglong(void *ptr);
UINT32 getUlong(void *ptr);
UINT16 getUshort(void *ptr);

std::wstring mb_to_utf8(std::string utf16_string);
HANDLE connectPipe(std::wstring pipename);
bool checkPipe(HANDLE pipe, std::deque< std::vector<byte>> *pktQueue);

std::wstring epochms_to_timestring(long long epochms);
long long ms_since_epoch();

