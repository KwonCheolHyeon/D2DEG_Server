#pragma once
#include "chScript.h"
#include "chAnimator.h"
namespace ch
{
	class EventScr : public Script
	{
	public:
		EventScr();
		virtual ~EventScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* oppo);
		virtual void OnCollision(Collider2D* oppo);
		virtual void OnCollisionExit(Collider2D* oppo);

		bool GetEventState() { return eventOn; }


	private:
		bool eventOn;
	};
}


