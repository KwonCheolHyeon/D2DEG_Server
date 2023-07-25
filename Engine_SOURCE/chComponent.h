#pragma once
#include "chMath.h"
#include "chEntity.h"

using namespace ch::enums;

namespace ch 
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initalize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		eComponentType GetOrder() { return mType; };

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
	private:
		const eComponentType mType;
		GameObject* mOwner;
	};


}

