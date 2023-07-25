#pragma once
#include <cmath>
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBase.h"
#include "chasePlayerOBJ.h"
#include "chGenericAnimator.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{
	class Bullet_Kin : public Script
	{
    public:
        Bullet_Kin();
        virtual ~Bullet_Kin();

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

        void endHitAnimation();

    public:
        void Spawn();
        void Idle();
        void chase();
        void Hit();
        void Move();
        void Attack();
        void Death();
        
        void GetP2Mangle();
        bool GetShot() { return Shot; }
        void SetShot(bool _a) { Shot = _a; }
        float GetAngle() { return P2Mangle; }
    private:
        Animator* monsAnimator;
        Transform* mTr;
        monsterState mS;
        monsterDir mD;
        monsterDir pervmD;

        GameObject* player;
        MonsterBase* thisMonster;
        GameObject* thisMosterCollider;

    private://수학
        float CalculateDistance(const Vector3& position1, const Vector3& position2)
        {
            Vector3 distanceVector = position2 - position1;
            return distanceVector.Length(); 
        }

        Vector3 Normalize(const Vector3& vector)
        {
            float magnitude = vector.Length(); 
            if (magnitude != 0.0f)
            {
                return vector / magnitude;
            }
            else
            {
                return Vector3(0.0f, 0.0f, 0.0f); 
            }
        }
    private:
        std::shared_ptr<AudioClip> audioClip[3];
        AudioSource* boss_audio[3];
        GameObject* audioObj[3];
    private:
        void GenericMoveAnimator(int dire);
        GenericAnimator GenericAnimator;
        Vector3 dir;
    private:
        int monsterHp;
        bool HitAcc;
        bool Shot;
    private:
        int term;// idle상태 일때 2초간 텀을 주기 위해 
        float P2Mangle;
        float hitTimer;
        float DeathTIME;
        

	};

}

