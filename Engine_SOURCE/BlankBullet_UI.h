#pragma once
#include "chScript.h"
namespace ch
{
	class BlankBullet_UI : public Script
	{
	public:
		BlankBullet_UI();
		virtual ~BlankBullet_UI();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


	public:
		void onBlankBullet() { on = true; }
		void offBlankBullet() { on = false; }

	private:
		class SpriteRenderer* sprite;
		bool on;
	};

}


