#pragma once
#include "chScript.h"
#include "MonsterBase.h"
#include "chAnimator.h"
#include "MonsterBullet2Obj.h"
#include "MonsterBullet2Scr.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{

    class CubeScr : public Script
    {
    public:
        CubeScr();
        virtual ~CubeScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);


    public:
        void Attack();
        void Idle();
        void Death();
        void BulletMake();

    private:
        Animator* anima;
        MonsterBase* thisMonster;
        monsterState ms;
        Transform* mTr;
    private:
        std::shared_ptr<AudioClip> audioClip[3];
        AudioSource* boss_audio[3];
        GameObject* audioObj[3];

    private:
        MonsterBullet2Obj* Mbobj[8];
        MonsterBullet2Scr* Mbscr[8];
    private:
        float nullbulletTime;
        bool moveOn;
        float bulletMakeTime;
        int bulletMakeCount;
        int monsterHp;
        float DeathTIME;
        
    };


}

