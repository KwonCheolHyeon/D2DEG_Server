#pragma once
#include "chGameObject.h"

namespace ch
{

	class HeartObj :public GameObject
	{
	public:
		HeartObj();
		virtual ~HeartObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}


