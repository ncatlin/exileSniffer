#include "stdafx.h"
#include "clientData.h"

clientHexData::~clientHexData()
{
	filteredLogfile.close();
	unfilteredLogfile.close();
}

std::string clientHexData::get_logpath(bool isfiltered)
{
	QString filepath;

	if (isfiltered)
	{
		filepath = storageDir.filePath("-filtered.log");
	}
	else
	{
		filepath = storageDir.filePath("-nofilter.log");
	}

	return filepath.toStdString();
}

std::ofstream& clientHexData::get_filtered_hexlog()
{
	if (filteredLogfile.is_open() || !logFiltered)
		return filteredLogfile;

	filteredLogfile = std::ofstream(get_logpath(true),
		std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	if (!filteredLogfile.is_open())
		logFiltered = false;

	return filteredLogfile;
}

std::ofstream& clientHexData::get_unfiltered_hexlog()
{
	if (unfilteredLogfile.is_open() || !logUnfiltered)
		return unfilteredLogfile;

	
	unfilteredLogfile = std::ofstream(get_logpath(false),
		std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	if (!unfilteredLogfile.is_open())
		logUnfiltered = false;

	return unfilteredLogfile;
}