#pragma once
#include "chScript.h"

namespace ch 
{
	class MonsterBullet2Scr : public Script
	{
    public:
        MonsterBullet2Scr();
        virtual ~MonsterBullet2Scr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        virtual void OnTriggerEnter(Collider2D* oppo);
        virtual void OnTrigger(Collider2D* oppo);
        virtual void OnTriggerExit(Collider2D* oppo);

        void shootingBullet(float Gunangle, Vector3 pos);
        void MoveBullet();
        void Reset();

        void moveOns() { moveOn = true; }
    private: //¼öÄ¡
        float speed;
        float bulletDirectionX;
        float bulletDirectionY;
        float angles;
        Vector3 GunPos;
        float bulletTime;

        bool moveOn;

    private:
        int twoHit;
        bool reflectOn;
	};
}




//{//Move
//    std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_fly", L"enterthe/enemy/Boss/fly.png");
//    mBossAni->Create(L"B_Boss_fly", texture, Vector2(0.0f, 0.0f), Vector2(29.0f, 86.0f), Vector2::Zero, 4, 0.15f);
//}
//{//Move
//    std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_flying", L"enterthe/enemy/Boss/flying.png");
//    mBossAni->Create(L"B_Boss_flying", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 51.0f), Vector2::Zero, 1, 0.15f);
//}
//{//Move
//    std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_skyBomb", L"enterthe/enemy/Boss/skyBomb.png");
//    mBossAni->Create(L"B_Boss_skyBomb", texture, Vector2(0.0f, 0.0f), Vector2(48.0f, 74.0f), Vector2::Zero, 5, 0.15f);
//}