#include "chMainMenuScene.h"
#include "chTransform.h"
#include "chMeshRenderer.h"
#include "chRenderer.h"
#include "chResources.h"
#include "chTexture.h"
#include "chPlayerScript.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chSpriteRenderer.h"
#include "chGridScript.h"
#include "chObject.h"
#include "chInput.h"
#include "chCollider2D.h"
#include "chPlayer.h"
#include "chMonster.h"
#include "chCollisionManager.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chAudioClip.h"
#include "chAudioSource.h"
namespace ch
{
	MainMenu::MainMenu()
		: Scene(eSceneType::Main)
		, chCamera(nullptr)
		, chUiCamera(nullptr)
	{
	}
	MainMenu::~MainMenu()
	{
	}
	void MainMenu::Initalize()
	{
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		{
			// main 카메라
			chCamera = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = chCamera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			chCamera->AddComponent<CameraScript>();
			
			mainCamera = cameraComp;
		}
		{ // UI
			{
				// ui 카메라
				chUiCamera = object::Instantiate<GameObject>(eLayerType::Camera, this);
				Camera* cameraComp = chUiCamera->AddComponent<Camera>();
				cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
				cameraComp->DisableLayerMasks();
				cameraComp->TurnLayerMask(eLayerType::UI, true);
			}

			{
			


			}
		}
	
		{//mainmenu
			{//bg
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround, this);
				rightObj->SetName(L"mainmenuBG");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				rightObjTr->SetScale(Vector3(30.0f, 30.0f, 0.1f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainBgMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}

			{//mainmenu
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround, this);
				rightObj->SetName(L"mainmenu");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(1.0f, 1.1f, 0.2f));
				rightObjTr->SetScale(Vector3(17.0f, 9.0f, 0.2f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainMenuMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}
		}


		audioObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		audioClip = Resources::Load<AudioClip>(L"intro", L"music\\ost\\intro.mp3");
		boss_audio = audioObj->AddComponent<AudioSource>();
		boss_audio->SetClip(audioClip);


		boss_audio->Play();

		Scene::Initalize();
	}
	void MainMenu::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{

			boss_audio->Stop();
			audioObj->GetComponent<Transform>()->SetPosition(Vector3(-10000.f, -10000.f, 0.f));
			

			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void MainMenu::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void MainMenu::Render()
	{
		Scene::Render();
	}
	void MainMenu::OnEnter()
	{		
		Scene::OnEnter();
	}
	void MainMenu::OnExit()
	{
		Scene::OnExit();
	}
	
}