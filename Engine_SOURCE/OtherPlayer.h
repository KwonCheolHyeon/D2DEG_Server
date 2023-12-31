#pragma once
#include "chScript.h"
#include "GameNetObject.h"

namespace ch
{
	class OtherPlayer : public Script, public GameNetObject
	{
	public:
		OtherPlayer();
		~OtherPlayer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();

	public:
		std::wstring GetAnimationName(int a);

	private://01
		

	};
}
