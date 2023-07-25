#pragma once
#include "chScript.h"
#include "chCollider2D.h"
namespace ch
{
    class chasePlayerSCR : public Script
    {
    public:
        chasePlayerSCR();
        virtual ~chasePlayerSCR();

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


    public:
        bool isFindPlayer() { return findPlayer; }

    public:
        bool findPlayer;

        Collider2D* mCollider;
   

    };
}

