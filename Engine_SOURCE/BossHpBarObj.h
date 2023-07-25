#pragma once
#include "chGameObject.h"

namespace ch
{

	class BossHpBarObj :public GameObject
	{
	public:
		BossHpBarObj();
		virtual ~BossHpBarObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}


