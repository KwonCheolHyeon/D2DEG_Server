#pragma once
#include "chGameObject.h"

namespace ch
{
	class EventObj :public GameObject
	{
	public:
		EventObj();
		virtual ~EventObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}