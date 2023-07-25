#pragma once
#include "chScript.h"
namespace ch
{
	class BlackMapScr : public Script
	{
	public:
		BlackMapScr();
		virtual ~BlackMapScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;



	};
}