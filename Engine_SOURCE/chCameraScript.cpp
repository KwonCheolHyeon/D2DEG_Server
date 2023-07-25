#include "chCameraScript.h"
#include "chCamera.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chAudioListener.h"


namespace ch
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
		mCameraObject = GetOwner()->GetComponent<Camera>();
		target = mCameraObject->GetTarget();

		weakOn = false;
		strongOn = false;
		shaketime = 0.f;
		verystrongOn = false;

		AudioListener* cccc = GetOwner()->AddComponent<AudioListener>();
	}

	void CameraScript::Update()
	{
		
		if (target)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();//

			Vector3 pos = tr->GetPosition(); // Camera position

			targetPos = target->GetComponent<Transform>()->GetPosition(); // Player position

			Vector3 mousePos =  Input::GetMousPosition(); // Mouse cursor position
			Vector3 mouseRelative = (mousePos / 100.f);
			mouseRelative += targetPos;//마우스 위치

			

			// Calculate distance between camera and target
			Vector3 distance = Vector3(mouseRelative.x, mouseRelative.y, mouseRelative.z) - Vector3(targetPos.x, targetPos.y, targetPos.z);
			distance = distance / 1.5f;
			
			float maxDistance = 3.0f; // Change this value to set the maximum distance
			if (distance.Length() > maxDistance)
			{
				distance.Normalize();
				distance *= maxDistance;
			}

			pos = targetPos + distance;
			
			if (weakOn == true)
			{
				pos = weakShake(pos);
			}
			if (strongOn == true)
			{
				pos = strongShake(pos);
			}
			if (verystrongOn == true)
			{
				pos = verystrongShake(pos);
			}
			

			tr->SetPosition(pos);
		}
		else {
		
			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 pos = tr->GetPosition();

			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos += 1.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos += 1.0f * -tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos += 1.0f * tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos += 1.0f * -tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
			{
				pos += 1.0f * tr->Up() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
			{
				pos += 1.0f * -tr->Up() * Time::DeltaTime();
			}
			tr->SetPosition(pos);
		}

		
	}
	void CameraScript::Render()
	{
	}

	Vector3 CameraScript::CameraWeakShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.1f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;

	}

	Vector3 CameraScript::CameraStrongShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.5f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}

	Vector3 CameraScript::weakShake(Vector3 pos)
	{
		shaketime += Time::DeltaTime();
		pos = CameraWeakShakeeffect(pos);
		
		if (shaketime >= 0.2f) 
		{
			weakOn = false;
			shaketime = 0.f;
			return pos;
		}
		
		return pos;
		
	}

	Vector3 CameraScript::strongShake(Vector3 pos)
	{
		shaketime += Time::DeltaTime();
		pos = CameraStrongShakeeffect(pos);

		if (shaketime >= 0.1f)//몇초간 
		{
			strongOn = false;
			shaketime = 0.f;
			return pos;
		}

		return pos;

	}

	Vector3 CameraScript::verystrongShake(Vector3 pos)
	{
		shaketime += Time::DeltaTime();
		pos = CameraStrongShakeeffect(pos);

		if (shaketime >= 1.f)//몇초간 
		{
			verystrongOn = false;
			shaketime = 0.f;
			return pos;
		}

		return pos;
	}


	
}