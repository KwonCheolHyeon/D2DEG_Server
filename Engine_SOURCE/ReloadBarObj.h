#pragma once
#include "chGameObject.h"
namespace ch
{
	class ReloadBarObj : public GameObject
	{
	public:
		ReloadBarObj();
		virtual ~ReloadBarObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}




