#pragma once
#include "GameNetPacket.h"
#include "PacketEnum.h"
#include "chMath.h"



class ObjectUpdatePacket : public GameNetPacket
{
public:
	int ObjectType = -1;
	ch::math::Vector3 Pos;
	int animaNumber;
	bool isLeft;

	ObjectUpdatePacket()
		: Pos(Vector3::Zero)
		, isLeft(true)
		, animaNumber(0)
		, ObjectType(-1)
	{
		SetPacketID(PacketEnumType::ObjectUpdatePacket);
	}
	// ³Ê 10
public:
	virtual void Serialize(GameNetSerializer& _Ser) override
	{
		GameNetPacket::Serialize(_Ser);
		_Ser << ObjectType;
		_Ser.Write(&Pos, sizeof(Pos));
		_Ser.Write(&animaNumber, sizeof(animaNumber));
		_Ser.Write(&isLeft, sizeof(isLeft));
		
	}

	virtual void DeSerialize(GameNetSerializer& _Ser) override
	{
		GameNetPacket::DeSerialize(_Ser);
		_Ser >> ObjectType;
		_Ser.Read(&Pos, sizeof(Pos));
		_Ser.Read(&animaNumber, sizeof(animaNumber));
		_Ser.Read(&isLeft, sizeof(isLeft));
	}

};