#include "MapObject.h"
#include "chMapCollider.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
namespace ch
{
	MapObject::MapObject()
	{
		map = dynamic_cast<GameObject*>(this);
		map->AddComponent<MapCollider>();
		
		SpriteRenderer* backSR = map->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"MapSample_Material2");
		backSR->SetMaterial(backmaterial);
		backSR->SetMesh(backmesh);

	}
	MapObject::~MapObject()
	{
	}
	void MapObject::Initalize()
	{
		GameObject::Initalize();
	}
	void MapObject::Update()
	{
		GameObject::Update();
	}
	void MapObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void MapObject::Render()
	{
		GameObject::Render();
	}
}