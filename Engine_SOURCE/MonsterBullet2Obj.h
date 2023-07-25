#pragma once
#include "chGameObject.h"
namespace ch 
{
	class MonsterBullet2Obj : public GameObject
	{
	public:
		MonsterBullet2Obj();
		virtual ~MonsterBullet2Obj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}


