#pragma once
#include "chGameObject.h"
#include "chasePlayerOBJ.h"

namespace ch 
{
	class DoorObj;
	enum monsterState 
	{
		Spawn,
		mIdle,
		chase,
		Hit,
		Move,
		Attack,
		SkyBomb,
		BossFlyAni,
		BossGoMid,
		Death
	};
	enum monsterDir 
	{
		mNorth = 1,//위 1
		mSouth = 2,//아래 2

		mEast = 3,//동 3
		mWest = 4,//서 4

		mNE = 5,//북동쪽 5
		mNW = 6,//북서쪽 6

		mSE = 7,//남동쪽 7
		mSW = 8,//남서쪽 8
		prev
	};
	class MonsterBase : public GameObject
	{
	public:
		MonsterBase();
		virtual ~MonsterBase();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetMonsterChaseCollider(chasePlayerOBJ* _a) { monsterChaseCollider = _a; }
		chasePlayerOBJ* GetMonsterChaseCollider() { return monsterChaseCollider; }

		void SetPlayer(GameObject* _a) { player = _a; }
		GameObject* GetPlayer() { return player; }

	private:
		chasePlayerOBJ* monsterChaseCollider; // Declare the member variable
		GameObject* player;
		
		
	};
}

