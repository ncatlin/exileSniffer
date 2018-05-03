#pragma once

#define ERASE_FROM_VECTOR(v, x) v.erase(std::remove(v.begin(), v.end(), x), v.end())
#define FIND_IN_VECTOR(v, x) std::find(v.begin(), v.end(), x)
#define IS_IN_VECTOR(v, x) (FIND_IN_VECTOR(v, x) != v.end())
#define WSTRING_CONTAINS(s, t) (s.find(t) != std::wstring::npos)
std::string timestamp();

UINT64 getUlonglong(void *ptr);
UINT32 getUlong(void *ptr);
UINT16 getUshort(void *ptr);

std::wstring mb_to_utf8(std::string utf16_string);
HANDLE connectPipe(std::wstring pipename);
bool checkPipe(HANDLE pipe, std::deque< std::vector<byte>> *pktQueue);

std::wstring epochms_to_timestring(long long epochms);
long long ms_since_epoch();
QString msToQStringSeconds(long long start, long long eventTime);

std::wstring IPToString(DWORD ip);

QString byteVecToHex(std::vector<byte> data);
std::vector<byte> extract_Iter_from_salsaObj(CryptoPP::Salsa20::Encryption& keyblob);