#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
namespace ch 
{
	class TableObject : public GameObject
	{
	public:
		TableObject();
		virtual ~TableObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* tAnimator;
	};
}




