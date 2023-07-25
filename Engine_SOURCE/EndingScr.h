#pragma once
#include "chScript.h"
#include "chLight.h"
namespace ch
{
	class EndingScr : public Script
	{
	public:
		EndingScr();
		virtual ~EndingScr();

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


