#include "chTestScene.h"
#include "chSceneManager.h"
#include "chInput.h"
#include "chGameObject.h"
#include "chObject.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chRenderer.h"
#include "chMeshRenderer.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chCollider2D.h"
#include "EndingObj.h"
#include "EndingScr.h"
namespace ch 
{
	TestScene::TestScene()
		: Scene(eSceneType::Test)
	{

	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initalize()
	{
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{ //Main Camera 
			chCameraOBJ = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = chCameraOBJ->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			chCameraOBJ->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}
		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
	
		{
			GameObject* ending = object::Instantiate<EndingObj>(eLayerType::UI, this);

			Transform* endingtr = ending->GetComponent<Transform>();
			endingtr->SetPosition(Vector3(1.f, 1.f, 0.f));
			endingtr->SetScale(Vector3(50.f, 50.f, 0.f));



			chCameraOBJ->GetComponent<Camera>()->SetTarget(ending);
		}
		
		
	
		Scene::Initalize();
	}

	void TestScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}

	void TestScene::OnEnter()
	{

		Scene::OnEnter();
	}

	void TestScene::OnExit()
	{
		Scene::OnExit();
	}

}