#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "EventObj.h"
namespace ch
{
	class BossSceneScr : public Script
	{
	public:
		BossSceneScr();
		virtual ~BossSceneScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	

		void SetEvent(EventObj* _a) { eventObj = _a; }



	private:
		EventObj* eventObj;
		Animator* ani;
		float timer;
	};
}


