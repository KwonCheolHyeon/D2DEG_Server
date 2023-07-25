#include "BossHpBarScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chBoss.h"
#include "EventScr.h"

//Animator* ani;
//MonsterBase* boss;
//EventObj* eventObj;
//	private:
//		float health;
//		float bossHp;
//		float prevBossHp;
//		float maxHp;
namespace ch
{
	BossHpBarScr::BossHpBarScr()
		:ani(nullptr)
		,boss(nullptr)
		,eventObj(nullptr)
		,health(0.f)
		,bossHp(0.f)
		,prevBossHp(0.f)
		,maxHp(0.f)
	{
	}
	BossHpBarScr::~BossHpBarScr()
	{
	}
	void BossHpBarScr::Initalize()//체력 상태 
	{


		ani = GetOwner()->AddComponent<Animator>();

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni", L"enterthe/UI/BossHp/bossHpAni.png");
			ani->Create(L"Boss_HpBar", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni01", L"enterthe/UI/BossHp/bossHpAni01.png");
			ani->Create(L"Boss_HpBar01", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni02", L"enterthe/UI/BossHp/bossHpAni02.png");
			ani->Create(L"Boss_HpBar02", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni03", L"enterthe/UI/BossHp/bossHpAni03.png");
			ani->Create(L"Boss_HpBar03", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni04", L"enterthe/UI/BossHp/bossHpAni04.png");
			ani->Create(L"Boss_HpBar04", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni05", L"enterthe/UI/BossHp/bossHpAni05.png");
			ani->Create(L"Boss_HpBar05", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni06", L"enterthe/UI/BossHp/bossHpAni06.png");
			ani->Create(L"Boss_HpBar06", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni07", L"enterthe/UI/BossHp/bossHpAni07.png");
			ani->Create(L"Boss_HpBar07", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni08", L"enterthe/UI/BossHp/bossHpAni08.png");
			ani->Create(L"Boss_HpBar08", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni09", L"enterthe/UI/BossHp/bossHpAni09.png");
			ani->Create(L"Boss_HpBar09", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni10", L"enterthe/UI/BossHp/bossHpAni10.png");
			ani->Create(L"Boss_HpBar10", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni11", L"enterthe/UI/BossHp/bossHpAni11.png");
			ani->Create(L"Boss_HpBar11", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni12", L"enterthe/UI/BossHp/bossHpAni12.png");
			ani->Create(L"Boss_HpBar12", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni14", L"enterthe/UI/BossHp/bossHpAni14.png");
			ani->Create(L"Boss_HpBar13", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni15", L"enterthe/UI/BossHp/bossHpAni15.png");
			ani->Create(L"Boss_HpBar14", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpAni16", L"enterthe/UI/BossHp/bossHpAni16.png");
			ani->Create(L"Boss_HpBar15", texture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		
		

		//ani->Play(L"Boss_HpBar");
		

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
	

	}
	void BossHpBarScr::Update()
	{
		if (eventObj->GetComponent<EventScr>()->GetEventState() == true)
		{
			int hp = boss->GetComponent<Boss>()->GetHp();
		
			bossHp = static_cast<float>(hp) / 10.f;
		
			if (bossHp > 13 && bossHp <= 14)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar") == false)
				{
					ani->Play(L"Boss_HpBar");
				}

			}
			else if (bossHp > 12 && bossHp <= 13)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar01") == false)
				{
					ani->Play(L"Boss_HpBar01");
				}

			}
			else if (bossHp > 11 && bossHp <= 12)
			{

				if (ani->IsAnimationRunning(L"Boss_HpBar02") == false)
				{
					ani->Play(L"Boss_HpBar02");
				}
			}
			else if (bossHp > 10 && bossHp <= 11)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar03") == false)
				{
					ani->Play(L"Boss_HpBar03");
				}

			}
			else if (bossHp > 9 && bossHp <= 10)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar04") == false)
				{
					ani->Play(L"Boss_HpBar04");
				}

			}
			else if (bossHp > 8 && bossHp <= 9)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar05") == false)
				{
					ani->Play(L"Boss_HpBar05");
				}

			}
			else if (bossHp > 7 && bossHp <= 8)
			{

				if (ani->IsAnimationRunning(L"Boss_HpBar06") == false)
				{
					ani->Play(L"Boss_HpBar06");
				}
			}
			else if (bossHp > 6 && bossHp <= 7)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar07") == false)
				{
					ani->Play(L"Boss_HpBar07");
				}

			}
			else if (bossHp > 6 && bossHp <= 7)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar08") == false)
				{
					ani->Play(L"Boss_HpBar08");
				}

			}
			else if (bossHp > 5 && bossHp <= 6)
			{

				if (ani->IsAnimationRunning(L"Boss_HpBar09") == false)
				{
					ani->Play(L"Boss_HpBar09");
				}
			}
			else if (bossHp > 4 && bossHp <= 5)
			{

				if (ani->IsAnimationRunning(L"Boss_HpBar10") == false)
				{
					ani->Play(L"Boss_HpBar10");
				}

			}
			else if (bossHp > 3 && bossHp <= 4)
			{

				if (ani->IsAnimationRunning(L"Boss_HpBar11") == false)
				{
					ani->Play(L"Boss_HpBar11");
				}

			}
			else if (bossHp > 2 && bossHp <= 3)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar12") == false)
				{
					ani->Play(L"Boss_HpBar12");
				}
			}
			else if (bossHp > 1 && bossHp <= 2)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar13") == false)
				{
					ani->Play(L"Boss_HpBar13");
				}
			}
			else if (bossHp > 0 && bossHp <= 1)
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar14") == false)
				{
					ani->Play(L"Boss_HpBar14");
				}
			}
			else if (bossHp == 0 )
			{
				if (ani->IsAnimationRunning(L"Boss_HpBar15") == false)
				{
					ani->Play(L"Boss_HpBar15");
				}
			}



		}

	}
	void BossHpBarScr::FixedUpdate()
	{
	}
	void BossHpBarScr::Render()
	{
	}
}