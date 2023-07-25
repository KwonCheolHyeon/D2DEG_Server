#pragma once
#include "chGameObject.h"

namespace ch
{
	class MapObject : public GameObject
	{
	public:
		MapObject();
		virtual ~MapObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		GameObject* map;


	};

}

