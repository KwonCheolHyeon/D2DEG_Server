#include "BossHpUIScr.h"
#include "BossHpUIObj.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "EventScr.h"
namespace ch 
{
	BossHpUIScr::BossHpUIScr()
	{
	}
	BossHpUIScr::~BossHpUIScr()
	{
	}
	void BossHpUIScr::Initalize()
	{
		ani = GetOwner()->AddComponent<Animator>();

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpBar", L"enterthe/UI/BossHp/HpBar.png");
			ani->Create(L"Boss_HpBar", texture, Vector2(0.0f, 0.0f), Vector2(200.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpBarhide", L"enterthe/UI/BossHp/bossHpAni16.png");
			ani->Create(L"Boss_HpBarHide", texture, Vector2(0.0f, 0.0f), Vector2(200.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		//ani->Play(L"Boss_HpBar");

	}
	void BossHpUIScr::Update()
	{
		if (eventObj->GetComponent<EventScr>()->GetEventState() == true)
		{
			ani->Play(L"Boss_HpBar");

		}


	}
	void BossHpUIScr::FixedUpdate()
	{
	}
	void BossHpUIScr::Render()
	{
	}
}