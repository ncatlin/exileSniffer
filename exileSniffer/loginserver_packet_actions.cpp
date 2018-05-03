#include "stdafx.h"
#include "exileSniffer.h"
#include "packetIDs.h"


void exileSniffer::init_loginPkt_Actioners()
{
	loginPktActioners[LOGIN_CLI_KEEP_ALIVE] = &exileSniffer::action_LOGIN_CLI_KEEP_ALIVE;
	loginPktActioners[LOGIN_EPHERMERAL_PUBKEY] = &exileSniffer::action_LOGIN_EPHERMERAL_PUBKEY;
	loginPktActioners[LOGIN_CLI_AUTH_DATA] = &exileSniffer::action_LOGIN_CLI_AUTH_DATA;	
	loginPktActioners[LOGIN_SRV_UNK0x4] = &exileSniffer::action_LOGIN_SRV_UNK0x4;
	loginPktActioners[LOGIN_CLI_CHANGE_PASSWORD] = &exileSniffer::action_LOGIN_CLI_CHANGE_PASSWORD;
	loginPktActioners[LOGIN_CLI_DELETE_CHARACTER] = &exileSniffer::action_LOGIN_CLI_DELETE_CHARACTER;
	loginPktActioners[LOGIN_CLI_CHARACTER_SELECTED_SELECTED] = &exileSniffer::action_LOGIN_CLI_CHARACTER_SELECTED;
	loginPktActioners[LOGIN_SRV_NOTIFY_GAMESERVER] = &exileSniffer::action_LOGIN_SRV_NOTIFY_GAMESERVER;
	loginPktActioners[LOGIN_CLI_CREATED_CHARACTER] = &exileSniffer::action_LOGIN_CLI_CREATED_CHARACTER;
	loginPktActioners[LOGIN_SRV_CHAR_LIST] = &exileSniffer::action_LOGIN_SRV_CHAR_LIST;
	loginPktActioners[LOGIN_SRV_FINAL_PKT] = &exileSniffer::action_LOGIN_SRV_FINAL_PKT;
	loginPktActioners[LOGIN_CLI_REQUEST_RACE_DATA] = &exileSniffer::action_LOGIN_CLI_REQUEST_RACE_DATA;
	loginPktActioners[LOGIN_SRV_LEAGUE_LIST] = &exileSniffer::action_LOGIN_SRV_LEAGUE_LIST;
	loginPktActioners[LOGIN_CLI_REQUEST_LEAGUES] = &exileSniffer::action_LOGIN_CLI_REQUEST_LEAGUES;
}

void exileSniffer::action_decoded_login_packet(UIDecodedPkt& decoded)
{
	auto it = loginPktActioners.find(decoded.messageID);
	if (it != loginPktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded, NULL);

		++decodedCount_Displayed_Filtered.first;
		updateDecodedFilterLabel();
	}
	else
	{
		stringstream err;
		err << "ERROR! no action setup for known login msg id 0x" << std::hex << decoded.messageID;
		add_metalog_update(QString::fromStdString(err.str()), decoded.clientProcessID());
	}

}


void exileSniffer::action_LOGIN_CLI_KEEP_ALIVE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client keepalive message";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_EPHERMERAL_PUBKEY(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 keyLen = obj.get_UInt32(L"KeySize");
	UINT32 sigLen = obj.get_UInt32(L"SignatureSize");

	if (!analysis)
	{
		std::wstringstream summary;
		summary <<"Diffie-Hellman ephemeral public key (" << std::dec << keyLen << " bytes)" ;
		if (sigLen > 0)
			summary << " + DSA signature ("<< sigLen << " bytes)";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::wstring key = obj.get_wstring(L"EphermeralKey");

	wstringstream analysisStream;

	analysisStream << std::dec << keyLen << " byte ";
	analysisStream << ((obj.streamFlags & PKTBIT_INBOUND) ? "Server" : "Client");

	analysisStream << " ephermeral Diffie-Hellman public key: " << std::endl;
	analysisStream << "" << key << std::endl;
	analysisStream << std::endl;

	if (sigLen)
	{
		std::wstring sig = obj.get_wstring(L"Signature");
		analysisStream << std::dec << sigLen << " byte DSA signature:" << std::endl;
		analysisStream << sig;
	}
	*analysis = QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_LOGIN_CLI_AUTH_DATA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	std::wstring accountName = obj.get_wstring(L"AccountName");


	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client authentication data for account: "+QString::fromStdWString(accountName);
		addDecodedListEntry(listentry, &obj);
		return;
	}

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	std::wstring clientHash = obj.get_wstring(L"ClientEXEHash");
	std::wstring nwkIfaceHash = obj.get_wstring(L"MACHash");
	UINT32 savedFlag1 = obj.get_UInt32(L"SavedFlag1");
	UINT32 savedFlag2 = obj.get_UInt32(L"SavedFlag2");

	wstringstream analysisStream;
	analysisStream << "Client authentication data:" << std::endl;
	analysisStream << "Unknown value 1: " << unk1 << std::endl;
	analysisStream << std::endl;

	analysisStream << "Account: " << accountName << std::endl;
	analysisStream << std::endl;

	analysisStream << "production_login.credentials: [redacted]" << std::endl;
	analysisStream << std::endl;

	analysisStream << "Sha256 hash of client binary: " << std::endl;
	analysisStream << clientHash << std::endl;
	analysisStream << std::endl;

	analysisStream << "Sha256 hash of partial network interface MAC list: " << std::endl;
	analysisStream << nwkIfaceHash << std::endl;
	analysisStream << std::endl;

	analysisStream << "Saved creds flag 1: " << savedFlag1 << std::endl;
	analysisStream << std::endl;

	analysisStream << "Saved creds flag 2: " << savedFlag2 << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_SRV_UNK0x4(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Unknown packet 0x04";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	////wstringstream analysisStream;
	////*analysis = QString::fromStdWString(analysisStream.str());
}

wstring bannerCodeLookup(uint code)
{
	switch (code)
	{
	case 1: return L"Red";
	case 2: return L"Blue";
	case 3: return L"Green";
	default: return L"None";
	}
}

void exileSniffer::action_LOGIN_SRV_CHAR_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	auto it = obj.payload.FindMember(L"CharacterList");
	if (it == obj.payload.MemberEnd())
	{
		add_metalog_update("Warning: No CharacterList found in payload of LOGIN_SRV_CHAR_LIST", obj.clientProcessID());
		return;
	}

	WValue &charList = it->value;
	unsigned short listSize = charList.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Character list with "+QString::number(listSize)+" characters";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	for (auto it = charList.Begin(); it != charList.End(); it++)
	{
		std::wstring name = it->FindMember(L"Name")->value.GetString();
		std::wstring league = it->FindMember(L"League")->value.GetString();
		uint bannerCode = it->FindMember(L"Banner")->value.GetUint();

		analysisStream << std::dec;
		analysisStream << name << " (" << league << "):" << std::endl;
		analysisStream << "\t Level: " << it->FindMember(L"Level")->value.GetUint() << std::endl;
		analysisStream << "\t Class: " << it->FindMember(L"Class")->value.GetUint() << std::endl;
		analysisStream << "\t Banner: " << bannerCode << " ("<< bannerCodeLookup(bannerCode)<<")" << std::endl;

		analysisStream << std::hex;
		//one of these will be the code sent as char chosen code
		analysisStream << "\t Unk1: 0x" << it->FindMember(L"Unk1")->value.GetUint() << std::endl;
		analysisStream << "\t Unk2: 0x" << it->FindMember(L"Unk2")->value.GetUint() << std::endl;
		analysisStream << "\t Unk3: 0x" << it->FindMember(L"Unk3")->value.GetUint() << std::endl;
		analysisStream << "\t Unk4: 0x" << it->FindMember(L"Unk4")->value.GetUint() << std::endl;
		analysisStream << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_LOGIN_SRV_FINAL_PKT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	
	UINT32 arg = obj.get_UInt32(L"Arg");
	
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Final loginserver packet. Arg: 0x"+QString::number(arg,16);
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_CHANGE_PASSWORD(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Password change";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_DELETE_CHARACTER(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Delete character";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_CHARACTER_SELECTED(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Character selected";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_SRV_NOTIFY_GAMESERVER(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 areaCode = obj.get_UInt32(L"AreaCode");
	UINT32 connID = obj.get_UInt32(L"ConnectionID");

	auto gbit = obj.payload.FindMember(L"ServerBlobs");
	if (gbit == obj.payload.MemberEnd())
	{
		add_metalog_update("Warning: No ServerBlobs found in payload of LOGIN_SRV_NOTIFY_GAMESERVER", obj.clientProcessID());
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Gameserver connection information [BAD]";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	WValue &blobList = gbit->value;
	unsigned short blobListSize = blobList.Size();

	std::wstring areaname;
	ggpk.lookup_areaCode(areaCode, areaname);

	if (!analysis)
	{
		DWORD firstIPDW = blobList[0].FindMember(L"IPAddr")->value.GetUint();
		DWORD firstPort = blobList[0].FindMember(L"Port")->value.GetUint();

		wstringstream summary;
		summary << "Gameserver connection info: " << IPToString(firstIPDW) <<
			":" << std::dec << firstPort << " (" << areaname << ")";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//todo 

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_CREATED_CHARACTER(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	std::wstring name = obj.get_wstring(L"Name");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Character created: "+QString::fromStdWString(name);
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	analysisStream << "Name: " << name << std::endl;
	analysisStream << "League: " << obj.get_wstring(L"League") << std::endl;
	analysisStream << "Class: " << obj.get_wstring(L"Class") << std::endl;
	analysisStream << "Unk1: " << obj.get_UInt64(L"Unk1") << std::endl;
	analysisStream << "\nTrailing data not handled" << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_REQUEST_RACE_DATA(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested race data";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_SRV_LEAGUE_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	auto evntIt = obj.payload.FindMember(L"EventList");
	WValue &blobList = evntIt->value;
	unsigned short blobListSize = blobList.Size();

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "League list with "+QString::number(blobListSize)+" entries";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	for (auto it = blobList.Begin(); it != blobList.End(); it++)
	{
		analysisStream << "Name: " << it->FindMember(L"Name")->value.GetString() << std::endl;
		analysisStream << "Label1: " << it->FindMember(L"Label1")->value.GetString() << std::endl;
		analysisStream << "Label2: " << it->FindMember(L"Label2")->value.GetString() << std::endl;

		analysisStream << "StartTime: " << it->FindMember(L"StartTime")->value.GetUint64() << std::endl;
		analysisStream << "RegisterTime: " << it->FindMember(L"RegisterTime")->value.GetUint64() << std::endl;
		analysisStream << "Time3: " << it->FindMember(L"Unk5_64")->value.GetUint64() << std::endl;
		analysisStream << "x7: " << it->FindMember(L"Unk6")->value.GetUint() << std::endl;
		analysisStream << "x8: " << it->FindMember(L"Unk7")->value.GetUint() << std::endl;

		analysisStream << std::endl;
	}

	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_LOGIN_CLI_REQUEST_LEAGUES(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested league list";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//wstringstream analysisStream;
	//*analysis = QString::fromStdWString(analysisStream.str());
}
