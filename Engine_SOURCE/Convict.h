#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chAnimator.h"
#include "chCollider2D.h"
#include "ConvictMove.h"
#include "chHeart_UI.h"
#include "BlankBulletObj.h"
#include "ConvictBlankBulletScr.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{
	class Convict : public Script
	{
	public:
        Convict();
        virtual ~Convict();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollisionStay(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

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

    public: //체력관련 함수
        void SetHeart_UI(std::vector<Heart_UI*> a) { pHeartControl = a; }
        void SetHeart();
    public:
        void SetBlankBullet_UI(std::vector<BlankBulletObj*> a) { pBlankBullet = a; }
        void SetBlankBullet();

        void SetBlankBulletscr(ConvictBlankBulletScr* _a) { cbb = _a; }

    private:
        bool isDodgeAnimationing();
        void afterDodging();
        void playWalkingAin();
    private:
        Transform* pTr;
        Collider2D* pCollider;
        Animator* pAnimator;
        CharacterBase* player;

        PlayerState cPS;
        PlayerDodgeDirections cPDD;
        PlayerDirections CPD;
    private:
        std::shared_ptr<AudioClip> audioClip[5];
        AudioSource* boss_audio[5];
        GameObject* audioObj[5];
        bool walk;

    private://01
        float c2mAngle;
        int prevIdleDirection;//
        int prevWalkDirection;//
        int prevPlayerState;
        bool playWalking;

        std::vector<Heart_UI*> pHeartControl;
        std::vector<BlankBulletObj*> pBlankBullet;
        ConvictBlankBulletScr* cbb;
        //HP
        int pHp;
        int prevHp;

        //공포탄
        int pBB;
        int prevBB;


    private:
        bool isOneHand;
        bool dodging;
	};
}

//죄수 캐릭터 이미지와 콜라이더와 체력 담당
