#include "HeartScr.h"
#include "chGameObject.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chLight.h"
namespace ch 
{
	HeartScr::HeartScr()
	{

	}

	HeartScr::~HeartScr()
	{

	}

	void HeartScr::Initalize()
	{
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(1.f, 1.0f));
		

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"FullHeartMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		Transform* mTr = GetOwner()->GetComponent<Transform>();
		
		mTr->SetScale(Vector3(0.5f, 0.5f, 0.1f));
	}
	

	void HeartScr::Update()
	{



	}

	void HeartScr::FixedUpdate()
	{
	}

	void HeartScr::Render()
	{
	}

	void HeartScr::OnCollisionEnter(Collider2D* collider)
	{
	}

	void HeartScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void HeartScr::OnCollisionExit(Collider2D* collider)
	{
	}

}