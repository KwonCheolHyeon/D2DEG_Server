#include "chBoss.h"
#include "chObject.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "MonsterBulletScr.h"
#include "chasePlayerSCR.h"
#include "BossBulletObj.h"
#include "BossBulletScr.h"
#include "chObject.h"

#include "chAudioListener.h"
#include "chAudioClip.h"
#include "chFmod.h"
#include "chAudioSource.h"

namespace ch
{
	Boss::Boss()
		: mBossAni(nullptr)
		, mBoss(nullptr)
		, mBtr()
		, mBcol(nullptr)
		, mS(Spawn)
		, mD(mNorth)
		, prevmD(mNorth)
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initalize()
	{
		thisMonster = dynamic_cast<MonsterBase*>(GetOwner());
		thisMosterCollider = thisMonster->GetMonsterChaseCollider();


		mBoss = GetOwner();
		mBoss->SetLayerType(eLayerType::Monster);
		mBossAni = GetOwner()->AddComponent<Animator>();
		mBtr = GetOwner()->GetComponent<Transform>();
		mBcol = GetOwner()->AddComponent<Collider2D>();
		mBcol->SetName(L"BossCollider");
		mBcol->SetType(eColliderType::Rect);
		mBcol->SetSize(Vector2(0.3f, 0.3f));


		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


	#pragma region 애니
		{//Death
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Attack", L"enterthe/enemy/Boss/Death.png");
			mBossAni->Create(L"Boss_Death", texture, Vector2(0.0f, 0.0f), Vector2(68.0f, 43.0f), Vector2::Zero, 6, 0.2f);
		}

		{//Down

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Attack", L"enterthe/enemy/Boss/Down_Attack.png");
				mBossAni->Create(L"Boss_Down_Attack", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 2, 0.5f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Hit", L"enterthe/enemy/Boss/Down_Hit.png");
				mBossAni->Create(L"Boss_Down_Hit", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 1, 0.1f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Idle", L"enterthe/enemy/Boss/Down_Idle.png");
				mBossAni->Create(L"Boss_Down_Idle", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 1, 0.1f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Move", L"enterthe/enemy/Boss/Down_Move.png");
				mBossAni->Create(L"Boss_Down_Move", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 4, 0.15f);
			}
		}
		{//Up
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Attack", L"enterthe/enemy/Boss/Up_Attack.png");
				mBossAni->Create(L"Boss_Up_Attack", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 2, 0.5f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Hit", L"enterthe/enemy/Boss/Up_Hit.png");
				mBossAni->Create(L"Boss_Up_Hit", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Idle", L"enterthe/enemy/Boss/Up_Idle.png");
				mBossAni->Create(L"Boss_Up_Idle", texture, Vector2(0.0f, 0.0f), Vector2(37.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Move", L"enterthe/enemy/Boss/Up_Move.png");
				mBossAni->Create(L"Boss_Up_Move", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 4, 0.15f);
			}
		}
		{//Left
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Attack", L"enterthe/enemy/Boss/Left_Attack.png");
				mBossAni->Create(L"Boss_Left_Attack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Hit", L"enterthe/enemy/Boss/Left_Hit.png");
				mBossAni->Create(L"Boss_Left_Hit", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Idle", L"enterthe/enemy/Boss/Left_Idle.png");
				mBossAni->Create(L"Boss_Left_Idle", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Move", L"enterthe/enemy/Boss/Left_Move.png");
				mBossAni->Create(L"Boss_Left_Move", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 4, 0.15f);
			}

		}
		{//Right
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Attack", L"enterthe/enemy/Boss/Right_Attack.png");
				mBossAni->Create(L"Boss_Right_Attack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Hit", L"enterthe/enemy/Boss/Right_Hit.png");
				mBossAni->Create(L"Boss_Right_Hit", texture, Vector2(0.0f, 0.0f), Vector2(76.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Idle", L"enterthe/enemy/Boss/Right_Idle.png");
				mBossAni->Create(L"Boss_Right_Idle", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Move", L"enterthe/enemy/Boss/Right_Move.png");
				mBossAni->Create(L"Boss_Right_Move", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 4, 0.15f);
			}

		}
		{//Right down

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Attack", L"enterthe/enemy/Boss/RightDown_Attack.png");
				mBossAni->Create(L"Boss_RightDown_Attack", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 61.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Hit", L"enterthe/enemy/Boss/RightDown_Hit.png");
				mBossAni->Create(L"Boss_RightDown_Hit", texture, Vector2(0.0f, 0.0f), Vector2(59.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Idle", L"enterthe/enemy/Boss/RightDown_Idle.png");
				mBossAni->Create(L"Boss_RightDown_Idle", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Move", L"enterthe/enemy/Boss/RightDown_Move.png");
				mBossAni->Create(L"Boss_RightDown_Move", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 6, 0.15f);
			}
		}
		{//Left Down
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Attack", L"enterthe/enemy/Boss/LeftDown_Attack.png");
				mBossAni->Create(L"Boss_LeftDown_Attack", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 59.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Hit", L"enterthe/enemy/Boss/LeftDown_Hit.png");
				mBossAni->Create(L"Boss_LeftDown_Hit", texture, Vector2(0.0f, 0.0f), Vector2(59.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Idle", L"enterthe/enemy/Boss/LeftDown_Idle.png");
				mBossAni->Create(L"Boss_LeftDown_Idle", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Move", L"enterthe/enemy/Boss/LeftDown_Move.png");
				mBossAni->Create(L"Boss_LeftDown_Move", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero,5, 0.15f);
			}

		}
		{//Right Up

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Attack", L"enterthe/enemy/Boss/RightUp_Attack.png");
				mBossAni->Create(L"Boss_RightUp_Attack", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Hit", L"enterthe/enemy/Boss/RightUp_Hit.png");
				mBossAni->Create(L"Boss_RightUp_Hit", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Idle", L"enterthe/enemy/Boss/RightUp_Idle.png");
				mBossAni->Create(L"Boss_RightUp_Idle", texture, Vector2(0.0f, 0.0f), Vector2(41.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Move", L"enterthe/enemy/Boss/RightUp_Move.png");
				mBossAni->Create(L"Boss_RightUp_Move", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 43.0f), Vector2::Zero, 3, 0.15f);
			}
		}
		{//Left Up

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Attack", L"enterthe/enemy/Boss/LeftUp_Attack.png");
				mBossAni->Create(L"Boss_LeftUp_Attack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 43.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Hit", L"enterthe/enemy/Boss/LeftUp_Hit.png");
				mBossAni->Create(L"Boss_LeftUp_Hit", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Idle", L"enterthe/enemy/Boss/LeftUp_Idle.png");
				mBossAni->Create(L"Boss_LeftUp_Idle", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Move", L"enterthe/enemy/Boss/LeftUp_Move.png");
				mBossAni->Create(L"Boss_LeftUp_Move", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 43.0f), Vector2::Zero, 3, 0.15f);
			}
		}
		{
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_fly", L"enterthe/enemy/Boss/fly.png");
				mBossAni->Create(L"B_Boss_fly", texture, Vector2(0.0f, 0.0f), Vector2(39.0f, 86.0f), Vector2::Zero, 4, 0.15f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_flying", L"enterthe/enemy/Boss/flying.png");
				mBossAni->Create(L"B_Boss_flying", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 51.0f), Vector2::Zero, 1, 0.15f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_skyBomb", L"enterthe/enemy/Boss/skyBomb.png");
				mBossAni->Create(L"B_Boss_skyBomb", texture, Vector2(0.0f, 0.0f), Vector2(48.0f, 74.0f), Vector2::Zero, 5, 0.2f);
			}
		}

	#pragma endregion

		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[2] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[3] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[4] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[5] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[6] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[7] = object::Instantiate<GameObject>(eLayerType::UI);
	
		audioClip[0] = Resources::Load<AudioClip>(L"gull_death", L"music\\boss\\gull_death.mp3");
		audioClip[1] = Resources::Load<AudioClip>(L"gull_leap", L"music\\boss\\gull_leap.mp3");
		audioClip[2] = Resources::Load<AudioClip>(L"gull_descend", L"music\\boss\\gull_descend.mp3");
		audioClip[3] = Resources::Load<AudioClip>(L"gull_rocket", L"music\\boss\\gull_rocket.mp3");
		audioClip[4] = Resources::Load<AudioClip>(L"gull_gatling", L"music\\boss\\gull_gatling.mp3");
		audioClip[5] = Resources::Load<AudioClip>(L"gull_gatlingloop", L"music\\boss\\gull_gatlingloop.mp3");
		audioClip[6] = Resources::Load<AudioClip>(L"gull_shoot01", L"music\\boss\\gull_shoot01.mp3");
		audioClip[7] = Resources::Load<AudioClip>(L"gull_shoot02", L"music\\boss\\gull_shoot02.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();
		boss_audio[2] = audioObj[2]->AddComponent<AudioSource>();
		boss_audio[3] = audioObj[3]->AddComponent<AudioSource>();
		boss_audio[4] = audioObj[4]->AddComponent<AudioSource>();
		boss_audio[5] = audioObj[5]->AddComponent<AudioSource>();
		boss_audio[6] = audioObj[6]->AddComponent<AudioSource>();
		boss_audio[7] = audioObj[7]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);
		boss_audio[2]->SetClip(audioClip[2]);
		boss_audio[3]->SetClip(audioClip[3]);
		boss_audio[4]->SetClip(audioClip[4]);
		boss_audio[5]->SetClip(audioClip[5]);
		boss_audio[6]->SetClip(audioClip[6]);
		boss_audio[7]->SetClip(audioClip[7]);



		mBtr->SetPosition(Vector3(15.28f, 23.28f, 1.f));
		mBtr->SetScale(Vector3(5.f, 6.f, 1.f));
		mBossAni->Play(L"Boss_LeftDown_Idle");
		monsterHp = 140;
		prevMonsterHp = 50;
		first = 1;
		player = thisMonster->GetPlayer();
		hit = false;
		oneDeath = false;
		prevbombCount = 6;
		deathTime = 0.f;

		oneDescend = true;
		beforeAttack = true;
	}
	void Boss::Update()
	{
		if (mS != monsterState::mIdle && thisMosterCollider->GetComponent<chasePlayerSCR>()->isFindPlayer() && first == 1)
		{
			first *= -1;
			mS = monsterState::mIdle;
		}
		if (prevMonsterHp != monsterHp)
		{
			prevMonsterHp = monsterHp;

			switch (monsterHp)
			{
			case 120:
				mS = monsterState::BossFlyAni;
				break;
			case 90:
				mS = monsterState::BossFlyAni;
				break;
			case 60:
				mS = monsterState::BossFlyAni;
				break;
			case 30:
				mS = monsterState::BossFlyAni;
				break;
			default:
				break;
			}

		}

		SetMd();

		switch (mS)
		{
		case monsterState::Spawn:
			BossSpawn();
			break;
		case monsterState::mIdle:
			BossIdle();
			break;
		case monsterState::chase:
			BossChase();
			break;
		case monsterState::Hit:
			BossHit();
			break;
		case monsterState::Move:
			BossMove();
			break;
		case monsterState::Attack:
			BossAttack();
			break;
		case monsterState::SkyBomb:
			BossSkyBomb();
			break;
		case monsterState::BossFlyAni:
			
			BossFlyAni();
			break;
		case monsterState::BossGoMid:
			BossGoMid();
			break;
		case monsterState::Death:
			BossDeath();
			break;
		default:
			break;
		}

	}
	void Boss::FixedUpdate()
	{
	}
	void Boss::Render()
	{
	}
	void Boss::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Weapone || oppo->GetOwner()->GetName() == L"reflectBullet")
		{
			monsterHp -= 1;
			if (monsterHp == 0)
			{
				mS = monsterState::Death;
			}
			else
			{
				hit = true;
			}
		}
	}
	void Boss::OnCollision(Collider2D* oppo)
	{

	}
	void Boss::OnCollisionExit(Collider2D* oppo)
	{

	}
	void Boss::OnTriggerEnter(Collider2D* oppo)
	{

	}
	void Boss::OnTrigger(Collider2D* oppo)
	{

	}
	void Boss::OnTriggerExit(Collider2D* oppo)
	{

	}
	void Boss::BossSpawn()
	{

	}
	void Boss::BossIdle()
	{
		if (thisMosterCollider->GetComponent<chasePlayerSCR>()->isFindPlayer() == true)
		{
			mS = monsterState::Attack;
		}
		else //false
		{
			mS = monsterState::Move;
		}
		
		
	}
	void Boss::BossChase()
	{
		
	}
	void Boss::BossHit()
	{

		switch (mD)
		{
		case monsterDir::mNorth:
			mBossAni->Play(L"Boss_Up_Hit",false);
			break;
		case monsterDir::mSouth:
			mBossAni->Play(L"Boss_Down_Hit",false);
			break;
		case monsterDir::mEast:
			mBossAni->Play(L"Boss_Right_Hit",false);
			break;
		case monsterDir::mWest:
			mBossAni->Play(L"Boss_Left_Hit",false);
			break;
		case monsterDir::mNE:
			mBossAni->Play(L"Boss_RightUp_Hit",false);
			break;
		case monsterDir::mNW:
			mBossAni->Play(L"Boss_LeftUp_Hit",false);
			break;
		case monsterDir::mSE:
			mBossAni->Play(L"Boss_RightDown_Hit",false);
			break;
		case monsterDir::mSW:
			mBossAni->Play(L"Boss_LeftDown_Hit",false);
			break;
		default:
			break;
		}

		hitAniTimer -= Time::DeltaTime(); // attackTimer 값을 감소

		if (hitAniTimer <= 0.0f)
		{
			prevmD = monsterDir::prev;
			hit = false;
			hitAniTimer = 0.4f; // 0.2초로 타이머 재설정
		}

		
	}
	void Boss::BossMove()
	{
		Vector3 monsterPosition = mBoss->GetComponent<Transform>()->GetPosition();
		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		float distanceToPlayer = CalculateDistance(monsterPosition, playerPosition);

		if (distanceToPlayer > 6.0f)
		{
			Vector3 direction = Normalize(playerPosition - monsterPosition);
			float moveDistance = 1.f * Time::DeltaTime();
			Vector3 newPosition = monsterPosition + direction * moveDistance;
			mBoss->GetComponent<Transform>()->SetPosition(newPosition);
		}

		if (distanceToPlayer < 3.0f) //플레이어와 보스 사이의 거리가 너무 가까우면 피함
		{
			mS = monsterState::BossFlyAni;
		}
		else 
		{
			mS = monsterState::mIdle;
		}

	}

	void Boss::BossAttack()
	{
		if (hit == true) 
		{
			BossHit();
		}
		else if(hit == false)
		{
			if (mD != prevmD) {
				prevmD = mD;
				switch (mD)
				{
				case monsterDir::mNorth:
					mBossAni->Play(L"Boss_Up_Move");
					break;
				case monsterDir::mSouth:
					mBossAni->Play(L"Boss_Down_Move");
					break;
				case monsterDir::mEast:
					mBossAni->Play(L"Boss_Right_Move");
					break;
				case monsterDir::mWest:
					mBossAni->Play(L"Boss_Left_Move");
					break;
				case monsterDir::mNE:
					mBossAni->Play(L"Boss_RightUp_Move");
					break;
				case monsterDir::mNW:
					mBossAni->Play(L"Boss_LeftUp_Move");
					break;
				case monsterDir::mSE:
					mBossAni->Play(L"Boss_RightDown_Move");
					break;
				case monsterDir::mSW:
					mBossAni->Play(L"Boss_LeftDown_Move");
					break;
				default:
					break;
				}
			}

		}

		if(beforeAttack == true)
		{
			beforeAttack = false;
			boss_audio[4]->Play();
		}

		attackTimer -= Time::DeltaTime(); // attackTimer 값을 감소

		if (attackTimer <= 0.0f)
		{
			boss_audio[5]->Play();
			Attack();
			attackTimer = 0.07f; // 0.2초로 타이머 재설정
		}

		BossMove();

		
	}
	void Boss::BossFlyAni()
	{
		BossFlyAniTimer += Time::DeltaTime();
		if (mBossAni->IsAnimationRunning(L"B_Boss_fly") == false) 
		{
			mBossAni->Play(L"B_Boss_fly",false);
		
			
			boss_audio[1]->Play();

		}

		if(BossFlyAniTimer >= 0.6f)
		{
			BossFlyAniTimer = 0;
			mS = monsterState::BossGoMid;
		}
		

		

	}
	void Boss::BossGoMid()
	{
	
		mBossAni->Play(L"B_Boss_flying");
		Vector3 a = mBtr->GetPosition();
		float bossDuration = 2.0f;  // Duration in seconds
		float bossSpeed = 0.0f;  // Speed (vertical movement distance per second)

		bossFly +=  Time::DeltaTime();

		mBtr->SetPosition(a + Vector3(0.f, bossFly * 0.5f, 0.f));

		if (bossFly >= 2.f)
		{
			if (oneDescend == true)
			{
				oneDescend = false;

				boss_audio[2]->Play();
			}
			// Boss has reached the desired height
			bossFly = 0.f;
			mBtr->SetPosition(Vector3(15.28f, 43.28f, -1.f));
			oneDescend = true;
			mS = monsterState::SkyBomb;
		}
	}
	void Boss::BossSkyBomb()
	{
		beforeAttack = true;
		bossSkyBomb += Time::DeltaTime();
		Vector3 a = mBtr->GetPosition();

		if (a.y >= 24.6) 
		{
			BossDown.y += static_cast<float>(bossSkyBomb) * 0.05f;
			mBtr->SetPosition(a - Vector3(0.f, BossDown.y, 0.f));
		}
		else 
		{
			boosSkyBombAttackTime += Time::DeltaTime();

			if (boosSkyBombAttackTime >= 1.1f) 
			{
				bombCount += 1;
				boosSkyBombAttackTime = 0;
			}
			if (mBossAni->IsAnimationRunning(L"B_Boss_skyBomb") == false)
			{
				mBossAni->Play(L"B_Boss_skyBomb", true);
				
			}

			if (prevbombCount != bombCount) {
				prevbombCount = bombCount;
				switch (bombCount)
				{
				case 0:
					boss_audio[3]->Play();
					monsterBullet1 = object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet1->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr1 = monsterBullet1->AddComponent<BossBulletScr>();
					monsterBulletScr1->Initalize();

					
					break;
				case 1:
					boss_audio[3]->Play();
					monsterBullet2 = object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet2->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr2 = monsterBullet2->AddComponent<BossBulletScr>();
					monsterBulletScr2->Initalize();
					player->getCameraScr()->strongEffectOn();

					break;
				case 2:
					boss_audio[3]->Play();
					monsterBullet3 = object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet3->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr3 = monsterBullet3->AddComponent<BossBulletScr>();
					monsterBulletScr3->Initalize();
					player->getCameraScr()->strongEffectOn();
					break;
				case 3:
					boss_audio[3]->Play();
					monsterBullet4 = object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet4->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr4 = monsterBullet4->AddComponent<BossBulletScr>();
					monsterBulletScr4->Initalize();
					player->getCameraScr()->strongEffectOn();
					break;
				case 4:
					boss_audio[3]->Play();
					monsterBullet5= object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet5->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr5 = monsterBullet5->AddComponent<BossBulletScr>();
					monsterBulletScr5->Initalize();
					player->getCameraScr()->strongEffectOn();
					break;
				case 5:
					boss_audio[3]->Play();
					monsterBullet6 = object::Instantiate<BossBulletObj>(eLayerType::MonsterBullet);
					monsterBullet6->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
					monsterBulletScr6 = monsterBullet6->AddComponent<BossBulletScr>();
					monsterBulletScr6->Initalize();
					player->getCameraScr()->strongEffectOn();
					break;
				case 6:
					
					player->getCameraScr()->strongEffectOn();
					bombCount = 0;
					boosSkyBombAttackTime = 0;
					bossSkyBomb = 0;
					BossDown = Vector3::Zero;
					prevbombCount = 7;
					mS = monsterState::mIdle;
					break;
				default:
					break;
				}

			}
		

		
		}
		




	}
	void Boss::BossDeath()
	{
		deathTime += Time::DeltaTime();
		if (oneDeath == false) 
		{
			oneDeath = true;
			mBossAni->Play(L"Boss_Death",false);
			boss_audio[0]->Play();
		}

		if (deathTime >= 6.f) 
		{

			SceneManager::LoadScene(eSceneType::Test);
		}
		
	}
	void Boss::SetMd()
	{
		Vector3 monsterPosition = mBoss->GetComponent<Transform>()->GetPosition();
		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		float dx = playerPosition.x - monsterPosition.x;
		float dy = playerPosition.y - monsterPosition.y;

		float angle = atan2(dy, dx) * 180 / 3.141592f;


		if (angle >= -22.5 && angle < 22.5)
		{
			mD = monsterDir::mEast;
		}
		else if (angle >= 22.5 && angle < 67.5)
		{
			mD = monsterDir::mNE;
		}
		else if (angle >= 67.5 && angle < 112.5)
		{
			mD = monsterDir::mNorth;
		}
		else if (angle >= 112.5 && angle < 157.5)
		{
			mD = monsterDir::mNW;
		}
		else if (angle >= 157.5 || angle < -157.5)
		{
			mD = monsterDir::mWest;
		}
		else if (angle >= -157.5 && angle < -112.5)
		{
			mD = monsterDir::mSW;
		}
		else if (angle >= -112.5 && angle < -67.5)
		{
			mD = monsterDir::mSouth;
		}
		else if (angle >= -67.5 && angle < -22.5)
		{
			mD = monsterDir::mSE;
		}
	}
	void Boss::Attack()
	{
		monsBullet = object::Instantiate<MonsterBulletObj>(eLayerType::MonsterBullet);
		MonsterBulletScr* bulletScript = monsBullet->AddComponent<MonsterBulletScr>();
		bulletScript->Initalize();
		float angle = 0;
		Vector3 boss = mBoss->GetComponent<Transform>()->GetPosition();
		audioClip[6]->Play();
		switch (mD)
		{
		case monsterDir::mNorth:
			angle = 90.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(0.2f,1.f,0.f);
			break;
		case monsterDir::mSouth:
			angle = 270.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-0.2f, -1.f, 0.f);
			break;
		case monsterDir::mEast:
			angle = 0.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, -0.2f, 0.f);
			break;
		case monsterDir::mWest:
			angle = 180.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, -0.2f, 0.f);
			break;
		case monsterDir::mNE:
			angle = 45.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, 1.f, 0.f);
			break;
		case monsterDir::mNW:
			angle = 135.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, 1.f, 0.f);
			break;
		case monsterDir::mSE:
			angle = 315.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, -1.f, 0.f);
			break;
		case monsterDir::mSW:
			angle = 225.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, -1.f, 0.f);
			break;
		default:
			break;
		}

		float angleVariation = static_cast<float>((rand() % 45) - 22);

		float finalAngle = angle + angleVariation;

		bulletScript->shootingBullet(finalAngle, boss);
		boss_audio[7]->Play();
	}
}