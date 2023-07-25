#include "YourPlayer.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"

#include "GlobalPacket.h"
#include "ServerScene.h"

namespace ch 
{
	YourPlayer::YourPlayer()
	{
	}

	YourPlayer::~YourPlayer()
	{
	}

	void YourPlayer::Initalize()
	{
		pAnimator = GetOwner()->GetComponent<Animator>();

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
		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		pAnimator->Play(L"P_O_Idle_Front");

		player = dynamic_cast<ServerCharacterBase*>(GetOwner());

		prevIdleDirection = 7;
		prevWalkDirection = 12;
		playWalking = false;
		isOneHand = true;
		walk = false;
		dodging = false;
	}

	void YourPlayer::Update()
	{

		HandSide();

		switch (cPS)
		{
		case eServerPlayerState::eIdle:
			dodging = false;
			IdleAni();
			break;
		case eServerPlayerState::eWalk:
			if (walk == false)
			{
				walk = true;
				dodging = false;
			}
			RunAni();
			break;
		case eServerPlayerState::eRolling:
			RollingAni();
			break;
		case eServerPlayerState::eDefault:

			break;
		}


		static float PacketTime = 0.0f;
		PacketTime += Time::DeltaTime();
		if (PacketTime < 1 / 60.0f)
		{
			return;
		}

		std::shared_ptr<ObjectUpdatePacket> ObjectPtr = std::make_shared<ObjectUpdatePacket>();
		ObjectPtr->SetObjectID(GetNetObjectID());
		ObjectPtr->ObjectType = 999;
		ObjectPtr->Pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		ObjectPtr->animaNumber = SetAnimationNumber(GetOwner()->GetComponent<Animator>()->GetPlayAnimationName());// 현재 실행중인 애니메이션 이름 보냄
		ObjectPtr->isLeft = GetOwner()->isLeft();
		ServerScene::NetInst->PacketSend(ObjectPtr);

		PacketTime -= 1 / 60.0f;

	}

	void YourPlayer::Render()
	{
	}

	void YourPlayer::OnCollisionEnter(Collider2D* collider)
	{
	}

	void YourPlayer::OnCollisionStay(Collider2D* collider)
	{
	}

	void YourPlayer::OnCollisionExit(Collider2D* collider)
	{
	}

	void YourPlayer::playerLookingMouse()
	{
	}

	void YourPlayer::HandSide()
	{
		if (GetOwner()->GetComponent<YourPlayerMove>()->GetCandDodging()) {
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

		cPS = GetOwner()->GetComponent<YourPlayerMove>()->GetPS();
		CPD = player->GetPD();
	}

	void YourPlayer::MouseAndPlayerAngle()
	{
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 mousePositon = (mousePos / 100.f);

		Vector3 CharterPosition = GetOwner()->GetCenterPos();
		mousePositon += CharterPosition;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		c2mAngle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}

	void YourPlayer::SetAnimation()
	{
		int a = player->GetComponent<YourPlayerMove>()->GetPS(); // playerState
		int b = player->GetPD(); // playerDirection
		int c = player->GetComponent<YourPlayerMove>()->GetPDD();//구르기 방향

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
		else if ((a == 2 && prevWalkDirection != b) || (a == 2 && playWalking)) //걷기 상태
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

	void YourPlayer::IdleAni()
	{
		if (isOneHand)
		{
			switch (CPD)
			{
			case eServerPlayerDirections::eNorth:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Back") == false)
					pAnimator->Play(L"P_O_Idle_Back");
				break;
			case eServerPlayerDirections::eSouth:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Front") == false)
					pAnimator->Play(L"P_O_Idle_Front");
				break;
			case eServerPlayerDirections::eEast:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Right") == false)
					pAnimator->Play(L"P_O_Idle_Right");
				break;
			case eServerPlayerDirections::eWest:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_Right") == false)
					pAnimator->Play(L"P_O_Idle_Right");
				break;
			case eServerPlayerDirections::eNE:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_BackRight") == false)
					pAnimator->Play(L"P_O_Idle_BackRight");
				break;
			case eServerPlayerDirections::eNW:
				if (pAnimator->IsAnimationRunning(L"P_O_Idle_BackRight") == false)
					pAnimator->Play(L"P_O_Idle_BackRight");
				break;
			default:
				break;
			}

		}
	}

	void YourPlayer::RunAni()
	{
		if (isOneHand)
		{
			switch (CPD)
			{
			case eServerPlayerDirections::eNorth:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBack") == false)
					pAnimator->Play(L"P_O_WalkingBack");

				break;
			case eServerPlayerDirections::eSouth:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingFront") == false)
					pAnimator->Play(L"P_O_WalkingFront");

				break;
			case eServerPlayerDirections::eEast:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingRight") == false)
					pAnimator->Play(L"P_O_WalkingRight");

				break;
			case eServerPlayerDirections::eWest:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingRight") == false)
					pAnimator->Play(L"P_O_WalkingRight");

				break;
			case eServerPlayerDirections::eNE:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBackRight") == false)
					pAnimator->Play(L"P_O_WalkingBackRight");

				break;
			case eServerPlayerDirections::eNW:
				if (pAnimator->IsAnimationRunning(L"P_O_WalkingBackRight") == false)
					pAnimator->Play(L"P_O_WalkingBackRight");

				break;
			default:
				break;
			}
		}
	}

	void YourPlayer::RollingAni()
	{
		dodging = true;
		
		walk = false;
		cPDD = GetOwner()->GetComponent<YourPlayerMove>()->GetPDD();
		switch (cPDD)
		{
		case eServerPlayerDodgeDirections::eNorthDodge:
			pAnimator->Play(L"P_DodgeBack", false);
			break;
		case eServerPlayerDodgeDirections::eSouthDodge:
			pAnimator->Play(L"P_DodgeFront", false);
			break;
		case eServerPlayerDodgeDirections::eEastDodge:

			pAnimator->Play(L"P_DodgeRight", false);
			GetOwner()->SetRight();
			break;
		case eServerPlayerDodgeDirections::eWestDodge:

			pAnimator->Play(L"P_DodgeRight", false);
			GetOwner()->SetLeft();
			break;
		case eServerPlayerDodgeDirections::eNEDodge:

			pAnimator->Play(L"P_DodgeBackRight", false);
			GetOwner()->SetRight();
			break;
		case eServerPlayerDodgeDirections::eNWDodge:

			pAnimator->Play(L"P_DodgeBackRight", false);
			GetOwner()->SetLeft();
			break;
		default:
			break;
		}
	}

	void YourPlayer::ShotAni()
	{
	}

	int YourPlayer::SetAnimationNumber(const std::wstring& name)
	{
		int a = 0;
		if (name == L"P_O_Idle_Front")
		{
			a = 0;
		}
		else if (name == L"P_O_Idle_Right")
		{
			a = 1;
		}
		else if (name == L"P_O_Idle_Back")
		{
			a = 2;
		}
		else if (name == L"P_O_Idle_BackRight")
		{
			a = 3;
		}
		else if (name == L"P_O_WalkingFront") 
		{
			a = 4;
		}
		else if (name == L"P_O_WalkingRight")
		{
			a = 5;
		}
		else if (name == L"P_O_WalkingBack")
		{
			a = 6;
		}
		else if (name == L"P_O_WalkingBackRight")
		{
			a = 7;
		}
		else if (name == L"P_DodgeFront")
		{
			a = 8;
		}
		else if (name == L"P_DodgeRight")
		{
			a = 9;
		}
		else if (name == L"P_DodgeLeft")
		{
			a = 10;
		}
		else if (name == L"P_DodgeBack")
		{
			a = 11;
		}
		else if (name == L"P_DodgeBackRight")
		{
			a = 12;
		}
		else if (name == L"P_DodgeBackLeft")
		{
			a = 13;
		}
		else 
		{
			a = 0;
		}

		return a;
	}

	bool YourPlayer::isDodgeAnimationing()
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

	void YourPlayer::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&YourPlayer::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&YourPlayer::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&YourPlayer::playWalkingAin, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&YourPlayer::playWalkingAin, this);
	}

	void YourPlayer::playWalkingAin()
	{
		playWalking = true;
	}



}