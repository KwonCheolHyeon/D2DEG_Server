#include "EventObj.h"
#include "EventScr.h"

namespace ch 
{
	EventObj::EventObj()
	{
	}

	EventObj::~EventObj()
	{
	}

	void EventObj::Initalize()
	{
		this->AddComponent<EventScr>();
		GameObject::Initalize();
	}

	void EventObj::Update()
	{
		GameObject::Update();
	}

	void EventObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void EventObj::Render()
	{
		GameObject::Render();
	}

}