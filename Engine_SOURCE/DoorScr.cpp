#include "DoorScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chObject.h"
namespace ch
{
	DoorScr::DoorScr()
	{
	}

	DoorScr::~DoorScr()
	{
	}

	void DoorScr::Initalize()
	{



		tAnimator = GetOwner()->GetComponent<Animator>();
		if (GetOwner()->GetName() == L"DoorFront")
		{
			tAnimator->Play(L"D_empty");
			Collider2D* col = GetOwner()->AddComponent<Collider2D>();
			col->SetName(L"DoorCollider");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.3f, 0.2f));
			col->SetCenter(Vector2(0.f, -0.97f));
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{
			tAnimator->Play(L"D_empty");
			Collider2D* col = GetOwner()->AddComponent<Collider2D>();
			col->SetName(L"DoorCollider");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.05f, 0.3f));
			col->SetCenter(Vector2(0.f, -0.8f));
		}
		else
		{
			int a = 0;
		}
		door = dynamic_cast<DoorObj*>(GetOwner());

		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI);

		audioClip[0] = Resources::Load<AudioClip>(L"gate_open", L"music\\object\\gate_open.mp3");
		audioClip[1] = Resources::Load<AudioClip>(L"gate_slam", L"music\\object\\gate_slam.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);


		doorKey = 0;

		oc = OpenClose::Defa;

		prevoc = OpenClose::Close;
		prevDoorState = false;
	}

	void DoorScr::Update()
	{
		//setState();

		switch (oc)
		{
		case OpenClose::Open:
			openDoor();
			break;
		case OpenClose::Close:
			closeDoor();
			break;
		case OpenClose::Defa:
			setState();
			break;
		default:
			break;
		}



	}

	void DoorScr::FixedUpdate()
	{
	}

	void DoorScr::Render()
	{
	}

	void DoorScr::OnCollisionEnter(Collider2D* oppo)
	{
	}

	void DoorScr::OnCollision(Collider2D* oppo)
	{
	}

	void DoorScr::OnCollisionExit(Collider2D* oppo)
	{
	}

	void DoorScr::openDoor()
	{
		if (GetOwner()->GetName() == L"DoorFront")
		{
			GetOwner()->SetLayerType(eLayerType::BackGround);
			tAnimator->Play(L"D_door_front_open", false);
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{
			GetOwner()->SetLayerType(eLayerType::BackGround);
			tAnimator->Play(L"D_door_side_open", false);
		}
		boss_audio[0]->Play();
		oc = OpenClose::Defa;
	}

	void DoorScr::closeDoor()
	{
		if (GetOwner()->GetName() == L"DoorFront")
		{

			tAnimator->Play(L"D_door_front_close", false);
			GetOwner()->SetLayerType(eLayerType::Wall);
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{

			tAnimator->Play(L"D_door_side_close", false);
			GetOwner()->SetLayerType(eLayerType::Wall);
		}
		boss_audio[1]->Play();
		oc = OpenClose::Defa;
	}

	void DoorScr::setState()
	{
		bool currentDoorState = door->GetisOpen();

		if (prevDoorState != currentDoorState)
		{
			prevDoorState = currentDoorState;

			if (currentDoorState)
			{
				oc = OpenClose::Open;
			}
			else
			{
				oc = OpenClose::Close;
			}
		}
	}

}
