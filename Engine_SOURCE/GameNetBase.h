#pragma once

#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <list>
#include <vector>
#include <mutex>
#include <memory>

#pragma comment(lib, "ws2_32")

#include <thread>
#include <iostream>
#include <assert.h>

namespace GameNetDebug
{
	void GetLastErrorPrint();
};

#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false); 