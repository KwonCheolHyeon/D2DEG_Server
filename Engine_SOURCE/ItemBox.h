#pragma once
#include "chGameObject.h"
namespace ch 
{
	class ItemBox : public GameObject
	{
	public:
		ItemBox();
		virtual ~ItemBox();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}

