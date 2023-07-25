 #pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBulletObj.h"
#include "MonsterBulletScr.h"
#include "Bullet_Kin_Gun.h"
namespace ch 
{
	class Bullet_Kin_Gun_Scr :public Script
	{
    public:
        Bullet_Kin_Gun_Scr();
        virtual ~Bullet_Kin_Gun_Scr();

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

        void Shot();
        void ShotTerm();
        void afterShot();
    private:
        std::shared_ptr<class AudioClip> audioClip;
        class AudioSource* boss_audio;
        GameObject* audioObj;
    private:
        Animator* anima;
        Transform* thisTrans;
        Bullet_Kin_Gun* Owner;
        bool allowShot;
        bool afterShotCalled;
        float ShotTime;
       
        MonsterBulletObj* monsBullet;
	};


}

