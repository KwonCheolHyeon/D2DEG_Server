#pragma once
#include "chScript.h"
#include "chGun.h"
#include "chPlayerHand.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{
	enum FightSabreState
	{
		SabreItemBox,
		SabreActive,//idle
		SabrenonActive,//pistol상태
		SabreReload,
		SabreShot,
	};

	class FightSabreScr : public Script
	{
	public:
		FightSabreScr();
		virtual ~FightSabreScr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetpistolHand(PlayerHand* hand) { playerHand = hand; }
		PlayerHand* GetpistolHand() { return playerHand; }

		void FightSabreOn() { fss = FightSabreState::SabreActive; }
		void FightSabreOff() { fss = FightSabreState::SabrenonActive; }

		void ItemBox();
		void Active();
		void nonActiveGun();
		void Reload();
		void Shot();

	public:
		//총 각도 관련
		void angleFind();
		void GunLookCursor();


	public:
		bool touchGun;
		bool prevTouchGun;

	private:
		Gun* gunObj;
		PlayerHand* playerHand;
		Animator* anima;
		FightSabreState fss;
		FightSabreState prevFss;
		Transform* gunTransform;
		Collider2D* col;
	private:
		std::shared_ptr<AudioClip> audioClip[2];
		AudioSource* boss_audio[2];
		GameObject* audioObj[2];

	private:
		float angle;
		float shotTimer = 0.0f;

	private:
		int agazine;
		float reloadTime;

	};

}

