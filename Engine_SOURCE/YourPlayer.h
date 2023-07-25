#pragma once
#include "chScript.h"
#include "GameNetObject.h"
#include "ServerCharacterBase.h"
#include "chAnimator.h"
#include "chCollider2D.h"
#include "YourPlayerMove.h"
namespace ch
{
	class YourPlayer : public Script, public GameNetObject
	{
	public:
		YourPlayer();
		~YourPlayer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

    public:// 01   : 마우스플레이어 사이 각도 관련
        void playerLookingMouse();
        void HandSide();
        void MouseAndPlayerAngle();
        void SetAnimation();

    public:
        void IdleAni();
        void RunAni();
        void RollingAni();
        void ShotAni();
    public:
        int SetAnimationNumber(const std::wstring& name);
    private:
        bool isDodgeAnimationing();
        void afterDodging();
        void playWalkingAin();
    private:
        Transform* pTr;
        Collider2D* pCollider;
        Animator* pAnimator;
        ServerCharacterBase* player;

        eServerPlayerState cPS;
        eServerPlayerDodgeDirections cPDD;
        eServerPlayerDirections CPD;
    private:
        bool walk;

    private://01
        float c2mAngle;
        int prevIdleDirection;//
        int prevWalkDirection;//
        int prevPlayerState;
        bool playWalking;

    private:
        bool isOneHand;
        bool dodging;
	
		
	};
}
