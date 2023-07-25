#include "chasePlayerOBJ.h"
#include "chasePlayerSCR.h"
#include "chTransform.h"
namespace ch 
{
	chasePlayerOBJ::chasePlayerOBJ()
	{
		this->AddComponent<chasePlayerSCR>();
		thisTr = GetComponent<Transform>();

	
		
	}

	chasePlayerOBJ::~chasePlayerOBJ()
	{
	}

	void chasePlayerOBJ::Initalize()
	{
		

		GameObject::Initalize();
	}

	void chasePlayerOBJ::Update()
	{
		thisTr->SetPosition(OwnerTr->GetPosition()); // 플레이어 쫒는 콜라이더 위치는 항상 해당 몬스터 고정
		

		GameObject::Update();
	}

	void chasePlayerOBJ::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void chasePlayerOBJ::Render()
	{
		GameObject::Render();
	}

}