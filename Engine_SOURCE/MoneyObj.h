#pragma once
#include "chGameObject.h"
namespace ch 
{
	class MoneyObj :public GameObject
	{
	public:
		MoneyObj();
		virtual ~MoneyObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}


