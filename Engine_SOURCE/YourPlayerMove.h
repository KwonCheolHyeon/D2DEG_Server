#pragma once
#include "chScript.h"
#include "ServerCharacterBase.h"
#include "chRigidbody.h"
#include "chCollider2D.h"
namespace ch
{
    enum eServerPlayerState
    {
        eIdle, // 기본 상태		//1
        eWalk, //걷기				//2
        eRolling, // 구르기			//3
        eDefault
    };
    enum eServerPlayerDodgeDirections
    {
        eNorthDodge,//위 1
        eSouthDodge,//아래 2

        eEastDodge,//동 3
        eWestDodge,//서 4

        eNEDodge,//북동쪽 5
        eNWDodge//북서쪽 6
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
       // bool chCheckDirectionKeyDoge(); //닷지용
        void chState();//상태에 따라 애니메이션 실행
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
    private: //플레이어 벽
        int directNum; //방향 결정
        int secdirectNum;
        int GetClosestDirection(Collider2D* collider);
        int colliderCount;
    };
}


//죄수 캐릭터 움직임 스크립
