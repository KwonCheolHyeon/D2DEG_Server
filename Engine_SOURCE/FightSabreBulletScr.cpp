#include "FightSabreBulletScr.h"
#include "chGameObject.h"
#include "chLight.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chTime.h"
namespace ch 
{
	FightSabreBulletScr::FightSabreBulletScr()
		:  Script()
	{
	}

	FightSabreBulletScr::~FightSabreBulletScr()
	{
	}

	void FightSabreBulletScr::Initalize()
	{
		GetOwner()->SetLayerType(eLayerType::Weapone);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(0.5f, 0.3f, 1.f));
		
		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(1.f, 1.f));

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"W_BulletMaterial2");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);
		

		bulletTime = 0.f;
	}

	void FightSabreBulletScr::Update()
	{
		bulletTime += Time::DeltaTime();
		MoveBullet();
		if (bulletTime >= 1.5f)
		{
			Reset();
		}
	}

	void FightSabreBulletScr::FixedUpdate()
	{
	}

	void FightSabreBulletScr::Render()
	{
	}

	void FightSabreBulletScr::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Wall  || collider->GetOwner()->GetLayerType() == eLayerType::Monster || collider->GetOwner()->GetLayerType() == eLayerType::Object)
		{
			Reset();
		}
		if (collider->GetOwner()->GetName() == L"Bullat" || collider->GetOwner()->GetName() == L"cBoss" || collider->GetOwner()->GetName() == L"Cube" || collider->GetOwner()->GetName() == L"BulletKin" || collider->GetOwner()->GetName() == L"MapWall")
		{
			Reset();
		}
	}

	void FightSabreBulletScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void FightSabreBulletScr::OnCollisionExit(Collider2D* collider)
	{
	}

	void FightSabreBulletScr::shootingBullet(float Gunangle, Vector3 pos)
	{
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetRotation(Vector3(0.f,180.f, Gunangle));
		mTr->SetPosition(pos);
	}

	void FightSabreBulletScr::MoveBullet()
	{
		float speed = 10.0f; // Bullet's movement speed
		float bulletDistance = speed * Time::DeltaTime();
		Vector3 bulletPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		// Update bullet position based on direction and distance
		bulletPos += Vector3(bulletDirectionX, bulletDirectionY, 0.0f) * bulletDistance;

		GetOwner()->GetComponent<Transform>()->SetPosition(bulletPos);
	}

	void FightSabreBulletScr::Reset()
	{
	

		GetOwner()->Death();
	}

}