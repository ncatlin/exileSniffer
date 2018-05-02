#pragma once
#include "base_thread.h"
#include "uiMsg.h"

#define SENT_BY_SERVER 1
#define SALSA_KEY_SIZE 32 
#define SALSA_IV_SIZE 8


typedef DWORD PROCESS_ID;

#define KEYBLOB_SIZE 12*4 //32 key bytes + 8 IV bytes + 8 unused
struct KEYDATA {
	DWORD salsakey[SALSA_KEY_SIZE/sizeof(DWORD)];
	DWORD IV[SALSA_IV_SIZE/sizeof(DWORD)];
	DWORD foundAddress;
	DWORD64 timeFound;
	bool used = false;
	DWORD sourceProcess;
};

class UNCLAIMED_KEY {
public:
	UNCLAIMED_KEY(KEYDATA *newkey) { key = newkey; }
	KEYDATA *key;
	vector<std::pair<unsigned int, byte>> streamsTested;
};

class GAMECLIENTINFO 
{
public:
	GAMECLIENTINFO(DWORD processID) { 
		pid = processID;
		addressQueueMutex = CreateMutex(0, 0, 0);
	}
	DWORD pid;
	HANDLE processhandle;
	bool needsLoginKey = true;
	semaphore handlesOpen;
	HANDLE addressQueueMutex;
	unsigned int memScanFiltersRelaxed = 0;
	std::queue<std::pair<void *, size_t>> addressQueue;
};

struct memWorkerParams {
	void *thisptr;
	GAMECLIENTINFO *clientInfo;
	bool started = false;
};



class key_grabber_thread :
	public base_thread
{
public:
	key_grabber_thread(SafeQueue<UI_MESSAGE>* uiq) {uiMsgQueue = uiq;}
	~key_grabber_thread();
	KEYDATA * getUnusedMemoryKey(unsigned int streamID, bool recvKey, KEYDATA *hintKey = NULL);

	void claimKey(KEYDATA *key, unsigned int keyStreamID);
	bool insertKey(KEYDATA *key);
	void stopProcessScan(DWORD pid);
	bool relaxScanFilters();
	void restartScanOnClient(DWORD pid);
	void suspend_scanning(DWORD activeProcessPID);
	void resume_scanning();

private:
	void main_loop();
	void grabKeys(GAMECLIENTINFO *clientInfo);
	void keyGrabController(GAMECLIENTINFO *gameClient);
	bool insertKey(DWORD pid, DWORD *keyblobptr, DWORD foundAddress);
	bool openClientHandle(GAMECLIENTINFO *gameClient);
	int getClientPIDs(std::vector <DWORD>& resultsList);
	GAMECLIENTINFO* get_process_obj(DWORD pid);
	void memoryScanWorker(GAMECLIENTINFO *);
	void purge_ended_processes(std::vector <DWORD>& latestClientPIDs);
	void erase_client_objects();

	static DWORD WINAPI scanControllerStart(void* Param) {
		memWorkerParams *paramsPtr = (memWorkerParams*)Param;
		paramsPtr->started = true;
		key_grabber_thread* This = (key_grabber_thread*)paramsPtr->thisptr;
		This->keyGrabController(paramsPtr->clientInfo);
		
		return 0;
	}
	static DWORD WINAPI scanWorkerStart(void* Param) {
		memWorkerParams *paramsPtr = (memWorkerParams*)Param;
		key_grabber_thread* This = (key_grabber_thread*)paramsPtr->thisptr;
		This->memoryScanWorker(paramsPtr->clientInfo);
		return 0;
	}

	bool terminateScanning = false;
	bool keyRequired = true;
	DWORD activeProcess = 0;

	SafeQueue<UI_MESSAGE> *uiMsgQueue;

	std::mutex processListMutex;
	std::vector <GAMECLIENTINFO *> activeClients;
	std::vector <GAMECLIENTINFO *> restartProcessScanClients;
	

	HANDLE keyVecMutex = CreateMutex(0, 0, 0);
	list<UNCLAIMED_KEY> unclaimedKeys;
};

