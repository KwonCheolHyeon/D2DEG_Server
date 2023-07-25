#pragma once
#define _WINSOCKAPI_
#include <WinSock2.h>
#include "chScene.h"

namespace ch
{
	//class Scene;
	class SceneManager 
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetPlayScene() { return mScenes[(UINT)eSceneType::Play]; }
		static Scene* GetTestScene() { return mScenes[(UINT)eSceneType::Test]; }
	
		static Scene* GetScene(eLayerType type) { return mScenes[(UINT)type]; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene; //³» ÇöÀç ¾À
	};
}
