#include "ServerScene.h"
#include "chTransform.h"
#include "chMeshRenderer.h"
#include "chRenderer.h"
#include "chResources.h"
#include "chTexture.h"

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
#include "chLight.h"
#include "chPaintShader.h"
#include "chParticleSystem.h"

//#include "chPlayerScript.h"
//#include "chOtherPlayerScript.h"

#include "ServerToClient.h"

#include "ServerCharacterBase.h"
#include "YourPlayer.h"
#include "YourPlayerMove.h"

#include "OtherPlayer.h"


#include "GlobalPacket.h"

namespace ch
{
	GameNetServer ServerScene::Server;
	GameNetClient ServerScene::Client;
	GameNet* ServerScene::NetInst;

	ServerScene::ServerScene()
		: Scene(eSceneType::Tilte)
	{
	}
	ServerScene::~ServerScene()
	{
	}
	void ServerScene::Initalize()
	{
#pragma region Light
		GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		directionalLight->SetName(L"directionalLight");

		directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 100.0f, 0.0f));
		directionalLight->GetComponent<Transform>()->SetRotation(Vector3(45.0f, 0.0f, 0.0f));

		Light* lightComp = directionalLight->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
#pragma endregion Light
#pragma region Main Camera
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->SetName(L"MainCamera");
		cameraObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
#pragma endregion Main Camera
#pragma region Player

		// 3D 기본 메쉬
		// 1. 큐브
		//mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
		// 2. 스피어
		//mr->SetMesh(Resources::Find<Mesh>(L"SphereMesh"));

#pragma endregion Player

		Scene::Initalize();
	}
	void ServerScene::Update()
	{
	
		static bool IsServer = false;

		if (Input::GetKeyDown(eKeyCode::N_9))
		{
			Server.Dispatcher.AddHandler<ObjectUpdatePacket>(PacketEnumType::ObjectUpdatePacket,
				[=](std::shared_ptr<ObjectUpdatePacket> _Packet)
				{
					if (false == GameNetObject::IsNetObject(_Packet->GetObjectID()))
					{
						GameObject* Otherplayer = object::Instantiate<GameObject>(eLayerType::Player);

						Otherplayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
						Otherplayer->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
						Otherplayer->SetName(L"OtherPlayer");

						OtherPlayer* Other = Otherplayer->AddComponent<OtherPlayer>();
						

						int ObjectID = _Packet->GetObjectID();

						Other->ClientObjectInit(_Packet->GetObjectID());

					}

					GameNetObject::PushObjectPacket(_Packet);

					// 다른 모든애들에게도 보낸다.
					NetInst->PacketSend(_Packet);
				}
			);

			Server.OpenHost(30000, [=](SOCKET _Socket)
				{//클라이언트 오브젝트 생성
					GameObject* Otherplayer = object::Instantiate<GameObject>(eLayerType::Player);
					
					Otherplayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
					Otherplayer->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
					Otherplayer->SetName(L"OtherPlayer");
	
					OtherPlayer* Other = Otherplayer->AddComponent<OtherPlayer>();
					
					// 서버 오브젝트 init를 호출해도 된다.
					Other->ServerObjectInit();
					// 나 2번임.

					// 패킷으로 클라이언트

					std::shared_ptr<UserIDPacket> ObjectPtr = std::make_shared<UserIDPacket>();
					int ObjectId = Other->GetNetObjectID();
					ObjectPtr->SetObjectID(ObjectId);

					GameNetSerializer Ser;
					ObjectPtr->SerializePacket(Ser);


					send(_Socket, Ser.GetDataConstPtr(), Ser.GetWriteOffSet(), 0);
				});
			NetInst = &Server;
			IsServer = true;

			// 내가 서버야 그럼 이제 난 그냥 그 순간 플레이어를 만든다. 
			//서버의 플레이어(서버 자신이 움직일 )를 생성
			ServerCharacterBase* player = object::Instantiate<ServerCharacterBase>(eLayerType::Player, this);
			
			player->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 10.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			player->SetName(L"Player");

			YourPlayer* PS = player->AddComponent<YourPlayer>();
			
			YourPlayerMove* PSM = player->AddComponent<YourPlayerMove>();
			

			PS->ServerObjectInit();
		}

		if (Input::GetKeyDown(eKeyCode::N_0))
		{
			Client.Dispatcher.AddHandler<UserIDPacket>(PacketEnumType::UserIDPacket,
				[=](std::shared_ptr<UserIDPacket> _Packet)
				{
					//클라이언트는 서버가 허락했으니까 이제 시작한다. 
					//클라이언트의 자신이 움직일 친구
					ServerCharacterBase* player = object::Instantiate<ServerCharacterBase>(eLayerType::Player);
					player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
					player->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
					player->SetName(L"Player");
					
					YourPlayer* Script = player->AddComponent<YourPlayer>();
					
					YourPlayerMove* PSM = player->AddComponent<YourPlayerMove>();
					

					int ObjectId = _Packet->GetObjectID();

					Script->ClientObjectInit(ObjectId);
					// Other->ClientObjectInit(_Packet->GetObjectId());
				}
			);

			Client.Dispatcher.AddHandler<ObjectUpdatePacket>(PacketEnumType::ObjectUpdatePacket,
				[=](std::shared_ptr<ObjectUpdatePacket> _Packet)
				{//서버와 동기화 할 오브젝트 
					if (false == GameNetObject::IsNetObject(_Packet->GetObjectID()))
					{
						GameObject* Otherplayer = object::Instantiate<GameObject>(eLayerType::Player);
						

						Otherplayer->GetComponent<Transform>()->SetPosition(Vector3(5.0f, 0.0f, 10.0f));
						Otherplayer->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
						Otherplayer->SetName(L"OtherPlayer");
				
						OtherPlayer* Other = Otherplayer->AddComponent<OtherPlayer>();
						
						int ObjectID = _Packet->GetObjectID();

						Other->ClientObjectInit(_Packet->GetObjectID());

					}

					GameNetObject::PushObjectPacket(_Packet);

				}
			);


			Client.Connect("127.0.0.1", 30000);
			NetInst = &Client;

			//SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void ServerScene::FixedUpdate()
	{
		// 오브젝트들이 업데이트 되기 전에
		if (nullptr != NetInst)
		{
			NetInst->PacketProcess();
		}

		Scene::FixedUpdate();
	}
	void ServerScene::Render()
	{
		Scene::Render();
	}
	void ServerScene::OnEnter()
	{
	}
	void ServerScene::OnExit()
	{
	}
}
