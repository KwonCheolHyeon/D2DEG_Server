#include "Bullet_Kin_Gun_Scr.h"
#include "Bullet_Kin_Gun.h"
#include "Bullet_Kin.h"
#include "chScene.h"
#include "chResources.h"
#include "chObject.h"
namespace ch 
{
	Bullet_Kin_Gun_Scr::Bullet_Kin_Gun_Scr()
	{
	}
	Bullet_Kin_Gun_Scr::~Bullet_Kin_Gun_Scr()
	{
	}
	void Bullet_Kin_Gun_Scr::Initalize()
	{
		anima = GetOwner()->GetComponent<Animator>();

		anima->Play(L"WGun_Idle");

		thisTrans = GetOwner()->GetComponent<Transform>();


		audioObj = object::Instantiate<GameObject>(eLayerType::UI);
		audioClip = Resources::Load<AudioClip>(L"shot", L"music\\enemy\\bulletkin\\shot.mp3");
		boss_audio = audioObj->AddComponent<AudioSource>();
		boss_audio->SetClip(audioClip);

		Owner = dynamic_cast<Bullet_Kin_Gun*>(GetOwner());
		allowShot = true;
		ShotTime = 0.f;
		afterShotCalled = false;
		
	}
	void Bullet_Kin_Gun_Scr::Update()
	{
		
	
		
		if (Owner->GetOwnerMonster()->GetComponent<Bullet_Kin>()->GetShot() == true && allowShot == true)
		{
			allowShot = false;
			Owner->GetOwnerMonster()->GetComponent<Bullet_Kin>()->SetShot(false);
			Shot();
			boss_audio->Play();
		}
		if (allowShot == false) 
		{
			ShotTerm();
		}
		if (afterShotCalled == true) 
		{
			anima->GetEndEvent(L"WGun_Shot") = std::bind(&Bullet_Kin_Gun_Scr::afterShot, this);
		}

		if (Owner->GetOwnerMonster()->IsDead() == true) 
		{
			this->GetOwner()->Death();
		}
	}
	void Bullet_Kin_Gun_Scr::FixedUpdate()
	{
	}
	void Bullet_Kin_Gun_Scr::Render()
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollision(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollisionExit(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTrigger(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTriggerExit(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::Shot()
	{

		Animator* monsterGunAni = GetOwner()->GetComponent<Animator>();
		monsterGunAni->Play(L"WGun_Shot",false);
		afterShotCalled = true;

	}
	void Bullet_Kin_Gun_Scr::ShotTerm()
	{
		ShotTime += Time::DeltaTime();


		if (ShotTime >= 2.5f) 
		{
			Animator* monsterGunAni = GetOwner()->GetComponent<Animator>();

			ShotTime = 0.f;
			allowShot = true;
		}
	}
	void Bullet_Kin_Gun_Scr::afterShot()
	{
		
		monsBullet = object::Instantiate<MonsterBulletObj>(eLayerType::MonsterBullet);
		
		MonsterBulletScr* bulletScript = monsBullet->AddComponent<MonsterBulletScr>();
		bulletScript->Initalize();
		
		float angle = Owner->GetP2Gangle();
		bulletScript->shootingBullet(angle, Owner->GetOwnerMonster()->GetComponent<Transform>()->GetPosition());
		afterShotCalled = false;
	}
}

//anima->GetCompleteEvent(L"WGun_Shot") = std::bind(&Bullet_Kin_Gun_Scr::afterShot, this);
