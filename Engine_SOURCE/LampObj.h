#pragma once
#include "chGameObject.h"
namespace ch 
{
	class LampObj : public GameObject
	{
	public:
		LampObj();
		virtual ~LampObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}


