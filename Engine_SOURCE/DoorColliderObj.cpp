#include "DoorColliderObj.h"
#include "DoorColliderScr.h"
namespace ch 
{
	DoorColliderObj::DoorColliderObj()
	{
	}
	DoorColliderObj::~DoorColliderObj()
	{
	}
	void DoorColliderObj::Initalize()
	{
		tr = this->GetComponent<Transform>();
		
		if (door->GetName() == L"DoorFront")
		{
			Collider2D* col = this->AddComponent<Collider2D>();
			col->SetSize(Vector2(1.f, 0.4f));
			col->SetName(L"DoorColCollider");
			col->SetType(eColliderType::Rect);
			col->SetCenter(Vector2(0.f, 0.f));
		}
		else if (door->GetName() == L"DoorSide")
		{
			Collider2D* col = this->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.4f, 1.f));
			col->SetName(L"DoorColCollider");
			col->SetType(eColliderType::Rect);
			col->SetCenter(Vector2(0.f, 0.f));
		}
		this->AddComponent<DoorColliderScr>();

		isMain = false;
		isMainKey = 1;
		GameObject::Initalize();
	}
	void DoorColliderObj::Update()
	{
		
		Vector3 OwnerPosition = door->GetComponent<Transform>()->GetPosition();

		if (door->GetName() == L"DoorFront") 
		{
			tr->SetPosition(OwnerPosition - Vector3(0.f, 1.f, 0.f));
		}
		else if (door->GetName() == L"DoorSide")
		{
			tr->SetPosition(OwnerPosition - Vector3(0.f, 0.8f, 0.f));
		} 

		GameObject::Update();
	}
	void DoorColliderObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void DoorColliderObj::Render()
	{
		GameObject::Render();
	}
}

