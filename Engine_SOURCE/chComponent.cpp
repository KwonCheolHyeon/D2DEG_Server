#include "chComponent.h"


namespace ch
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
}
