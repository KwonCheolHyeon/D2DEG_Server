
#pragma once
#include "chGameObject.h"
namespace ch
{

	class BoosDoorObj : public GameObject
	{
	public:
		BoosDoorObj();
		virtual ~BoosDoorObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}


