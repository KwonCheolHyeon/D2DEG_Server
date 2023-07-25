#pragma once
#include "chScript.h"
#include "chGun.h"
#include "chPlayerHand.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch 
{
	enum PistolState
	{
		PistolActive,//idle
		PistolnonActive,//비활성화상태
		PistolReload,
		PistolShot,
	};
	class BasicGunScript : public Script
	{
	public:
		BasicGunScript();
		virtual ~BasicGunScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetpistolHand(PlayerHand* hand) { playerHand = hand; }
		PlayerHand* GetpistolHand() { return playerHand; }

		void SetpistolPool(BulletPool* pool) { bulletpool = pool; }
		BulletPool* GetpistolPool() { return bulletpool; }

		void SetGunBox(GameObject* box) { gunBox = box; }


		void PistolOn() { ps = PistolState::PistolActive; }
		void PistolOff() { ps = PistolState::PistolnonActive; }

		void Active();//활성
		void Disable();//비활성
		void Shot();
		void Reload();
		void ReturnBullet();

		//총 각도 관련
		void angleFind();
		void GunLookCursor();

	public://반동 효과
		Vector3 rebound;
		void HandDownAnimate(Vector3 handPos);//GenericAnimator
		void HandUpAnimate(Vector3 handPos);//GenericAnimator
		void HandDownPos(float cur);
		void HandUpPos(float cur);

		bool reboundTrue;

	private:
		std::shared_ptr<AudioClip> audioClip[2];
		AudioSource* boss_audio[2];
		GameObject* audioObj[2];


	private:
		Gun* gunObj;
		GameObject* gunBox;
		PistolState ps;
		PlayerHand* playerHand;
		Transform* gunTransform;
		GenericAnimator genericAnimator;
		Animator* gunani;

		BulletPool* bulletpool;
		Bullet* bulletOBJ;
		std::vector<Bullet*> bullets;
	private:
		float angle;
		float shotTimer = 0.0f;


	};
}


