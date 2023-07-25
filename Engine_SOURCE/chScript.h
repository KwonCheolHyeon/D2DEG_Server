#pragma once
#include "chComponent.h"
#include "chCollider2D.h"

namespace ch
{
	struct GunState 
	{
		bool active;
		int GunNum;//num == 1 : ÇÇ½ºÅç,  num == 2 : 2¹øÃÑ 
	};

	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

	private:
		//std::vector<Script*> mScripts;
		//state jump;
		//state Attack;
	};
}
