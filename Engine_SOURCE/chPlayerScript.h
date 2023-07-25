#pragma once
#include "chScript.h"
#include "GameNetObject.h"

namespace ch
{
	class PlayerScript : public Script, public GameNetObject
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();
	private:

	};
}
