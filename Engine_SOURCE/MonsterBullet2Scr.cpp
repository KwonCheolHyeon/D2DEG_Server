#include "MonsterBullet2Scr.h"
#include "chGameObject.h"
#include "chLight.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chTime.h"

namespace ch
{
	MonsterBullet2Scr::MonsterBullet2Scr()
	{

	}
	MonsterBullet2Scr::~MonsterBullet2Scr()
	{

	}
	void MonsterBullet2Scr::Initalize()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(0.3f, 0.3f, 1.f));

		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(1.f, 1.f));

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"Enemy_Bullet_material");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		this->GetOwner()->SetName(L"MonsterBullet");
		reflectOn = false;
		moveOn = false;
		twoHit = 0;
	}
	void MonsterBullet2Scr::Update()
	{
		if (moveOn == true) {
			bulletTime += Time::DeltaTime();
			MoveBullet();
			if (bulletTime >= 1.5f)
			{
				Reset();
			}
		}
	}
	void MonsterBullet2Scr::FixedUpdate()
	{

	}
	void MonsterBullet2Scr::Render()
	{

	}
	void MonsterBullet2Scr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetLayerType() == eLayerType::Player || oppo->GetOwner()->GetName() == L"ConvictBlankcolider")
		{
			Reset();
		}
		if (oppo->GetOwner()->GetName() == L"MapWall" || oppo->GetOwner()->GetName() == L"DoorSide" || oppo->GetOwner()->GetName() == L"DoorFront" || oppo->GetOwner()->GetName() == L"table1" )
		{
			Reset();
		}
		if (oppo->GetOwner()->GetName() == L"Cube" || oppo->GetOwner()->GetName() == L"BulletKin" || oppo->GetOwner()->GetName() == L"cBoss" || oppo->GetOwner()->GetName() == L"Bullat")
		{
			if (GetOwner()->GetName() == L"reflectBullet") 
			{
				Reset();
			}
		}
		if (oppo->GetOwner()->GetName() == L"FightSabreCollider")
		{
			reflectOn = true;
		}

	}
	void MonsterBullet2Scr::OnCollision(Collider2D* oppo)
	{

	}
	void MonsterBullet2Scr::OnCollisionExit(Collider2D* oppo)
	{

	}
	void MonsterBullet2Scr::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void MonsterBullet2Scr::OnTrigger(Collider2D* oppo)
	{
	}
	void MonsterBullet2Scr::OnTriggerExit(Collider2D* oppo)
	{
	}
	void MonsterBullet2Scr::shootingBullet(float Gunangle, Vector3 pos)
	{
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(pos);
	}
	void MonsterBullet2Scr::MoveBullet()
	{
		float speed = 5.0f; // Bullet's movement speed
		float bulletDistance = speed * Time::DeltaTime();
		Vector3 bulletPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		// Update bullet position based on direction and distance
		bulletPos += Vector3(bulletDirectionX, bulletDirectionY, 0.0f) * bulletDistance;

		if (reflectOn == true)
		{
			GetOwner()->SetLayerType(eLayerType::Weapone);
			// Reverse the direction of the bullet
			bulletDirectionX = -bulletDirectionX;
			bulletDirectionY = -bulletDirectionY;


			GetOwner()->SetName(L"reflectBullet");
			bulletTime = 0;
			// Reset the reflection state to prevent continuous reflection
			reflectOn = false;
		}

		GetOwner()->GetComponent<Transform>()->SetPosition(bulletPos);
	}
	void MonsterBullet2Scr::Reset()
	{
		GetOwner()->Pause();
	}
}
