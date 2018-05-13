#pragma once
#include "uiMsg.h"

class gameDataStore
{
public:
	gameDataStore(SafeQueue<UI_MESSAGE *>* uiq) {
		uiMsgQueue = uiq;
		fill_gamedata_lists();
	};
	~gameDataStore();

	bool lookup_areaCode(unsigned long code, std::wstring& result);
	bool lookup_hash(unsigned long hash, std::string& result, std::string& category);
	bool threadsafe_lookup_hash(unsigned long hash, std::string& result, std::string& category);

	void generateMonsterLevelHashes(unsigned int level);
	std::wstring getVisualEffect(unsigned int ref);
	std::wstring getVisualIdentity(unsigned int ref);
	std::wstring getProphecy(unsigned int ref);

public:
	std::map <unsigned long, std::string> gameObjHashes;
	std::map <unsigned long, std::string> monsterHashes;
	std::map<unsigned long, unsigned int> levelAdjustedMonsterHashes;
	std::map <unsigned long, std::string> chestHashes;
	std::map <unsigned long, std::string> characterHashes;
	std::map <unsigned long, std::string> NPCHashes;
	std::map <unsigned long, std::string> petHashes;
	std::map <unsigned long, std::string> itemHashes;
	std::map <unsigned long, std::string> itemVisuals;
	std::map <unsigned long, std::string> areaCodes;
	std::map <unsigned int, std::string> prophecies;
	std::map <unsigned int, std::string> hideouts;
	std::map <unsigned int, std::string> itemEffects;

	std::map <unsigned short, std::string> UIPaneIDs;


	std::vector <std::string> monsterVarieties;
	std::vector <std::string> statDescriptions;
	std::vector <std::pair<std::string, byte>> buffDefinitions_names_statCounts;
	std::vector <std::string> buffVisuals;
	std::vector <int> recoveryBuffs;

	std::vector <unsigned int> hashedMonsterLevels;
	unsigned int lastAreaLevel = INT_MAX;

private:
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::mutex myMutex; 
	SafeQueue<UI_MESSAGE *> *uiMsgQueue = NULL;

	void fill_gamedata_lists();
	void fill_UI_pane_IDs();

	void genericHashesLoad(rapidjson::Value& itemsDoc, std::map <unsigned long, std::string>& targMap);
	bool searchLevelAdjustedMonsters(unsigned long hash, std::string& result);
};

