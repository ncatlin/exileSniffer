
/*
Libraries used:

Qt for the GUI
libtins for sniffing
boost for libtins (+ others)
rapidjson for ggpk data

*/
#define TINS_STATIC
#include "tins/tins.h"
#include "tins/tcp_ip/stream_follower.h"
#pragma comment(lib, "tins.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "wpcap.lib")

#include <Windows.h>
#include <WinSock2.h>

//learned the hard way - this needs to come after the libtins stuff
#include <QtWidgets> 

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <locale>
#include <queue>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <iostream>
#include <array>

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h" 
#include "rapidjson\allocators.h"

#include <cryptopp\cryptlib.h>
#include <cryptopp\salsa.h>