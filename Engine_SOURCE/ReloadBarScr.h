#pragma once
#include "chScript.h"

namespace ch
{
	class ReloadBarScr : public Script
	{
	public:
		ReloadBarScr();
		virtual ~ReloadBarScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	
		void SetPlayer(GameObject* _a) { player = _a; }

	private:
		GameObject* player;

		bool reloadOn;
		float reloadTimer;
	};
}


