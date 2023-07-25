#pragma once
#include "chGameObject.h"
#include "chAnimator.h"

namespace ch
{
	class mainPlayer : public GameObject
	{
	public:
		mainPlayer();
		virtual ~mainPlayer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		
		
	private:
		GameObject* pHand;
		Transform* pTr;
		Collider2D* pCollider;
		Animator* pAnimator;
		
	};
}

