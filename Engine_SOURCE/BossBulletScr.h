#pragma once
#include "chScript.h"
#include "chGameObject.h"
#include "chAnimator.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch 
{
	class BossBulletScr : public Script
	{
    public:
        BossBulletScr();
        virtual ~BossBulletScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);


        void Reset();
        void bombCollderEffect();

        std::shared_ptr<AudioClip> audioClip;
        AudioSource* boss_audio;
        GameObject* audioObj;
    private:
        Animator* bossBullet;
        Collider2D* col;

    private:
        float bombTimer;
        float bombCollder;;


	};

}


