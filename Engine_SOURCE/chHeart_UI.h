#pragma once
#include "chGameObject.h"

namespace ch
{
	class Heart_UI : public GameObject
	{
	public:
		Heart_UI();
		virtual ~Heart_UI();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}

