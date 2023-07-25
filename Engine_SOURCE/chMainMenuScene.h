	#pragma once
#include "chScene.h"


namespace ch
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		virtual ~MainMenu();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* chCamera;
		GameObject* chUiCamera;
		GameObject* chUiCursor;

	private:
		std::shared_ptr<class AudioClip> audioClip;
		class AudioSource* boss_audio;
		GameObject* audioObj;
	};


}

