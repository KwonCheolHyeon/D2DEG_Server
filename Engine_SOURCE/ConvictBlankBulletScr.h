#pragma once
#include "chScript.h"
#include "chGameObject.h"
namespace ch
{
	class ConvictBlankBulletScr : public Script
	{
	public:
		ConvictBlankBulletScr();
		virtual ~ConvictBlankBulletScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetConvit(GameObject* _a) { gameObject = _a; }

		void onBlankBulletEffect() { on = true; }
		void BlankBulletEffect();
	private:
		GameObject* gameObject;

		Collider2D* col;
		Transform* tr;
		
	private:
		bool on;
		float time;
		float reloadTime;
		bool reloadOn;
	};

}