#include "GameNetThread.h"
#include "GameNetString.h"

GameNetThread::GameNetThread()
{
}

GameNetThread::~GameNetThread()
{
	Join();
}

// 윈도우의 기능을 통해서 쓰레드에 이름을 지어줄수 있는데.
// 그 이름을 지어주는 기능을 사용하기 위해서 
void GameNetThread::GameNetThreadFunction(GameNetThread* _Thread, std::string _Name)
{
	std::wstring WName = GameNetString::AnsiToUniCodeReturn(_Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	_Thread->WorkFunction();
}