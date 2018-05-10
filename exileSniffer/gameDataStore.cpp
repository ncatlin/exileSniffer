#include "stdafx.h"
#include "gameDataStore.h"
#include "MurmurHash2.h"

gameDataStore::~gameDataStore()
{
}


void gameDataStore::genericHashesLoad(rapidjson::Value& itemsDoc, std::map <unsigned long, std::string>& targMap)
{
	rapidjson::Value::ConstMemberIterator recordsIt = itemsDoc.MemberBegin();
	for (; recordsIt != itemsDoc.MemberEnd(); recordsIt++)
	{
		std::string hashString = recordsIt->name.GetString();
		unsigned long hash = std::stoul(hashString);
		targMap[hash] = recordsIt->value.GetString();
	}
}

bool gameDataStore::lookup_areaCode(unsigned long code, std::wstring& result)
{
	//todo json 16
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	auto areasIt = areaCodes.find(code);
	if (areasIt != areaCodes.end())
	{
		result = converter.from_bytes(areasIt->second);
		return true;
	}

	std::stringstream failResString;
	failResString << "<LookupFailure UnknownArea 0x" << std::hex << code << ">";
	result = converter.from_bytes(failResString.str());
	return false;
}

bool gameDataStore::threadsafe_lookup_hash(unsigned long hash, std::string& result, std::string& category)
{
	auto monstersIt = monsterHashes.find(hash);
	if (monstersIt != monsterHashes.end())
	{
		result = monstersIt->second;
		category = "Monster";
		return true;
	}

	auto objectsIt = gameObjHashes.find(hash);
	if (objectsIt != gameObjHashes.end())
	{
		result = objectsIt->second;
		category = "Object";
		return true;
	}

	auto chestsIt = chestHashes.find(hash);
	if (chestsIt != chestHashes.end())
	{
		result = chestsIt->second;
		category = "Chest";
		return true;
	}

	auto charactersIt = characterHashes.find(hash);
	if (charactersIt != characterHashes.end())
	{
		result = charactersIt->second;
		category = "Character";
		return true;
	}

	auto npcsIt = NPCHashes.find(hash);
	if (npcsIt != NPCHashes.end())
	{
		result = npcsIt->second;
		category = "NPC";
		return true;
	}

	auto petsIt = petHashes.find(hash);
	if (petsIt != petHashes.end())
	{
		result = petsIt->second;
		category = "Pet";
		return true;
	}

	auto itemsIt = itemHashes.find(hash);
	if (itemsIt != itemHashes.end())
	{
		result = itemsIt->second;
		category = "Item";
		return true;
	}

	if (searchLevelAdjustedMonsters(hash, result))
	{
		category = "Monster";
		return true;
	}

	std::stringstream resString;
	resString << "<0x" << std::hex << hash << ">";
	result = resString.str();
	category = "UnknownHash";

	return false;
}

bool gameDataStore::lookup_hash(unsigned long hash, std::string& result, std::string& category)
{
	bool found;
	myMutex.lock();
	found = threadsafe_lookup_hash(hash, result, category);
	myMutex.unlock();
	return found;
}

void gameDataStore::fill_UI_pane_IDs()
{
	UIPaneIDs[0] = "World";
	UIPaneIDs[1] = "PlayerStash";
	UIPaneIDs[2] = "GuildStash";
	UIPaneIDs[3] = "Social";
	UIPaneIDs[4] = "Atlas";
	//?
	UIPaneIDs[6] = "DivineFont";
	UIPaneIDs[7] = "StoneAltar";
	//?
	UIPaneIDs[9] = "Ascendancy";
	UIPaneIDs[10] = "EventsPVP-EventsTab";
	UIPaneIDs[11] = "CardTrade";
	UIPaneIDs[12] = "EventsPVP-PVPTab";
	UIPaneIDs[13] = "Darkshrine";
	UIPaneIDs[14] = "LabyrinthMap";
	UIPaneIDs[15] = "Labyrinth";
	UIPaneIDs[16] = "Challenges_1";
	UIPaneIDs[17] = "Inventory";
	UIPaneIDs[18] = "Atlas";
	UIPaneIDs[19] = "Pantheon";
	UIPaneIDs[20] = "Challenges_2"; //something other than achievements tab?
	UIPaneIDs[22] = "BloodAltar";
	UIPaneIDs[23] = "MapCrafting";
	UIPaneIDs[24] = "Crafting_AnimGuardianDrop";
	UIPaneIDs[25] = "Crafting_1";
	UIPaneIDs[26] = "Crafting_2";
	UIPaneIDs[27] = "Crafting_3";
	UIPaneIDs[28] = "Crafting_4";
	UIPaneIDs[29] = "Crafting_5";
	UIPaneIDs[30] = "Crafting_6";

}

//todo check entries exist
void gameDataStore::fill_gamedata_lists()
{

	char buffer[65536];

	FILE* pFile;
	std::string filename = "ggpk_exports.json";
	fopen_s(&pFile, filename.c_str(), "rb");
	if (!pFile)
	{
		std::cerr << "Warning: Could not open " << filename << " for reading as ggpk data. Abandoning Load." << std::endl;
		return;
	}

	//load it all from json
	rapidjson::Document jsondoc;
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	jsondoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	fclose(pFile);

	if (!jsondoc.IsObject())
	{
		std::cerr << "Warning: Corrupt ggpk_exports file "<< filename<<". Abandoning Load." << std::endl;
		if (jsondoc.HasParseError())
		{
			std::cerr << "\t rapidjson parse error " << jsondoc.GetParseError()
				<< " at offset " << jsondoc.GetErrorOffset() << std::endl;
		}
		return;
	}
	rapidjson::Value::ConstValueIterator recordsIt;
	rapidjson::Value::MemberIterator docIt = jsondoc.FindMember("MonsterVarietiesIndex");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &varietiesDoc = docIt->value;
		recordsIt = varietiesDoc.Begin();
		for (; recordsIt != varietiesDoc.End(); recordsIt++)
		{
			monsterVarieties.push_back(recordsIt->GetString());
		}
	}

	docIt = jsondoc.FindMember("StatIndexes");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &statIndexDoc = docIt->value;
		recordsIt = statIndexDoc.Begin();
		for (; recordsIt != statIndexDoc.End(); recordsIt++)
		{
			statDescriptions.push_back(recordsIt->GetString());
		}
	}

	docIt = jsondoc.FindMember("BuffDefinitions");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &buffDefsDoc = docIt->value;
		recordsIt = buffDefsDoc.Begin();
		for (; recordsIt != buffDefsDoc.End(); recordsIt++)
		{
			auto &entry = recordsIt[0];
			std::pair<std::string, byte> name_statCount;
			name_statCount.first = entry[0].GetString();
			name_statCount.second = entry[1].GetUint();
			buffDefinitions_names_statCounts.push_back(name_statCount);
		}
	}

	docIt = jsondoc.FindMember("RecoveryBuffs");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &recovBufsDoc = docIt->value;
		recordsIt = recovBufsDoc.Begin();
		for (; recordsIt != recovBufsDoc.End(); recordsIt++)
		{
			unsigned int buffRow = recordsIt->GetUint();
			recoveryBuffs.push_back(buffRow);
		}
	}

	docIt = jsondoc.FindMember("BuffVisuals");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &buffVisDoc = docIt->value;
		recordsIt = buffVisDoc.Begin();
		for (; recordsIt != buffVisDoc.End(); recordsIt++)
		{
			buffVisuals.push_back(recordsIt->GetString());
		}
	}

	docIt = jsondoc.FindMember("ItemVisuals");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &itemVisDoc = docIt->value;
		rapidjson::Value::ConstMemberIterator mapIt = itemVisDoc.MemberBegin();
		for (; mapIt != itemVisDoc.MemberEnd(); mapIt++)
		{
			//uint ref = mapIt->name.GetUint(); //need to wait for pypoe update
			uint ref = std::stoi(mapIt->name.GetString());
			itemVisuals[ref] = mapIt->value.GetString();
		}
	}

	docIt = jsondoc.FindMember("ItemVisualEffects");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &itemEffectsDoc = docIt->value;
		rapidjson::Value::ConstMemberIterator effectIt = itemEffectsDoc.MemberBegin();
		for (; effectIt != itemEffectsDoc.MemberEnd(); effectIt++)
		{
			//uint ref = effectIt->name.GetInt();
			uint ref = std::stoi(effectIt->name.GetString());
			itemEffects[ref] = effectIt->value.GetString();
		}
	}

	docIt = jsondoc.FindMember("Prophecies");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &prophDoc = docIt->value;
		rapidjson::Value::ConstMemberIterator prophIt = prophDoc.MemberBegin();
		for (; prophIt != prophDoc.MemberEnd(); prophIt++)
		{
			uint ref = std::stoi(prophIt->name.GetString());
			prophecies[ref] = prophIt->value.GetString();
		}
	}

	docIt = jsondoc.FindMember("Hideouts");
	if (docIt != jsondoc.MemberEnd())
	{
		auto &hideoutDoc = docIt->value; 
		rapidjson::Value::ConstMemberIterator hideIt = hideoutDoc.MemberBegin();
		for (; hideIt != hideoutDoc.MemberEnd(); hideIt++)
		{
			uint ref = std::stoi(hideIt->name.GetString());
			hideouts[ref] = hideIt->value.GetString();
		}
	}

	docIt = jsondoc.FindMember("MonsterVarietiesHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, monsterHashes);

	docIt = jsondoc.FindMember("AreaCodes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, areaCodes);

	docIt = jsondoc.FindMember("ObjRegisterHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, gameObjHashes);

	docIt = jsondoc.FindMember("ChestHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, chestHashes);

	docIt = jsondoc.FindMember("PetHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, petHashes);

	docIt = jsondoc.FindMember("CharacterHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, characterHashes);

	docIt = jsondoc.FindMember("NPCHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, NPCHashes);
	
	docIt = jsondoc.FindMember("ItemHashes");
	if (docIt != jsondoc.MemberEnd())
		genericHashesLoad(docIt->value, itemHashes);



	fill_UI_pane_IDs();
}

unsigned long levelAdjustedHash(std::string baseString, unsigned int level, std::string& hashedString_Out)
{
	hashedString_Out = baseString + "@" + std::to_string(level);
	return MurmurHash2(hashedString_Out.c_str(), hashedString_Out.size(), 0);
}

/*
as a space saving measure we only save an index to the monster that a hash refers to
once found we work out what level was appended to the path string
*/
bool gameDataStore::searchLevelAdjustedMonsters(unsigned long hash, std::string& result)
{
	auto monstersIt = levelAdjustedMonsterHashes.find(hash);
	if (monstersIt == levelAdjustedMonsterHashes.end())
		return false;

	const std::string baseString = monsterVarieties.at(monstersIt->second);
	unsigned long testhash = levelAdjustedHash(baseString, lastAreaLevel, result);

	if (testhash == hash)
	{
		return true;
	}

	for (auto it = hashedMonsterLevels.begin(); it != hashedMonsterLevels.end(); it++)
	{
		unsigned int testLevel = *it;
		testhash = levelAdjustedHash(baseString, testLevel, result);
		if (testhash == hash)
		{
			return true;
		}
	}

	//shouldn't happen
	result = baseString + "@<UnkLevel>"; 
	return true;
}

/*
SRV_AREA_INFO monster hashes are the hash of the metadata path with '@[arealevel]' appended
this hashes all possible monster types with a level the first time we load an area of that level

not code to be proud of but it takes about 64ms per list on my test vm and will be 
called 0-3ish times on entering an area with a new monsterlevel so... meh
*/
void gameDataStore::generateMonsterLevelHashes(unsigned int level)
{
	if (level == lastAreaLevel)	return;
	//search from the back because player prob going to encounter recent levels more often
	if (std::find(hashedMonsterLevels.rbegin(), hashedMonsterLevels.rend(), level) != hashedMonsterLevels.rend())
		return;

	for (int index = 0; index < monsterVarieties.size(); index++)
	{
		const std::string& targ = monsterVarieties.at(index);
		std::string hashedString;
		unsigned long hash = levelAdjustedHash(targ, level, hashedString);
		levelAdjustedMonsterHashes[hash] = index;
		//std::cout << "Ad hash of " << hashedString << std::endl;
	}

	lastAreaLevel = level;
	hashedMonsterLevels.push_back(level);
}

std::wstring gameDataStore::getVisualIdentity(unsigned int ref)
{
	std::wstringstream result;

	if (ref == 0) return L"None";

	auto it = itemVisuals.find(ref);
	if (it != itemVisuals.end())
		result << converter.from_bytes(it->second);
	else
		result << L"[Unknown 0x" << std::hex << ref << "]";

	return result.str();
}

std::wstring gameDataStore::getVisualEffect(unsigned int ref)
{
	std::wstringstream result;

	if (ref == 0) return L"None";

	auto it = itemEffects.find(ref);
	if (it != itemEffects.end())
		result << converter.from_bytes(it->second);
	else
		result << L"[Unknown 0x" << std::hex << ref << "]";

	return result.str();
}


std::wstring gameDataStore::getProphecy(unsigned int ref)
{
	std::wstringstream result;

	if (ref == 0) return L"None";

	auto it = prophecies.find(ref);
	if (it != prophecies.end())
		result << converter.from_bytes(it->second);
	else
		result << L"[Unknown 0x" << std::hex << ref << "]";

	return result.str();
}
