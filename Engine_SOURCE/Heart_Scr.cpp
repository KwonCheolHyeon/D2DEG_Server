#include "Heart_Scr.h"
#include "chHeart_UI.h"
#include "chSpriteRenderer.h"
#include "chResources.h"

namespace ch
{
	Heart_Scr::Heart_Scr()
	{
	}

	Heart_Scr::~Heart_Scr()
	{
	}

	void Heart_Scr::Initalize()
	{
		
		countHeart = 2;
		prevHeartCount = 3;

		sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHeartMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(mateiral);
		sprite->SetMesh(mesh);
	}

	void Heart_Scr::Update()
	{
		if (countHeart != prevHeartCount) 
		{
			if (countHeart == 2)
			{
				prevHeartCount = countHeart;
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHeartMaterial");
				sprite->SetMaterial(mateiral);
			}
			else if (countHeart == 1) 
			{
				prevHeartCount = countHeart;
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"HalfHeartMaterial");
				sprite->SetMaterial(mateiral);
			}
			else if (countHeart == 0)
			{
				prevHeartCount = countHeart;
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"NoHeartMaterial");
				sprite->SetMaterial(mateiral);
			}
		}
	}

	void Heart_Scr::FixedUpdate()
	{
	}

	void Heart_Scr::Render()
	{
	}

}