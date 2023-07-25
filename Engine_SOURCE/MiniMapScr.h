#pragma once
#include "chScript.h"

namespace ch
{
	class MiniMapScr : public Script
	{
	public:
		MiniMapScr();
		virtual ~MiniMapScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		
	};
}


