#pragma once
#include "chScript.h"
#include "chSpriteRenderer.h"
namespace ch
{
	class Heart_Scr : public Script
	{
	public:
		Heart_Scr();
		virtual ~Heart_Scr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void setCountHeart(int a) { countHeart = a; }
		
		
	private:
		int countHeart;
		int prevHeartCount;
		SpriteRenderer* sprite;
	};
}

