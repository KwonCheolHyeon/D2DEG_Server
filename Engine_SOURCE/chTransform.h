#pragma once
#include "chComponent.h"

using namespace ch::math;
namespace ch
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		void SetOffset(Vector3 offset) { moffSet = offset; }
		void SetPosition(Vector3 position) { mPosition = position + moffSet; };
		
		void SetRotation(Vector3 degree) { mRotation = degree; };
		void SetScale(Vector3 scale) { mScale = scale; };


		Vector3 GetPosition() { return mPosition; };
		Vector3 GetCenterPos() { return Vector3(mPosition.x / 2, mPosition.y / 2, mPosition.z / 2); }
		Vector3 GetRotation() { return mRotation; };
		
		Vector3 GetScale() { return mScale; };
		
		Vector3 Foward() { return mFoward; }

		Vector3 Right() { return mRight; }

		Vector3 Up() { return mUp; }

		Matrix& GetWolrdMatrix() { return mWorld; }

		const Vector3& GetWorldPosition() const { return mWorldPosition; }
		const Vector3& GetWorldRotation() const { return mWorldRotation; }
		const Vector3& GetWorldScale() const { return mWorldScale; }

		float GetWorldPositionX() const { return mWorldPosition.x; }
		float GetWorldPositionY() const { return mWorldPosition.y; }
		float GetWorldPositionZ() const { return mWorldPosition.z; }
		Vector2 GetWorldPositionXY() const { return Vector2(mWorldPosition.x, mWorldPosition.y); }


		bool GetInheritParentScale() const { return mInheritParentScale; }
		void SetInheritParentScale(bool inherit) { mInheritParentScale = inherit; }

	private:
		Transform* mParent;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mUp;
		Vector3 mPosition;
		Vector3 moffSet;
	
		Vector3 mRotation;
		Vector3 mScale;
		Matrix mWorld;

		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;
		bool mInheritParentScale;
	};
}
