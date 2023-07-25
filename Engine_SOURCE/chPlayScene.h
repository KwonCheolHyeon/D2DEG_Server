#pragma once
#include "chScene.h"
#include "chBulletPool.h"
#include "chHeart_UI.h"
#include "BlankBulletObj.h"
#include "DoorObj.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
#include "EventObj.h"
namespace ch
{
	
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	public://생성할 함수
		void generateBullet(int size);
		void generateMap();
		void generateObject();

	private:
		GameObject* chCameraOBJ;
		GameObject* chUiCursor;
		CameraScript* cameraScr;
		Transform* chUiCursorTR;
		GameObject* player;
		GameObject* player2;
		MonsterBase* bossObj;


		BulletPool* pool;
		
		Transform* mapTr;

		std::vector<Heart_UI*> HeartControl;
		std::vector<BlankBulletObj*> BlankBulletControl;
		//저장할 공간
		std::vector<Bullet*> containBullets;
		
		DoorObj* mainDoor1;
		DoorObj* mainDoor2;
		DoorObj* mainDoor3;
		DoorObj* mainDoor4;
		DoorObj* mainDoor5;
		DoorObj* mainDoor6;
		DoorObj* mainDoor7;
		DoorObj* mainDoor8;
	private:
		std::shared_ptr<AudioClip> audioClip[3];
		AudioSource* boss_audio[3];
		GameObject* audioObj[3];

		EventObj* eventobj;
		bool bossdeath;
		bool evnetOnce;
	
		
	};
}

