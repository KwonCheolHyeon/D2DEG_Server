#include "BoosDoorScr.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chObject.h"
namespace ch 
{

	BoosDoorScr::BoosDoorScr()
	{
	}

	BoosDoorScr::~BoosDoorScr()
	{
	}

	void BoosDoorScr::Initalize()
	{
		col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.5f, 0.5f));
	
		anima = GetOwner()->AddComponent<Animator>();
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BossDoor", L"enterthe/object/door/BossDoor.png");
			anima->Create(L"m_BossDoor", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 48.0f), Vector2::Zero, 1, 0.1f);
		}

		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BossDoorOpen", L"enterthe/object/door/BossDoorOpen.png");
			anima->Create(L"m_BossDoorOpen", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 48.0f), Vector2::Zero, 1, 0.1f);
		}

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"EmptyMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		Transform* mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetScale(Vector3(5.5f, 5.5f, 0.1f));
		mTr->SetPosition(Vector3(15.27f, 12.513f, -1.f));

		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(0.0f, 0.0f, 0.0f, 1.0f));

		audioObj = object::Instantiate<GameObject>(eLayerType::UI);
		audioClip = Resources::Load<AudioClip>(L"bossdoor_open", L"music\\object\\bossdoor_open.mp3");
		audio = audioObj->AddComponent<AudioSource>();
		audio->SetClip(audioClip);

		anima->Play(L"m_BossDoor");
		doorOn = false;
		doorSound = false;
	}

	void BoosDoorScr::Update()
	{
		anima->Play(L"m_BossDoor");

		if (doorOn == true) 
		{
			timer += Time::DeltaTime();
			Transform* mTr = GetOwner()->GetComponent<Transform>();
			Vector3 a = mTr->GetPosition();
			if (doorSound == false) 
			{
				doorSound = true;
				audio->Play();
			}
		
			if (timer >= 1.f) 
			{
				anima->Play(L"m_BossDoorOpen");
				Light* lightComp = GetOwner()->GetComponent<Light>();
				lightComp->SetType(eLightType::Point);
				lightComp->SetRadius(2.5f);
				lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			else
			{
				// Calculate the y-axis increment for each frame
				float yIncrement = 1.f / 1.f * Time::DeltaTime();
				// Update the position of the door
				Vector3 newPosition = a + Vector3(0.0f, yIncrement, -10.0f);
				mTr->SetPosition(newPosition);
			}
		}

	}

	void BoosDoorScr::FixedUpdate()
	{
	}

	void BoosDoorScr::Render()
	{
	}

	void BoosDoorScr::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player) 
		{
			doorOn = true;
			collider->GetOwner()->getCameraScr()->vecrstrongEffectOn();
			col->SetCenter(Vector2(1000.f, 1000.f));
		}
	}

	void BoosDoorScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void BoosDoorScr::OnCollisionExit(Collider2D* collider)
	{
	}

}