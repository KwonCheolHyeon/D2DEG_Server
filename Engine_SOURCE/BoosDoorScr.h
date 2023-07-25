
#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "BoosDoorObj.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{
	class BoosDoorScr : public Script
	{
	public:
		BoosDoorScr();
		virtual ~BoosDoorScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		std::shared_ptr<AudioClip> audioClip;
		AudioSource* audio;
		GameObject* audioObj;
	private:
		Collider2D* col;
		Animator* anima;

	private:
		float timer;
		bool doorOn;
		bool doorSound;

	};
}