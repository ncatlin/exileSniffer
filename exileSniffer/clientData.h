#pragma once


#include "uiMsg.h"
class clientHexData
{
public:
	clientHexData() {};
	~clientHexData() {};

	bool isLoggedIn = false;

	vector <UI_RAWHEX_PKT *> rawHexPackets;
};

