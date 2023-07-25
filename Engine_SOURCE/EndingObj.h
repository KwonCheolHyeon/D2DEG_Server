#pragma once
#include "chGameObject.h"
namespace ch
{
	class EndingObj : public GameObject
	{
	public:
		EndingObj();
		virtual ~EndingObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}




