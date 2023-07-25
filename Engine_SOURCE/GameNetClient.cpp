#include "GameNetClient.h"

GameNetClient::GameNetClient()
{
}

GameNetClient::~GameNetClient()
{
    if (0 != ClientSocket)
    {
        closesocket(ClientSocket);
    }
}

void GameNetClient::Connect(const std::string& _IP, short _Port)
{
    // 내 프로그램이 네트워크를 사용할래요.
    WSAData WsaData;

    // 이 프로그램이 윈도우에게 서버를 사용하겠다고 알려주는 겁니다.
    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgBoxAssert("socket Error");
        return;
    }

    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == ClientSocket)
    {
        return;
    }

    SOCKADDR_IN ClientAdd;

    ClientAdd.sin_family = AF_INET;
    ClientAdd.sin_port = htons(30000);

    // 로컬호스트 ip 내컴퓨터에 내가 접속하겠다.
    std::string IP = _IP;

    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
    {
        return;
    }

    int Len = sizeof(SOCKADDR_IN);

    // 접속 시간을 초과했습니다.
    if (SOCKET_ERROR == connect(ClientSocket, (const sockaddr*)&ClientAdd, Len))
    {
        MsgBoxAssert("커넥트에 실패했습니다.");
        return;
    }

    RecvThread.Start("ClientRecvThread", std::bind(RecvThreadFunction, ClientSocket, this));
}

void GameNetClient::Send(void* _Data, unsigned int _Size)
{
    send(ClientSocket, reinterpret_cast<const char*>(_Data), _Size, 0);
}

void GameNetClient::PacketSend(std::shared_ptr<GameNetPacket> _Packet)
{
    GameNetSerializer Ser;
    _Packet->SerializePacket(Ser);
    send(ClientSocket, reinterpret_cast<const char*>(Ser.GetDataPtr()), Ser.GetWriteOffSet(), 0);
}