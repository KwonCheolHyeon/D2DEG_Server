#pragma once
#include "chScript.h"

namespace ch 
{
	class MouseCursorScript : public Script
	{
	public :
		MouseCursorScript();
		virtual ~MouseCursorScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetTarget(GameObject* _target) { tar = _target; }

	private:
		Transform* mTrans;
		Vector3 mPos;
		Vector3 mRot;
		GameObject* tar;
	
	};


}

