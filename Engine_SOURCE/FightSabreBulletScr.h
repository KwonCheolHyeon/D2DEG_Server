#pragma once
#include "chScript.h"

namespace ch 
{
	class FightSabreBulletScr :public Script
	{
	public:
		FightSabreBulletScr();
		virtual ~FightSabreBulletScr();

		virtual void Initalize() ;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void shootingBullet(float Gunangle, Vector3 pos); //{ angles = Gunangle, GunPos = pos , mState[(UINT)eBulletState::wait] = false, mState[(UINT)eBulletState::live] = true, mState[(UINT)eBulletState::Dead] = false;}
		void MoveBullet();
		void Reset();
	private:
		Transform* mTr;
		
	private:
		float speed;
		float bulletDirectionX;
		float bulletDirectionY;
		float angles;
		Vector3 GunPos;

		float bulletTime;
	};


}

