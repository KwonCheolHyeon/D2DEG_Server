#include "chTransform.h"
#include "chRenderer.h"
#include "chCamera.h"

namespace ch
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mParent(nullptr)
		, moffSet(Vector3::Zero)
		, mInheritParentScale(true)
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::Initalize()
	{
		
	}

	void Transform::Update()
	{
		//실제 로직상 캐릭터이동 처리
	}

	void Transform::FixedUpdate()
	{
		//렌더링에 사용될 위치값들을 업데이트

		// 월드 행렬 생성

		// 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전 변환 행렬
		Matrix rotation;

		Vector3 radian(mRotation.x * (XM_PI / 180)
			, mRotation.y * (XM_PI / 180)
			, mRotation.z * (XM_PI / 180));

		rotation = Matrix::CreateRotationX(radian.x);
		rotation *= Matrix::CreateRotationY(radian.y);
		rotation *= Matrix::CreateRotationZ(radian.z);

		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		Matrix offset;
		offset.Translation(moffSet);

		mWorld = scale * rotation * position * offset;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		// 카메라 컴포넌트에서 세팅해준다
		// 뷰행렬 세팅
		// 프로젝션 행렬 세팅

		if (mParent)
		{
			if (!mInheritParentScale)
			{
				// Get the parent's world matrix without scale
				Matrix parentWorldNoScale = mParent->GetWolrdMatrix();
				Vector3 parentWorldScale, parentWorldTranslation;
				Quaternion parentWorldRotation;
				parentWorldNoScale.Decompose(parentWorldScale, parentWorldRotation, parentWorldTranslation);
				parentWorldNoScale = Matrix::CreateFromQuaternion(parentWorldRotation) * Matrix::CreateTranslation(parentWorldTranslation);

				// Combine the current object's transform with the parent's transform without scale
				mWorld = mWorld * parentWorldNoScale;
			}
			else
			{
				// Combine the current object's transform with the parent's world matrix
				mWorld *= mParent->GetWolrdMatrix();
			}
		}


	}

	void Transform::Render()
	{
		
	}

	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
}
