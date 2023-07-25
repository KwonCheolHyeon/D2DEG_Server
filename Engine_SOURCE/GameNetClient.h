#pragma once
#include "GameNetBase.h"
#include "GameNet.h"
#include "GameNetThread.h"

// Ό³Έν :
class GameNetClient : public GameNet
{
public:
	// constrcuter destructer
	GameNetClient();
	~GameNetClient();

	// delete Function
	GameNetClient(const GameNetClient& _Other) = delete;
	GameNetClient(GameNetClient&& _Other) noexcept = delete;
	GameNetClient& operator=(const GameNetClient& _Other) = delete;
	GameNetClient& operator=(GameNetClient&& _Other) noexcept = delete;

	void Connect(const std::string& IP, short Port);

	void Send(void* _Data, unsigned int _Size) override;

	void PacketSend(std::shared_ptr<GameNetPacket> _Packet) override;
protected:


private:
	SOCKET ClientSocket = 0;
	GameNetThread RecvThread;
};

