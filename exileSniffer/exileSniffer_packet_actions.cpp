/*
These member functions take the data produced by the decoders and
present it to the user in a way that is meaningful to them. 

It maintains game state for each client. eg: The names associated 
with object ID's and skill ID's in respective list packets can be 
referred to when those object ID's are seen in future 'object ID 
used skill ID' packets.

These operate in the UI thread and should be primarily low overhead
UI update operations
*/

#include "stdafx.h"
#include "exileSniffer.h"
#include "packetIDs.h"
#include "inventory.h"

std::wstring explainModifier(byte lastByte)
{
	/*
	00001000 click       0x8
	00001001 +shift		 0x9
	00001010 +windowOpen 0xa
	00001100 +ctrl		 0xc

	8 = inventory/etc open
	9 = shift held
	c = control held
	*/

	std::wstring result = L"";

	if (lastByte & 0x1)
		result += L"+shift ";
	if (lastByte & 0x2)
		result += L"+openPane ";
	if (lastByte & 0x4)
		result += L"+ctrl ";
	return result;
}


void exileSniffer::init_DecodedPktActioners()
{
	decodedPktActioners[CLI_CHAT_MSG_ITEMS] = &exileSniffer::action_CLI_CHAT_MSG_ITEMS;
	decodedPktActioners[CLI_CHAT_MESSAGE] = &exileSniffer::action_CLI_CHAT_MSG;
	decodedPktActioners[CLI_PING_CHALLENGE] = &exileSniffer::action_CLI_PING_CHALLENGE;
	decodedPktActioners[SRV_PING_RESPONSE] = &exileSniffer::action_SRV_PING_RESPONSE;
	decodedPktActioners[SRV_AREA_INFO] = &exileSniffer::action_SRV_AREA_INFO;
	decodedPktActioners[CLI_CHAT_COMMAND] = &exileSniffer::action_CLI_CHAT_COMMAND;
	decodedPktActioners[SRV_CHAT_MESSAGE] = &exileSniffer::action_SRV_CHAT_MESSAGE;
	decodedPktActioners[SRV_SERVER_MESSAGE] = &exileSniffer::action_SRV_SERVER_MESSAGE;
	decodedPktActioners[CLI_LOGGED_OUT] = &exileSniffer::action_CLI_LOGGED_OUT;

	decodedPktActioners[SRV_PRELOAD_MONSTER_LIST] = &exileSniffer::action_SRV_PRELOAD_MONSTER_LIST;
	decodedPktActioners[SRV_UNK_0x13] = &exileSniffer::action_SRV_UNK_0x13;

	decodedPktActioners[SRV_PLAYER_ITEMS] = &exileSniffer::action_SRV_PLAYER_ITEMS;
	decodedPktActioners[CLI_CLICKED_GROUND_ITEM] = &exileSniffer::action_CLI_CLICKED_GROUND_ITEM;
	decodedPktActioners[CLI_ACTION_PREDICTIVE] = &exileSniffer::action_CLI_ACTION_PREDICTIVE;
	decodedPktActioners[SRV_INSTANCE_SERVER_DATA] = &exileSniffer::action_SRV_INSTANCE_SERVER_DATA;
	decodedPktActioners[CLI_PICKUP_ITEM] = &exileSniffer::action_CLI_PICKUP_ITEM;
	decodedPktActioners[CLI_PLACE_ITEM] = &exileSniffer::action_CLI_PLACE_ITEM;
	decodedPktActioners[CLI_REMOVE_SOCKET] = &exileSniffer::action_CLI_REMOVE_SOCKET;
	decodedPktActioners[CLI_INSERT_SOCKET] = &exileSniffer::action_CLI_INSERT_SOCKET;

	decodedPktActioners[CLI_LEVEL_SKILLGEM] = &exileSniffer::action_CLI_LEVEL_SKILLGEM;
	decodedPktActioners[CLI_SKILLPOINT_CHANGE] = &exileSniffer::action_CLI_SKILLPOINT_CHANGE;
	decodedPktActioners[CLI_CANCEL_BUF] = &exileSniffer::action_CLI_CANCEL_BUF;
	decodedPktActioners[CLI_SET_HOTBARSKILL] = &exileSniffer::action_CLI_SET_HOTBARSKILL;
	decodedPktActioners[SRV_SKILL_SLOTS_LIST] = &exileSniffer::action_SRV_SKILL_SLOTS_LIST;

	decodedPktActioners[CLI_USE_BELT_SLOT] = &exileSniffer::action_CLI_USE_BELT_SLOT;
	decodedPktActioners[CLI_USE_ITEM] = &exileSniffer::action_CLI_USE_ITEM;

	decodedPktActioners[CLI_UNK_x56] = &exileSniffer::action_CLI_UNK_x56;
	decodedPktActioners[SRV_UNK_ACCT_SOCIAL_NAME] = &exileSniffer::action_SRV_UNK_ACCT_SOCIAL_NAME;
	
	decodedPktActioners[CLI_REQUEST_PUBLICPARTIES] = &exileSniffer::action_CLI_REQUEST_PUBLICPARTIES;
	decodedPktActioners[SRV_RESPOND_PUBLICPARTIES] = &exileSniffer::action_SRV_RESPOND_PUBLICPARTIES;
	decodedPktActioners[SRV_CREATE_ITEM] = &exileSniffer::action_SRV_CREATE_ITEM;
	decodedPktActioners[SRV_SLOT_ITEMSLIST] = &exileSniffer::action_SRV_SLOT_ITEMSLIST;
	decodedPktActioners[CLI_SKILLPANE_ACTION] = &exileSniffer::action_CLI_SKILLPANE_ACTION;
	decodedPktActioners[CLI_MICROSTRANSACTIONPANE_ACTION] = &exileSniffer::action_CLI_MICROSTRANSACTIONPANE_ACTION;
	decodedPktActioners[CLI_PACKET_EXIT] = &exileSniffer::action_CLI_PACKET_EXIT;
	decodedPktActioners[CLI_USED_SKILL] = &exileSniffer::action_CLI_USED_SKILL;
	decodedPktActioners[CLI_CLICK_OBJ] = &exileSniffer::action_CLI_CLICK_OBJ;
	decodedPktActioners[CLI_MOUSE_HELD] = &exileSniffer::action_CLI_MOUSE_HELD;
	decodedPktActioners[CLI_MOUSE_RELEASE] = &exileSniffer::action_CLI_MOUSE_RELEASE;
	decodedPktActioners[SRV_DISPLAY_BUILTIN_MSG] = &exileSniffer::action_SRV_DISPLAY_BUILTIN_MSG;
	decodedPktActioners[CLI_GUILD_CREATE] = &exileSniffer::action_CLI_GUILD_CREATE;
	decodedPktActioners[SRV_MOBILE_USED_SKILL] = &exileSniffer::action_SRV_MOBILE_USED_SKILL;
	decodedPktActioners[SRV_MOBILE_UNK_0xeb] = &exileSniffer::action_SRV_MOBILE_UNK_0xeb;
	decodedPktActioners[SRV_MOBILE_UPDATE_HMS] = &exileSniffer::action_SRV_MOBILE_UPDATE_HMS;
	decodedPktActioners[SRV_STAT_CHANGED] = &exileSniffer::action_SRV_STAT_CHANGED;
	decodedPktActioners[CLI_REQUEST_PLAYERID] = &exileSniffer::action_CLI_REQUEST_PLAYERID;
	decodedPktActioners[SRV_UNKNOWN_0x111] = &exileSniffer::action_SRV_UNKNOWN_0x111;
	decodedPktActioners[SRV_NOTIFY_PLAYERID] = &exileSniffer::action_SRV_NOTIFY_PLAYERID;
	decodedPktActioners[CLI_OPTOUT_TUTORIALS] = &exileSniffer::action_CLI_OPTOUT_TUTORIALS;
	decodedPktActioners[SRV_HEARTBEAT] = &exileSniffer::action_SRV_HEARTBEAT;
	decodedPktActioners[SRV_ADD_OBJECT] = &exileSniffer::action_SRV_ADD_OBJECT;


}

void exileSniffer::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui.decodedList->columnCount(); tablecolumn++)
	{
		QTableWidgetItem *item = ui.decodedList->item(tablerow, tablecolumn);
		if(item)
			item->setBackgroundColor(colour);
	}
}

void exileSniffer::addDecodedListEntry(UI_DECODED_LIST_ENTRY& entry, UIDecodedPkt *obj)
{
	unsigned int rowIndex = ui.decodedList->rowCount();
	ui.decodedList->setRowCount(rowIndex + 1);
	if(ui.decodedAutoscrollCheck->isChecked())
		ui.decodedList->scrollToBottom();

	QTableWidgetItem *time = new QTableWidgetItem(entry.floatSeconds(startMSSinceEpoch));
	time->setData(Qt::UserRole, QVariant::fromValue<UIDecodedPkt *>(obj));
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_TIME, time);

	QTableWidgetItem *sender = new QTableWidgetItem(entry.sender());
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_SENDER, sender);

	QTableWidgetItem *pktID = new QTableWidgetItem(entry.hexPktID());
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_MSGID, pktID);

	QTableWidgetItem *summary = new QTableWidgetItem(entry.summary);
	ui.decodedList->setItem(rowIndex, HEADER_SECTION_SUMMARY, summary);

	if (entry.badDecode())
	{
		setRowColor(rowIndex, QColor(255, 150, 150, 255));
		return;
	}

	byte flags = entry.pktFlags();
	if (!(flags & PKTBIT_GAMESERVER))
	{
		if (flags & PKTBIT_LOGINSERVER)
			setRowColor(rowIndex, QColor(232, 226, 155, 255));
		else if (flags & PKTBIT_PATCHSERVER)
			setRowColor(rowIndex, QColor(153, 217, 234, 255));
		else
			setRowColor(rowIndex, QColor(255, 0, 0, 0));
	}
}

void exileSniffer::action_undecoded_packet(UIDecodedPkt& obj)
{
	obj.toggle_payload_operations(true);

	size_t sizeAfterID = obj.bufferOffsets.second - obj.bufferOffsets.first;
	wstringstream summary;
	summary << "Undecoded packet or multipacket blob ("
		<< std::dec << sizeAfterID << " byte";
	summary << ((sizeAfterID == 1) ? ")" : "s)");

	UI_DECODED_LIST_ENTRY listentry(obj);
	listentry.summary = QString::fromStdWString(summary.str());
	addDecodedListEntry(listentry, &obj);

	++decodedErrorPacketCount;
	updateDecodedFilterLabel();
}

void exileSniffer::action_decoded_packet(UIDecodedPkt& decoded)
{
	clientData *client = get_client(decoded.clientProcessID());
	if (!client) {
		std::cerr << "Error: Client had PID 0 when decoding pkt id 0x" << std::hex << decoded.messageID << std::endl;
		return;
	}

	if (!packet_passes_decoded_filter(decoded, client))
	{
		++decodedCount_Displayed_Filtered.second;
		updateDecodedFilterLabel();
		return;
	}

	auto it = decodedPktActioners.find(decoded.messageID);
	if (it != decodedPktActioners.end())
	{
		exileSniffer::actionFunc f = it->second;
		(this->*f)(decoded, NULL);

		++decodedCount_Displayed_Filtered.first;
		updateDecodedFilterLabel();
	}
	else
	{
		stringstream err;
		err << "ERROR! no action setup for known pkt id 0x" << std::hex << decoded.messageID;
		add_metalog_update(QString::fromStdString(err.str()), decoded.clientProcessID());
	}

}


void exileSniffer::action_SRV_PKT_ENCAPSULATED(UIDecodedPkt& obj, QString *analysis)
{
	/* no action for this, action the packet it encapsulates instead*/
	//silently dropped
}

void exileSniffer::action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) sent chat message with with linked items";
		addDecodedListEntry(listentry, &obj);
		return;
	}
	
}

void exileSniffer::action_CLI_CHAT_COMMAND(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	/*
	todo - load into presupplied data blob or lookup in ggpk
	0x04 = /remaining, 0x06=/pvp, 0x08=/oos, 0x0d=/fixmyhelmet, etc
	*/
	UINT32 commandsDatIndex = obj.get_UInt32(L"CommandID");
	UINT32 unk1 = obj.get_UInt32(L"Unk1");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Player(You) used command at commands.dat index: " << std::dec << commandsDatIndex <<
			" [unkVal 0x: " << std::hex << unk1 << "]";
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

std::wstring wchar_to_channel(wchar_t firstbyte)
{
	switch (firstbyte)
	{
	case L'#':
		return L"Global";
	case L'%':
		return L"Party";
	case L'@':
		return L"Whisper";
	case L'$':
		return L"Trade";
	case L'&':
		return L"Guild";
	default:
		return L"Local";
	}
}


void exileSniffer::action_SRV_CHAT_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	std::wstring name = obj.get_wstring(L"Name");
	std::wstring tag = obj.get_wstring(L"Tag");
	std::wstring text = obj.get_wstring(L"Text");
	wstring channel;
	if (!text.empty())
		channel = wchar_to_channel(text.front());

	ushort devFlag = obj.get_UInt32(L"Dev");

	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		
		wstringstream summary;
		if (devFlag)
			summary << "{-DEV-} ";
		summary << "Chat <" << channel << "> " << name << "[" << tag << "]: " << text;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SERVER_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent message";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_LOGGED_OUT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 arg = obj.get_UInt32(L"Unk1");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Game client logged out. [Arg: 0x"+QString::number((byte)arg, 16)+"]";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_CHAT_MSG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	//todo - item or not
	//todo - channel decode
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) spoke in chat: "+ QString::fromStdWString(obj.get_wstring(L"Message"));
		addDecodedListEntry(listentry, &obj);
		return;
	}

/*
	if (cliChatObj.linkedItemCount == 0)
		std::wcout << "[You In Chat]:\"" << cliChatObj.msg << "\"" << std::endl;
	else
	{
		int itemPos = cliChatObj.msg.find(0x5f, 0);
		std::wcout << "[You In Chat]:\"" << cliChatObj.msg.substr(0, itemPos);
		std::wcout << "_ITEM";
		std::wcout << cliChatObj.msg.substr(itemPos, cliChatObj.msg.size()) << std::endl;
	}
	*/
}

void exileSniffer::action_CLI_PING_CHALLENGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 challenge = obj.get_UInt64(L"Challenge");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Game Client sent ping challenge 0x" + QString::number(challenge, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_PING_RESPONSE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 response = obj.get_UInt64(L"Response");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent HNC response 0x" + QString::number(response, 16);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_AREA_INFO(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD areaCode = obj.get_UInt64(L"AreaCode");
	std::wstring areaname;
	lookup_areaCode(areaCode, areaname);

	auto it = obj.payload.FindMember(L"PreloadHashList");
	if (it == obj.payload.MemberEnd())
	{
		add_metalog_update("Warning: No list found in payload of SRV_AREA_INFO", obj.clientProcessID());
		return;
	}
	WValue &preloadList = it->value;
	unsigned short listSize = preloadList.Size();

	if (!analysis)
	{
		wstringstream summary;
		summary << "<Loading Area: " << areaname
			<< "> - Server sent environment and objects preload data (" << std::dec << listSize << " items)";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	DWORD variant = obj.get_UInt64(L"AreaVariant");
	analysisStream << "Animation preload information" << std::hex << std::endl;
	analysisStream << "Area " << areaname << " 0x" << areaCode << " in worldareas.dat>" << std::endl;
	analysisStream << "Area variant 0x" << variant << std::endl;
	analysisStream << "Difficulty name: " << obj.get_wstring(L"Difficulty") << std::endl;
	analysisStream << std::endl;

	analysisStream << "Unknown values: A: " << obj.get_UInt32(L"Unk1") <<
		" B: " << obj.get_UInt32(L"Unk2") <<
		" C: " << obj.get_UInt32(L"Unk3") <<
		" D: " << obj.get_UInt32(L"Unk4") << std::endl << std::endl;

	it = obj.payload.FindMember(L"Unk5_b4_1");
	if (it != obj.payload.MemberEnd())
	{
		analysisStream << "Control bit 4 set. Data:" << std::endl;
		analysisStream << "\t1: 0x" << obj.get_UInt64(L"Unk5_b4_1") << std::endl;
		analysisStream << "\t2: 0x" << obj.get_UInt32(L"Unk5_b4_2") << std::endl;
		analysisStream << "\t3: 0x" << obj.get_UInt32(L"Unk5_b4_3") << std::endl << std::endl;
	}

	it = obj.payload.FindMember(L"Unk5_b5_1");
	if (it != obj.payload.MemberEnd())
	{
		analysisStream << "Control bit 5 set. Data:" << std::endl;
		analysisStream << "\t1: 0x" << obj.get_UInt64(L"Unk5_b5_1") << std::endl << std::endl;
	}


	vector<std::pair<std::string, std::pair<std::string, DWORD>>> preloadVec;
	for (auto it = preloadList.Begin(); it != preloadList.End(); it++)
	{
		DWORD hash = it->GetUint64();
		std::string hashResult;
		std::string hashCategory;
		lookup_hash(hash, hashResult, hashCategory);
		preloadVec.push_back(make_pair(hashCategory, make_pair(hashResult, hash)));
	}
	sort(preloadVec.begin(), preloadVec.end());

	analysisStream << "List of object hashes to preload" << std::endl;

	std::string activeCategory = "";
	for (auto it = preloadVec.begin(); it != preloadVec.end(); it++)
	{
		std::string hashCategory = it->first;
		std::pair<std::string, DWORD> result_hash = it->second;
		if (hashCategory != activeCategory)
		{
			analysisStream << converter.from_bytes(hashCategory) << "s:" << std::endl;
			activeCategory = hashCategory;
		}

		analysisStream << "\t\"" << converter.from_bytes(result_hash.first) << "\" <0x" << result_hash.second << ">" << std::endl;
	}
	analysisStream << std::endl;

	analysisStream << "Byte list 1:" << std::endl;
	WValue &blist1 = obj.payload.FindMember(L"ByteList1")->value;
	for (auto it = blist1.Begin(); it != blist1.End(); it++)
	{
		analysisStream << "\t0x" << it->GetUint() << ", ";
	}
	analysisStream << std::endl << std::endl;

	analysisStream << "Byte list 2:" << std::endl;
	WValue &blist2 = obj.payload.FindMember(L"ByteList2")->value;
	for (auto it = blist2.Begin(); it != blist2.End(); it++)
	{
		analysisStream << "\t0x" << it->GetUint() << ", ";
	}
	analysisStream << std::endl << std::endl;


	auto plit = obj.payload.FindMember(L"ByteList4");
	if (plit != obj.payload.MemberEnd())
	{
		analysisStream << "Byte list 4:" << std::endl;
		WValue &blist4 = plit->value;
		for (auto it = blist4.Begin(); it != blist4.End(); it++)
		{
			analysisStream << "\t0x" << it->GetUint() << ", ";
		}
		analysisStream << std::endl << std::endl;
	}

	
	plit = obj.payload.FindMember(L"ByteList5");
	if (plit != obj.payload.MemberEnd())
	{
		analysisStream << "Byte list 5:" << std::endl;
		WValue &blist5 = plit->value;
		for (auto it = blist5.Begin(); it != blist5.End(); it++)
		{
			analysisStream << "\t0x" << it->GetUint() << ", ";
		}
		analysisStream << std::endl << std::endl;
	}


	
	plit = obj.payload.FindMember(L"PairList");
	if (plit != obj.payload.MemberEnd())
	{
		analysisStream << "PairList:" << std::endl;
		WValue &blist5 = plit->value;
		for (auto pairlistit = blist5.Begin(); pairlistit != blist5.End(); pairlistit++)
		{
			
			WValue &pair = *pairlistit;
			analysisStream << "\t0x" << pair[0].GetUint64() << ", 0x" << pair[1].GetUint64() << std::endl;
		}
		analysisStream << std::endl;
	}



	*analysis = QString::fromStdWString(analysisStream.str());

}

void exileSniffer::action_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt& obj, QString *analysis)
{

	obj.toggle_payload_operations(true);

	auto it = obj.payload.FindMember(L"PreloadList");
	if (it == obj.payload.MemberEnd())
	{
		add_metalog_update("Warning: No list found in payload of SRV_PRELOAD_MONSTER_LIST", obj.clientProcessID());
		return;
	}
	

	WValue &monsterList = it->value;
	unsigned short listSize = monsterList.Size();
	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent monster preload list with " << std::dec << listSize << " entries";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	std::vector<std::pair<unsigned short, unsigned short>> pairVec;
	for (auto it = monsterList.Begin(); it != monsterList.End(); it++)
	{
		auto pairArray = it->GetArray();
		if (pairArray.Size() != 2)
		{
			add_metalog_update("Warning: Bad pair array in SRV_PRELOAD_MONSTER_LIST", obj.clientProcessID());
			return;
		}
		unsigned short varietyIndex = pairArray[0].GetUint();
		unsigned short unk1 = pairArray[1].GetUint();
		pairVec.push_back(make_pair(unk1, varietyIndex));
	}

	std::sort(pairVec.rbegin(), pairVec.rend());

	wstringstream analysisStream;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	analysisStream << "Monster preload list sent by server <Indexes into MonsterVarieties.dat> " << std::endl;

	unsigned int activeCategory = pairVec.front().first + 1;
	for (auto it = pairVec.begin(); it != pairVec.end(); it++)
	{
		unsigned short category = it->first;
		unsigned short varietyIndex = it->second;

		if (category < activeCategory)
		{
			analysisStream << "Category: " << std::dec << category << std::endl;
			activeCategory = category;
		}

		if (varietyIndex < monsterVarieties.size())
		{
			//TODO: change encoding to 16 in this and generator script
			std::wstring todo_unicode_jsondatafile = converter.from_bytes(monsterVarieties.at(varietyIndex));
			analysisStream << "\t"<< "0x" << std::hex << varietyIndex <<
				": " << todo_unicode_jsondatafile <<std::endl;
		}
		else
			analysisStream << std::hex << "Unknown MonsterVariety Idx: 0x" << varietyIndex << std::endl;;
	}
	*analysis = QString::fromStdWString(analysisStream.str());

}

void exileSniffer::action_SRV_UNK_0x13(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	WValue &bloblist = obj.payload.FindMember(L"BlobList")->value;
	size_t listSize = bloblist.Size();


	std::wstring endString = obj.payload.FindMember(L"EndString")->value.GetString();
	DWORD endShort = obj.payload.FindMember(L"EndShort")->value.GetUint();
	DWORD endDWORD = obj.payload.FindMember(L"EndDWORD")->value.GetUint64();


	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent pck 0x13 with " << std::dec << listSize << 
			" entries. Endstring: "<<endString<<", EndVal1: 0x"<<std::hex<< endShort<<
			", EndVal2: 0x"<<endDWORD;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;

	int i = 0;
	for (auto listit = bloblist.Begin(); listit != bloblist.End(); listit++)
	{
		analysisStream << "Blob: " << std::dec << i << std::hex <<std::endl;
		analysisStream << "-------" << std::endl;
		analysisStream << "DW1: 0x" << listit->FindMember(L"DW1")->value.GetUint64() << std::endl;
		analysisStream << "DW2: 0x" << listit->FindMember(L"DW2")->value.GetUint64() << std::endl;
		analysisStream << "String: "<< listit->FindMember(L"UnkString")->value.GetString() << std::endl;
		analysisStream << "Short1: 0x" << listit->FindMember(L"Short1")->value.GetUint() << std::endl;
		analysisStream << "Short2: 0x" << listit->FindMember(L"Short2")->value.GetUint() << std::endl;
		analysisStream << "DW3: 0x" << listit->FindMember(L"DW3")->value.GetUint64() << std::endl;
		analysisStream << "DW4: 0x" << listit->FindMember(L"DW4")->value.GetUint64() << std::endl;
		analysisStream << "Byte2: 0x" << listit->FindMember(L"Byte2")->value.GetUint() << std::endl;
		analysisStream << "ControlByte: 0x" << listit->FindMember(L"ControlByte")->value.GetUint() << std::endl;

		auto CB_GT_0x80it = listit->FindMember(L"DW_8_1");
		if (CB_GT_0x80it != listit->MemberEnd())//controlByte > 0x80)
		{
			analysisStream << "DW_8_1: 0x" << listit->FindMember(L"DW_8_1")->value.GetUint64() << std::endl;
			analysisStream << "DW_8_2: 0x" << listit->FindMember(L"DW_8_2")->value.GetUint64() << std::endl;
		}

		auto CB_GTE_0x40it = listit->FindMember(L"Byte_b7");
		if (CB_GTE_0x40it != listit->MemberEnd())//controlByte & 0x40
		{
			analysisStream << "Byte_b7: 0x" << listit->FindMember(L"Byte_b7")->value.GetUint() << std::endl;
		}
		analysisStream << std::endl << std::endl;
		i += 1;
	}

	analysisStream << "Endstring: " << endString << std::endl;
	analysisStream << "EndShort : 0x" << std::hex << endShort << std::endl;
	analysisStream << "EndDWORD : 0x" << std::hex << endDWORD << std::endl;
	*analysis = QString::fromStdWString(analysisStream.str());
}

void exileSniffer::action_SRV_PLAYER_ITEMS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD objID = obj.get_UInt64(L"ObjID");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server listing items held by Player <ID: 0x"+QString::number(objID,16)+">";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 targID = obj.get_UInt64(L"TargID");
	UINT64 Unk1 = obj.get_UInt64(L"Unk1");
	UINT32 modifier = obj.get_UInt32(L"Modifier");
	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Player(You) clicked ground itemID 0x" << std::hex << targID << " Arg1: 0x" << Unk1;

		if (modifier)
			summary << " [" << explainModifier(modifier) << "]";

		if (modifier > 0xf || !(modifier & 0x8))
			summary << " <!Unusual modifier 0x" << std::hex << modifier << " - what are you doing?>";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_ACTION_PREDICTIVE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT64 coord1 = obj.get_UInt64(L"TargCoord1");
	UINT64 coord2 = obj.get_UInt64(L"TargCoord2");
	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 PkCount = obj.get_UInt32(L"PkCount");
	UINT32 modifier = obj.get_UInt32(L"Modifier");
	if (!analysis)
	{

		std::wstringstream summary;
		summary << "Player(You) used skillID 0x" << std::hex << skillID <<
			" on coord " << std::dec << coord1 << "," << coord2;
		if (modifier != 0x08) //standard mouse click
			summary << "[" << explainModifier(modifier) << "]";

		if (modifier > 0xf || !(modifier & 0x8))
			summary << " <!Unusual modifier 0x" << std::hex<< modifier << " - what are you doing?>";
	

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt& obj, QString *analysis)
{
		obj.toggle_payload_operations(true);
		if (!analysis)
		{
			UI_DECODED_LIST_ENTRY listentry(obj);
			listentry.summary = QString::fromStdWString(L"Server sent instance server data");
			addDecodedListEntry(listentry, &obj);
			return;
		}
}


void exileSniffer::action_CLI_PICKUP_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	UINT64 container = obj.get_UInt64(L"Container");
	UINT64 itemID = obj.get_UInt32(L"ItemID");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");

	std::wstringstream summary;
	summary << "Player(You) picked up itemID 0x" << std::hex << itemID 
		<< "in container " << slotToString(container) <<" < unk2: 0x"<<unk2<<">";

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_PLACE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
	listentry.summary = "Player(You) placed item down";
	addDecodedListEntry(listentry, &obj);
	return;
	}
}

void exileSniffer::action_CLI_REMOVE_SOCKET(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) emptied socket";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_INSERT_SOCKET(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) inserted into socket";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_LEVEL_SKILLGEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) levelled a skillgem";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) added a skillpoint";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CANCEL_BUF(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) cancelled a buff";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_SET_HOTBARSKILL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) changed a hotbar skill";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_SKILL_SLOTS_LIST(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent hotbar skill ID list";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	//todo - lookup the id and match with the associated skillgem or action
	std::wstringstream analysisStream;
	analysisStream << std::hex << "Primary skill bar:" << std::endl;
	analysisStream << "\tSkill 1 ID: 0x" << obj.get_UInt32(L"Skill1") << std::endl;
	analysisStream << "\tSkill 2 ID: 0x" << obj.get_UInt32(L"Skill2") << std::endl;
	analysisStream << "\tSkill 3 ID: 0x" << obj.get_UInt32(L"Skill3") << std::endl;
	analysisStream << "Secondary skill bar:" << std::endl;
	analysisStream << "\tSkill 4 ID: 0x" << obj.get_UInt32(L"Skill4") << std::endl;
	analysisStream << "\tSkill 5 ID: 0x" << obj.get_UInt32(L"Skill5") << std::endl;
	analysisStream << "\tSkill 6 ID: 0x" << obj.get_UInt32(L"Skill6") << std::endl;
	analysisStream << "\tSkill 7 ID: 0x" << obj.get_UInt32(L"Skill7") << std::endl;
	analysisStream << "\tSkill 8 ID: 0x" << obj.get_UInt32(L"Skill8") << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}


void exileSniffer::action_CLI_USE_BELT_SLOT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 slot = obj.get_UInt32(L"Slot");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) activated belt slot "+slot;
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_USE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) used inventory item X on item Y";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_CLI_UNK_x56(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	//seen 1 while going from town to riverways, maybe declares area as fightable/droppable items?

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		if (arg != 1)
			listentry.summary = "Client sent packet 0x56 - (usual 1 as argument)";
		else
			listentry.summary = "!Client packet 0x56 has new argument!: " + QString::number(arg);
		addDecodedListEntry(listentry, &obj);
		return;
	}
}
void exileSniffer::action_SRV_UNK_ACCT_SOCIAL_NAME(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Unknown social/account name " << obj.get_wstring(L"Name") << std::hex;
		summary << "  -  Other data: 0x" << obj.get_UInt64(L"Unk1") << ", 0x" << obj.get_UInt64(L"Unk2")
			<< ", 0x" << obj.get_UInt32(L"Unk3") << ", 0x" << obj.get_UInt32(L"Unk4");

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested latest public parties";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_RESPOND_PUBLICPARTIES(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server sent list of public parties";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_CREATE_ITEM(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent new item in inventory";
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}


void exileSniffer::action_SRV_SLOT_ITEMSLIST(UIDecodedPkt& obj, QString *analysis)
{

	obj.toggle_payload_operations(true);

	//this is wrong when opening vendor things
	//unk or previous packet describes obj listing is for
	DWORD containerCode = obj.get_UInt64(L"Container");
	std::wstring container = slotToString(containerCode);

	DWORD itemCount = obj.get_UInt64(L"Count");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server sent list of " << std::dec << itemCount << " items in slot " << container;
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	auto it = obj.payload.FindMember(L"ItemList");
	if (it == obj.payload.MemberEnd())
	{
		add_metalog_update("Warning: No itemlist found in payload of action_SRV_SLOT_ITEMSLIST", obj.clientProcessID());
		return;
	}
	WValue &itemList = it->value;
	unsigned short listSize = itemList.Size();

	wstringstream analysisStream;
	analysisStream << "Listing requires significant reversing of object/modifier parsing" << std::hex<< std::endl;
	analysisStream << "Unknown bytes before actual item list:" << std::endl;
	analysisStream << "\tUnk1: 0x"<< obj.get_UInt32(L"Unk1") << std::endl;
	analysisStream << "\t---\n\tUnk2: 0x" << obj.get_UInt32(L"Unk2") << std::endl;
	analysisStream << "\tUnk3: 0x" << obj.get_UInt32(L"Unk3") << std::endl;
	analysisStream << "\tUnk4: 0x" << obj.get_UInt32(L"Unk4") << std::endl;
	analysisStream << "\tUnk5: 0x" << obj.get_UInt32(L"Unk5") << std::endl;
	analysisStream << "\tUnk6: 0x" << obj.get_UInt32(L"Unk6") << std::endl;

	
	if (itemList.Size() == 0)
		analysisStream << "\nItem List: (empty)"<<std::endl;
	else
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		analysisStream << "\nItem List (Location):Name (Hash) ServerID" << std::endl;

		for (auto it = itemList.Begin(); it != itemList.End(); it++)
		{
			DWORD instanceID = it->FindMember(L"InstanceID")->value.GetUint64();
			ushort posX = it->FindMember(L"PosX")->value.GetUint();
			ushort posY = it->FindMember(L"PosY")->value.GetUint();
			DWORD hash = it->FindMember(L"ItemHash")->value.GetUint64();
			std::string itemname, category;
			lookup_hash(hash, itemname, category);

			analysisStream << "   (" << std::dec << (ushort)posX << "," << (ushort)posY << "): " <<
				converter.from_bytes(itemname) << std::hex << " (0x" << hash << ") ID: 0x" << instanceID << std::endl;
		}
		analysisStream << std::endl;
		analysisStream << "These can be looked up by their hash in BaseItemTypes.dat" << std::endl;
	}

	analysisStream << "\nFinal(?) unknown: 0x" << std::hex << obj.get_UInt32(L"FinalUnk") << std::endl;

	*analysis = QString::fromStdWString(analysisStream.str());
}



void exileSniffer::action_CLI_SKILLPANE_ACTION(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) used skillpane";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_MICROSTRANSACTIONPANE_ACTION(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) opened microtransaction pane";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_USED_SKILL(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) used skill (lockstep)";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_CLICK_OBJ(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) clicked object x";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_MOUSE_HELD(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) is holding mouse";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_MOUSE_RELEASE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) released mouse";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_DISPLAY_BUILTIN_MSG(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 msgID = obj.get_UInt64(L"MsgID");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Server displayed built-in msg ID 0x" << std::hex << msgID;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_GUILD_CREATE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) created guild";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_CLI_PACKET_EXIT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client exited";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_MOBILE_USED_SKILL(UIDecodedPkt& obj, QString *analysis)
{
	/*
	00 EA 
	00 00 03 E4
	00 00 03 E4 
	70 00 
	00 
	80 B7 
	80 9D 
	80 B9 
	80 83 
	29 09 //skill
	84 68 //pkid


#3351 17:23:20 Server[Game] to PlayerClient(31 bytes)
  00 EA 
  00 00 03 E4 
  00 00 00 00 
  00 00 
  80 
  00 00 00 A9 
  80 B8 
  80 8B 
  80 BC 
  80 74 
  02 66 
  84 69 //pkid
	
	*/
	obj.toggle_payload_operations(true);

	UINT64 user = obj.get_UInt64(L"User1");
	UINT64 id2 = obj.get_UInt64(L"ID2");
	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	UINT32 modifier = obj.get_UInt32(L"Modifier"); 



	UINT32 startCoord1 = obj.get_UInt32(L"StartCoord1");
	UINT32 startCoord2 = obj.get_UInt32(L"StartCoord2");
	UINT32 targCoord1 = obj.get_UInt32(L"TargCoord1");
	UINT32 targCoord2 = obj.get_UInt32(L"TargCoord2");
	//stuff gonna break here after low/high coords -> handle high/low bits!

	UINT32 skillID = obj.get_UInt32(L"SkillID");
	UINT32 PkCount = obj.get_UInt32(L"PkCount");

	if (!analysis)
	{
		wstringstream summary;
		summary << "Entity ID 0x" << std::hex << user << "/id2 0x"<< id2 <<
			" (" << std::dec << startCoord1 << "," << startCoord2 << ")" << std::hex <<
			" used skill 0x" << skillID << 
			" -> (" << std::dec << targCoord1 << "," << targCoord2 << ")" << explainModifier(modifier)
			<< std::hex << " Unk1: 0x" << unk1 << ", Modifier: 0x" << modifier;
		if (modifier & 0x80)
		{
			UINT64 unk2 = obj.get_UInt64(L"Unk2");
			summary << " [ TargetID: 0x" << unk2 << "]";
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_MOBILE_UNK_0xeb(UIDecodedPkt& obj, QString *analysis)
{
	UINT64 id1 = obj.get_UInt64(L"ID1");
	UINT64 id2 = obj.get_UInt64(L"ID2");
	UINT32 unk1 = obj.get_UInt32(L"Unk1");
	if (!analysis)
	{

		wstringstream summary;
		summary << std::hex << "Unk skill packet 0xeb. ID1: 0x" << id1 << ", ID2: 0x" << id2 << " unk1(skill?): 0x" << unk1;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

}

void exileSniffer::action_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT64 id2 = obj.get_UInt64(L"ObjID");
	UINT64 unk1 = obj.get_UInt64(L"Unk1");
	UINT32 unk2 = obj.get_UInt32(L"Unk2");

	UINT64 val = obj.get_UInt64(L"NewValue");
	UINT64 unk3 = obj.get_UInt64(L"Unk3");
	UINT32 stat = obj.get_UInt32(L"Stat");
	UINT32 unk4 = obj.get_UInt32(L"Unk4");

	if (!analysis)
	{

		wstringstream summary;
		summary << "Stat update - obj 0x" << std::hex << id2 << " (caused by 0x" << unk1 << "?)" <<
			" - [";
		switch (stat) {
		case 0x0:
			summary << L"Health";
			break;
		case 0x1:
			summary << L"Mana";
			break;
		case 0x2:
			summary << L"Shield";
			break;
		default:
			summary << L"<Unknown stat 0x" << stat << ">";
		}
		summary << "] is now " << std::dec << val << " Unk4(more?): 0x"<<unk4<< std::endl;


		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_STAT_CHANGED(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	DWORD objID = obj.get_UInt64(L"ObjID");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << "Stat change for object ID 0x" <<std::hex << objID;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

}

void exileSniffer::action_CLI_REQUEST_PLAYERID(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client requested playerID";
		addDecodedListEntry(listentry, &obj);
		return;
	}

	*analysis = "No additional data expected";
}

void exileSniffer::action_SRV_UNKNOWN_0x111(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 count1 = obj.get_UInt32(L"Count1"); 

	UINT32 count2 = obj.get_UInt32(L"Count2");


	if (!analysis)
	{
		std::wstringstream summary;
		 
		if (count1 == 0 && count2 == 0)
			summary << "0x111 packet with empty lists";
		else
		{
			summary << std::dec<<"!![Alert]!! 0x111 packet with lists! List 1 has "
				<< count1 << ", list 2 has " << count2;
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}


}

void exileSniffer::action_SRV_NOTIFY_PLAYERID(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	DWORD ID1 = obj.get_UInt64(L"ID1");
	DWORD ID2 = obj.get_UInt64(L"ID2");
	ushort ID3 = obj.get_UInt64(L"ID3");

	if (!analysis)
	{
		std::wstringstream summary;
		summary << std::hex << "Server notified client of playerID. ID1 0x"
			<< ID1 << ", ID2: 0x" << ID2 << " ID3: 0x" << ID3;

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	analysisStream << std::hex << "Server notified client of playerID. ID1 0x"
		<< ID1 << ", ID2: 0x" << ID2 << " ID3: 0x" << ID3;
	QString::fromStdWString(analysisStream.str());
}



void exileSniffer::action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Player(You) opted out of tutorials";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_HEARTBEAT(UIDecodedPkt& obj, QString *analysis)
{
	//maybe increment a counter or something
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Server Heartbeat";
		addDecodedListEntry(listentry, &obj);
		return;
	}
}

void exileSniffer::action_SRV_ADD_OBJECT(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	DWORD objectID = obj.get_UInt64(L"ObjID");
	DWORD unk1 = obj.get_UInt64(L"unkID1");
	ushort unk2 = obj.get_UInt32(L"ObjID");
	DWORD objHash = obj.get_UInt64(L"objHash");
	DWORD dataLen = obj.get_UInt32(L"DataLen");


	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string hashResult;
	std::string hashCategory;
	lookup_hash(objHash, hashResult, hashCategory);

	if (!analysis)
	{
		wstringstream summary;
		summary << std::hex << converter.from_bytes(hashCategory) << " added <"<<converter.from_bytes(hashResult)<<
			"> ID 0x" << objectID <<" ("<<std::dec<<dataLen<<" bytes)";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}
}
