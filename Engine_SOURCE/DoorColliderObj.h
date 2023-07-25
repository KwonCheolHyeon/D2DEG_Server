#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "DoorObj.h"
#include "MonsterBase.h"
namespace ch
{
	class DoorColliderObj : public GameObject
	{
	public:
		DoorColliderObj();
		virtual ~DoorColliderObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetDoor(DoorObj* a) { door = a; }
		DoorObj* GetDoor() { return door; }

	public:
		bool isMain;
		int isMainKey;
	private:
		DoorObj* door;
		Transform* tr;
		OpenClose oc;
		MonsterBase* mb;
	};


}
