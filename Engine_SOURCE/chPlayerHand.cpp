#include "chPlayerHand.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chGun.h"
#include "chPlayerScr.h"
#include "chTime.h"
#include "chInput.h"


namespace ch 
{
	PlayerHand::PlayerHand()
	{
		handDistance = 0.f;
	}
	PlayerHand::~PlayerHand()
	{
	}
	void PlayerHand::Initalize()
	{
		GameObject* phand = this;

		phandTr = phand->GetComponent<Transform>();
		phandTr->SetPosition(Vector3(0.f, 0.f, -9.f));
		phandTr->SetScale(Vector3(0.1f, .1f, 1.0f));
		
		SpriteRenderer* sprite = phand->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pHandMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(mateiral);
		sprite->SetMesh(mesh);
		
		isPistol = true;
		reloadOn = false;
		GameObject::Initalize();
	}
	void PlayerHand::Update()
	{
		if (Input::GetKeyDown(eKeyCode::R))
		{
			reloadOn = true;
		}
		if (reloadOn == true) 
		{
			reloadtime += Time::DeltaTime();
			
			if (reloadtime >= 1.96f) 
			{
				reloadtime = 0;
				reloadOn = false;
			}
		}
		else 
		{
			HandLookCursor();
		}
		
		HandPosition();

		if (Input::GetKeyDown(eKeyCode::NUM_1))
		{
			SpriteRenderer* sprite = this->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pHandMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMaterial(mateiral);
			sprite->SetMesh(mesh);

			isPistol = true;
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			SpriteRenderer* sprite = this->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMaterial(mateiral);
			sprite->SetMesh(mesh);

			isPistol = false;
		}
		GameObject::Update();
	}
	void PlayerHand::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PlayerHand::Render()
	{
		GameObject::Render();
	}
	void PlayerHand::HandLookCursor()
	{
		Vector3 mousePos = Input::GetMousPosition();
		Vector3 handPosition = phandTr->GetPosition();
		Vector3 characterPos = player->GetComponent<Transform>()->GetPosition();

		Vector3 mouseRelative = (mousePos / 100.f) + characterPos;
		//mouseRelative += characterPos;
		float angle = atan2(mouseRelative.y - characterPos.y, mouseRelative.x - characterPos.x);
		// Set the rotation of the gun's hand
		float rotationZ = angle * (180.0f / XM_PI);

		phandTr->SetRotation(Vector3(180.0f, 0.0f, rotationZ));

	}


	void PlayerHand::HandPosition()
	{
		if (isPistol == true) 
		{
			Vector3 characterPosition = player->GetComponent<Transform>()->GetPosition();
			Vector3 handPosition = phandTr->GetPosition();
			if (player->GetHand())
			{
				if (player->isLeft() == true)
				{
					handPosition = characterPosition + Vector3(-0.13f, -0.16f, 0.f);
					chHandLeft = true;
				}
				else
				{
					handPosition = characterPosition + Vector3(0.13f, -0.16f, 0.f);
					chHandLeft = false;
				}
			}
			else
			{
				if (player->isLeft() == true)
				{
					handPosition = characterPosition + Vector3(-0.13f, -10.16f, 0.f);
					chHandLeft = true;
				}
				else
				{
					handPosition = characterPosition + Vector3(0.13f, -10.16f, 0.f);
					chHandLeft = false;
				}
			}

			phandTr->SetPosition(handPosition);
		
		}
		else 
		{
			Vector3 characterPosition = player->GetComponent<Transform>()->GetPosition();
			Vector3 handPosition = phandTr->GetPosition();
			if (player->GetHand())
			{
				if (player->isLeft() == true)
				{
					handPosition = characterPosition + Vector3(0.f, -0.16f, 0.f);
					chHandLeft = true;
				}
				else
				{
					handPosition = characterPosition + Vector3(0.f, -0.16f, 0.f);
					chHandLeft = false;
				}
			}
			else
			{
				if (player->isLeft() == true)
				{
					handPosition = characterPosition + Vector3(-0.13f, -10.16f, 0.f);
					chHandLeft = true;
				}
				else
				{
					handPosition = characterPosition + Vector3(-0.13f, -10.16f, 0.f);
					chHandLeft = false;
				}
			}

			phandTr->SetPosition(handPosition);
		
		}
		

		
		
		
		
	}
}
