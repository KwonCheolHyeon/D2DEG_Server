#include "BlackMapObj.h"
#include "BlackMapScr.h"

namespace ch 
{



	BlackMapObj::BlackMapObj()
	{
	}

	BlackMapObj::~BlackMapObj()
	{
	}

	void BlackMapObj::Initalize()
	{
		this->AddComponent<BlackMapScr>();
		GameObject::Initalize();
	}

	void BlackMapObj::Update()
	{
		GameObject::Update();
	}

	void BlackMapObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BlackMapObj::Render()
	{
		GameObject::Render();
	}

}