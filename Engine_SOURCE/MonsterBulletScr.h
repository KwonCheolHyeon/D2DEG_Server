#pragma once
#include "chScript.h"
namespace ch 
{
	class MonsterBulletScr : public Script
	{
    public:
        MonsterBulletScr();
        virtual ~MonsterBulletScr();

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
        void Reflect();
    private: //¼öÄ¡
        float speed;
        float bulletDirectionX;
        float bulletDirectionY;
        float angles;
        Vector3 GunPos;

        float bulletTime;

    private:
        bool reflectOn;
        int twoHit;

	};


}

