#include "BlackMapScr.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "BlackMapObj.h"
namespace ch
{



	BlackMapScr::BlackMapScr()
	{
	}

	BlackMapScr::~BlackMapScr()
	{
	}

	void BlackMapScr::Initalize()
	{
		SpriteRenderer* backSR = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"Black_Material");
		backSR->SetMaterial(backmaterial);
		backSR->SetMesh(backmesh);

	}

	void BlackMapScr::Update()
	{
	}

	void BlackMapScr::FixedUpdate()
	{
	}

	void BlackMapScr::Render()
	{
	}

}