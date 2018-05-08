#pragma once
#include "uiMsg.h"
#include <fstream>

class clientHexData
{
public:
	clientHexData(bool filtered, bool unfiltered, QDir filedir);
	~clientHexData();


	std::ofstream& get_filtered_hexlog();
	std::ofstream& get_unfiltered_hexlog();
	std::string get_logpath(bool isfiltered);

	bool isLoggedIn = false;
	bool logFiltered = false;
	bool logUnfiltered = false;
	QDir storageDir;

	vector <UI_RAWHEX_PKT *> rawHexPackets;

	std::ofstream filteredLogfile;
	std::ofstream unfilteredLogfile;
};

