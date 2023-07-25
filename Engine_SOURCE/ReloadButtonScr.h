#pragma once
#include "chScript.h"

namespace ch
{
	class ReloadButtonScr : public Script
	{
	public:
		ReloadButtonScr();
		virtual ~ReloadButtonScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetPlayer(GameObject* _a) { player = _a; }
	private:
		bool reloadOn;
		float reloadTimer;
		GameObject* player;
	};
}


