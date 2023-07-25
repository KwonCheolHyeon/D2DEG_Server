#include "chtestBulletscr.h"
#include "chTime.h"
#include "chGameObject.h"
#include "chPlayScene.h"
#include "chSceneManager.h"
#include "chGun.h"
#include "chScene.h"
#include "chTransform.h"
#include "chInput.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chBulletScr.h"

namespace ch
{
	testBulletscr::testBulletscr()
		: Script()
		
	{
	}
	testBulletscr::~testBulletscr()
	{
	}
	void testBulletscr::Initalize()
	{
		SpriteRenderer* render = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"W_BulletMaterial");
		render->SetMaterial(bulletMaterial);
		std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(bulletMesh);

		GetOwner()->AddComponent<BulletScr>();
		GetOwner()->GetComponent<BulletScr>()->Initalize();
	}
	void testBulletscr::Update()
	{
		
	}
	void testBulletscr::FixedUpdate()
	{
	}
	void testBulletscr::Render()
	{
	}

	
}