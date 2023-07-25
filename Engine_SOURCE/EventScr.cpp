#include "EventScr.h"
#include "chGameObject.h"
namespace ch
{
	EventScr::EventScr()
	{
	}

	EventScr::~EventScr()
	{
	}

	void EventScr::Initalize()
	{
		eventOn = false;
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

	}

	void EventScr::Update()
	{
	}

	void EventScr::FixedUpdate()
	{
	}

	void EventScr::Render()
	{
	}

	void EventScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			eventOn = true;
		}
	}

	void EventScr::OnCollision(Collider2D* oppo)
	{
	}

	void EventScr::OnCollisionExit(Collider2D* oppo)
	{
	}

}