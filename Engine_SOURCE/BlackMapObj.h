
#pragma once
#include "chGameObject.h"
namespace ch
{

	class BlackMapObj : public GameObject
	{
	public:
		BlackMapObj();
		virtual ~BlackMapObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}


