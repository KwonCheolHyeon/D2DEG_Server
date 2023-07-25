#include "BlankBulletScr.h"
#include "chGameObject.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chLight.h"

namespace ch
{
	BlankBulletScr::BlankBulletScr()
	{
	}
	BlankBulletScr::~BlankBulletScr()
	{
	}
	void BlankBulletScr::Initalize()
	{
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(1.f, 1.0f));


		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"Blank_bulletsMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);
		
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetScale(Vector3(0.5f, 0.5f, 0.1f));

	}
	void BlankBulletScr::Update()
	{
	}
	void BlankBulletScr::FixedUpdate()
	{
	}
	void BlankBulletScr::Render()
	{
	}
	void BlankBulletScr::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BlankBulletScr::OnCollisionStay(Collider2D* collider)
	{
	}
	void BlankBulletScr::OnCollisionExit(Collider2D* collider)
	{
	}
}