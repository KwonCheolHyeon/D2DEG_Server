#pragma once
#include "chScript.h"
#include "ServerCharacterBase.h"
#include "chRigidbody.h"
#include "chCollider2D.h"
namespace ch
{
    enum eServerPlayerState
    {
        eIdle, // �⺻ ����		//1
        eWalk, //�ȱ�				//2
        eRolling, // ������			//3
        eDefault
    };
    enum eServerPlayerDodgeDirections
    {
        eNorthDodge,//�� 1
        eSouthDodge,//�Ʒ� 2

        eEastDodge,//�� 3
        eWestDodge,//�� 4

        eNEDodge,//�ϵ��� 5
        eNWDodge//�ϼ��� 6
    };
    class YourPlayerMove :public Script
    {
    public:
        YourPlayerMove();
        virtual ~YourPlayerMove();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        eServerPlayerState GetPS() { return pS; }
        void SetPS(eServerPlayerState _a) { pS = _a; };

        eServerPlayerDodgeDirections GetPDD() { return pDD; }
        void SetPDD(eServerPlayerDodgeDirections _a) { pDD = _a; };

        bool GetCandDodging() { return ServercanDodge; }
    public:
        void Idle();
        void Walking();
        void afterWalking();
        void Dodging();
        void afterDodging();
        void gotoNormal();


    public:
        bool CheckKeyDirection();
       // bool chCheckDirectionKeyDoge(); //������
        void chState();//���¿� ���� �ִϸ��̼� ����
      //  void chIdleAni();

    private://
        eServerPlayerState pS;
        eServerPlayerDodgeDirections pDD;
    private://
        Transform* pTr;
        Rigidbody* pRb;
        ServerCharacterBase* player;

    public:
        static bool ServercanDodge;
        bool isDodging;
        bool isRolling;
        bool isWall;
        Vector3 wallPosition;
        float speed;
    private: //�÷��̾� ��
        int directNum; //���� ����
        int secdirectNum;
        int GetClosestDirection(Collider2D* collider);
        int colliderCount;
    };
}


//�˼� ĳ���� ������ ��ũ��
