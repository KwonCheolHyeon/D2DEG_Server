#include "chInput.h"
#include "chApplication.h"
#include "chCamera.h"

extern ch::Application application;

namespace ch
{
	std::vector<Input::Key> Input::mKeys;
	math::Vector3 Input::mMousPosition; 
	math::Vector3 Input::mWorldMousePosition;
	math::Vector2 Input::mMousePosition;
	math::Vector2 Input::mMouseWorldPosition;
	float Input::mWinWidthCenter;
	float Input::mWinHeightCenter;

	int ASCII[(UINT)eKeyCode::END] =
	{
		//Alphabet
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		//Special Key
		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		//Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		//Num Line
		'0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9',
	};


	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key key;
			key.eType = (eKeyCode)i;
			key.eState = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
		RECT winRect = {};
		GetClientRect(application.GetHwnd(), &winRect);
		mWinWidthCenter = ((float)winRect.right - (float)winRect.left) / 2.0f;
		mWinHeightCenter = ((float)winRect.bottom - (float)winRect.top) / 2.0f;
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			//KEY
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				// 해당키가 현재 눌려있다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::PRESSED;
					else
						mKeys[i].eState = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				else // 해당키가 현재 안눌려있다.
				{
					// 이전 프레임에는 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::UP;
					else // 이전 프레임에도 안눌려 있었다.
						mKeys[i].eState = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}

			

			ConvertMousePos();
			
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				if (eKeyState::DOWN == mKeys[i].eState || eKeyState::PRESSED == mKeys[i].eState)
					mKeys[i].eState = eKeyState::UP;
				else if (eKeyState::UP == mKeys[i].eState)
					mKeys[i].eState = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}

	}

	void Input::Render(HDC hdc)
	{
		HWND hWnd = application.GetHwnd();

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"X : %f | Y : %f", mMousPosition.x, mMousPosition.y);

		SetWindowText(hWnd, szFloat);
	}

	void Input::ConvertMousePos()
	{

		POINT ptMouse = {};
		GetCursorPos(&ptMouse);
		ScreenToClient(application.GetHwnd(), &ptMouse);

		RECT windowRect;
		GetClientRect(application.GetHwnd(), &windowRect);

		Vector2 resolutionRatio = application.GetResolutionRatio();

		Vector2 mousePos;

		mousePos.x = static_cast<float>(ptMouse.x - (windowRect.right - windowRect.left) * 0.5f) * resolutionRatio.x;
		mousePos.y = static_cast<float>((windowRect.bottom - windowRect.top) * 0.5f - ptMouse.y) * resolutionRatio.y;

		mMousPosition.x = mousePos.x;
		mMousPosition.y = mousePos.y;

		if (renderer::mainCamera)
		{
			Vector3 camPos = renderer::mainCamera->GetOwner()->GetWorldPos();

			mWorldMousePosition.x = (mMousPosition.x / 100.f) + camPos.x;
			mWorldMousePosition.y = (mMousPosition.y / 100.f) + camPos.y;
		}


		Camera* cameraComp = renderer::mainCamera;

		if (nullptr == cameraComp)
			return;

		Vector3 cameraPos = cameraComp->GetOwner()->GetComponent<Transform>()->GetPosition();
		mMouseWorldPosition = mMousePosition + Vector2(cameraPos.x, cameraPos.y);


	}

	
	
}