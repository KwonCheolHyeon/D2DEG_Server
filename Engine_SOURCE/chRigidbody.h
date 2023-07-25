#pragma once
#include "chComponent.h"


using namespace ch::math;

namespace ch
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void AddForce(Vector3 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

	public:
		static bool dodgeForceReset;//구르기때 힘 초기화 함수
	
	private:
		// 힘과 마찰력을 이용한 이동
		float mMass; //무게
		float mFriction; //마찰
		//float mDamping;//감쇄 속도

		//float mMoveFriction;
		Vector3 mForce; //크기, 방향
		Vector3 mVelocity; //속도(속력 + 방향)
		Vector3 mAccelation; //가속도

		// 중력 이용한 점프
		Vector3 mGravity;
		bool mbGround;
		float mLimitVelocity;

	private:
		float mForceResetTimer;

	private:
		void objectMove();
	};

}

