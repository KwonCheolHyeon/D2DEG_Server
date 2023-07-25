#include "MonsterBulletScr.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chLight.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chTime.h"
#include "chLayer.h"
namespace ch 
{
	MonsterBulletScr::MonsterBulletScr()
	{
	}

	MonsterBulletScr::~MonsterBulletScr()
	{
	}

	void MonsterBulletScr::Initalize()
	{
		/*Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterBullet);*/

	 
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(0.3f,0.3f,1.f));

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

		reflectOn = false;

		this->GetOwner()->SetName(L"MonsterBullet");
	}

	void MonsterBulletScr::Update()
	{
		
		bulletTime += Time::DeltaTime();
		MoveBullet();
		if (bulletTime >= 1.5f)
		{
			Reset();
		}
	}

	void MonsterBulletScr::FixedUpdate()
	{
	}

	void MonsterBulletScr::Render()
	{
	}

	void MonsterBulletScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetLayerType() == eLayerType::Player || oppo->GetOwner()->GetName() == L"ConvictBlankcolider")
		{
			Reset();
			
		}
		
		if (oppo->GetOwner()->GetName() == L"MapWall" || oppo->GetOwner()->GetName() == L"DoorSide" || oppo->GetOwner()->GetName() == L"DoorFront" || oppo->GetOwner()->GetName() == L"table1" || oppo->GetOwner()->GetName() == L"cBoss")
		{
			Reset();
		}

		if (oppo->GetOwner()->GetName() == L"Cube")
		{
			
			twoHit += 1;
			if (twoHit == 2)
			{
				Reset();
			}
			
			
		}
		if (oppo->GetOwner()->GetName() == L"BulletKin")
		{
			twoHit += 1;
			if (twoHit == 2)
			{
				Reset();
			}
		}

		if (oppo->GetOwner()->GetName() == L"FightSabreCollider" )
		{
			reflectOn = true;
		}
		
	}

	void MonsterBulletScr::OnCollision(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnCollisionExit(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTrigger(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTriggerExit(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::shootingBullet(float Gunangle, Vector3 pos)
	{
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(pos);
	}

	void MonsterBulletScr::MoveBullet()
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
	void MonsterBulletScr::Reset()
	{

		GetOwner()->Death();
		
	}
	void MonsterBulletScr::Reflect()
	{



	}
}