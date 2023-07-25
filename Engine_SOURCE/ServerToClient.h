#pragma once

#include "GameNetPacket.h"
#include "PacketEnum.h"

class UserIDPacket : public GameNetPacket
{
public:
	UserIDPacket()
	{
		SetPacketID(PacketEnumType::UserIDPacket);
	}
	// �� 10
public:
	virtual void Serialize(GameNetSerializer& _Ser) override
	{
		GameNetPacket::Serialize(_Ser);
	}

	virtual void DeSerialize(GameNetSerializer& _Ser) override
	{
		GameNetPacket::DeSerialize(_Ser);
	}

};