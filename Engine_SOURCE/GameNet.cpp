#include "GameNet.h"
#include "GameNetSerializer.h"

void GameNet::RecvThreadFunction(SOCKET _Socket, GameNet* _Net)
{
	// ������� �⺻������ ������ü�� ���̰ɷ��ִ�.
	// �ƹ��� ���� �����尡 �����Ѵٰ� �ϴ���
	// �޸� ������ ������ �ʴ´�.
	// window interlock �Լ��� �̿��ؼ� ����������ϴ�.
	char Data[1024] = {};

	GameNetSerializer Ser;
	int PacketType = -1;
	int PacketSize = -1;

	while (true == _Net->GetIsNet())
	{
		// ����� ��ǻ�Ϳ��� ���ƿ� �������� ũ��
		int Result = recv(_Socket, Data, sizeof(Data), 0);

		// ������ �������ٴ� �Ҹ�
		if (-1 == Result)
		{
			// ������ ������ ��������.
			// �ҽÿ� ��ǻ�Ͱ� �����ٰų� ����� ���� ���ɼ��� �����ϴ�.
			return;
		}

		// ���Ͽ� ������ �־ return;
		if (SOCKET_ERROR == _Socket || INVALID_SOCKET == _Socket)
		{
			return;
		}

		// �츮�� ������ UDP�� TCP�� �����ϱ�� �ߴ�.
		// UDP�� �ȿ��� �ȿ��� 12����Ʈ�� �ƴ϶� 1����Ʈ�� ��� ���� ��찡 ���ٰ� �߾�.
		Ser.Write(Data, Result);

		if (8 > Ser.GetWriteOffSet())
		{
			continue;
		}

		// ���������� 
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

		// ����� �� �޾Ҵ�.
		// ����Ʈ ����� ��Ŷ���� �ٽ� ��������� �Ѵ�.

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



		// ������� ����������
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
	// ������ ������ queue������ �ٲٴ°� �� �������̴�.
	// ����.
	PacketLock.lock();
	RecvPackets.push_back(_Packet);
	PacketLock.unlock();
}

void GameNet::PacketSend(std::shared_ptr<GameNetPacket> _Packet)
{

}
