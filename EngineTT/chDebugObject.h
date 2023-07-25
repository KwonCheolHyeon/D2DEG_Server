#pragma once
#include "chGameObject.h"


namespace ch
{
	class DebugObject : public ch::GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;
	
	private:
	};
}
