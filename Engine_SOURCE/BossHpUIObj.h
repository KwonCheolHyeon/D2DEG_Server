#pragma once
#include "chGameObject.h"

namespace ch
{
	class BossHpUIObj :public GameObject
	{
	public:
		BossHpUIObj();
		virtual ~BossHpUIObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}