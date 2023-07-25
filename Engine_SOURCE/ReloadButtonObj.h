#pragma once
#include "chGameObject.h"
namespace ch
{
	class ReloadButtonObj : public GameObject
	{
	public:
		ReloadButtonObj();
		virtual ~ReloadButtonObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}




