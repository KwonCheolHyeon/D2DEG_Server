#include "LampObj.h"
#include "LampScr.h"
namespace ch 
{
	LampObj::LampObj()
	{
	}
	LampObj::~LampObj()
	{
	}
	void LampObj::Initalize()
	{
		this->AddComponent<LampScr>();
		GameObject::Initalize();
	}
	void LampObj::Update()
	{
		GameObject::Update();
	}
	void LampObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void LampObj::Render()
	{
		GameObject::Render();
	}
}