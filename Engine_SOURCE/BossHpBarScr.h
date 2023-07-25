#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "BossHpBarObj.h"
#include "chTexture.h"
#include "MonsterBase.h"
#include "EventObj.h"
namespace ch
{
	class BossHpBarScr : public Script
	{
	public:
		BossHpBarScr();
		virtual ~BossHpBarScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetBossMonster(MonsterBase* _a) { boss = _a; }
		MonsterBase* GetBossMonster() { return boss; }

		void SetEvent(EventObj* _a) { eventObj = _a; }
		//EventObj* GetBossMonster() { return boss; }

	private:

		Animator* ani;
		MonsterBase* boss;
		EventObj* eventObj;
	private:
		float health;
		float bossHp;
		float prevBossHp;
		float maxHp;

	};
}


