#include "chTitleScene.h"
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
#include "mainPlayer.h"
#include "chAnimator.h"
#include "chLight.h"
#include "chPaintShader.h"
#include "chParticleSystem.h"


namespace ch
{
	TitleScene::TitleScene()
		:Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		//paint shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player,this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		}


		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, true);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		Transform* zeldaTr;
		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Zelda");
			zeldaTr = obj->GetComponent<Transform>();
			zeldaTr->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
			//zeldaTr->SetRotation(Vector3(0.0f, 0.0f, 45.0f));
			zeldaTr->SetScale(Vector3(200.0f, 200.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");
			animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 3, 0.1f);
			animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
			animator->Create(L"MoveLeft", texture, Vector2(0.0f, 650.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 10, 0.1f);

			animator->Play(L"MoveLeft", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(obj);
		}
		
		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			//tr->SetScale(Vector3(2.0f, 1.0f, 1.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetSize(Vector2(2.0f, 2.0f));
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			object::DontDestroyOnLoad(obj);
		}
		//Particle
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle, this);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			obj->AddComponent<ParticleSystem>();
		}

		//post process object
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::PostProcess,this);
			obj->SetName(L"PostProcessGameObject");
			zeldaTr = obj->GetComponent<Transform>();
			zeldaTr->SetPosition(Vector3(0.0f, 0.0f, 19.0f));
			zeldaTr->SetScale(Vector3(200.0f, 200.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetSize(Vector2(1.0f, 0.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PostProcessMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);
		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		
		if (Input::GetKeyDown(eKeyCode::N)) 
		{
			
			SceneManager::LoadScene(eSceneType::Main);
		}
		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
	
}