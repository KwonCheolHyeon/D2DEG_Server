#pragma once
#include "GameNetSerializer.h"
#include "GameNetPacket.h"
#include <functional>
#include <map>

// ���� :
class GameNetDispatcher
{
public:
	// constrcuter destructer
	GameNetDispatcher();
	~GameNetDispatcher();

	// delete Function
	GameNetDispatcher(const GameNetDispatcher& _Other) = delete;
	GameNetDispatcher(GameNetDispatcher&& _Other) noexcept = delete;
	GameNetDispatcher& operator=(const GameNetDispatcher& _Other) = delete;
	GameNetDispatcher& operator=(GameNetDispatcher&& _Other) noexcept = delete;

	template<typename PacketType, typename EnumType>
	void AddHandler(EnumType _Type, std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		AddHandler(static_cast<int>(_Type), _CallBack);
	}


	//           1000
	template<typename PacketType>
	void AddHandler(int Type, std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		ConvertFunctionMap[Type] = [=](GameNetSerializer& _Ser)
		{
			std::shared_ptr<PacketType> Packet = std::make_shared<PacketType>();
			Packet->DeSerializePacket(_Ser);
			return Packet;
		};


		PacketProcessMap[Type] = [=](std::shared_ptr<GameNetPacket> _Packet)
		{
			std::shared_ptr<PacketType> ConvertPacket = std::dynamic_pointer_cast<PacketType>(_Packet);

			if (nullptr == ConvertPacket)
			{
				MsgBoxAssert("��Ŷ ����Ʈ�� �����߽��ϴ�.");
			}

			_CallBack(ConvertPacket);
		};
	}

	std::shared_ptr<GameNetPacket> ConvertPacket(int Type, GameNetSerializer& _Ser)
	{
		if (false == ConvertFunctionMap.contains(Type))
		{
			MsgBoxAssert("AddHandler�� ������� ���� ��Ŷ�Դϴ�");
			return nullptr;
		}

		return ConvertFunctionMap[Type](_Ser);
	}

	void ProcessPacket(std::shared_ptr<GameNetPacket> _Packet)
	{
		if (false == PacketProcessMap.contains(_Packet->GetPacketID()))
		{
			MsgBoxAssert("AddHandler�� ������� ���� ��Ŷ�Դϴ�");
			return;
		}

		PacketProcessMap[_Packet->GetPacketID()](_Packet);
	}


protected:

private:
	// � ������ ���̸� � ��Ŷ���� ��ȯ�ؾ���?
	std::map<int, std::function<std::shared_ptr<GameNetPacket>(GameNetSerializer&)>> ConvertFunctionMap;
	// � ��Ŷ�� ������ ��� ó���ؾ���?
	std::map<int, std::function<void(std::shared_ptr<GameNetPacket>)>> PacketProcessMap;
};

