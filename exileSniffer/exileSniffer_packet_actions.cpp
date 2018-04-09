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
	decodedPktActioners[SRV_PRELOAD_MONSTER_LIST] = &exileSniffer::action_SRV_PRELOAD_MONSTER_LIST;
	decodedPktActioners[CLI_CHAT_COMMAND] = &exileSniffer::action_CLI_CHAT_COMMAND;
	decodedPktActioners[SRV_CHAT_MESSAGE] = &exileSniffer::action_SRV_CHAT_MESSAGE;
	decodedPktActioners[SRV_SERVER_MESSAGE] = &exileSniffer::action_SRV_SERVER_MESSAGE;
	decodedPktActioners[CLI_LOGGED_OUT] = &exileSniffer::action_CLI_LOGGED_OUT;

	decodedPktActioners[CLI_CLICKED_GROUND_ITEM] = &exileSniffer::action_CLI_CLICKED_GROUND_ITEM;
	decodedPktActioners[CLI_ACTION_PREDICTIVE] = &exileSniffer::action_CLI_ACTION_PREDICTIVE;
	decodedPktActioners[SRV_PLAYER_ITEMS] = &exileSniffer::action_SRV_PLAYER_ITEMS;
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
	decodedPktActioners[CLI_REQUEST_PUBLICPARTIES] = &exileSniffer::action_CLI_REQUEST_PUBLICPARTIES;
	decodedPktActioners[SRV_RESPOND_PUBLICPARTIES] = &exileSniffer::action_SRV_RESPOND_PUBLICPARTIES;
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
	decodedPktActioners[SRV_MOBILE_UPDATE_HMS] = &exileSniffer::action_SRV_MOBILE_UPDATE_HMS;
	decodedPktActioners[SRV_UNKNOWN_0x111] = &exileSniffer::action_SRV_UNKNOWN_0x111;
	decodedPktActioners[CLI_OPTOUT_TUTORIALS] = &exileSniffer::action_CLI_OPTOUT_TUTORIALS;
	decodedPktActioners[SRV_HEARTBEAT] = &exileSniffer::action_SRV_HEARTBEAT;
	decodedPktActioners[SRV_ADD_OBJECT] = &exileSniffer::action_SRV_ADD_OBJECT;


}

void exileSniffer::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui.decodedList->columnCount(); tablecolumn++)
	{
		ui.decodedList->item(tablerow, tablecolumn)->setBackgroundColor(colour);
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

void exileSniffer::action_SRV_CHAT_MESSAGE(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);
	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Chat message from server";
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
		listentry.summary = "Game client logged out. [Arg: "+QString::number(arg)+"]";
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

	auto it = obj.payload.FindMember(L"PreloadList");
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
		summary << "<Loading Area: "<<areaname
			<<"> - Server sent environment and objects preload data ("<<std::dec<<listSize<<" items)";

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
		return;
	}

	wstringstream analysisStream;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	DWORD variant = obj.get_UInt64(L"AreaVariant");
	analysisStream << "Animation preload information" << std::hex << std::endl;
	analysisStream << "Area " << areaname << " 0x"<< areaCode << " in worldareas.dat>" << std::endl;
	analysisStream << "Area variant 0x" << variant << std::endl;
	analysisStream << "Difficulty name: " << obj.get_wstring(L"Difficulty") << std::endl;
	analysisStream << std::endl;



	std::wcout << "Unknown values: 1: " << obj.get_UInt32(L"Unk1") <<
		" 2: " << obj.get_UInt32(L"Unk2") <<
		" 3: " << obj.get_UInt32(L"Unk3") <<
		" 4: " << obj.get_UInt32(L"Unk4") <<
		" 5: " << obj.get_UInt32(L"Unk5") << std::endl;
	std::wcout << "Unknown values: 6: " << obj.get_UInt32(L"Unk6") <<
		" 7: " << obj.get_UInt32(L"Unk7") <<
		" 8: " << obj.get_UInt32(L"Unk8") <<
		" 9: " << obj.get_UInt32(L"Unk9") <<
		" 10: " << obj.get_UInt32(L"Unk10") << std::endl;

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

		analysisStream << "\t"<<converter.from_bytes(result_hash.first) << " hash 0x"<< result_hash.second << std::endl;
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

	UINT32 arg = obj.get_UInt32(L"Arg");

	if (!analysis)
	{
		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = "Client sent packet 0x56 - (seen 1) is: "+arg;
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

void exileSniffer::action_SRV_SLOT_ITEMSLIST(UIDecodedPkt& obj, QString *analysis)
{

	DWORD containerCode = obj.get_UInt64(L"Container");
	std::wstring container = slotToString(containerCode);
	DWORD itemCount = obj.get_UInt64(L"Count");

	obj.toggle_payload_operations(true);
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
		summary << "Server displayed built-in msg ID 0x" << msgID;

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
		summary << "Entity ID 0x" << std::hex << user <<
			" at (" << std::dec << startCoord1 << "," << startCoord2 << ")" <<
			" used skill 0x" << skillID << " on targ 0x" << std::hex << id2 <<
			" (" << std::dec << targCoord1 << "," << targCoord2 << ")" << explainModifier(modifier)
			<< std::hex << " Unk1: 0x" << unk1;

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


void exileSniffer::action_SRV_UNKNOWN_0x111(UIDecodedPkt& obj, QString *analysis)
{
	obj.toggle_payload_operations(true);

	UINT32 count = obj.get_UInt32(L"UnkCount"); 
	UINT32 zero = obj.get_UInt32(L"UnkZero");


	if (!analysis)
	{
		std::wstringstream summary;
		 
		if (count == 0 && zero == 0)
			summary << "0x111 packet with null values";
		else
		{
			if (count != 0)
				summary << "!![Alert]!! 0x111 packet with nonzero values! Count byte: " << count;
			else
				summary << "!!! Very weird 0x111 packet with zero count and nonzero zero: " << zero;
		}

		UI_DECODED_LIST_ENTRY listentry(obj);
		listentry.summary = QString::fromStdWString(summary.str());
		addDecodedListEntry(listentry, &obj);
	}

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
