#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "chCameraScript.h"
namespace ch
{

	enum PlayerDirections//얘는 하나만 켜짐
	{
		North=1,//위 1
		South=2,//아래 2

		East=3,//동 3
		West=4,//서 4

		NE=5,//북동쪽 5
		NW=6//북서쪽 6
	};

	class CharacterBase : public GameObject
	{
	public:
		CharacterBase();
		virtual ~CharacterBase();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		PlayerDirections GetPD() { return pD; }
		void SetPD(PlayerDirections _a) { pD = _a; };

		void reset();

	public:// 01   : 마우스플레이어 사이 각도 관련
		void MouseAndPlayerAngle();
		void playerLookingMouse();
		

	public:
		PlayerDirections pD;
		Collider2D* pCollider;
	private://01
		float c2mAngle;

	private://보류
		Animator* pAnima;
		GameObject* playerOBJ;
		
	};
}

