#pragma once
#include "GameNetBase.h"
#include <memory>
#include "GameNetSerializer.h"

// 레퍼런스 카운팅을 침습형으로 바꾼다.

// 설명 :
class GameNetPacket : public std::enable_shared_from_this<GameNetPacket>
{
public:
	// constrcuter destructer
	GameNetPacket();
	~GameNetPacket();

	//// delete Function
	//GameNetPacket(const GameNetPacket& _Other) = delete;
	//GameNetPacket(GameNetPacket&& _Other) noexcept = delete;
	//GameNetPacket& operator=(const GameNetPacket& _Other) = delete;
	//GameNetPacket& operator=(GameNetPacket&& _Other) noexcept = delete;

	template<typename ConvertType>
	std::shared_ptr<ConvertType> DynamicConvert()
	{
		return std::dynamic_pointer_cast<ConvertType>(shared_from_this());
	}


	void SerializePacket(GameNetSerializer& _Ser)
	{
		this->Serialize(_Ser);
		SerializeEnd(_Ser);
	}

	void DeSerializePacket(GameNetSerializer& _Ser)
	{
		this->DeSerialize(_Ser);
	}


	template<typename EnumType>
	EnumType GetPacketIDToEnum()
	{
		return static_cast<EnumType>(PacketID);
	}

	unsigned int GetPacketID()
	{
		return PacketID;
	}

	template<typename EnumType>
	void SetPacketID(EnumType _PacketID)
	{
		PacketID = static_cast<int>(_PacketID);
	}

	void SetPacketID(unsigned int _PacketID)
	{
		PacketID = _PacketID;
	}


	unsigned int GetObjectID()
	{
		return ObjectID;
	}

	void SetObjectID(unsigned int _ObjectID)
	{
		ObjectID = _ObjectID;
	}

	virtual void Serialize(GameNetSerializer& _Ser) = 0
	{
		_Ser << PacketID;
		_Ser << Size;
		_Ser << ObjectID;
	}

	virtual void DeSerialize(GameNetSerializer& _Ser) = 0
	{
		_Ser >> PacketID;
		_Ser >> Size;
		_Ser >> ObjectID;
	}

protected:



private:
	unsigned int PacketID = -1;
	unsigned int Size = -1;
	unsigned int ObjectID = -1;

	void SerializeEnd(GameNetSerializer& _Ser)
	{
		Size = _Ser.GetWriteOffSet();

		if (Size <= 0)
		{
			MsgBoxAssert("0바이트 패킷이 감지되었습니다");
		}

		unsigned char* Ptr = _Ser.GetDataPtr();
		memcpy_s(&Ptr[4], sizeof(int), &Size, sizeof(int));
	}
};

