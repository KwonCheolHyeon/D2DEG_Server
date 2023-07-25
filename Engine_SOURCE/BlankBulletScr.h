#pragma once
#include "chScript.h"

namespace ch
{
	class BlankBulletScr : public Script
	{
	public:
		BlankBulletScr();
		virtual ~BlankBulletScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


	};
}