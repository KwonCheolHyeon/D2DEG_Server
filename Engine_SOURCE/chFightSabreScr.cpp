#include "chFightSabreScr.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chPlayScene.h"
#include "chObject.h"
#include "chSpriteRenderer.h"
#include "chAnimation.h"
#include "chResources.h"
#include "chInput.h"
#include "FightSabreBullet.h"
#include "FightSabreBulletScr.h"
#include "chTime.h"
namespace ch 
{
	FightSabreScr::FightSabreScr()
	{
	}

	FightSabreScr::~FightSabreScr()
	{
	}

	void FightSabreScr::Initalize()
	{
		gunObj = dynamic_cast<Gun*>(GetOwner());


		gunTransform = gunObj->GetComponent<Transform>();
		
		gunTransform->SetParent(playerHand->GetComponent<Transform>());
		gunTransform->SetInheritParentScale(false);

		Vector3 gunPosition = gunTransform->GetPosition();
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		gunTransform->SetPosition(gunPosition);

		SpriteRenderer* sprite = gunObj->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

#pragma region 애니메이터
		anima = gunObj->GetComponent<Animator>();

		{//기본
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Idle", L"enterthe/Waepone/FightSabre/idle/idle.png");
			anima->Create(L"W_FightSabre_Idle", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.5f);
		}
		{//총쏘기
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_shot", L"enterthe/Waepone/FightSabre/shot/shot.png");
			anima->Create(L"W_FightSabre_shot", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.3f);
		}
		{//장전
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_reload", L"enterthe/Waepone/FightSabre/reload.png");
			anima->Create(L"W_FightSabre_reload", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 41.0f), Vector2::Zero, 14, 0.14f);
		}
		{//아이템
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Item", L"enterthe/Waepone/FightSabre/Item.png");
			anima->Create(L"W_FightSabre_Item", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}
		{//투명
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_empty", L"empty.png");
			anima->Create(L"W_FightSabre_empty", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}

		 
#pragma endregion

		
		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI);

		audioClip[0] = Resources::Load<AudioClip>(L"magnum_reload", L"music\\gun\\magnum_reload.mp3");
		audioClip[1] = Resources::Load<AudioClip>(L"magnum_shot01", L"music\\gun\\magnum_shot01.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);

		col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.f, 0.f));
		col->SetCenter(Vector2(0.f, 0.f));
		

		fss = FightSabreState::SabreItemBox;
		prevFss = FightSabreState::SabrenonActive;
		touchGun = false;
		prevTouchGun = true;
	}

	void FightSabreScr::Update()
	{

		switch (fss)
		{
		case FightSabreState::SabreItemBox:
			ItemBox();
			break;
		case FightSabreState::SabreActive:
			Active();
			break;
		case FightSabreState::SabrenonActive:
			nonActiveGun();
			break;
		case FightSabreState::SabreReload:
			Reload();
			break;
		case FightSabreState::SabreShot:
			Shot();
			break;
		default:
			break;
		}
	

	}

	void FightSabreScr::FixedUpdate()
	{
	}

	void FightSabreScr::Render()
	{


	}

	void FightSabreScr::ItemBox()//아이템 박스에 튀어나와서 플레이어가 줍기전
	{
		
		
	}

	void FightSabreScr::Active() // 기본 들고 있을때 
	{
		if (prevFss != fss) 
		{
			gunTransform->SetScale(Vector3(6.f, 5.f, 1.0f));
			prevFss = fss;
			anima->Play(L"W_FightSabre_Idle", true);
		}
		angleFind();
		GunLookCursor();

		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			fss = FightSabreState::SabreShot;
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			fss = FightSabreState::SabreReload;
		}

	}

	void FightSabreScr::nonActiveGun() // 피스톨과 스왑했을때
	{
		prevFss = fss;
		

	}
	
	void FightSabreScr::Reload() // 장전
	{
		prevFss = fss;
		reloadTime += Time::DeltaTime();
		
	
		if (anima->IsAnimationRunning(L"W_FightSabre_reload") == false)
		{
			anima->Play(L"W_FightSabre_reload", false);
			audioObj[0]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
			boss_audio[0]->Play();
		}
		if (reloadTime >= 1.96f) 
		{
			
			reloadTime = 0;
			fss = FightSabreState::SabreActive;
		}


	}

	void FightSabreScr::Shot() //쏠때
	{
		prevFss = fss;
		
		audioObj[1]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		boss_audio[1]->Play();

		if (anima->IsAnimationRunning(L"W_FightSabre_shot") == false)
		{
			anima->Play(L"W_FightSabre_shot", false);
		}
		

		FightSabreBullet* bullet = object::Instantiate<FightSabreBullet>(eLayerType::Weapone);
		FightSabreBulletScr* scr = bullet->AddComponent<FightSabreBulletScr>();
		scr->Initalize();
		scr->shootingBullet(angle, playerHand->GetComponent<Transform>()->GetPosition());

		fss = FightSabreState::SabreActive;
	}

	void FightSabreScr::angleFind()
	{
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 characterPos = playerHand->GetComponent<Transform>()->GetPosition();

		Vector3 mouseRelative = (mousePos / 100.f);
		mouseRelative += characterPos;

		// Calculate the angle between the mouse cursor position and the character position
		float angle2 = atan2(mouseRelative.y - characterPos.y, mouseRelative.x - characterPos.x);

		float rotationZ = angle2 * (180.0f / XM_PI);

		angle = rotationZ;
	}

	void FightSabreScr::GunLookCursor()
	{

		if (playerHand->IsHandLeft()) //왼손
		{
			gunTransform->SetScale(Vector3(4.28f, 4.23f, 1.0f));
			gunObj->SetLeft();
			gunObj->SetRotation(Vector3(0.0f, 0.f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(-0.85f, -0.9f, 0.f));
		}
		else //오른손
		{
			gunTransform->SetScale(Vector3(4.28f, 4.23f, 1.0f));
			gunObj->SetLeft();
			gunObj->SetRotation(Vector3(180.0f, 0.0f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(-0.85f, -1.1f, 0.f));
		}
	}

	

}