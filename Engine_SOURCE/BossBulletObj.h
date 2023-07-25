#pragma once
#include "chGameObject.h"
namespace ch 
{
	class BossBulletObj : public GameObject
	{
	public:
		BossBulletObj();
		virtual ~BossBulletObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}


