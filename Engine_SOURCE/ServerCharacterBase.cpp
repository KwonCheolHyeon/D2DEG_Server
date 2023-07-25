#include "ServerCharacterBase.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
#include "chInput.h"

#include "chScene.h"
#include "ServerScene.h"

namespace ch 
{
	ServerCharacterBase::ServerCharacterBase()
	{
		playerOBJ = dynamic_cast<GameObject*>(this);

		SpriteRenderer* sprite = playerOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Transform* pTr = playerOBJ->GetComponent<Transform>();
		pTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));
		//pTr->SetPosition(Vector3(-18.1f, 14.5f, -9.f));

		pCollider = playerOBJ->AddComponent<Collider2D>(); //오류 걸림
		pCollider->SetName(L"playerCollider");
		pCollider->SetType(eColliderType::Rect);
		pCollider->SetSize(Vector2(.1f, .1f));

		pAnima = playerOBJ->AddComponent<Animator>();
		playerOBJ->AddComponent<Rigidbody>();

		reset();
	}

	ServerCharacterBase::~ServerCharacterBase()
	{
	}

	void ServerCharacterBase::Initalize()
	{
		GameObject::Initalize();
	}

	void ServerCharacterBase::Update()
	{

		playerLookingMouse();
		GameObject::Update();
	}

	void ServerCharacterBase::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}


	void ServerCharacterBase::Render()
	{
		GameObject::Render();
	}

	void ServerCharacterBase::reset()
	{
		pD = eServerPlayerDirections::eSouth; //정면
	}

	void ServerCharacterBase::MouseAndPlayerAngle()
	{
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 mousePositon = (mousePos / 100.f);

		Vector3 CharterPosition = GetCenterPos();
		mousePositon += CharterPosition;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		c2mAngle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}

	void ServerCharacterBase::playerLookingMouse()
	{
		MouseAndPlayerAngle();
		if (c2mAngle >= 30 && c2mAngle < 60) //right back
		{
			pD = eServerPlayerDirections::eNE;
		}
		else if (c2mAngle >= 60 && c2mAngle < 120) //back
		{
			pD = eServerPlayerDirections::eNorth;
		}
		else if (c2mAngle >= 120 && c2mAngle < 150) //left Back
		{
			pD = eServerPlayerDirections::eNW;
		}
		else if (c2mAngle >= 150 && c2mAngle < 225) //left
		{
			pD = eServerPlayerDirections::eWest;
		}
		else if (c2mAngle >= 225 && c2mAngle < 315)//front
		{
			pD = eServerPlayerDirections::eSouth;
		}
		else //right
		{
			pD = eServerPlayerDirections::eEast;
		}
	}

}