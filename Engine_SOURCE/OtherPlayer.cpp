#include "OtherPlayer.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"

#include "PacketEnum.h"
#include "GlobalPacket.h"

namespace ch
{
	OtherPlayer::OtherPlayer()
		: Script()
	{
	}

	OtherPlayer::~OtherPlayer()
	{
	}

	void OtherPlayer::Initalize()
	{

		Animator* pAnimator = GetOwner()->AddComponent<Animator>();

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

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		pAnimator->Play(L"P_O_Idle_Front");
		
	}

	void OtherPlayer::Update()
	{
		
		if (0 == Packets.size())
		{
			return;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* anu = GetOwner()->GetComponent<Animator>();
		
		while (0 != Packets.size())
		{
			std::shared_ptr<GameNetPacket> Packet = Packets.front();

			PacketEnumType Type = Packet->GetPacketIDToEnum<PacketEnumType>();

			switch (Type)
			{
			case PacketEnumType::ObjectUpdatePacket:
			{
				std::shared_ptr<ObjectUpdatePacket> ObjectPacket = Packet->DynamicConvert<ObjectUpdatePacket>();
				tr->SetPosition(ObjectPacket->Pos);
				if (anu->IsAnimationRunning(GetAnimationName(ObjectPacket->animaNumber)) == false) 
				{
					anu->Play(GetAnimationName(ObjectPacket->animaNumber), true);
				}
				if (ObjectPacket->isLeft == true)
				{
					GetOwner()->SetLeft();
				}
				else 
				{
					GetOwner()->SetRight();
				}

				break;
			}
			default:
				break;
			}

			Packets.pop_front();
			
		}



		int a = 0;

	}

	void OtherPlayer::Render()
	{
	}

	void OtherPlayer::OnCollisionEnter(Collider2D* collider)
	{
	}

	void OtherPlayer::OnCollisionStay(Collider2D* collider)
	{
	}

	void OtherPlayer::OnCollisionExit(Collider2D* collider)
	{
	}

	void OtherPlayer::Start()
	{
	}

	void OtherPlayer::Action()
	{
	}

	void OtherPlayer::End()
	{
	}

	std::wstring OtherPlayer::GetAnimationName(int a)
	{
		std::wstring name = L"";
		if (a == 0)
		{
			name = L"P_O_Idle_Front";
		}
		else if (a==1)
		{
			name = L"P_O_Idle_Right";
		}
		else if (a==2)
		{
			name = L"P_O_Idle_Back";
		}
		else if (a==3)
		{
			name = L"P_O_Idle_BackRight";
		}
		else if (a==4)
		{
			name = L"P_O_WalkingFront";
		}
		else if (a==5)
		{
			name = L"P_O_WalkingRight";
		}
		else if (a==6)
		{
			name = L"P_O_WalkingBack";
		}
		else if (a==7)
		{
			name = L"P_O_WalkingBackRight";
		}
		else if (a==8)
		{
			name = L"P_DodgeFront";
		}
		else if (a==9)
		{
			name = L"P_DodgeRight";
		}
		else if (a==10)
		{
			name = L"P_DodgeLeft";
		}
		else if (a==11)
		{
			name = L"P_DodgeBack";
		}
		else if (a==12)
		{
			name = L"P_DodgeBackRight";
		}
		else if (a==13)
		{
			name = L"P_DodgeBackLeft";
		}
		else
		{
			name = L"P_O_Idle_Front";
		}

		return name;
	}

	

}
