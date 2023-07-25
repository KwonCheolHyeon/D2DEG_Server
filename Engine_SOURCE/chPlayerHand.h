#pragma once
#include "chGameObject.h"

namespace ch 
{
	class PlayerHand : public GameObject
	{
	public:
		PlayerHand();
		virtual ~PlayerHand();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPlayer(GameObject* _player) { player = _player; }
		GameObject* GetPlayer() { return player; }
		
		void HandLookCursor();
		void HandPosition();
		bool IsHandLeft() { return chHandLeft; }
	private:
		Transform* phandTr;
		GameObject* player;

	private:
		float handDistance;
		bool chHandLeft;
		bool isPistol;
	private:
		float reloadtime;
		bool reloadOn;
	};
}


