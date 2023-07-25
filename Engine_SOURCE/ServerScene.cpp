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

		// 3D �⺻ �޽�
		// 1. ť��
		//mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
		// 2. ���Ǿ�
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

					// �ٸ� ���ֵ鿡�Ե� ������.
					NetInst->PacketSend(_Packet);
				}
			);

			Server.OpenHost(30000, [=](SOCKET _Socket)
				{//Ŭ���̾�Ʈ ������Ʈ ����
					GameObject* Otherplayer = object::Instantiate<GameObject>(eLayerType::Player);
					
					Otherplayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
					Otherplayer->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 5.0f));
					Otherplayer->SetName(L"OtherPlayer");
	
					OtherPlayer* Other = Otherplayer->AddComponent<OtherPlayer>();
					
					// ���� ������Ʈ init�� ȣ���ص� �ȴ�.
					Other->ServerObjectInit();
					// �� 2����.

					// ��Ŷ���� Ŭ���̾�Ʈ

					std::shared_ptr<UserIDPacket> ObjectPtr = std::make_shared<UserIDPacket>();
					int ObjectId = Other->GetNetObjectID();
					ObjectPtr->SetObjectID(ObjectId);

					GameNetSerializer Ser;
					ObjectPtr->SerializePacket(Ser);


					send(_Socket, Ser.GetDataConstPtr(), Ser.GetWriteOffSet(), 0);
				});
			NetInst = &Server;
			IsServer = true;

			// ���� ������ �׷� ���� �� �׳� �� ���� �÷��̾ �����. 
			//������ �÷��̾�(���� �ڽ��� ������ )�� ����
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
					//Ŭ���̾�Ʈ�� ������ ��������ϱ� ���� �����Ѵ�. 
					//Ŭ���̾�Ʈ�� �ڽ��� ������ ģ��
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
				{//������ ����ȭ �� ������Ʈ 
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
		// ������Ʈ���� ������Ʈ �Ǳ� ����
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
