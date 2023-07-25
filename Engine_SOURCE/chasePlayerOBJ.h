#pragma once
#include "chGameObject.h"
#include "chCollider2D.h"
namespace ch
{
	class chasePlayerOBJ : public GameObject
	{
	public:
		chasePlayerOBJ();
		virtual ~chasePlayerOBJ();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		
	public:
		void SetOwnerTransform(Transform* _a) { OwnerTr = _a; }


	private:
		Transform* OwnerTr;
		Collider2D* mCollider;
	public:
		
		Transform* thisTr;
	};

}

