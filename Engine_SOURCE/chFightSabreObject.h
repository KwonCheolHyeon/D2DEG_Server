#pragma once
#include "chGameObject.h"

namespace ch
{
	class FightSabreObject :public GameObject
	{
	public:
		FightSabreObject();
		virtual ~FightSabreObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	
	};
}
