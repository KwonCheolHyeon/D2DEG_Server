#pragma once
#include "GameNetBase.h"
#include <string>
#include <thread>
#include <functional>

// Ό³Έν :
class GameNetThread
{
public:
	// constrcuter destructer
	GameNetThread();
	~GameNetThread();

	// delete Function
	GameNetThread(const GameNetThread& _Other) = delete;
	GameNetThread(GameNetThread&& _Other) noexcept = delete;
	GameNetThread& operator=(const GameNetThread& _Other) = delete;
	GameNetThread& operator=(GameNetThread&& _Other) noexcept = delete;

	void Start(const std::string _ThreadName, std::function<void()> _CallBack)
	{
		WorkFunction = _CallBack;
		Thread = std::thread(GameNetThreadFunction, this, _ThreadName);
	}

	void Join()
	{
		if (nullptr != WorkFunction)
		{
			Sleep(1);
			Thread.join();
			WorkFunction = nullptr;
		}
	}

protected:

private:
	std::thread Thread;
	std::function<void()> WorkFunction;

	static void GameNetThreadFunction(GameNetThread* _Thread, std::string _Name);

};

