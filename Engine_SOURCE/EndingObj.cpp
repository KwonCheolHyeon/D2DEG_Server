#include "EndingObj.h"
#include "EndingScr.h"

namespace ch 
{



	EndingObj::EndingObj()
	{
	}

	EndingObj::~EndingObj()
	{
	}

	void EndingObj::Initalize()
	{
		this->AddComponent<EndingScr>();
		GameObject::Initalize();
	}

	void EndingObj::Update()
	{
		GameObject::Update();
	}

	void EndingObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void EndingObj::Render()
	{
		GameObject::Render();
	}

}