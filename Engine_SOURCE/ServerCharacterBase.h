#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "chCameraScript.h"

namespace ch 
{
	enum eServerPlayerDirections//얘는 하나만 켜짐
	{
		eNorth = 1,//위 1
		eSouth = 2,//아래 2

		eEast = 3,//동 3
		eWest = 4,//서 4

		eNE = 5,//북동쪽 5
		eNW = 6//북서쪽 6
	};

	class ServerCharacterBase : public GameObject
	{
	public:
		ServerCharacterBase();
		virtual ~ServerCharacterBase();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		eServerPlayerDirections GetPD() { return pD; }
		void SetPD(eServerPlayerDirections _a) { pD = _a; };

		void reset();

	public:// 01   : 마우스플레이어 사이 각도 관련
		void MouseAndPlayerAngle();
		void playerLookingMouse();


	public:
		eServerPlayerDirections pD;
		Collider2D* pCollider;
	private://01
		float c2mAngle;

	private://보류
		Animator* pAnima;
		GameObject* playerOBJ;

	};
}


