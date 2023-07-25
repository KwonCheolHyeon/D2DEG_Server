#pragma once
#include "chGameObject.h"

namespace ch 
{
	class FightSabreBullet :public GameObject
	{
	public:
		FightSabreBullet();
		virtual ~FightSabreBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();



	};
}


