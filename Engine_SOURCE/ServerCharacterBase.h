#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "chCameraScript.h"

namespace ch 
{
	enum eServerPlayerDirections//��� �ϳ��� ����
	{
		eNorth = 1,//�� 1
		eSouth = 2,//�Ʒ� 2

		eEast = 3,//�� 3
		eWest = 4,//�� 4

		eNE = 5,//�ϵ��� 5
		eNW = 6//�ϼ��� 6
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

	public:// 01   : ���콺�÷��̾� ���� ���� ����
		void MouseAndPlayerAngle();
		void playerLookingMouse();


	public:
		eServerPlayerDirections pD;
		Collider2D* pCollider;
	private://01
		float c2mAngle;

	private://����
		Animator* pAnima;
		GameObject* playerOBJ;

	};
}


