#include "chBulletScr.h"
#include "chTime.h"
#include "chGameObject.h"
#include "chPlayScene.h"
#include "chSceneManager.h"
#include "chGun.h"
#include "chScene.h"
#include "chTransform.h"
#include "chInput.h"
#include "chResources.h"
#include "chSpriteRenderer.h"

namespace ch
{
	BulletScr::BulletScr()
		: Script()
		, speed(0.0f)
		, bulletDirectionX(0.f)
		, bulletDirectionY(0.f)
		, bulletTime(0.0f)
	{
	
	}
	BulletScr::~BulletScr()
	{
	}
	void BulletScr::Initalize()
	{
		

		mState[(UINT)eBulletState::wait] = true; //대기 상태
		mState[(UINT)eBulletState::live] = true; // 쏘고 움직이는 상태
		mState[(UINT)eBulletState::Dead] = false;
		
	}
	void BulletScr::Update()
	{
		if (mState[(UINT)eBulletState::wait] == false && mState[(UINT)eBulletState::Dead] == false && mState[(UINT)eBulletState::live] == true)
		{
			bulletTime += Time::DeltaTime();
			MoveBullet();
		}
		if (bulletTime >= 1.5f)
		{
			Reset();
		}
	}
	void BulletScr::FixedUpdate()
	{
	}
	void BulletScr::Render()
	{
	}
	void BulletScr::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Reset();
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Object)
		{
			Reset();
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Wall || collider->GetOwner()->GetName() == L"MapWall" || collider->GetOwner()->GetName() == L"DoorSide" || collider->GetOwner()->GetName() == L"DoorFront" )
		{
			Reset();
		}
		if (collider->GetOwner()->GetName() == L"Bullat" || collider->GetOwner()->GetName() == L"cBoss" || collider->GetOwner()->GetName() == L"Cube" || collider->GetOwner()->GetName() == L"BulletKin" )
		{
			Reset();
		}
	}
	void BulletScr::OnCollisionStay(Collider2D* collider)
	{
	}
	void BulletScr::OnCollisionExit(Collider2D* collider)
	{
		
	}
	void BulletScr::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BulletScr::OnTriggerStay(Collider2D* collider)
	{
	}
	void BulletScr::OnTriggerExit(Collider2D* collider)
	{
	}
	void BulletScr::shootingBullet(float Gunangle, Vector3 Gunpos)
	{
		
		mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(Gunpos);

		mState[(UINT)eBulletState::wait] = false;
		mState[(UINT)eBulletState::live] = true;
		mState[(UINT)eBulletState::Dead] = false;
	}
	void BulletScr::MoveBullet()
	{
		speed = 10.0f; // Bullet's movement speed
		float bulletDistance = speed * Time::DeltaTime();
		Vector3 bulletPos = mTr->GetPosition();

		// Update bullet position based on direction and distance
		bulletPos += Vector3(bulletDirectionX, bulletDirectionY, 0.0f) * bulletDistance;

		mTr->SetPosition(bulletPos);
	}

	void BulletScr::Reset()
	{
		bulletTime = 0;
		speed = 0;
		bulletDirectionX = 0;
		bulletDirectionY = 0;
		mTr->SetPosition(Vector3(-1000.f,-1000.f, 0.f));
		mTr->SetRotation(Vector3(0.f, 0.f, 0.f));
		mState[(UINT)eBulletState::Dead] = true;
		mState[(UINT)eBulletState::live] = false;
		mState[(UINT)eBulletState::wait] = true;
	}
	bool BulletScr::isReset()
	{
		if (mState[(UINT)eBulletState::wait] == true && mState[(UINT)eBulletState::Dead] == true && mState[(UINT)eBulletState::live] == false )
		{
			return true;
			mState[(UINT)eBulletState::wait] = true; 
			mState[(UINT)eBulletState::live] = true; 
			mState[(UINT)eBulletState::Dead] = false;
		}
		else 
		{
			return false;
		}
	
	}
}