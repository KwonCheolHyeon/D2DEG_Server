#pragma once
#include "chScript.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
#include "chAnimator.h"
namespace ch
{
 
    class FightSabreBoxScr :public Script
    {
    public:
        FightSabreBoxScr();
        virtual ~FightSabreBoxScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollisionStay(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        void turnEquipItme() { equipItem = true; }

        void LifeOn() { LifeOns = true; }

    private:
        Collider2D* obCollider;
        Rigidbody* obRigid;
        Animator* obAnima;

    private:
        bool firstKey;
        bool equipItem;
        bool LifeOns;
    };


}

