#pragma once
class gameDataStore
{
public:
	gameDataStore() {
		fill_gamedata_lists();
	};
	~gameDataStore();

	bool lookup_areaCode(unsigned long code, std::wstring& result);
	bool lookup_hash(unsigned long hash, std::string& result, std::string& category);

public:
	std::map <unsigned long, std::string> gameObjHashes;
	std::map <unsigned long, std::string> monsterHashes;
	std::map <unsigned long, std::string> chestHashes;
	std::map <unsigned long, std::string> characterHashes;
	std::map <unsigned long, std::string> NPCHashes;
	std::map <unsigned long, std::string> petHashes;
	std::map <unsigned long, std::string> itemHashes;
	std::map <unsigned long, std::string> areaCodes;


	std::vector <std::string> monsterVarieties;
	std::vector <std::string> statDescriptions;
	std::vector <std::string> buffDefinitions;
	std::vector <std::string> buffVisuals;

private:

	void fill_gamedata_lists();
	void genericHashesLoad(rapidjson::Value& itemsDoc, std::map <unsigned long, std::string>& targMap);

};

