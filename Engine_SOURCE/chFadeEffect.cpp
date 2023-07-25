#include "chFadeEffect.h"
#include "chSpriteRenderer.h"
#include "chGameObject.h"
#include "chTransform.h"
#include "chInput.h"
namespace ch
{
	FadeEffect::FadeEffect()
	{
	
	}

	FadeEffect::~FadeEffect()
	{
	}
	void FadeEffect::Initalize()
	{
		Idle = 2.0f;
		FadeIn = 5.0f;
		FadeOut = 5.0f;
		alpha = 1.0f;
		
	}
	void FadeEffect::Update()
	{
		/*
		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
		float scale = mCamera->GetScale();
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::FadeEffect];
		renderer::FadeEffectCB data;
		*/
		mCurrentTime += Time::DeltaTime();
		
		switch (state)
		{
		case ch::FadeEffect::FADEIN:
			if (mCurrentTime >= FadeIn)
			{
				mCurrentTime -= FadeIn;
				state = FadeEffect::IDLE;
				alpha = 1.0f;
			}
			else
			{
				alpha = mCurrentTime / FadeIn;
			}
			break;
		case ch::FadeEffect::FADEOUT:
			if (mCurrentTime >= FadeOut)
			{
				mCurrentTime = FadeOut;
			}
			alpha = (FadeOut - mCurrentTime) / FadeOut;
			break;
		case ch::FadeEffect::IDLE:
			if (mCurrentTime >= Idle)
			{
				mCurrentTime -= Idle;
				state = FadeEffect::FADEOUT;
				alpha = (FadeOut - mCurrentTime) / FadeOut;
			}
			else
			{
				alpha = 1;
			}
			break;
		default:
			break;
		}
		
		std::shared_ptr<Material> material = GetOwner()->GetComponent<SpriteRenderer>()->GetMaterial();

		material->SetData(eGPUParam::Float, &alpha);
		
		/*
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.alphaAmount = alpha;

		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
		*/
	}
	void FadeEffect::FixedUpdate()
	{


	}
	void FadeEffect::Render()
	{
	}
}
