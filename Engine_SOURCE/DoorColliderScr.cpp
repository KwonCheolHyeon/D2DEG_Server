#include "DoorColliderScr.h"
namespace ch
{
	DoorColliderScr::DoorColliderScr()
	{
	}
	DoorColliderScr::~DoorColliderScr()
	{
	}
	void DoorColliderScr::Initalize()
	{
		DCO = dynamic_cast<DoorColliderObj*>(GetOwner());
		doorObj = DCO->GetDoor();

		col = this->GetOwner()->GetComponent<Collider2D>();
		col->SetName(L"DoorColCollider");
		col->SetType(eColliderType::Rect);
		col->SetCenter(Vector2(0.f, 0.f));


		isInCollider = false;
	}
	void DoorColliderScr::Update()
	{



	}
	void DoorColliderScr::FixedUpdate()
	{

	}
	void DoorColliderScr::Render()
	{
	}
	void DoorColliderScr::OnCollisionEnter(Collider2D* oppo)
	{

		if (oppo->GetOwner()->GetName() == L"Player")
		{
			isInCollider = true;
		}
	}
	void DoorColliderScr::OnCollision(Collider2D* oppo)
	{


	}
	void DoorColliderScr::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			if (isInCollider == true)

			isInCollider = false;
			doorObj = DCO->GetDoor();
			doorObj->isOpenFalse(); //close
			col->SetSize(Vector2(0.f, 0.f));
			GetOwner()->Death();
		}
	}
}
