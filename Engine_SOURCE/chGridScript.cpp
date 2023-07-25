#include "chGridScript.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chApplication.h"
#include "chConstantBuffer.h"
#include "chRenderer.h"
#include "chSceneManager.h"

extern ch::Application application;

namespace ch
{
	GridScript::GridScript()
		: Script()
		, mCamera(nullptr)
	{

	}

	GridScript::~GridScript()
	{

	}

	void GridScript::Initalize()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		mCamera = renderer::cameras[(UINT)type][0];
	}

	void GridScript::Update()
	{
		//	CBUFFER(GridCB, CBSLOT_GRID)
		//{
		//	Vector4 cameraPosition;
		//	Vector2 cameraScale;
		//	Vector2 resolution;
		//};

		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = static_cast<float>(winRect.right - winRect.left);
		float height = static_cast<float>(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void GridScript::FixedUpdate()
	{
	}

	void GridScript::Render()
	{
	}

}
