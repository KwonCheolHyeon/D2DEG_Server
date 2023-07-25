#include "EndingScr.h"
#include "chAnimator.h"
#include "EndingObj.h"
#include "chResources.h"
#include "chSpriteRenderer.h"

namespace ch 
{
	EndingScr::EndingScr()
	{
	}
	EndingScr::~EndingScr()
	{
	}
	void EndingScr::Initalize()
	{
		Animator* ani = GetOwner()->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Ending", L"enterthe/Ending/ending.png");
			ani->Create(L"Ending", texture, Vector2(0.0f, 0.0f), Vector2(311.0f, 174.0f), Vector2::Zero, 8, 0.2f);
		}

		ani->Play(L"Ending");


		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
	
	}
	void EndingScr::Update()
	{
	}
	void EndingScr::FixedUpdate()
	{
	}
	void EndingScr::Render()
	{
	}
}