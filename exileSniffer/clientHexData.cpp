#include "stdafx.h"
#include "clientHexData.h"

clientHexData::clientHexData(bool filtered, bool unfiltered, QDir filedir)
{
	logFiltered = filtered;
	logUnfiltered = unfiltered;
	storageDir = filedir;

	if (!storageDir.exists()) { storageDir.mkpath("."); }
}

clientHexData::~clientHexData()
{
	filteredLogfile.close();
	unfilteredLogfile.close();
}

std::string clientHexData::get_logpath(bool isfiltered)
{
	QString filepath;

	char timestamp[32];
	time_t t = time(0);
	struct tm *tm = gmtime(&t);
	strftime(timestamp, sizeof(timestamp), "%m%d-%H-%M-%S", tm);

	QString timeprefix(timestamp);
	if (isfiltered)
	{
		filepath = storageDir.filePath(timeprefix + "_filtered.log");
	}
	else
	{
		filepath = storageDir.filePath(timeprefix + "_nofilter.log");
	}

	return filepath.toStdString();
}

std::ofstream& clientHexData::get_filtered_hexlog()
{
	if (filteredLogfile.is_open() || !logFiltered)
		return filteredLogfile;

	filteredLogfile = std::ofstream(get_logpath(true),
		std::ofstream::out | std::ofstream::app);

	if (!filteredLogfile.is_open())
		logFiltered = false;

	return filteredLogfile;
}

std::ofstream& clientHexData::get_unfiltered_hexlog()
{
	if (unfilteredLogfile.is_open() || !logUnfiltered)
		return unfilteredLogfile;
	
	unfilteredLogfile = std::ofstream(get_logpath(false),
		std::ofstream::out | std::ofstream::app);

	if (!unfilteredLogfile.is_open())
		logUnfiltered = false;

	return unfilteredLogfile;
}