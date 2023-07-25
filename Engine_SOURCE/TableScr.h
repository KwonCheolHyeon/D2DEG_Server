#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{

	class TableScr : public Script
	{
    public:
        TableScr();
        virtual ~TableScr();

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

        int GetClosestDirection(Collider2D* collider);
    private:
        std::shared_ptr<AudioClip> audioClip;
        AudioSource* boss_audio;
        GameObject* audioObj;
    private:
        bool tableOn;
        int directionNumber; // 1 = ╩С , 2 = ©Л , 3 = го , 4 = аб
        int prevDN;
        int once2;
        int once1;
        int once0;
        Animator* tAnimator;
        int tableCount;


	};
}

