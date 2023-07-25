#include "chPlayerScript.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chAnimator.h"
#include "GlobalPacket.h"
#include "ServerScene.h"

namespace ch
{
	PlayerScript::PlayerScript()
		: Script()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();



		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x += 60.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x -= 60.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 60.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 60.0f * Time::DeltaTime();
			tr->SetPosition(pos);
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
		ObjectPtr->Pos = tr->GetPosition();

		ServerScene::NetInst->PacketSend(ObjectPtr);

		PacketTime -= 1 / 60.0f;

		// 움직임이 끝났을때
	}

	void PlayerScript::Render()
	{
		std::wstring strTest = L"화살표 - 플레이어 이동(X,Y)\nWASD - 카메라 이동(X,Z)";
		Color testColor;
		testColor.R(255.f);
		testColor.G(255.f);
		testColor.B(255.f);
		testColor.A(255.f);
		const wchar_t* result = strTest.c_str();

	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		int a = 0;
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
	}

}
