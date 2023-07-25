#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chRigidbody.h"

namespace ch
{
    enum PlayerState
    {
        Idle, // 기본 상태		//1
        Walk, //걷기				//2
        Rolling, // 구르기			//3
        Default
    };
    enum PlayerDodgeDirections
    {
        NorthDodge,//위 1
        SouthDodge,//아래 2

        EastDodge,//동 3
        WestDodge,//서 4

        NEDodge,//북동쪽 5
        NWDodge//북서쪽 6
    };
	class ConvictMove :public Script
	{
    public:
        ConvictMove();
        virtual ~ConvictMove();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        virtual void OnTriggerEnter(Collider2D* oppo);
        virtual void OnTrigger(Collider2D* oppo);
        virtual void OnTriggerExit(Collider2D* oppo);

        PlayerState GetPS() { return pS; }
        void SetPS(PlayerState _a) { pS = _a; };

        PlayerDodgeDirections GetPDD() { return pDD; }
        void SetPDD(PlayerDodgeDirections _a) { pDD = _a; };

        bool GetCandDodging() {return canDodge;}
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
       // void chIdleAni();

    private://
        PlayerState pS;
        PlayerDodgeDirections pDD;
    private://
        Transform* pTr;
        Rigidbody* pRb;
        CharacterBase* player;

    public:
        static bool canDodge; 
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
