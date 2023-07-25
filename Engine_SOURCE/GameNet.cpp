#include "GameNet.h"
#include "GameNetSerializer.h"

void GameNet::RecvThreadFunction(SOCKET _Socket, GameNet* _Net)
{
	// 아토믹은 기본적으로 변수자체에 락이걸려있다.
	// 아무리 많은 쓰레드가 접근한다고 하더라도
	// 메모리 문제가 생기지 않는다.
	// window interlock 함수를 이용해서 만들어졌습니다.
	char Data[1024] = {};

	GameNetSerializer Ser;
	int PacketType = -1;
	int PacketSize = -1;

	while (true == _Net->GetIsNet())
	{
		// 상대편 컴퓨터에서 날아온 데이터의 크기
		int Result = recv(_Socket, Data, sizeof(Data), 0);

		// 연결이 끊어졌다는 소리
		if (-1 == Result)
		{
			// 상대와의 연결이 끊어졌다.
			// 불시에 컴퓨터가 꺼졌다거나 등등의 일일 가능성이 높습니다.
			return;
		}

		// 소켓에 문제가 있어도 return;
		if (SOCKET_ERROR == _Socket || INVALID_SOCKET == _Socket)
		{
			return;
		}

		// 우리는 무조건 UDP랑 TCP로 동신하기로 했다.
		// UDP는 안오면 안왔지 12바이트가 아니라 1바이트씩 끊어서 오는 경우가 없다고 했어.
		Ser.Write(Data, Result);

		if (8 > Ser.GetWriteOffSet())
		{
			continue;
		}

		// 프로토콜은 
		if (-1 == PacketSize)
		{
			{
				unsigned char* TypePivotPtr = &Ser.GetDataPtr()[0];
				int* ConvertPtr = reinterpret_cast<int*>(TypePivotPtr);
				PacketType = *ConvertPtr;
			}

			{
				unsigned char* SizePivotPtr = &Ser.GetDataPtr()[4];
				int* ConvertPtr = reinterpret_cast<int*>(SizePivotPtr);
				PacketSize = *ConvertPtr;
			}
		}

		if (PacketSize > Ser.GetWriteOffSet())
		{
			continue;
		}

		// 제대로 다 받았다.
		// 바이트 덩어리를 패킷으로 다시 복구해줘야 한다.

		while (true)
		{
			std::shared_ptr<GameNetPacket> Packet = _Net->Dispatcher.ConvertPacket(PacketType, Ser);
			_Net->PushPacket(Packet);

			if (Ser.GetWriteOffSet() == Ser.GetReadOffSet())
			{
				Ser.Reset();
			} //         100                   60
			else if (Ser.GetWriteOffSet() > Ser.GetReadOffSet())
			{
				Ser.ClearReadData();

				{
					unsigned char* TypePivotPtr = &Ser.GetDataPtr()[0];
					int* ConvertPtr = reinterpret_cast<int*>(TypePivotPtr);
					PacketType = *ConvertPtr;
				}

				{
					unsigned char* SizePivotPtr = &Ser.GetDataPtr()[4];
					int* ConvertPtr = reinterpret_cast<int*>(SizePivotPtr);
					PacketSize = *ConvertPtr;
				}
				continue;
			}

			PacketType = -1;
			PacketSize = -1;
			break;
		}



		// 여기까지 내려왔으면
	}
}

void GameNet::PacketProcess()
{
	PacketLock.lock();
	MainThreadPackets = RecvPackets;
	RecvPackets.clear();
	PacketLock.unlock();

	while (0 != MainThreadPackets.size())
	{
		std::shared_ptr<GameNetPacket> Packet = MainThreadPackets.front();
		MainThreadPackets.pop_front();
		Dispatcher.ProcessPacket(Packet);
	}

}

void GameNet::PushPacket(std::shared_ptr<GameNetPacket> _Packet)
{
	// 쓰레드 세이프 queue등으로 바꾸는게 더 빠를것이다.
	// 안함.
	PacketLock.lock();
	RecvPackets.push_back(_Packet);
	PacketLock.unlock();
}

void GameNet::PacketSend(std::shared_ptr<GameNetPacket> _Packet)
{

}
