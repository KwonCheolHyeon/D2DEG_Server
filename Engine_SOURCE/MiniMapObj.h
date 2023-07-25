#pragma once
#include "chGameObject.h"

namespace ch
{
	class MiniMapObj :public GameObject 
	{
	public:
		MiniMapObj();
		virtual ~MiniMapObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}