#include "BlankBullet_UI.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chGameObject.h"

namespace ch 
{
	BlankBullet_UI::BlankBullet_UI()
	{
	}
	BlankBullet_UI::~BlankBullet_UI()
	{
	}
	void BlankBullet_UI::Initalize()
	{


		sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"Blank_bulletsMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(bodyMateiral);
		sprite->SetMesh(mesh);

		

	}
	void BlankBullet_UI::Update()
	{
		if (on == true) 
		{
		
			sprite = GetOwner()->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"Blank_bulletsMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMaterial(bodyMateiral);
			sprite->SetMesh(mesh);
		}
		else 
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
			sprite->SetMaterial(mateiral);
		}


	}
	void BlankBullet_UI::FixedUpdate()
	{
	}
	void BlankBullet_UI::Render()
	{
	}
	
}