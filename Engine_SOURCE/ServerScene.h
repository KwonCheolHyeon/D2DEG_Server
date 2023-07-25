#pragma once
#include "chScene.h"
#include "GameNetServer.h"
#include "GameNetClient.h"

namespace ch
{
	class ServerScene : public Scene
	{
	public:
		static class GameNetServer Server;
		static class GameNetClient Client;
		static class GameNet* NetInst;


		ServerScene();
		virtual ~ServerScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	};


}

