#include "GameNetThread.h"
#include "GameNetString.h"

GameNetThread::GameNetThread()
{
}

GameNetThread::~GameNetThread()
{
	Join();
}

// �������� ����� ���ؼ� �����忡 �̸��� �����ټ� �ִµ�.
// �� �̸��� �����ִ� ����� ����ϱ� ���ؼ� 
void GameNetThread::GameNetThreadFunction(GameNetThread* _Thread, std::string _Name)
{
	std::wstring WName = GameNetString::AnsiToUniCodeReturn(_Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	_Thread->WorkFunction();
}