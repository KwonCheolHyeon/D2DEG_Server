#include "chPistol.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chtestBulletscr.h"
#include "chTime.h"

namespace ch 
{
	Pistol::Pistol()
	{

	}

	Pistol::~Pistol()
	{
		int a = 0;
	}

	void Pistol::Initalize()
	{
		

		GameObject::Initalize();
		
	}

	void Pistol::Update()
	{
		

		GameObject::Update();
	}

	void Pistol::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Pistol::Render()
	{
		Gun::Render();
	}

	

	
}