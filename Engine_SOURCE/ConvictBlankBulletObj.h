#pragma once
#include "chGameObject.h"
namespace ch
{
	class ConvictBlankBulletObj : public GameObject
	{
	public:
		ConvictBlankBulletObj();
		virtual ~ConvictBlankBulletObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	};

}