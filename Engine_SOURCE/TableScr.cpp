#include "TableScr.h"
#include "TableObject.h"
#include "chInput.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chObject.h"
namespace ch 
{
	
	TableScr::TableScr()
	{
	}

	TableScr::~TableScr()
	{

	}

	void TableScr::Initalize()
	{
		audioObj = object::Instantiate<GameObject>(eLayerType::UI);
		audioClip = Resources::Load<AudioClip>(L"table_flip", L"music\\object\\table_flip.mp3");
		boss_audio = audioObj->AddComponent<AudioSource>();
		boss_audio->SetClip(audioClip);


		directionNumber = 10;
		prevDN = 5;
		tAnimator = this->GetOwner()->GetComponent<Animator>();
		tableCount = 3;
		once0 = 0;
		once1 = 0;
		once2 = 0;
		tableOn = false;
	}

	void TableScr::Update()
	{
		if (directionNumber != 0 && prevDN != 1)
		{
			if (Input::GetKeyDown(eKeyCode::E) && tableOn == true)
			{
				audioObj->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
				boss_audio->Play();
				if (directionNumber == 1)//╩С
				{
					this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(8.f, 6.f, 1.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetCenter(Vector2(-0.09f, -0.09f));
					this->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(0.16f, 0.09f));
					tAnimator->Play(L"T_table_front_Ani",false);
				}
				else if (directionNumber == 2) //©Л 
				{
					this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(9.6f, 5.625f, 1.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetCenter(Vector2(-0.75f, 0.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(0.02f, 0.2f));
					tAnimator->Play(L"T_table_left_Ani",false);
				}
				else if (directionNumber == 3) // го
				{
					this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(8.f, 6.f, 1.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetCenter(Vector2(-0.07f, 0.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(0.16f, 0.08f));
					tAnimator->Play(L"T_table_back_Ani",false);
				}
				else if (directionNumber == 4) // аб
				{
					this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(9.6f, 5.625f, 1.f));
					this->GetOwner()->GetComponent<Transform>()->SetPosition(this->GetOwner()->GetComponent<Transform>()->GetPosition() - Vector3(0.5f,0.f,0.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetCenter(Vector2(0.85f, 0.f));
					this->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(0.02f, 0.2f));
					tAnimator->Play(L"T_table_right_Ani",false);
				}
				prevDN = 1;
			}
		}


		if (tableCount == 2 && prevDN == 1 && once2 == 0 )
		{
			if (directionNumber == 1) //front
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Front_01_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 2) // left
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Left_01_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 3) // back
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Back_01_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 4)  // right
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Right_01_Material");
				sprite->SetMaterial(mateiral);
			}
			once2 +=1;
		}
		else if (tableCount == 1 && prevDN == 1 && once1 ==0)
		{
			if (directionNumber == 1)
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Front_02_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 2)
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Left_02_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 3)
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Back_02_Material");
				sprite->SetMaterial(mateiral);
			}
			else if (directionNumber == 4)
			{
				SpriteRenderer* sprite = this->GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Right_02_Material");
				sprite->SetMaterial(mateiral);
			}
			once1 += 1;
		}
		else if (tableCount == 0 && prevDN == 1 && once0 == 0 )
		{
			if (directionNumber == 1)
			{
				tAnimator->Play(L"T_table_front_break_Ani", false);
				this->GetOwner()->SetLayerType(eLayerType::Dummy);
			}
			else if (directionNumber == 2)
			{
				tAnimator->Play(L"T_table_left_break_Ani", false);
				this->GetOwner()->SetLayerType(eLayerType::Dummy);
			}
			else if (directionNumber == 3)
			{
				tAnimator->Play(L"T_table_back_break_Ani", false);
				this->GetOwner()->SetLayerType(eLayerType::Dummy);
			}
			else if (directionNumber == 4)
			{
				tAnimator->Play(L"T_table_right_break_Ani", false);
				this->GetOwner()->SetLayerType(eLayerType::Dummy);
			}
			once0 += 1;
			this->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2::Zero);
		}
		
	}

	void TableScr::FixedUpdate()
	{
	}

	void TableScr::Render()
	{
	}

	void TableScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (prevDN != 1)
		{
			if (GetClosestDirection(oppo) == 1) //╩С
			{
				directionNumber = 1;
			}
			else if (GetClosestDirection(oppo) == 2)
			{
				directionNumber = 2;
			}
			else if (GetClosestDirection(oppo) == 3)
			{
				directionNumber = 3;
			}
			else if (GetClosestDirection(oppo) == 4)
			{
				directionNumber = 4;
			}
		}

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Weapone || oppo->GetOwner()->GetLayerType() == eLayerType::MonsterBullet || oppo->GetOwner()->GetName() == L"Bullat" || oppo->GetOwner()->GetName() == L"MonsterBullet")
		{
			
			tableCount -= 1;
		}
	
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			tableOn = true;
			
		}

	}

	void TableScr::OnCollision(Collider2D* oppo)
	{
		
		
	}

	void TableScr::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			tableOn = false;

		}
	}

	void TableScr::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void TableScr::OnTrigger(Collider2D* oppo)
	{
	
	}

	void TableScr::OnTriggerExit(Collider2D* oppo)
	{
		
	}

	int TableScr::GetClosestDirection(Collider2D* collider)
	{
		// Get the positions of the two colliders
		Vector3 playerPosition = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 objectPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();

		// Calculate the differences in x and y coordinates
		float dx = objectPosition.x - playerPosition.x;
		float dy = objectPosition.y - playerPosition.y;

		// Calculate the absolute differences
		float absDX = std::abs(dx);
		float absDY = std::abs(dy);

		// Determine the closest direction based on the differences
		if (absDX > absDY)
		{
			// Horizontal direction is closer
			if (dx > 0)
				return 4; // ©Л
			else
				return 2; // аб
		}
		else
		{
			// Vertical direction is closer
			if (dy > 0)
				return 3; //╩С
			else
				return 1; //го
		}
	}

}