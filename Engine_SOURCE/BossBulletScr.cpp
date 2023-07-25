#include "BossBulletScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chObject.h"
namespace ch 
{
	BossBulletScr::BossBulletScr()
	{
	}

	BossBulletScr::~BossBulletScr()
	{
	}

	void BossBulletScr::Initalize()
	{


		bossBullet = GetOwner()->AddComponent<Animator>();
		{//Attack
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_SpawnBullet", L"enterthe/enemy/SpawnEnemy.png");
			bossBullet->Create(L"Boss_SpawnBullet", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 12, 0.1f);
		}
		{//Attack
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_bossBombEffect", L"enterthe/enemy/Boss/bossBombEffect.png");
			bossBullet->Create(L"Boss_bossBombEffect", texture, Vector2(0.0f, 0.0f), Vector2(84.0f, 114.0f), Vector2::Zero, 6, 0.1f);
		}

		GetOwner()->SetLayerType(eLayerType::MonsterBullet);
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetScale(Vector3(5.6f, 5.6f, 0.0f));

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BulletKinMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		col = GetOwner()->AddComponent<Collider2D>();
		col->SetName(L"BombCollider");
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.01f, 0.01f));
		col->SetCenter(Vector2(10.f, 10.f));



		audioObj = object::Instantiate<GameObject>(eLayerType::UI);
		audioClip = Resources::Load<AudioClip>(L"bombsound", L"music\\boss\\bombsound.mp3");
		boss_audio = audioObj->AddComponent<AudioSource>();
		boss_audio->SetClip(audioClip);


		bossBullet->Play(L"Boss_SpawnBullet");
		bombTimer = 0.f;
		bombCollder = 0.f;
	}

	void BossBulletScr::Update()
	{
		bombTimer += Time::DeltaTime();

		if (bombTimer >= 1.2f)
		{
			col->SetCenter(Vector2(0.f, 0.f));
			bombCollder += Time::DeltaTime();
			if (bossBullet->IsAnimationRunning(L"Boss_bossBombEffect") == false)
			{
				bossBullet->Play(L"Boss_bossBombEffect", false);
				boss_audio->Play();
			}
			
			bombCollderEffect();

		}

		if(bombTimer >= 1.9)
		{
			Reset();
		}

	}

	void BossBulletScr::FixedUpdate()
	{
	}

	void BossBulletScr::Render()
	{
	}

	void BossBulletScr::OnCollisionEnter(Collider2D* oppo)
	{


	}

	void BossBulletScr::OnCollision(Collider2D* oppo)
	{
	}

	void BossBulletScr::OnCollisionExit(Collider2D* oppo)
	{
	}

	void BossBulletScr::Reset()
	{
		GetOwner()->Death();
	}

	void BossBulletScr::bombCollderEffect()
	{
		float initialSize = 0.1f;
		float maxSize = 0.5f;

		// 크기 변화에 사용할 시간 비율 계산
		float timeRatio = bombCollder * 2.f;

		// 크기 계산
		float currentSize = initialSize + (maxSize - initialSize) * timeRatio;

		// 크기 적용
		col->SetSize(Vector2(currentSize, currentSize));
	}

}