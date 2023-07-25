#include "GameNetObject.h"

std::atomic<int> GameNetObject::AtomicObjectID;
std::mutex GameNetObject::ObjectLock;
std::map<int, GameNetObject*> GameNetObject::AllNetObjects;


GameNetObject::GameNetObject()
{
}

GameNetObject::~GameNetObject()
{
	ObjectLock.lock();
	AllNetObjects.erase(ObjectID);
	ObjectLock.unlock();
}



void GameNetObject::ServerObjectInit()
{
	ObjectID = ++AtomicObjectID;

	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, GameNetObject*>(ObjectID, this));
	ObjectLock.unlock();
}

// 서버에게 받아서 클라이언의 오브젝트가 만들어 져야 한다.
void GameNetObject::ClientObjectInit(int _Object)
{
	ObjectID = _Object;
	ObjectLock.lock();

	if (true == AllNetObjects.contains(ObjectID))
	{
		MsgBoxAssert("이미 존재하는 오브젝트ID에 또 등록하려고 했습니다.");
		return;
	}

	AllNetObjects.insert(std::pair<int, GameNetObject*>(ObjectID, this));
	ObjectLock.unlock();
}

void GameNetObject::PushObjectPacket(std::shared_ptr<GameNetPacket> _Packet)
{
	if (false == AllNetObjects.contains(_Packet->GetObjectID()))
	{
		return;
	}

	AllNetObjects[_Packet->GetObjectID()]->Packets.push_back(_Packet);
}