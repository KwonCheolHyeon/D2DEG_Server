#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "MonsterBase.h"
namespace ch 
{

	enum dir
	{
		Side,
		Front
	};
	enum OpenClose
	{
		Open,
		Close,
		Defa
	};
	class DoorObj : public GameObject
	{
	public:
		DoorObj();
		virtual ~DoorObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void isOpenTrue() { isOpen = true; }
		void isOpenFalse() { isOpen = false; }
		bool GetisOpen() { return isOpen; }

		void isMainDoorTrue() { mainDoor = true; }
		bool isMainDoor() { return mainDoor; }

		void SetDoors(DoorObj* bullet) { doorObjs.push_back(bullet); }
		DoorObj* GetDoors(int a) { return doorObjs[a]; }

		void SetMonsterBases(MonsterBase* bullet) { monsterBases.push_back(bullet); }
		MonsterBase* GetMonsterBases(int a) { return monsterBases[a]; }

		bool GetdeathCol() { return deathCol; }
		void TrueDeathCol() { deathCol = true; }

	

	public:
		static bool isOpen;
		bool mainDoor;
		bool endRoom;
		int endRoomKey;
		bool deathCol;
	private:
		Animator* tAnimator;
		dir dr;
		OpenClose oc;
		std::vector<DoorObj*> doorObjs;
		std::vector<MonsterBase*> monsterBases;
		
		

	private:
		int doorOpenCount;
		bool one;
		bool two;
		bool three;
		bool four;
		bool five;
		bool six;
	};


}

