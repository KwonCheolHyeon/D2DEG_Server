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
    // �� ���α׷��� ��Ʈ��ũ�� ����ҷ���.
    WSAData WsaData;

    // �� ���α׷��� �����쿡�� ������ ����ϰڴٰ� �˷��ִ� �̴ϴ�.
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

    // ����ȣ��Ʈ ip ����ǻ�Ϳ� ���� �����ϰڴ�.
    std::string IP = _IP;

    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
    {
        return;
    }

    int Len = sizeof(SOCKADDR_IN);

    // ���� �ð��� �ʰ��߽��ϴ�.
    if (SOCKET_ERROR == connect(ClientSocket, (const sockaddr*)&ClientAdd, Len))
    {
        MsgBoxAssert("Ŀ��Ʈ�� �����߽��ϴ�.");
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