#pragma once
#include <atomic>
#include <queue>
#include "GameNetBase.h"
#include "GameNetPacket.h"
#include "GameNetDispatcher.h"

// ������ Ŭ���̾�Ʈ�� �����ϴ�
// �Լ����̳� �ɹ��������� ��ӳ����ִ� �뵵�Դϴ�.

// ������ Ŭ���̾�Ʈ�� ������ ������ ������ ����Ҹ��� ������� ���⿡ �������ε�

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
	// �߻�Ŭ����
	static void RecvThreadFunction(SOCKET _Socket, GameNet* _Net);

	std::mutex PacketLock;
	std::list<std::shared_ptr<GameNetPacket>> RecvPackets;

	std::list<std::shared_ptr<GameNetPacket>> MainThreadPackets;

	void PushPacket(std::shared_ptr<GameNetPacket> _Packet);

private:
	// ��Ʈ��ũ ����� �����ϴ��� ���ϴ��ĸ� ǥ���մϴ�.
	std::atomic<bool> IsNet = true;
};

