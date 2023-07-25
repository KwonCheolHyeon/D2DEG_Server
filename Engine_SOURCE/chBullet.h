#pragma once
#include "chGameObject.h"

namespace ch 
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		
		virtual ~Bullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		
	};

}

