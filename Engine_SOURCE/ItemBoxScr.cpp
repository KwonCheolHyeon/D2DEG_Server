#include "ItemBoxScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chInput.h"
#include "chObject.h"
#include "chFightSabreObject.h"
#include "FightSabreBoxScr.h"
#include "chRigidbody.h"
#include "chTransform.h"
namespace ch 
{
	ItemBoxScr::ItemBoxScr()
	{
	}
	ItemBoxScr::~ItemBoxScr()
	{
	}
	void ItemBoxScr::Initalize()
	{
		GetOwner()->SetLayerType(eLayerType::Object);
		bAnimator = GetOwner()->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"itemBox", L"enterthe/object/itemBox/itemBox.png");
			bAnimator->Create(L"D_itemBox", texture, Vector2(0.0f, 0.0f), Vector2(29.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		}
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"itemBox_open", L"enterthe/object/itemBox/itemBox_open.png");
			bAnimator->Create(L"D_itemBox_open", texture, Vector2(0.0f, 0.0f), Vector2(29.0f, 26.0f), Vector2::Zero, 3, 0.1f);
		}

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.1f, 0.1f));

		audioObj = object::Instantiate<GameObject>(eLayerType::UI);
		audioClip = Resources::Load<AudioClip>(L"chest_open", L"music\\object\\chest_open.mp3");
		boss_audio = audioObj->AddComponent<AudioSource>();
		boss_audio->SetClip(audioClip);

		bAnimator->Play(L"D_itemBox", false);
		ibs = itemBoxState::CloseBox;
		oneOpen = false;
		p2bOn = false;
		p2bOnKey = false;
	}
	void ItemBoxScr::Update()
	{
		switch (ibs)
		{
		case itemBoxState::CloseBox:
			closeBox();
			break;
		case itemBoxState::OpenBox:
			openBox();
			break;
		default:
			break;
		}

		
	}
	void ItemBoxScr::FixedUpdate()
	{
	}
	void ItemBoxScr::Render()
	{
	}
	void ItemBoxScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			//p2bOn = true;
		}

	}
	void ItemBoxScr::OnCollisionStay(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			if (Input::GetKeyDown(eKeyCode::E))
			{
				ibs = itemBoxState::OpenBox;
			}
		}

	}
	void ItemBoxScr::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			p2bOn = false;
		}
	}
	void ItemBoxScr::openBox()
	{
		if(oneOpen == false)
		{
			boss_audio->Play();
			oneOpen = true;
			bAnimator->Play(L"D_itemBox_open",false);

			Transform* tr = fightsa->GetComponent<Transform>();
			tr->SetScale(Vector3(5.f, 5.f, 0.1f));
			tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

			fightsa->GetComponent<FightSabreBoxScr>()->LifeOn();
			
		} 


	}
	void ItemBoxScr::closeBox()
	{
		if (p2bOn == true) 
		{
			p2bOn = false;
			if (Input::GetKeyDown(eKeyCode::E))
			{
				ibs = itemBoxState::OpenBox;
			}
		
		}
		

	}
}