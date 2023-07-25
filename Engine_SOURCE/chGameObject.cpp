#include "chGameObject.h"
#include "chTransform.h"

namespace ch
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mType(eLayerType::None)
		, mbDontDestroy(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* scrComp : mScripts)
		{
			if (scrComp == nullptr)
				continue;

			delete scrComp;
			scrComp = nullptr;
		}

	
	}

	void GameObject::Initalize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initalize();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Initalize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}


		if (mbIsLeft != prevIsLeft) 
		{
		
			Flip();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		eComponentType order = comp->GetOrder();

		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = comp;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(dynamic_cast<Script*>(comp));
			comp->SetOwner(this);
		}
	}
	void GameObject::SetPos(Vector3 _Value)
	{
		if (nullptr != GetComponent<Transform>())
		{
			GetComponent<Transform>()->SetPosition(_Value);
		}
	}
	
	void GameObject::SetRotation(Vector3 _Value)
	{
		if (nullptr != GetComponent<Transform>())
		{
			GetComponent<Transform>()->SetRotation(_Value);
		}
	}
	Vector3 GameObject::GetWorldPos()
	{
		return GetComponent<Transform>()->GetWorldPosition();
	}
	Vector3 GameObject::GetPos()
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vector3 GameObject::GetRotation()
	{
		return GetComponent<Transform>()->GetRotation();
	}
	void GameObject::Flip()
	{
		prevIsLeft = mbIsLeft;
		if (mbIsLeft == false) //오른쪽
		{
			GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.f, 0.f));

		}
		else if (mbIsLeft == true) // 왼쪽
		{
			GetComponent<Transform>()->SetRotation(Vector3(0.0f, 180.f, 0.f));//y축 기준으로 180도 회전  
		}

	}
	
}
