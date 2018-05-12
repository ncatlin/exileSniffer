#pragma once
#include "base_thread.h"
#include "safequeue.h"
#include "uiMsg.h"

class json_pipe_thread :
	public base_thread
{
public:
	json_pipe_thread(SafeQueue<UI_MESSAGE *>* uiq, QString pipename);
	~json_pipe_thread();

	void sendPacket(rapidjson::GenericDocument<rapidjson::UTF16<> > &doc);
	void setPipePath(QString pipename);
	DWORD connectedReaders();
	void close();

	bool running = true;
	bool ded = false;
private:
	void main_loop();

	HANDLE JSONpipe = NULL;
	bool connected = false;
	QString pipepath;

	SafeQueue<UI_MESSAGE *> *uiMsgQueue;
	SafeQueue<std::wstring> entryQ; //should be rjson wvalue or a doc


};

