#pragma once
#include "chGameObject.h"

namespace ch
{
	class BossSceneObj :public GameObject
	{
	public:
		BossSceneObj();
		virtual ~BossSceneObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}