#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "DoorColliderObj.h"
#include "DoorObj.h"
namespace ch
{
    class DoorColliderScr : public Script
    {
    public:
        DoorColliderScr();
        virtual ~DoorColliderScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

    private:
        DoorColliderObj* DCO;
        DoorObj* doorObj;
        Collider2D* col;
        bool isInCollider;
       

    };

}
