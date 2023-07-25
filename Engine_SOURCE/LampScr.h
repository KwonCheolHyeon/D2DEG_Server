#pragma once
#include "chScript.h"
#include "chLight.h"
namespace ch 
{
	class LampScr : public Script
	{
	public:
		LampScr();
		virtual ~LampScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		Light* lightComp;
		float time;
		float radius;

	};
}


