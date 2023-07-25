#pragma once
#include "chScript.h"


namespace ch
{
	class BulletScr : public Script
	{
	public:
		enum class eBulletState
		{
			live,
			wait,
			Dead,
			End
		};

		BulletScr();
		virtual ~BulletScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		void shootingBullet(float Gunangle, Vector3 pos);
		void MoveBullet();
		void Reset();
		bool isReset();
		
	public://총알 상태
		std::bitset<static_cast<UINT>(eBulletState::End)> mState;
	private:
		Transform* mTr;
		

	private: //수치
		float speed;
		float bulletDirectionX;
		float bulletDirectionY;
		float angles;
		Vector3 GunPos;

	private:
		float bulletTime;

	
		
	};

}