#include "stdafx.h"
#include "json_pipe_thread.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

json_pipe_thread::json_pipe_thread(SafeQueue<UI_MESSAGE *>* uiq, QString pipename)
{
	uiMsgQueue = uiq;
	pipepath = "\\\\.\\pipe\\" + pipename;
}

void json_pipe_thread::close()
{
	connected = false;
	CloseHandle(JSONpipe);
}

json_pipe_thread::~json_pipe_thread()
{
	close();
	running = false;
}

void json_pipe_thread::setPipePath(QString pipename)
{
	connected = false;
	pipepath = "\\\\.\\pipe\\" + pipename;
	CloseHandle(JSONpipe); //what could go wrong
}

void json_pipe_thread::main_loop()
{
	
	DWORD ignored;

	while (running)
	{
		HANDLE hEvent;
		hEvent = CreateEvent(0, true, true, 0);
		OVERLAPPED oOverlap;
		oOverlap.hEvent = hEvent;
		JSONpipe = CreateNamedPipeA(pipepath.toStdString().c_str(),
			PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_MESSAGE,
			5,
			4024 * 1024, 4024 * 1024, 10, 0);

		if (JSONpipe == INVALID_HANDLE_VALUE)
		{
			std::stringstream err;
			err << "CreateNamedPipe " << pipepath.toStdString() << " error " << GetLastError();
			UIaddLogMsg(err.str(), 0, uiMsgQueue);
			running = false; 
			break;
		}

		ConnectNamedPipe(JSONpipe, &oOverlap);

		bool fConnected;
		while (1)
		{
			WaitForSingleObject(JSONpipe, 400);
		
			fConnected = GetOverlappedResult(JSONpipe, &oOverlap, &ignored, false);
				break;
			if (fConnected || !running)
				break;
		}

		if (!running)
			break;

		if (fConnected)
		{
			UIaddLogMsg("JSON Subscriber Connected", 0, uiMsgQueue);
			connected = true;
			bool pendingIO = false;
			while (connected && running)
			{
				if (pendingIO)
				{
					DWORD mush3;
					if (GetOverlappedResult(JSONpipe, &oOverlap, &mush3, true))
					{
						pendingIO = false;
					}
				}

				if (entryQ.empty())
				{
					Sleep(100);
					char awful[] = "Use overlapped pls";
					connected = WriteFile(JSONpipe, awful, 0, &ignored, 0);
					if (!connected)
					{
						CloseHandle(JSONpipe);
						break;
					}

					continue;
				}
				std::wstring doc = entryQ.waitItem();
				doc.append(L"\r"); //needed to make it a discrete pipe message

				DWORD writtenBytes = 0;
				DWORD byteSize = doc.size() * sizeof(wchar_t);
				bool done = WriteFile(JSONpipe, doc.c_str(), byteSize, &writtenBytes, false);
				if (!done || (writtenBytes != byteSize))
				{
					DWORD err = GetLastError();
					if (err == ERROR_IO_PENDING)
					{
						pendingIO = true;
						continue;
					}
					else
					{
						UIaddLogMsg("JSON Subscriber Disconnected", 0, uiMsgQueue);
						connected = false;
						CloseHandle(JSONpipe);
						while (!entryQ.empty())
							entryQ.pop();
					}
				}
			}
		}
		else
		{
			connected = false;
			CloseHandle(JSONpipe);
		}
	}

	ded = true;
}



void json_pipe_thread::sendPacket(rapidjson::GenericDocument<rapidjson::UTF16<>, rapidjson::CrtAllocator> &doc)
{
	if (!connected) return;
	rapidjson::GenericStringBuffer<rapidjson::UTF16<>> buffer;
	rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF16<>>, rapidjson::UTF16<>> writer(buffer);
	doc.Accept(writer);

	std::wstring resultstring = buffer.GetString();
	entryQ.addItem(resultstring);
}