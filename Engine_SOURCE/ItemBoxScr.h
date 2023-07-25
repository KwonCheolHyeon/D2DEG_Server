#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "ItemBox.h"
#include "chFightSabreObject.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch 
{
    enum itemBoxState 
    {
        CloseBox,
        OpenBox,
    };
	class ItemBoxScr :public Script
	{
    public:
        ItemBoxScr();
        virtual ~ItemBoxScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollisionStay(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        void openBox();
        void closeBox();

        void SetFightSabreObject(FightSabreObject* _a) { fightsa = _a; }
    private:
        std::shared_ptr<AudioClip> audioClip;
        AudioSource* boss_audio;
        GameObject* audioObj;
    private:
        Animator* bAnimator;
        itemBoxState ibs;
        FightSabreObject* fightsa;
        bool oneOpen;
        bool p2bOn;
        bool p2bOnKey;

	};


}

