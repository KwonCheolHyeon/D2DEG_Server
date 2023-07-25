#pragma once
#include "chGameObject.h"

namespace ch 
{
	class MonsterBulletObj : public GameObject
	{
	public:
		MonsterBulletObj();
		virtual ~MonsterBulletObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};

}
