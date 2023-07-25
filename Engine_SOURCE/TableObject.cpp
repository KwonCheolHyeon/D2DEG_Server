#include "TableObject.h"
#include "TableScr.h"
#include "chGameObject.h"
#include "chResources.h"
#include "chAnimator.h"
#include "chSpriteRenderer.h"
#include "chRigidbody.h"
#include "chPlayerHand.h"
#include "chTransform.h"
#include "chCollider2D.h"
namespace ch 
{
	TableObject::TableObject()
	{
		SetLayerType(eLayerType::Object);
		this->AddComponent<TableScr>();
		GameObject* tableOBJ = dynamic_cast<GameObject*>(this);

		tAnimator = tableOBJ->AddComponent<Animator>();

#pragma region 애니메이션
		{//back
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_back_Ani", L"enterthe/object/table/back/table_back_Ani.png");
			tAnimator->Create(L"T_table_back_Ani", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_back_break_Ani", L"enterthe/object/table/back/table_back_break_Ani.png");
			tAnimator->Create(L"T_table_back_break_Ani", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 20.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_front_Ani", L"enterthe/object/table/front/table_front_Ani.png");
			tAnimator->Create(L"T_table_front_Ani", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 24.0f), Vector2::Zero, 4, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_front_break_Ani", L"enterthe/object/table/front/table_front_break_Ani.png");
			tAnimator->Create(L"T_table_front_break_Ani", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 26.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_left_Ani", L"enterthe/object/table/left/table_left_Ani.png");
			tAnimator->Create(L"T_table_left_Ani", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 42.0f), Vector2::Zero, 3, 0.1f);
			
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_left_break_Ani", L"enterthe/object/table/left/table_left_break_Ani.png");
			tAnimator->Create(L"T_table_left_break_Ani", texture, Vector2(0.0f, 0.0f), Vector2(31.0f, 40.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_right_Ani", L"enterthe/object/table/right/table_right_Ani.png");
			tAnimator->Create(L"T_table_right_Ani", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 42.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"table_right_break_Ani", L"enterthe/object/table/right/table_right_break_Ani.png");
			tAnimator->Create(L"T_table_right_break_Ani", texture, Vector2(0.0f, 0.0f), Vector2(31.0f, 41.0f), Vector2::Zero, 3, 0.1f);
		}

#pragma endregion
		SpriteRenderer* sprite = tableOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Table_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


		Collider2D* pCollider = tableOBJ->AddComponent<Collider2D>();
		pCollider->SetName(L"TableCollider");
		pCollider->SetType(eColliderType::Rect);
		pCollider->SetSize(Vector2(1.f, 0.7f));
		pCollider->SetCenter(Vector2(0.f, 0.1f));

		tableOBJ->AddComponent<Rigidbody>();

	}

	TableObject::~TableObject()
	{

	}

	void TableObject::Initalize()
	{
		GameObject::Initalize();
	}

	void TableObject::Update()
	{
		GameObject::Update();
	}

	void TableObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void TableObject::Render()
	{
		GameObject::Render();
	}

}


