#pragma once
#include "chGameObject.h"

namespace ch
{
	class MiniMapPlayerObj :public GameObject
	{
	public:
		MiniMapPlayerObj();
		virtual ~MiniMapPlayerObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}