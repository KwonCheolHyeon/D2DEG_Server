#pragma once
#include "chGameObject.h"
namespace ch 
{

	class BlankBulletObj : public GameObject
	{
	public:
		BlankBulletObj();
		virtual ~BlankBulletObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};

}


