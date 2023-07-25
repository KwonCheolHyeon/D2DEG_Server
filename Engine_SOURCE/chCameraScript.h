#pragma once
#include "chScript.h"
#include <d2d1.h>
#include <dwrite.h>

namespace ch
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		Vector3 CameraWeakShakeeffect(Vector3 pos);
		Vector3 CameraStrongShakeeffect(Vector3 pos);
		float RandomRange(float min, float max)
		{
			return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
		}

		Vector3 weakShake(Vector3 pos);
		Vector3 strongShake(Vector3 pos);
		Vector3 verystrongShake(Vector3 pos);

		void weakEffectOn() { weakOn = true; }
		void strongEffectOn() { strongOn = true; }
		void vecrstrongEffectOn() { verystrongOn = true; }
	private: //¼öÇÐ
		bool weakOn;
		bool strongOn;
		bool verystrongOn;
		float shaketime;
	private:
		class Camera* mCameraObject;
		GameObject* target;
		Vector3 targetPos;

	};
}
