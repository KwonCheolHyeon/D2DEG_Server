#pragma once
#include "chScene.h"
#include "chAudioClip.h"
#include "chAudioSource.h"

namespace ch
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	public:
		void SetPlayerData(GameObject* _player) { player = _player; }
		GameObject* GetPlayerData() { return player; }

	private:
		GameObject* chCameraOBJ;
		GameObject* player;
		class MonsterBase* kinMonster;
		class chasePlayerOBJ* chaseCollier;


	};
}

