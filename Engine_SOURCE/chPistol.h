#pragma once
#include "chGun.h"
namespace ch 
{
	class Pistol : public Gun
	{
	public:
		Pistol();
		virtual ~Pistol();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	
				
	};


}

