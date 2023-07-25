#include "chSceneManager.h"
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
#include "chTitleScene.h"
#include "chPlayScene.h"
#include "chTestScene.h"
#include "ServerScene.h"
#include "chMainMenuScene.h"

namespace ch
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)eSceneType::End);//endscene��ŭ �Ҵ�

		mScenes[(UINT)eSceneType::Tilte] = new TitleScene(); //scene�߰� �κ�
		mScenes[(UINT)eSceneType::Main] = new MainMenu();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Test] = new TestScene();
		mScenes[(UINT)eSceneType::Server] = new ServerScene();

		mActiveScene = mScenes[(UINT)eSceneType::Server];

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				return;

			scene->Initalize();
		}

	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// �ٲ� dontDestory ������Ʈ�� ���������� ���� �Ѱ�����Ѵ�.
		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();

		mActiveScene = mScenes[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		if (mActiveScene)
			mActiveScene->OnEnter();
	}
}