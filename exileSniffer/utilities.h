#pragma once

std::string timestamp();

unsigned int getUlong(void *ptr);
unsigned int getUshort(void *ptr);
std::wstring mb_to_utf8(std::string utf16_string);
HANDLE connectPipe(std::wstring pipename);
bool checkPipe(HANDLE pipe, std::queue< std::vector<byte>> *pktQueue);