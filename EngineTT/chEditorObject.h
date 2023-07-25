#pragma once
#include "..\Engine_SOURCE\chGameObject.h"


namespace ch
{
	class EditorObject : public ch::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		
	};
}