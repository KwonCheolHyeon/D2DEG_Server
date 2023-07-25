#pragma once
#include "GameNetBase.h"
#include <map>
#include "GameNetPacket.h"

// Ό³Έν :
class GameNetObject
{
public:

	// constrcuter destructer
	GameNetObject();
	~GameNetObject();

	// delete Function
	GameNetObject(const GameNetObject& _Other) = delete;
	GameNetObject(GameNetObject&& _Other) noexcept = delete;
	GameNetObject& operator=(const GameNetObject& _Other) = delete;
	GameNetObject& operator=(GameNetObject&& _Other) noexcept = delete;

	static bool IsNetObject(int ObjectID)
	{
		return AllNetObjects.contains(ObjectID);
	}

	static void PushObjectPacket(std::shared_ptr<GameNetPacket> _Packet);


	int GetNetObjectID()
	{
		return ObjectID;
	}

	void ServerObjectInit();

	void ClientObjectInit(int _Object);


protected:
	int ObjectID = -1;
	std::list<std::shared_ptr<GameNetPacket>> Packets;

private:
	static std::atomic<int> AtomicObjectID;
	static std::mutex ObjectLock;
	static std::map<int, GameNetObject*> AllNetObjects;

};

