#include "HeartObj.h"
#include "HeartScr.h"

namespace ch 
{
	HeartObj::HeartObj()
	{
	}

	HeartObj::~HeartObj()
	{
	}

	void HeartObj::Initalize()
	{
		this->AddComponent<HeartScr>();
		GameObject::Initalize();
	}

	void HeartObj::Update()
	{
		GameObject::Update();
	}

	void HeartObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void HeartObj::Render()
	{
		GameObject::Render();
	}

}