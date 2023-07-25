#include "BullatScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chLight.h"
#include "chCollider2D.h"
#include "chasePlayerSCR.h"
#include "chObject.h"
namespace ch
{
	BullatScr::BullatScr()
	{
	}
	BullatScr::~BullatScr()
	{
	}
	void BullatScr::Initalize()
	{
		thisMonster = dynamic_cast<MonsterBase*>(GetOwner());

		anima = GetOwner()->AddComponent<Animator>();
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bullat_Fly", L"enterthe/enemy/BulletBat/Bullat/Fly.png");
			anima->Create(L"M_Bullat_Fly", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 20.0f), Vector2::Zero, 6, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bullat_Attack", L"enterthe/enemy/BulletBat/Bullat/Attack.png");
			anima->Create(L"M_Bullat_Attack", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 20.0f), Vector2::Zero, 6, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bullat_AttackOk", L"enterthe/enemy/BulletBat/Bullat/AttackOk.png");
			anima->Create(L"M_Bullat_AttackOk", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 14.0f), Vector2::Zero, 8, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bullat_death", L"enterthe/enemy/BulletBat/Bullat/death.png");
			anima->Create(L"M_Bullat_death", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 38.0f), Vector2::Zero, 4, 0.2f);
		}

	
		mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BulletKinMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Collider2D* mCollider = GetOwner()->AddComponent<Collider2D>();
		mCollider->SetName(L"BulletAtCollider");
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));


		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI);

		audioClip[0] = Resources::Load<AudioClip>(L"beforeAttack", L"music\\enemy\\bullat\\beforeAttack.wav");
		audioClip[1] = Resources::Load<AudioClip>(L"death", L"music\\enemy\\bullat\\death.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);


		anima->Play(L"M_Bullat_Fly");
		DeathTIME = 0.f;
		ms = monsterState::Move;
		setAttackTime = 0.f;
		goToDeathTime = 0.f;
		reflectOn = false;
	}
	void BullatScr::Update()
	{
		switch (ms)
		{
		case monsterState::Spawn:
			break;
		case monsterState::mIdle:
			break;
		case monsterState::chase:
			AttackOk();
			break;
		case monsterState::Move:
			Fly();
			break;
		case monsterState::Attack:
			Attack();
			break;
		case monsterState::Death:
			Death();
			break;
		default:
			break;
		}
	}
	void BullatScr::FixedUpdate()
	{ 
	}
	void BullatScr::Render()
	{
	}
	void BullatScr::OnCollisionEnter(Collider2D* oppo)
	{

		
		if (oppo->GetName() == L"PlayerCollider" || oppo->GetOwner()->GetName() == L"reflectBullet" )
		{
			ms = monsterState::Death;;

		}
		if (oppo->GetOwner()->GetName() == L"Player" || oppo->GetOwner()->GetName() == L"MapWall" || oppo->GetOwner()->GetName() == L"Bullet"  )
		{
			ms = monsterState::Death;
		}

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Player )
		{
			ms = monsterState::Death;
		}

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Weapone || oppo->GetOwner()->GetLayerType() == eLayerType::Wall)
		{
			ms = monsterState::Death;
		}

		if (oppo->GetOwner()->GetName() == L"FightSabreCollider")
		{
			reflectOn = true;
		}
	
	}
	void BullatScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void BullatScr::OnCollisionExit(Collider2D* oppo)
	{

	}
	void BullatScr::Fly()
	{
		if (thisMonster->GetMonsterChaseCollider()->GetComponent<chasePlayerSCR>()->isFindPlayer() == true) 
		{
			ms = monsterState::Attack;
			thisMonster->GetMonsterChaseCollider()->Death();
		}
	}
	void BullatScr::Attack()
	{
		setAttackTime += Time::DeltaTime();

		if (anima->IsAnimationRunning(L"M_Bullat_Attack") == false)
		{
			anima->Play(L"M_Bullat_Attack", false);
			audioObj[0]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
			boss_audio[0]->Play();
		}

		if (setAttackTime >= 1.4f) 
		{
			GetP2Mangle();
			shootingBullet(P2Mangle, mTr->GetPosition());
			ms = monsterState::chase;
			
		}
	}
	void BullatScr::AttackOk()
	{
		if (anima->IsAnimationRunning(L"M_Bullat_AttackOk") == false)
		{
			anima->Play(L"M_Bullat_AttackOk", true);
		}

		MoveBullet();

	}
	void BullatScr::Death()
	{
		if (anima->IsAnimationRunning(L"M_Bullat_death") == false )
		{
			anima->Play(L"M_Bullat_death", false);
			audioObj[1]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
			boss_audio[1]->Play();
		}
		
		DeathTIME += Time::DeltaTime();
		if (DeathTIME >= 1.25f)
		{
			//thisMonster->GetDoor()->SetDeathCount();
			
			GetOwner()->Death();
		}
	}

	void BullatScr::afterDeath()
	{
		GetOwner()->Death();
	}

	void BullatScr::GetP2Mangle()
	{
		Vector3 playerPos = thisMonster->GetPlayer()->GetComponent<Transform>()->GetPosition();

		Vector3 MonsterPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		
		float aaa = atan2(playerPos.y - MonsterPos.y, playerPos.x - MonsterPos.x);
		P2Mangle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360°¢
		
	}
	void BullatScr::shootingBullet(float Gunangle, Vector3 pos)
	{
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(pos);
	}
	
	void BullatScr::MoveBullet()
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
			goToDeathTime = 0;
			// Reset the reflection state to prevent continuous reflection
			reflectOn = false;
		}


		GetOwner()->GetComponent<Transform>()->SetPosition(bulletPos);


		goToDeathTime += Time::DeltaTime();
		if (goToDeathTime >= 3.f) 
		{
			ms = monsterState::Death;
		}
	}
}