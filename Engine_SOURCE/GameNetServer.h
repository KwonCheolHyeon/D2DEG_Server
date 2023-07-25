#pragma once
#include "GameNetBase.h"
#include "GameNet.h"
#include "GameNetThread.h"

// Ό³Έν :
class GameNetServer : public GameNet
{
public:
	// constrcuter destructer
	GameNetServer();
	~GameNetServer();

	// delete Function
	GameNetServer(const GameNetServer& _Other) = delete;
	GameNetServer(GameNetServer&& _Other) noexcept = delete;
	GameNetServer& operator=(const GameNetServer& _Other) = delete;
	GameNetServer& operator=(GameNetServer&& _Other) noexcept = delete;

	void OpenHost(short _Port, std::function<void(SOCKET)> _NewUserAcceptFunction, int _BackLog = 512);

	void Send(void* _Data, unsigned int _Size) override;

	void PacketSend(std::shared_ptr<GameNetPacket> _Packet) override;

protected:
	void PacketProcess() override;

private:
	SOCKET AcceptSocket;
	GameNetThread AcceptThread;

	std::mutex UserLock;
	std::vector<SOCKET> AllUser;
	std::vector<std::shared_ptr<GameNetThread>> RecvThreads;


	std::mutex AcceptLock;
	std::list<std::function<void()>> NewUserWorks;

	std::function<void(SOCKET)> NewUserAcceptFunction;



	static void AcceptThreadFunction(SOCKET _AcceptSocket, class GameNetServer* _Net);
};

