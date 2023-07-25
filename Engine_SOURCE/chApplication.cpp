#include "chApplication.h"
#include "chRenderer.h"
#include "chTime.h"
#include "chInput.h"
#include "chSceneManager.h"
#include "chResources.h"
#include "chCollisionManager.h"
#include "chFmod.h"
namespace ch
{
	using namespace graphics;

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Initalize()
	{
		Time::Initialize();
		Input::Initialize();
		CollisionManager::Initialize();
		Fmod::Initialize();
		renderer::Initialize();
		SceneManager::Initalize();
		
	}

	// 게임 로직 캐릭터 이동 등등 
	// CPU UPDATE
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	// GPU update
	void Application::FixedUpdate()
	{
		CollisionManager::FixedUpdate();
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		//SceneManager::Render();
		renderer::Render();
		CollisionManager::Render();
		//graphicDevice->Render();
		//graphicDevice->Present();
		SceneManager::Destroy();

	}
	void Application::Destroy()
	{

	}

	// Running main engine loop
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
		Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::Release()
	{
		Resources::deleteTest();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;


			ValidationMode vaildationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			//graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

	Vector2 Application::GetResolutionRatio()
	{
		RECT	windowRC;

		GetClientRect(mHwnd, &windowRC);

		float width = static_cast<float>(windowRC.right - windowRC.left);
		float height = static_cast<float>(windowRC.bottom - windowRC.top);

		return Vector2(mWidth / width, mHeight / height);

	}
}



