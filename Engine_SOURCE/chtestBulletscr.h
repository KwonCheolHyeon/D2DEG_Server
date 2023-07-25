#pragma once
#include "chScript.h"
namespace ch 
{

	class testBulletscr : public Script
	{
	public:
	
		testBulletscr();
		virtual ~testBulletscr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	
	};

}

