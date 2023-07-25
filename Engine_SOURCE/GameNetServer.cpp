#include "GameNetServer.h"

GameNetServer::GameNetServer()
{
}

GameNetServer::~GameNetServer()
{
    if (0 != AcceptSocket)
    {
        closesocket(AcceptSocket);
    }
}

void GameNetServer::Send(void* _Data, unsigned int _Size)
{
    UserLock.lock();

    for (size_t i = 0; i < AllUser.size(); i++)
    {
        send(AllUser[i], reinterpret_cast<const char*>(_Data), _Size, 0);
    }

    UserLock.unlock();

}

void GameNetServer::OpenHost(short _Port, std::function<void(SOCKET)> _NewUserAcceptFunction, int _BackLog/* = 512*/)
{
    WSAData WsaData;

    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgBoxAssert("socket Error");
        return;
    }

    SOCKADDR_IN Add;
    Add.sin_family = AF_INET; // ip4주소 체계를 쓰겠다.
    Add.sin_port = htons(_Port); // 네트워크 통신에 유효한 에디안 방식으로 만들어준다.
    if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
    {
        return;
    }

    AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == AcceptSocket)
    {
        return;
    }

    if (SOCKET_ERROR == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return;
    }

    if (SOCKET_ERROR == listen(AcceptSocket, _BackLog))
    {
        return;
    }

    NewUserAcceptFunction = _NewUserAcceptFunction;

    AcceptThread.Start("AcceptThread", std::bind(AcceptThreadFunction, AcceptSocket, this));
}

void GameNetServer::AcceptThreadFunction(SOCKET _AcceptSocket, GameNetServer* _Net)
{
    int AddressLen = sizeof(SOCKADDR_IN);
    SOCKADDR_IN ClientAdd;
    while (true == _Net->GetIsNet())
    {
        memset(&ClientAdd, 0, sizeof(ClientAdd));

        // ip6 버전일지 ip4
        SOCKET ClientSocket = accept(_AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

        if (SOCKET_ERROR == ClientSocket || INVALID_SOCKET == ClientSocket)
        {
            return;
        }


        _Net->UserLock.lock();

        _Net->AllUser.push_back(ClientSocket);
        std::shared_ptr<GameNetThread> RecvThread = std::make_shared<GameNetThread>();
        _Net->RecvThreads.push_back(RecvThread);
        std::string ThreadName = std::to_string(ClientSocket);

        // 함수포인터인데
        // 인자의 제한도 없고
        // 자료형의 제한도 없고
        // 맴버함수의 제한도 없어

        _Net->AcceptLock.lock();
        // 펑셔널은 함수를 예약하고 실행하는 시점을 지연시킬수도 있다.

        // 여기중단점 까지는 액셉트 쓰레드 겠지만
        _Net->NewUserWorks.push_back([=]
            {
                // main 쓰레드가 됩니다.
                _Net->NewUserAcceptFunction(ClientSocket);
            });

        _Net->AcceptLock.unlock();


        ThreadName += " UserServerRecvThread";
        RecvThread->Start(ThreadName, std::bind(RecvThreadFunction, ClientSocket, _Net));


        _Net->UserLock.unlock();
    }
}

void GameNetServer::PacketProcess()
{
    AcceptLock.lock();
    while (0 != NewUserWorks.size())
    {
        std::function<void()> Work = NewUserWorks.front();
        NewUserWorks.pop_front();
        Work();
    }
    AcceptLock.unlock();

    GameNet::PacketProcess();

}

void GameNetServer::PacketSend(std::shared_ptr<GameNetPacket> _Packet)
{
    if (true == AllUser.empty())
    {
        return;
    }

    UserLock.lock();

    GameNetSerializer Ser;
    _Packet->SerializePacket(Ser);
    for (size_t i = 0; i < AllUser.size(); i++)
    {
        // 보낸 당사자에게는 보내면 안되요.

        send(AllUser[i], reinterpret_cast<const char*>(Ser.GetDataPtr()), Ser.GetWriteOffSet(), 0);
    }
    UserLock.unlock();
}