#include "DoorObj.h"
#include "DoorScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch 
{
	bool DoorObj::isOpen = true;
	
	DoorObj::DoorObj()
	{
		SetLayerType(eLayerType::Wall);
		
		GameObject* DoorOBJ = dynamic_cast<GameObject*>(this);

		tAnimator = DoorOBJ->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_close", L"enterthe/object/door/front_close.png");
			tAnimator->Create(L"D_door_front_close", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_open", L"enterthe/object/door/front_open.png");
			tAnimator->Create(L"D_door_front_open", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_default", L"enterthe/object/door/front_default.png");
			tAnimator->Create(L"D_door_front_default", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 1, 0.1f);
		}


		{//side
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_close", L"enterthe/object/door/side_close.png");
			tAnimator->Create(L"D_door_side_close", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_open", L"enterthe/object/door/side_open.png");
			tAnimator->Create(L"D_door_side_open", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_default", L"enterthe/object/door/side_default.png");
			tAnimator->Create(L"D_door_side_default", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 1, 0.1f);
		}

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"empty", L"empty.png");
			tAnimator->Create(L"D_empty", texture, Vector2(0.0f, 0.0f), Vector2(12.0f, 102.0f), Vector2::Zero, 1, 0.1f);
		}

		tAnimator->Play(L"D_empty");

		SpriteRenderer* sprite = DoorOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


		isOpen = true;
		mainDoor = false;
		endRoom = false;
		endRoomKey = 0;
		deathCol = false;
		monsterBases.clear();

		one = true;
		two = true;
		three = true;
		four = true;
		five = true;
		six = true;

		
	}
	
	DoorObj::~DoorObj()
	{
	


	}
	void DoorObj::Initalize()
	{
		GameObject::Initalize();
	}
	void DoorObj::Update()
	{

		if (endRoom == true && endRoomKey == 1)
		{
			endRoomKey += 1;
			isOpen = true;
			
			deathCol = true;
		}

#pragma region ÁÖ¼®
		if (!monsterBases.empty())
		{
			

			bool allMonstersDead = false;
		
			if (monsterBases[0]->IsDead() && one == true)
			{
				one = false;
				doorOpenCount += 1;
			}
			if (monsterBases[1]->IsDead() && two == true)
			{
				two = false;
				doorOpenCount += 1;
			}
			if (monsterBases[2]->IsDead() && three == true)
			{
				three = false;
				doorOpenCount += 1;
			}
			if (monsterBases[3]->IsDead() && four == true)
			{
				four = false;
				doorOpenCount += 1;
			}
			if (monsterBases[4]->IsDead() && five == true)
			{
				five = false;
				doorOpenCount += 1;
			}
			if (monsterBases[5]->IsDead() && six == true)
			{
				six = false;
				doorOpenCount += 1;
			}

			if(doorOpenCount  == 6)
			{
				doorOpenCount = 0;
				allMonstersDead = true;
			
			}


			if (allMonstersDead)
			{
				endRoom = true;
				endRoomKey += 1;
			}

		}
#pragma endregion

		GameObject::Update();
	}
	void DoorObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void DoorObj::Render()
	{
		GameObject::Render();
	}
}