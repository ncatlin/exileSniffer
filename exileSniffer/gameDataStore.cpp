#include "stdafx.h"
#include "gameDataStore.h"

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

bool gameDataStore::lookup_hash(unsigned long hash, std::string& result, std::string& category)
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

	std::stringstream resString;
	resString << "<0x" << std::hex << hash << ">";
	result = resString.str();
	category = "UnknownHash";

	return false;
}

void gameDataStore::fill_gamedata_lists()
{

	char buffer[65536];

	FILE* pFile;
	std::string filename = "ggpk_exports.json";
	fopen_s(&pFile, filename.c_str(), "rb");
	if (!pFile)
	{
		std::cerr << "Warning: Could not open " << filename << " for reading. Abandoning Load." << std::endl;
		return;
	}

	//load it all from json
	rapidjson::Document jsondoc;
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	jsondoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	fclose(pFile);

	if (!jsondoc.IsObject())
	{
		std::cerr << "Warning: Corrupt ggpk_exports file. Abandoning Load." << std::endl;
		if (jsondoc.HasParseError())
		{
			std::cerr << "\t rapidjson parse error " << jsondoc.GetParseError()
				<< " at offset " << jsondoc.GetErrorOffset() << std::endl;
		}
		return;
	}

	rapidjson::Value& monsterVarietyIndexDoc = jsondoc.FindMember("MonsterVarietiesIndex")->value;
	rapidjson::Value::ConstValueIterator recordsIt = monsterVarietyIndexDoc.Begin();
	for (; recordsIt != monsterVarietyIndexDoc.End(); recordsIt++)
	{
		monsterVarieties.push_back(recordsIt->GetString());
	}

	rapidjson::Value& statIndexDoc = jsondoc.FindMember("StatIndexes")->value;
	recordsIt = statIndexDoc.Begin();
	for (; recordsIt != statIndexDoc.End(); recordsIt++)
	{
		statDescriptions.push_back(recordsIt->GetString());
	}

	rapidjson::Value& buffDefsDoc = jsondoc.FindMember("BuffDefinitions")->value;
	recordsIt = buffDefsDoc.Begin();
	for (; recordsIt != buffDefsDoc.End(); recordsIt++)
	{
		buffDefinitions.push_back(recordsIt->GetString());
	}

	rapidjson::Value& buffVisDoc = jsondoc.FindMember("BuffVisuals")->value;
	recordsIt = buffVisDoc.Begin();
	for (; recordsIt != buffVisDoc.End(); recordsIt++)
	{
		buffVisuals.push_back(recordsIt->GetString());
	}

	rapidjson::Value& monsterVarietyDoc = jsondoc.FindMember("MonsterVarietiesHashes")->value;
	genericHashesLoad(monsterVarietyDoc, monsterHashes);

	rapidjson::Value& areaCodesDoc = jsondoc.FindMember("AreaCodes")->value;
	genericHashesLoad(areaCodesDoc, areaCodes);

	rapidjson::Value& objectRegisterDoc = jsondoc.FindMember("ObjRegisterHashes")->value;
	genericHashesLoad(objectRegisterDoc, gameObjHashes);

	rapidjson::Value& chestsDoc = jsondoc.FindMember("ChestHashes")->value;
	genericHashesLoad(chestsDoc, chestHashes);

	rapidjson::Value& petsDoc = jsondoc.FindMember("PetHashes")->value;
	genericHashesLoad(petsDoc, petHashes);

	rapidjson::Value& charactersDoc = jsondoc.FindMember("CharacterHashes")->value;
	genericHashesLoad(charactersDoc, characterHashes);

	rapidjson::Value& npcsDoc = jsondoc.FindMember("NPCHashes")->value;
	genericHashesLoad(npcsDoc, NPCHashes);

	rapidjson::Value& itemsDoc = jsondoc.FindMember("ItemHashes")->value;
	genericHashesLoad(itemsDoc, itemHashes);
}