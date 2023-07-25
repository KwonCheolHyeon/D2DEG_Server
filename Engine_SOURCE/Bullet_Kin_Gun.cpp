#include "Bullet_Kin_Gun.h"
#include "Bullet_Kin_Gun_Scr.h"
#include "Bullet_Kin.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chasePlayerSCR.h"
namespace ch 
{

	Bullet_Kin_Gun::Bullet_Kin_Gun()
	{
		
		
	}

	Bullet_Kin_Gun::~Bullet_Kin_Gun()
	{
	}

	void Bullet_Kin_Gun::Initalize()
	{
		this->AddComponent<Bullet_Kin_Gun_Scr>();


		SpriteRenderer* sprite = this->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		monsterGunAni = this->AddComponent<Animator>();
		{//¿œπ› 
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WGun_Idle", L"enterthe/enemy/bullet_Kin/gun_Idle.png");
			monsterGunAni->Create(L"WGun_Idle", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 16.0f), Vector2::Zero, 1, 0.1f);
		}
		{//√— ΩÚ∂ß
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WGun_Shot", L"enterthe/enemy/bullet_Kin/gun_shot.png");
			monsterGunAni->Create(L"WGun_Shot", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 16.0f), Vector2::Zero, 5, 0.1f);
		}

		monsterGunAni->Play(L"WGun_Shot");
		this->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		this->GetComponent<Transform>()->SetParent(OwnerMonster->GetComponent<Transform>());
		this->GetComponent<Transform>()->SetScale(Vector3(1.f, .9f, 1.f));
		this->GetComponent<Transform>()->SetOffset(Vector3(0.06f, 0.f, 0.1f));

		monsterChaseCollider = OwnerMonster->GetMonsterChaseCollider();
		GameObject::Initalize();
	}

	void Bullet_Kin_Gun::Update()
	{
		
		GunPos();

		GameObject::Update();
	}

	void Bullet_Kin_Gun::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Bullet_Kin_Gun::Render()
	{
		GameObject::Render();
	}

	void Bullet_Kin_Gun::GunPos()
	{
		Transform* tr = this->GetComponent<Transform>();
		Transform* OMtr = OwnerMonster->GetComponent<Transform>();

		GunRotation();

		
		if (monsterChaseCollider->GetComponent<chasePlayerSCR>()->isFindPlayer() == true) 
		{
			
			if (OwnerMonster->isLeft() == true)
			{
				tr->SetRotation(Vector3(180.0f, 180.0f, -P2Gangle));
			}
			else
			{
				tr->SetRotation(Vector3(0.0f, 0.0f, P2Gangle));
			}

		}
		else 
		{
			tr->SetRotation(Vector3::Zero);
		}

	}

	void Bullet_Kin_Gun::GunRotation()
	{


		Vector3 playerPos = OwnerMonster->GetPlayer()->GetComponent<Transform>()->GetCenterPos();

		Vector3 GunPos = OwnerMonster->GetComponent<Transform>()->GetCenterPos();
		

		float angle = atan2(playerPos.y - GunPos.y, playerPos.x - GunPos.x);
		float rotationZ = fmodf((angle * (180.0f / XM_PI) + 360.0f), 360.0f); // Calculate the rotation angle in degrees

		P2Gangle = rotationZ;

	}



}