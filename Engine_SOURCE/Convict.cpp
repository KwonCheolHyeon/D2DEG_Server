#include "Convict.h"
#include "CharacterBase.h"
#include "ConvictMove.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chInput.h"
#include "Heart_Scr.h"
#include "BlankBullet_UI.h"
#include "chAudioListener.h"
#include "chObject.h"
namespace ch
{
	Convict::Convict()
	{
			
	}

	Convict::~Convict()
	{
	}

	void Convict::Initalize()
	{
		pTr = GetOwner()->GetComponent<Transform>();
		pAnimator = GetOwner()->GetComponent<Animator>();
		pCollider = GetOwner()->GetComponent<Collider2D>();
		pCollider->SetName(L"PlayerCollider");
#pragma region Animator
		#pragma region 한손무기
		#pragma region 기본 상태
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleFront", L"enterthe/character/weap/Idle/WIdleFront.png");
			pAnimator->Create(L"P_O_Idle_Front", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleRight", L"enterthe/character/weap/Idle/WIdleRight.png");
			pAnimator->Create(L"P_O_Idle_Right", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
			//이미지 편집 변경필요
		}
		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBack", L"enterthe/character/weap/Idle/WIdleBack.png");
			pAnimator->Create(L"P_O_Idle_Back", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBackRight", L"enterthe/character/weap/Idle/WIdleBackRight.png");
			pAnimator->Create(L"P_O_Idle_BackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
	#pragma endregion
		#pragma region 걷기
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingFront", L"enterthe/character/weap/Walking/WWalkingFront.png");
			pAnimator->Create(L"P_O_WalkingFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingRight", L"enterthe/character/weap/Walking/WWalkingRight.png");
			pAnimator->Create(L"P_O_WalkingRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBack", L"enterthe/character/weap/Walking/WWalkingBack.png");
			pAnimator->Create(L"P_O_WalkingBack", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBackRight", L"enterthe/character/weap/Walking/WWalkingBackRight.png");
			pAnimator->Create(L"P_O_WalkingBackRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
	#pragma endregion
		#pragma region 구르기
		{//dodge
			{ // 정면
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeFront", L"enterthe/character/dodge/dodgeFront.png");
				pAnimator->Create(L"P_DodgeFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 24.0f), Vector2::Zero, 9, 0.11f);
			}
			{//우측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeRight", L"enterthe/character/dodge/dodgeRight.png");
				pAnimator->Create(L"P_DodgeRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}
			{ // 좌측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeLeft", L"enterthe/character/dodge/dodgeLeft.png");
				pAnimator->Create(L"P_DodgeLeft", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}

			{ //뒤
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBack", L"enterthe/character/dodge/dodgeBack.png");
				pAnimator->Create(L"P_DodgeBack", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 24.0f), Vector2::Zero, 9, 0.11f);
			}

			{//뒤 우측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackRight", L"enterthe/character/dodge/dodgeBackRight.png");
				pAnimator->Create(L"P_DodgeBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}

			{ // 뒤 좌측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackLeft", L"enterthe/character/dodge/dodgeBackLeft.png");
				pAnimator->Create(L"P_DodgeBackLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}
		}

	#pragma endregion
		#pragma endregion
		#pragma region 두손무기

		#pragma region 기본 상태
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleFront", L"enterthe/characterTwoHand/Idle/twohand_Idle_Front.png");
			pAnimator->Create(L"PT_IdleFront", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}

		{//오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleRight", L"enterthe/characterTwoHand/Idle/twohand_Idle_Right.png");
			pAnimator->Create(L"PT_IdleRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}

		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleBack", L"enterthe/characterTwoHand/Idle/twohand_Idle_Back.png");
			pAnimator->Create(L"PT_IdleBack", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleBackRight", L"enterthe/characterTwoHand/Idle/twohand_Idle_BackRight.png");
			pAnimator->Create(L"PT_IdleBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		#pragma endregion

		#pragma region 걷기
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkFront", L"enterthe/characterTwoHand/Walking/twohand_Walk_Front.png");
			pAnimator->Create(L"PT_WalkFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}

		{//오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkRight", L"enterthe/characterTwoHand/Walking/twohand_Walk_Right.png");
			pAnimator->Create(L"PT_WalkRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}

		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkBack", L"enterthe/characterTwoHand/Walking/twohand_Walk_Back.png");
			pAnimator->Create(L"PT_WalkBack", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}
		{//뒤 오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkBackRight", L"enterthe/characterTwoHand/Walking/twohand_Walk_BackRight.png");
			pAnimator->Create(L"PT_WalkBackRight", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}
		#pragma endregion
	
	#pragma endregion
#pragma endregion

		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[2] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[3] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[4] = object::Instantiate<GameObject>(eLayerType::UI);
		
		audioClip[0] = Resources::Load<AudioClip>(L"convict_leap", L"music\\player\\convict_leap.mp3");
		audioClip[1] = Resources::Load<AudioClip>(L"convict_roll", L"music\\player\\convict_roll.mp3");
		audioClip[2] = Resources::Load<AudioClip>(L"step", L"music\\player\\step.mp3");
		audioClip[3] = Resources::Load<AudioClip>(L"blank", L"music\\player\\blank.mp3");
		audioClip[4] = Resources::Load<AudioClip>(L"item_pickup2", L"music\\player\\item_pickup.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();
		boss_audio[2] = audioObj[2]->AddComponent<AudioSource>();
		boss_audio[3] = audioObj[3]->AddComponent<AudioSource>();
		boss_audio[4] = audioObj[4]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);
		boss_audio[2]->SetClip(audioClip[2]);
		boss_audio[3]->SetClip(audioClip[3]);
		boss_audio[4]->SetClip(audioClip[4]);


		player = dynamic_cast<CharacterBase*>(GetOwner());
		
		
		pAnimator->Play(L"P_O_Idle_Front");
		prevIdleDirection = 7;
		prevWalkDirection = 12;
		pHp = 6;
		prevHp = 5;
		playWalking = false;
		isOneHand = true;

		pBB = 2;
		prevBB = 0;

		walk = false;

		dodging = false;
	}

	void Convict::Update()
	{
	
		HandSide();
		
		switch (cPS)
		{
		case PlayerState::Idle:
			dodging = false;
			IdleAni();
			break;
		case PlayerState::Walk:
			if (walk == false) 
			{
				walk = true;
				audioObj[2]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
				boss_audio[2]->SetLoop(true);
				boss_audio[2]->Play();
				dodging = false;
			}
			RunAni();
			break;
		case PlayerState::Rolling:
			RollingAni();
			break;
		case PlayerState::Default:

			break;
		}
		
		if (prevHp != pHp)
		{
			if (pHp > 6) 
			{
				pHp = 6;
			}
			if (pHp < 0) 
			{
				pHp = 0;
			}
			SetHeart();
		}
		if (prevBB != pBB) 
		{
			SetBlankBullet();
		}

		if (Input::GetKeyDown(eKeyCode::NUM_1))
		{
			isOneHand = true;
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			isOneHand = false;
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			audioObj[3]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
			boss_audio[3]->Play();
			pBB -= 1;
			cbb->onBlankBulletEffect();
			GetOwner()->getCameraScr()->strongEffectOn();
		}
		if (Input::GetKeyDown(eKeyCode::H))
		{
			pHp += 1;
			pBB += 1;
		}
		
	}

	void Convict::FixedUpdate()
	{
	}

	void Convict::Render()
	{
	}

	void Convict::OnCollisionEnter(Collider2D* oppo)
	{
		eLayerType type = oppo->GetOwner()->GetLayerType();

		
		if (oppo->GetOwner()->GetName() == L"Bullat"|| oppo->GetOwner()->GetName() == L"MonsterBullet") 
		{
			if (dodging == true)
			{
			
			}
			else
			{
				pHp -= 1;
				GetOwner()->getCameraScr()->weakEffectOn();
			}
			
		}
	

	}

	void Convict::OnCollisionStay(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"heartObj")
		{
			if (Input::GetKeyDown(eKeyCode::E))
			{
				audioObj[4]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
				boss_audio[4]->Play();
				oppo->GetOwner()->Death();
				pHp += 1;
			}
		}
		if (oppo->GetOwner()->GetName() == L"BlankBulletObj")
		{
			if (Input::GetKeyDown(eKeyCode::E))
			{
				audioObj[4]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
				boss_audio[4]->Play();
				oppo->GetOwner()->Death();
				pBB += 1;
			}
		}
		if (oppo->GetName() == L"FightSabreCol")
		{
			if (Input::GetKeyDown(eKeyCode::E))
			{
				audioObj[4]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
				boss_audio[4]->Play();
				oppo->GetOwner()->Death();
			}
		}
	}

	void Convict::OnCollisionExit(Collider2D* oppo)
	{
	}

	#pragma region 충돌 관련
	
#pragma endregion


	void Convict::playerLookingMouse()
	{
		
	}

	void Convict::HandSide()
	{
		if (GetOwner()->GetComponent<ConvictMove>()->GetCandDodging()) {
			MouseAndPlayerAngle();
			if (c2mAngle >= 90 && c2mAngle < 270) //총 위치 왼쪽 //왼쪽 보기
			{
				GetOwner()->SetLeft();
			}
			else  //총 위치 오른쪽 // 오른쪽 보기
			{
				GetOwner()->SetRight();
			}
		}

		cPS = GetOwner()->GetComponent<ConvictMove>()->GetPS();
		CPD = player->GetPD();
		
	}

	void Convict::MouseAndPlayerAngle()
	{
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 mousePositon = (mousePos / 100.f);

		Vector3 CharterPosition = GetOwner()->GetCenterPos();
		mousePositon += CharterPosition;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		c2mAngle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}

	void Convict::SetAnimation()
	{
		int a = player->GetComponent<ConvictMove>()->GetPS(); // playerState
		int b = player->GetPD(); // playerDirection
		int c = player->GetComponent<ConvictMove>()->GetPDD();//구르기 방향

			if (a == 1 && prevIdleDirection != b) //기본상태
			{
				if (b == 1)
				{
					pAnimator->Play(L"P_O_Idle_Back");
				}
				else if (b == 2)
				{
					pAnimator->Play(L"P_O_Idle_Front");
				}
				else if (b == 3)
				{
					pAnimator->Play(L"P_O_Idle_Right");
				}
				else if (b == 4)
				{
					pAnimator->Play(L"P_O_Idle_Right");
				}
				else if (b == 5)
				{
					pAnimator->Play(L"P_O_Idle_BackRight");
				}
				else if (b == 6)
				{
					pAnimator->Play(L"P_O_Idle_BackRight");
				}
				prevIdleDirection = b;
				prevWalkDirection = 0;
			}
			else if ((a == 2 && prevWalkDirection != b) || (a == 2 && playWalking )) //걷기 상태
			{
				if (b == 1)
				{
					pAnimator->Play(L"P_O_WalkingBack");
				}
				else if (b == 2)
				{
					pAnimator->Play(L"P_O_WalkingFront");
				}
				else if (b == 3)
				{
					pAnimator->Play(L"P_O_WalkingRight");
				}
				else if (b == 4)
				{
					pAnimator->Play(L"P_O_WalkingRight");
				}
				else if (b == 5)
				{
					pAnimator->Play(L"P_O_WalkingBackRight");
				}
				else if (b == 6)
				{
					pAnimator->Play(L"P_O_WalkingBackRight");
				}
				prevWalkDirection = b;
				prevIdleDirection = 0;
				playWalking = false;
			}
			else if (a == 3 && isDodgeAnimationing() == false) //닷지 상태
			{
				if (c == 1)
				{
					pAnimator->Play(L"P_DodgeBack", false);
				}
				else if (c == 2)
				{
					pAnimator->Play(L"P_DodgeFront", false);
				}
				else if (c == 3)
				{
					GetOwner()->SetRight();
					pAnimator->Play(L"P_DodgeRight", false);
				}
				else if (c == 4)
				{
					GetOwner()->SetLeft();
					pAnimator->Play(L"P_DodgeRight", false);
				}
				else if (c == 5)
				{
					GetOwner()->SetRight();
					pAnimator->Play(L"P_DodgeBackRight", false);
				}
				else if (c == 6)
				{
					GetOwner()->SetLeft();
					pAnimator->Play(L"P_DodgeBackRight", false);
				}
				c = 7;
			}
		
	}

	void Convict::IdleAni()
	{
		boss_audio[2]->Stop();
		walk = false;
		if (isOneHand) 
		{
			switch (CPD)
			{
			case PlayerDirections::North:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Back") == false)
					pAnimator->Play(L"P_O_Idle_Back");
				break;
			case PlayerDirections::South:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Front") == false)
					pAnimator->Play(L"P_O_Idle_Front");
				break;
			case PlayerDirections::East:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Right") == false)
					pAnimator->Play(L"P_O_Idle_Right");
				break;
			case PlayerDirections::West:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Right") == false)
					pAnimator->Play(L"P_O_Idle_Right");
				break;
			case PlayerDirections::NE:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_BackRight") == false)
					pAnimator->Play(L"P_O_Idle_BackRight");
				break;
			case PlayerDirections::NW:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_BackRight") == false)
					pAnimator->Play(L"P_O_Idle_BackRight");
				break;
			default:
				break;
			}
		
		}
		else 
		{
			switch (CPD)
			{
			case PlayerDirections::North:
				if (pAnimator->IsAnimationRunning(L"PT_IdleBack") == false)
					pAnimator->Play(L"PT_IdleBack");
				break;
			case PlayerDirections::South:
				if (pAnimator->IsAnimationRunning(L"PT_IdleFront") == false)
					pAnimator->Play(L"PT_IdleFront");
				break;
			case PlayerDirections::East:
				if (pAnimator->IsAnimationRunning(L"PT_IdleRight") == false)
					pAnimator->Play(L"PT_IdleRight");
				break;
			case PlayerDirections::West:
				if (pAnimator->IsAnimationRunning(L"PT_IdleRight") == false)
					pAnimator->Play(L"PT_IdleRight");
				break;
			case PlayerDirections::NE:
				if (pAnimator->IsAnimationRunning(L"PT_IdleBackRight") == false)
					pAnimator->Play(L"PT_IdleBackRight");
				break;
			case PlayerDirections::NW:
				if (pAnimator->IsAnimationRunning(L"PT_IdleBackRight") == false)
					pAnimator->Play(L"PT_IdleBackRight");
				break;
			default:
				break;
			}
		
		}
		

	}

	void Convict::RunAni()
	{
		if (isOneHand)
		{
			switch (CPD)
			{
			case PlayerDirections::North:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBack") == false)
					pAnimator->Play(L"P_O_WalkingBack");
					
				break;
			case PlayerDirections::South:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingFront") == false)
					pAnimator->Play(L"P_O_WalkingFront");
					
				break;
			case PlayerDirections::East:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingRight") == false)
					pAnimator->Play(L"P_O_WalkingRight");
					
				break;
			case PlayerDirections::West:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingRight") == false)
					pAnimator->Play(L"P_O_WalkingRight");
					
				break;
			case PlayerDirections::NE:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBackRight") == false)
					pAnimator->Play(L"P_O_WalkingBackRight");
					
				break;
			case PlayerDirections::NW:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBackRight") == false)
					pAnimator->Play(L"P_O_WalkingBackRight");
					
				break;
			default:
				break;
			}
		}
		else 
		{
		
			switch (CPD)
			{
			case PlayerDirections::North:
				if (pAnimator->IsAnimationRunning(L"PT_WalkBack") == false)
					pAnimator->Play(L"PT_WalkBack");
				break;
			case PlayerDirections::South:
				if (pAnimator->IsAnimationRunning(L"PT_WalkFront") == false)
					pAnimator->Play(L"PT_WalkFront");
				break;
			case PlayerDirections::East:
				if (pAnimator->IsAnimationRunning(L"PT_WalkRight") == false)
					pAnimator->Play(L"PT_WalkRight");
				break;
			case PlayerDirections::West:
				if (pAnimator->IsAnimationRunning(L"PT_WalkRight") == false)
					pAnimator->Play(L"PT_WalkRight");
				break;
			case PlayerDirections::NE:
				if (pAnimator->IsAnimationRunning(L"PT_WalkBackRight") == false)
					pAnimator->Play(L"PT_WalkBackRight");
				break;
			case PlayerDirections::NW:
				if (pAnimator->IsAnimationRunning(L"PT_WalkBackRight") == false)
					pAnimator->Play(L"PT_WalkBackRight");
				break;
			default:
				break;
			}
		}
	}

	void Convict::RollingAni()
	{
		dodging = true; 
		boss_audio[2]->Stop();
		walk = false;
		audioObj[0]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		boss_audio[0]->Play();
		cPDD = GetOwner()->GetComponent<ConvictMove>()->GetPDD();
		switch (cPDD)
		{
		case PlayerDodgeDirections::NorthDodge:
			pAnimator->Play(L"P_DodgeBack", false);
			break;
		case PlayerDodgeDirections::SouthDodge:
			pAnimator->Play(L"P_DodgeFront", false);
			break;
		case PlayerDodgeDirections::EastDodge: 
			
			pAnimator->Play(L"P_DodgeRight", false);
			GetOwner()->SetRight();
			break;
		case PlayerDodgeDirections::WestDodge:
			
			pAnimator->Play(L"P_DodgeRight", false);
			GetOwner()->SetLeft();
			break;
		case PlayerDodgeDirections::NEDodge:
			
			pAnimator->Play(L"P_DodgeBackRight", false);
			GetOwner()->SetRight();
			break;
		case PlayerDodgeDirections::NWDodge:
			
			pAnimator->Play(L"P_DodgeBackRight", false);
			GetOwner()->SetLeft();
			break;
		default:
			break;
		}
	}

	void Convict::ShotAni()
	{
	}

	bool Convict::isDodgeAnimationing()
	{
		// Check if any of the dodge animations are running
		if (pAnimator->IsAnimationRunning(L"P_DodgeBack") ||
			pAnimator->IsAnimationRunning(L"P_DodgeFront") ||
			pAnimator->IsAnimationRunning(L"P_DodgeRight") ||
			pAnimator->IsAnimationRunning(L"P_DodgeBackRight"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Convict::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&Convict::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&Convict::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&Convict::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&Convict::playWalkingAin, this);
	
	}

	void Convict::playWalkingAin()
	{
		playWalking = true;
	}

	void Convict::SetHeart()
	{
		if (pHeartControl.size() != 0) //왜 두번 되는거지?
		{
			prevHp = pHp;

			if (pHp >= 6) 
			{
				pHp = 6;
			}
			if (pHp == 6)
			{
			
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 5)
			{
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(1);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 4)
			{
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(0);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 3)
			{
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(1);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 2)
			{
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(0);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 1)
			{
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(1);
			}
			else if (pHp == 0)
			{
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(0);
			}
			else 
			{
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(0);
			}
		}
	}

	void Convict::SetBlankBullet()
	{
		if (pBlankBullet.size() != 0)
		{
			prevBB = pBB;
			if (pBB <= 0)
			{
				pBB = 0;
				prevBB = 10;
			}
			if (pBB >= 4) 
			{
				pBB = 4;
			}
		
		
			if (pBB == 4)
			{
				pBlankBullet[3]->GetComponent<BlankBullet_UI>()->onBlankBullet();

			}
			else if (pBB == 3)
			{

				pBlankBullet[3]->GetComponent<BlankBullet_UI>()->offBlankBullet();
				pBlankBullet[2]->GetComponent<BlankBullet_UI>()->onBlankBullet();
				pBlankBullet[1]->GetComponent<BlankBullet_UI>()->onBlankBullet();
				pBlankBullet[0]->GetComponent<BlankBullet_UI>()->onBlankBullet();
			}
			else if (pBB == 2)
			{
				pBlankBullet[3]->GetComponent<BlankBullet_UI>()->offBlankBullet();
				pBlankBullet[2]->GetComponent<BlankBullet_UI>()->offBlankBullet();
				pBlankBullet[1]->GetComponent<BlankBullet_UI>()->onBlankBullet();
				pBlankBullet[0]->GetComponent<BlankBullet_UI>()->onBlankBullet();
			}
			else if (pBB == 1)
			{
				pBlankBullet[1]->GetComponent<BlankBullet_UI>()->offBlankBullet();
				pBlankBullet[0]->GetComponent<BlankBullet_UI>()->onBlankBullet();
			}
			else if (pBB == 0)
			{
				pBlankBullet[0]->GetComponent<BlankBullet_UI>()->offBlankBullet();
			}

		}
	}
	
}