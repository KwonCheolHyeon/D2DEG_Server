#include "ConvictBlankBulletScr.h"
#include "chInput.h"
#include "chTime.h"
namespace ch 
{
	ConvictBlankBulletScr::ConvictBlankBulletScr()
	{
	}

	ConvictBlankBulletScr::~ConvictBlankBulletScr()
	{
	}

	void ConvictBlankBulletScr::Initalize()
	{
		tr = this->GetOwner()->GetComponent<Transform>();
		
		col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.1f, 0.1f));

		time = 0.f;
		reloadOn = false;
	}

	void ConvictBlankBulletScr::Update()
	{
		Vector3 a = gameObject->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(a);

		if (on == true) 
		{
			time += Time::DeltaTime();
			BlankBulletEffect();
			if (time >= 0.2f) 
			{
				on = false;
				time = 0.f;
				col->SetSize(Vector2(0.1f, 0.1f));
			}
		
		}

		
		if (Input::GetKeyDown(eKeyCode::R))
		{
			reloadOn = true;
		}


		if (reloadOn == true) 
		{
			reloadTime += Time::DeltaTime();
			col->SetSize(Vector2(1.5f, 1.f));
			col->GetOwner()->SetName(L"FightSabreCollider");
			if (reloadTime >= 1.96f) 
			{
				reloadTime = 0;
				reloadOn = false;
				col->SetSize(Vector2(0.1f, 0.1f));
				col->GetOwner()->SetName(L"ConvictBlankcolider");
			}
		}





	}

	void ConvictBlankBulletScr::FixedUpdate()
	{
	}

	void ConvictBlankBulletScr::Render()
	{
	}

	void ConvictBlankBulletScr::OnCollisionEnter(Collider2D* collider)
	{


	}

	void ConvictBlankBulletScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void ConvictBlankBulletScr::OnCollisionExit(Collider2D* collider)
	{
	}

	void ConvictBlankBulletScr::BlankBulletEffect()
	{

		float initialSize = 0.1f;
		float maxSize = 70.0f;

		// 크기 변화에 사용할 시간 비율 계산
		float timeRatio = time ;

		// 크기 계산
		float currentSize = initialSize + (maxSize - initialSize) * timeRatio;

		// 크기 적용
		col->SetSize(Vector2(currentSize, currentSize));

	}

}