#include "ReloadBarScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chGameObject.h"
#include "chTime.h"
#include "chInput.h"
namespace ch 
{



	ReloadBarScr::ReloadBarScr()
	{
	}

	ReloadBarScr::~ReloadBarScr()
	{
	}

	void ReloadBarScr::Initalize()
	{

		/*SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadBarMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);*/

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		reloadOn = false;
		reloadTimer = 0.f;
	}

	void ReloadBarScr::Update()
	{
		Vector3 playerPos = player->GetComponent<Transform>()->GetPosition();
		GetOwner()->GetComponent<Transform>()->SetPosition(playerPos + Vector3(0.f,0.5f,0.f));

		if (Input::GetKeyDown(eKeyCode::R))
		{
			reloadOn = true;
		}

		if (reloadOn == true)
		{
			reloadTimer += Time::DeltaTime();


			if (reloadTimer >= 1.96f) 
			{
				reloadOn = false;
				reloadTimer = 0;
			}
			else
			{
				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadBarMaterial");
				sprite->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMesh(mesh);

			}

		}
		else 
		{
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
			sprite->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMesh(mesh);
		}
	


	}

	void ReloadBarScr::FixedUpdate()
	{
	}

	void ReloadBarScr::Render()
	{
	}

}