#pragma once
#include <atomic>
#include <queue>
#include "GameNetBase.h"
#include "GameNetPacket.h"
#include "GameNetDispatcher.h"

// 서버와 클라이언트가 공유하는
// 함수들이나 맴버변수들을 상속내려주는 용도입니다.

// 서버와 클라이언트가 완전히 동일한 로직을 사용할만한 내용들을 여기에 담을것인데

class GameNet
{
public:
	GameNet() {}
	virtual ~GameNet() {}

	bool GetIsNet()
	{
		return IsNet;
	}

	virtual void Send(void* _Data, unsigned int _Size) = 0;

	virtual void PacketSend(std::shared_ptr<GameNetPacket> _Packet);

	virtual void PacketProcess();

	GameNetDispatcher Dispatcher;

protected:
	// 추상클래스
	static void RecvThreadFunction(SOCKET _Socket, GameNet* _Net);

	std::mutex PacketLock;
	std::list<std::shared_ptr<GameNetPacket>> RecvPackets;

	std::list<std::shared_ptr<GameNetPacket>> MainThreadPackets;

	void PushPacket(std::shared_ptr<GameNetPacket> _Packet);

private:
	// 네트워크 기능이 동작하느냐 안하느냐를 표현합니다.
	std::atomic<bool> IsNet = true;
};

