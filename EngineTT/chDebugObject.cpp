#include "chDebugObject.h"


namespace ch
{
	DebugObject::DebugObject()
	{

	}
	DebugObject::~DebugObject()
	{

	}

	void DebugObject::FixedUpdate()
	{
		for (ch::Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}
	}
}