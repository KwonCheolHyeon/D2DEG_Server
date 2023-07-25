#pragma once
#include "chScript.h"
#include "chTime.h"
#include "chCamera.h"

namespace ch
{
	class FadeEffect : public Script
	{
	public:
		enum FadeState
		{
			FADEIN,
			FADEOUT,
			IDLE
		};
		FadeEffect();
		virtual ~FadeEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		
		//void SetCamera(Camera* camera) { mCamera = camera; }

	private:

		FadeState state;
		float mCurrentTime;
		float FadeIn;
		float FadeOut;
		float Idle;
		float alpha;

		//Camera* mCamera;
	};
}