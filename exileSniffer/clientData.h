#pragma once

#include "uiMsg.h"
class clientData
{
public:
	clientData();
	~clientData();

	void cleanup();

	DWORD processID;
	bool isRunning;
	bool isLoggedIn = false;

	vector <UI_RAWHEX_PKT *> rawHexPackets;
};

