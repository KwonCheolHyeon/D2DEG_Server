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

// �������� �޾Ƽ� Ŭ���̾��� ������Ʈ�� ����� ���� �Ѵ�.
void GameNetObject::ClientObjectInit(int _Object)
{
	ObjectID = _Object;
	ObjectLock.lock();

	if (true == AllNetObjects.contains(ObjectID))
	{
		MsgBoxAssert("�̹� �����ϴ� ������ƮID�� �� ����Ϸ��� �߽��ϴ�.");
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