#include "LampScr.h"
#include "chGameObject.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chTime.h"
namespace ch 
{
	LampScr::LampScr()
	{
	}

	LampScr::~LampScr()
	{
	}

	void LampScr::Initalize()
	{
		Animator* bAnimator = GetOwner()->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Light", L"enterthe/object/Light/Light.png");
			bAnimator->Create(L"L_Light", texture, Vector2(0.0f, 0.0f), Vector2(7.0f, 13.0f), Vector2::Zero, 5, 0.1f);
		}

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


		lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(0.5f, 0.5f, 0.0f, 0.1f));
		

		bAnimator->Play(L"L_Light");
		time = 0.f;
		radius = 0.3f;
	}

	void LampScr::Update()
	{
		time += Time::DeltaTime();

		if (time > 5.f) 
		{
			time = 0.f;
			radius = 0.3f;
		}
		else if (time > 2.5f && time <= 5.f) 
		{
			radius -= Time::DeltaTime();
			lightComp->SetRadius(radius);
		}
		else if (time >=0.f && time<= 2.5f) 
		{
			radius += Time::DeltaTime();
			lightComp->SetRadius(radius);
		}

		if (GetOwner()->GetName() == L"Lingh01") 
		{
			lightComp->SetDiffuse(Vector4(0.5f, 0.5f, 0.0f, 0.1f));
		}
		else if (GetOwner()->GetName() == L"Lingh02")
		{
			lightComp->SetDiffuse(Vector4(1.5f, 0.5f, 0.0f, 0.1f));
		}
		else if (GetOwner()->GetName() == L"Lingh03")
		{
			lightComp->SetDiffuse(Vector4(0.5f, 1.5f, 0.0f, 0.1f));
		}
	}

	void LampScr::FixedUpdate()
	{
	}

	void LampScr::Render()
	{
	}

}