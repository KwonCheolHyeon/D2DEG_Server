#include "ReloadButtonScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chGameObject.h"
#include "chTime.h"
#include "chInput.h"
namespace ch 
{



	ReloadButtonScr::ReloadButtonScr()
	{
	}

	ReloadButtonScr::~ReloadButtonScr()
	{
	}

	void ReloadButtonScr::Initalize()
	{


		/*SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadButtonMaterial");
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

	void ReloadButtonScr::Update()
	{
		Vector3 playerPos = player->GetComponent<Transform>()->GetPosition();
		Transform* transform = GetOwner()->GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::R))
		{
			reloadOn = true;
		}

		if (reloadOn == true)
		{
			reloadTimer += Time::DeltaTime();

			if (reloadTimer >= 1.96f)
			{
				reloadTimer = 0;
				// Movement is complete, set the final position
				transform->SetPosition(playerPos + Vector3(0.44f, 0.5f, 0.f));
				reloadOn = false;

				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
				sprite->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMesh(mesh);
			}
			else
			{
				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadButtonMaterial");
				sprite->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMesh(mesh);

				// Calculate the interpolation factor (0 to 1) based on elapsed time
				float t = reloadTimer / 1.96f;

				// Interpolate between initial and final positions
				Vector3 startPosition = playerPos + Vector3(-0.44f, 0.5f, 0.f);
				Vector3 finalPosition = playerPos + Vector3(0.44f, 0.5f, 0.f);
				Vector3 interpolatedPosition = Vector3::Lerp(startPosition, finalPosition, t);

				// Set the current position based on the interpolation
				transform->SetPosition(interpolatedPosition);
			}
		}

	}

	void ReloadButtonScr::FixedUpdate()
	{
	}

	void ReloadButtonScr::Render()
	{
	}

}