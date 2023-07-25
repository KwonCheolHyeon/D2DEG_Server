#include "chPlayScene.h"  
#include "chSceneManager.h"
#include "chInput.h"
#include "chObject.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chRenderer.h"
#include "chMeshRenderer.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "mainPlayer.h"
#include "chMouseCursorScript.h"
#include "chPlayerHand.h"
#include "chGun.h"
#include "chBulletPool.h"
#include "chBulletScr.h"
#include "chPaintShader.h"
#include "chHeart_UI.h"
#include "Heart_Scr.h"
#include "chPlayerScr.h"
#include "MonsterBase.h"
#include "Bullet_Kin.h"
#include "TableObject.h"
#include "MapObject.h"
#include "chCollisionManager.h"
#include "CharacterBase.h"
#include "Bullet_Kin_Gun.h"
#include "chBoss.h"
#include "Convict.h"
#include "ItemBoxScr.h"
#include "DoorObj.h"
#include "DoorScr.h"
#include "DoorColliderObj.h"
#include "HeartObj.h"
#include "BlankBulletObj.h"
#include "BlankBulletScr.h"
#include "BlankBullet_UI.h"
#include "ConvictBlankBulletObj.h"
#include "ConvictBlankBulletScr.h"
#include "LampObj.h"
#include "BullatScr.h"
#include "CubeScr.h"
#include "BoosDoorObj.h"
#include "BoosDoorScr.h"
#include "BlackMapObj.h"
#include "chFightSabreObject.h"
#include "FightSabreBoxScr.h"
#include "BossHpUIObj.h"
#include "BossHpUIScr.h"
#include "BossHpBarObj.h"
#include "BossHpBarScr.h"
#include "EventObj.h"
#include "EventScr.h"
#include "BossSceneObj.h"
#include "BossSceneScr.h"
#include "ReloadButtonObj.h"
#include "ReloadButtonScr.h"
#include "ReloadBarObj.h"
#include "ReloadBarScr.h"

namespace ch
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, chUiCursor(nullptr)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		{
			{
				GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Directional);
				lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			}

			{//횟불에 씀
				/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Point);
				lightComp->SetRadius(10.0f);
				lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));*/
			}
		
		
		}
		{ //Main Camera 
			chCameraOBJ = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = chCameraOBJ->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraScr = chCameraOBJ->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
#pragma region UI모음
		{
			{
				BlankBulletObj* blank0 = object::Instantiate<BlankBulletObj>(eLayerType::UI, this);
				blank0->SetName(L"BlankBulletUI");
				blank0->AddComponent<BlankBullet_UI>();
				Transform* htr0 = blank0->GetComponent<Transform>();
				htr0->SetPosition(Vector3(-6.5f, 3.9f, 0.f));
				htr0->SetScale(Vector3(0.7f, 0.65f, 0.f));

				BlankBulletObj* blank1 = object::Instantiate<BlankBulletObj>(eLayerType::UI, this);
				blank1->SetName(L"BlankBulletUI");
				blank1->AddComponent<BlankBullet_UI>();
				Transform* htr1 = blank1->GetComponent<Transform>();
				htr1->SetPosition(Vector3(-5.7f, 3.9f, 0.f));
				htr1->SetScale(Vector3(0.7f, 0.65f, 0.f));

				BlankBulletObj* blank2 = object::Instantiate<BlankBulletObj>(eLayerType::UI, this);
				blank2->SetName(L"BlankBulletUI");
				blank2->AddComponent<BlankBullet_UI>();
				Transform* htr2 = blank2->GetComponent<Transform>();
				htr2->SetPosition(Vector3(-4.9f, 3.9f, 0.f));
				htr2->SetScale(Vector3(0.7f, 0.65f, 0.f));

				BlankBulletObj* blank3 = object::Instantiate<BlankBulletObj>(eLayerType::UI, this);
				blank3->SetName(L"BlankBulletUI");
				blank3->AddComponent<BlankBullet_UI>();
				Transform* htr3 = blank3->GetComponent<Transform>();
				htr3->SetPosition(Vector3(-4.1f, 3.9f, 0.f));
				htr3->SetScale(Vector3(0.7f, 0.65f, 0.f));

				BlankBulletControl.push_back(blank0);
				BlankBulletControl.push_back(blank1);
				BlankBulletControl.push_back(blank2);
				BlankBulletControl.push_back(blank3);

			}
			{
				Heart_UI* heart0 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart0->SetName(L"HearUI");
				heart0->AddComponent<Heart_Scr>();
				Transform* htr0 = heart0->GetComponent<Transform>();
				htr0->SetPosition(Vector3(-6.5f, 4.9f, 0.f));
				htr0->SetScale(Vector3(0.7f, 0.65f, 0.f));


				Heart_UI* heart1 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart1->SetName(L"HearUI");
				heart1->AddComponent<Heart_Scr>();
				Transform* htr1 = heart1->GetComponent<Transform>();
				htr1->SetPosition(Vector3(-5.7f, 4.9f, 0.f));
				htr1->SetScale(Vector3(0.7f, 0.65f, 0.f));


				Heart_UI* heart2 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart2->SetName(L"HearUI");
				heart2->AddComponent<Heart_Scr>();
				Transform* htr2 = heart2->GetComponent<Transform>();
				htr2->SetPosition(Vector3(-4.9f, 4.9f, 0.f));
				htr2->SetScale(Vector3(0.7f, 0.65f, 0.f));

				HeartControl.push_back(heart0); //첫번째
				HeartControl.push_back(heart1); //두번째
				HeartControl.push_back(heart2); //세번째
			}

			

		}
#pragma endregion

		{//총알

			generateBullet(100);
		}

		generateObject();

		{
				player = object::Instantiate<CharacterBase>(eLayerType::Player, this);
				player->SetName(L"Player");
				player->GetComponent<Convict>()->SetHeart_UI(HeartControl);
				player->GetComponent<Convict>()->SetBlankBullet_UI(BlankBulletControl);
				player->setCameraScr(cameraScr);

				GameObject* ConvictBlankcol = object::Instantiate<ConvictBlankBulletObj>(eLayerType::Player, this);
				ConvictBlankcol->SetName(L"ConvictBlankcolider");
				ConvictBlankBulletScr* ConBlankscr = ConvictBlankcol->AddComponent<ConvictBlankBulletScr>();
				ConBlankscr->SetConvit(player);
				player->GetComponent<Convict>()->SetBlankBulletscr(ConBlankscr);

				GameObject* gunBox = object::Instantiate<GameObject>(eLayerType::Weapone, this);
				gunBox->SetName(L"GunBox");
				gunBox->GetComponent<Transform>()->SetPosition(Vector3(-16.1f, -3.23f, 0.f));
				gunBox->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f,0.f));


				PlayerHand* hand = object::Instantiate<PlayerHand>(eLayerType::Hand, this);
				hand->SetName(L"PHand");
				hand->SetPlayer(player);

				Gun *gun = object::Instantiate<Gun>(eLayerType::Hand, this);
				gun->SetName(L"PGun");
				gun->SetHand(hand);
				gun->SetPool(pool);
				gun->SetGunBox(gunBox);
				gun->SetPlayer(player);


		}
			//재장전 바
		{
			ReloadBarObj* reloadBar = object::Instantiate<ReloadBarObj>(eLayerType::Dummy, this);
			Transform* reloadBarTr = reloadBar->GetComponent<Transform>();
			reloadBarTr->SetScale(Vector3(1.f, 0.2f, 1.f));
			ReloadBarScr* reloadBarScr = reloadBar->AddComponent<ReloadBarScr>();
			reloadBarScr->SetPlayer(player);

			ReloadButtonObj* reloadButton = object::Instantiate<ReloadButtonObj>(eLayerType::Dummy, this);
			Transform* reloadButtonTr = reloadButton->GetComponent<Transform>();
			
			
			reloadButtonTr->SetScale(Vector3(0.05f, 0.15f, 1.f));
			ReloadButtonScr* reloadbuttonScr = reloadButton->AddComponent<ReloadButtonScr>();
			reloadbuttonScr->SetPlayer(player);

		}


		{//보스 문
			GameObject* BoosDoor = object::Instantiate<BoosDoorObj>(eLayerType::Object, this);
			BoosDoor->AddComponent<BoosDoorScr>();

		}

		{
			GameObject* Heart = object::Instantiate<HeartObj>(eLayerType::Object, this);
			Heart->SetName(L"heartObj");
			
			Transform* tr1 = Heart->GetComponent<Transform>();
			tr1->SetPosition(Vector3(-0.5f, -14.9f, 0.1f));

			GameObject* shopBullet = object::Instantiate<BlankBulletObj>(eLayerType::Object, this);
			shopBullet->SetName(L"BlankBulletObj");
			shopBullet->AddComponent<BlankBulletScr>();
			Transform* tr2 = shopBullet->GetComponent<Transform>();
			tr2->SetPosition(Vector3(4.78f, -22.88f, 0.1f));

			GameObject* shopHeart = object::Instantiate<HeartObj>(eLayerType::Object, this);
			shopHeart->SetName(L"heartObj");
			
			Transform* tr3 = shopHeart->GetComponent<Transform>();
			tr3->SetPosition(Vector3(7.27f, -22.88f, 0.1f));

			GameObject* BulletBlank = object::Instantiate<BlankBulletObj>(eLayerType::Object, this);
			BulletBlank->SetName(L"BlankBulletObj");
			BulletBlank->AddComponent<BlankBulletScr>();
			Transform* tr4 = BulletBlank->GetComponent<Transform>();
			tr4->SetPosition(Vector3(0.374f, -3.23f, 0.1f));
		}
#pragma region 스테이지1 몬스터
		{// 스테이지1 몬스터1
			
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-1.63f, 6.02f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(7.f, 7.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);
			

			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-5.011f, 6.56f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(7.f, 7.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);


			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-4.86f, 11.44f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(7.f, 7.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);


			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터4

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-7.87f, 5.52f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);



			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터5

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-6.65f, 6.77f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);



			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터6

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-2.078f, 12.66f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);



			mainDoor1->SetMonsterBases(kinMonster);
		}
#pragma endregion

#pragma region 스테이지2 몬스터
		{//스테이지2 몬스터1

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-19.44f, 8.32f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);



			mainDoor2->SetMonsterBases(kinMonster);
		}
		{//스테이지2 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-19.44f, 6.26f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);



			mainDoor2->SetMonsterBases(kinMonster);
		}
		{//스테이지2 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-19.45f, 4.24f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);



			mainDoor2->SetMonsterBases(kinMonster);
		}
	
		{//스테이지2 몬스터4

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-22.92f, 8.55f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor2->SetMonsterBases(kinMonster);
		}
		{//스테이지2 몬스터5

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-22.92f, 3.73f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor2->SetMonsterBases(kinMonster);
		}
		{//스테이지2 몬스터6

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-22.92f, 6.23f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor2->SetMonsterBases(kinMonster);

		}


		


#pragma endregion

#pragma region 스테이지3 몬스터
		{//스테이지3 몬스터1

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(11.45f, 1.86f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(13.05f, -0.15f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(15.9f, 2.f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor3->SetMonsterBases(kinMonster);
		}

		{//스테이지3 몬스터4

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Bullat");
			kinMonster->AddComponent<BullatScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(13.43f, 3.25f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"ChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(8.f, 8.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);



			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터5

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Bullat");
			kinMonster->AddComponent<BullatScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(10.57f, 2.6f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"ChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(8.f, 8.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);



			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터6

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(15.2f, 0.31f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor3->SetMonsterBases(kinMonster);

		}

		

#pragma endregion


#pragma region 스테이지4 몬스터
		{//스테이지4 몬스터1

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(12.45f, -11.23f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor4->SetMonsterBases(kinMonster);
		}
		{//스테이지4 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(10.483f, -9.476f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor4->SetMonsterBases(kinMonster);
		}
		{//스테이지4 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(14.94f, -14.08f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor4->SetMonsterBases(kinMonster);
		}
		{//스테이지4 몬스터4
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(11.01f, -13.68f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor4->SetMonsterBases(kinMonster);
		}

		{//스테이지4 몬스터5
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(10.42f, -11.16f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor4->SetMonsterBases(kinMonster);
		}

		{//스테이지4 몬스터6
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Bullat");
			kinMonster->AddComponent<BullatScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(14.61f, -11.16f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"ChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(8.f, 8.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);


			mainDoor4->SetMonsterBases(kinMonster);
		}
#pragma endregion

#pragma region 스테이지5 몬스터
		{//스테이지5 몬스터1

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-13.7f, -12.046f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			

			mainDoor5->SetMonsterBases(kinMonster);
		}
		{//스테이지5 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"BulletKin");
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-14.7f, -15.046f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);



			mainDoor5->SetMonsterBases(kinMonster);
		}
		{//스테이지5 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-13.7f, -15.046f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor5->SetMonsterBases(kinMonster);
		}

		{//스테이지5 몬스터4

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-12.1f, -16.97f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor5->SetMonsterBases(kinMonster);
		}

		{//스테이지5 몬스터5

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Cube");
			kinMonster->AddComponent<CubeScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-16.27f, -16.97f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			mainDoor5->SetMonsterBases(kinMonster);
		}

		{//스테이지5 몬스터6
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->SetName(L"Bullat");
			kinMonster->AddComponent<BullatScr>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-16.53f, -13.91f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"ChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(8.f, 8.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);


			mainDoor5->SetMonsterBases(kinMonster);
		}
#pragma endregion

		{ //보스

			bossObj = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			bossObj->SetName(L"cBoss");
			bossObj->AddComponent<Boss>();
			Transform* bossTr = bossObj->GetComponent<Transform>();
			bossObj->SetPlayer(player);

			chasePlayerOBJ* chaseCol = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCol->SetName(L"Boss");

			Collider2D* mCollider = chaseCol->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(14.f, 12.f));

			chaseCol->SetOwnerTransform(bossTr);
			bossObj->SetMonsterChaseCollider(chaseCol);
			bossdeath = false;
		}

		{
			eventobj = object::Instantiate<EventObj>(eLayerType::Object, this);
			eventobj->AddComponent<EventScr>();
			Transform* tr = eventobj->GetComponent<Transform>();
			tr->SetPosition(Vector3(15.26f, 16.511f, 0.f));
			tr->SetScale(Vector3(1.f, 1.f, 0.1f));

			Collider2D* col = eventobj->AddComponent<Collider2D>();
			col->SetName(L"eventCol");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(1.f, 1.f));

			BossHpUIObj* blank = object::Instantiate<BossHpUIObj>(eLayerType::UI, this);
			blank->SetName(L"BossHpUIObj");
			BossHpUIScr* bb = blank->AddComponent<BossHpUIScr>();
			bb->SetEvent(eventobj);
			Transform* htr0 = blank->GetComponent<Transform>();
			htr0->SetPosition(Vector3(1.f, -3.f, 0.f));
			htr0->SetScale(Vector3(10.f, 10.f, 0.f));

			BossHpBarObj* blank0 = object::Instantiate<BossHpBarObj>(eLayerType::UI, this);
			blank0->SetName(L"BossHpBarObj");
			BossHpBarScr* aa = blank0->AddComponent<BossHpBarScr>();
			aa->SetBossMonster(bossObj);
			aa->SetEvent(eventobj);
			Transform* htr = blank0->GetComponent<Transform>();
			htr->SetPosition(Vector3(1.f, -3.f, 0.f));
			htr->SetScale(Vector3(10.f, 10.f, 0.f));


			BossSceneObj* bossScene = object::Instantiate<BossSceneObj>(eLayerType::UI, this);
			bossScene->SetName(L"BossScene");
			BossSceneScr* bsc = bossScene->AddComponent<BossSceneScr>();
			bsc->SetEvent(eventobj);
			Transform* ht = bossScene->GetComponent<Transform>();
			ht->SetPosition(Vector3(0.f, 1.f, -20.f));
			ht->SetScale(Vector3(35.f, 35.f, 0.f));
		}
		
		generateMap();
		
		audioObj[0] = object::Instantiate<GameObject>(eLayerType::UI,this);
		audioObj[1] = object::Instantiate<GameObject>(eLayerType::UI,this);
		audioObj[2] = object::Instantiate<GameObject>(eLayerType::UI);

		audioClip[0] = Resources::Load<AudioClip>(L"gamestart", L"music\\ost\\gamestart.mp3");
		audioClip[1] = Resources::Load<AudioClip>(L"bossfinding", L"music\\ost\\bossfind.mp3");
		audioClip[2] = Resources::Load<AudioClip>(L"bossend", L"music\\ost\\bossend.mp3");

		boss_audio[0] = audioObj[0]->AddComponent<AudioSource>();
		boss_audio[1] = audioObj[1]->AddComponent<AudioSource>();
		boss_audio[2] = audioObj[2]->AddComponent<AudioSource>();

		boss_audio[0]->SetClip(audioClip[0]);
		boss_audio[1]->SetClip(audioClip[1]);
		boss_audio[2]->SetClip(audioClip[2]);

		evnetOnce = false;


		chCameraOBJ->GetComponent<Camera>()->SetTarget(player);
		Scene::Initalize();

	}

	void PlayScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Main);
		}
		
		
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Vector3 mouse = Input::GetWorldMousPosition();
			Vector2 mouse2 = Input::GetWorldMousPosition2();
			Vector3 chara = player->GetComponent<Transform>()->GetPosition();

			int b = 0;   
		}

		if (eventobj->GetComponent<EventScr>()->GetEventState() == true && evnetOnce== false)
		{
			evnetOnce = true;
			boss_audio[0]->Stop();
			boss_audio[1]->Play();

		}
		if (bossObj->GetComponent<Boss>()->GetHp() == 0 && bossdeath == false)
		{
			bossdeath = true;
			boss_audio[1]->Stop();
			boss_audio[2]->Play();
		}
		
		audioObj[0]->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition() + Vector3(0.f,0.f,10.f));
		audioObj[1]->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition() + Vector3(0.f, 0.f, 10.f));
		audioObj[2]->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition() + Vector3(0.f, 0.f, 10.f));

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		CollisionManager::CollisionLayerCheck(eLayerType::Weapone, eLayerType::Monster);
		CollisionManager::CollisionLayerCheck(eLayerType::Object, eLayerType::Player); // 책상과 플레이어
		CollisionManager::CollisionLayerCheck(eLayerType::Object, eLayerType::Weapone);//총알과 책상
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Wall, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Wall, eLayerType::Weapone);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterCollider);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Object, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Wall, eLayerType::Monster);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);

		boss_audio[0]->SetLoop(true);
		boss_audio[0]->Play();

		Scene::OnEnter();
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();

	}

	void PlayScene::generateBullet(int size)
	{
		pool = object::Instantiate<BulletPool>(eLayerType::Weapone, this);

		for (size_t i = 0; i < size; i++)
		{
			Bullet* bulletobj = object::Instantiate<Bullet>(eLayerType::Weapone, this);
			containBullets.push_back(bulletobj);
			containBullets[i]->SetLayerType(eLayerType::Weapone);
			containBullets[i]->SetName(L"Bullet");
			containBullets[i]->GetComponent<Transform>()->SetPosition(Vector3(-1000.0f,-1000.0f, 0.0f));
			containBullets[i]->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 0.2f));

			Collider2D* mCollider = bulletobj->AddComponent<Collider2D>();
			mCollider->SetName(L"billetKinCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(1.f, 1.f));

			SpriteRenderer* render = containBullets[i]->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"W_BulletMaterial");
			render->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(bulletMesh);

			containBullets[i]->AddComponent<BulletScr>();
			pool->SetBullets(containBullets[i]);

		}

	}

	void PlayScene::generateMap()
	{
		{//back ground01
			GameObject* back = object::Instantiate<MapObject>(eLayerType::BackGround, this);
			back->SetName(L"BG01");

			mapTr = back->GetComponent<Transform>();
			mapTr->SetPosition(Vector3(0.0f, 0.0f, 5.1f));
			mapTr->SetScale(Vector3(50.0f, 62.91f, 0.1f));
		}
		{//back ground01
			GameObject* back = object::Instantiate<BlackMapObj>(eLayerType::BackGround, this);
			back->SetName(L"BG02");

			mapTr = back->GetComponent<Transform>();
			mapTr->SetPosition(Vector3(0.0f, 0.0f, 7.1f));
			mapTr->SetScale(Vector3(100.0f, 100.f, 0.1f));
		}
#pragma region 콜라이더
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-17.95f, -8.65f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.8f, 4.73f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.18f, -8.685f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.838f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.18f, -8.685f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.838f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-7.44f, -12.3f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.7f, 4.12f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-0.849f, -12.72f, 0.0f));
			mapColliderTr->SetScale(Vector3(7.61f, 1.44f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-7.47f, -17.145f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.64f, 3.55f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-13.05f, -21.057f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.975f, 4.686f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-18.3945f, -21.0669f, 0.0f));
			mapColliderTr->SetScale(Vector3(2.789f, 4.6482f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-19.045f, -14.8275f, 0.0f));
			mapColliderTr->SetScale(Vector3(2.201f, 8.075f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(5.8106f, -17.952f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.6181f, 5.136f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.466f, -18.15f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.312f, 4.718f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(1.51025f, -25.133133f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.7605f, 9.209f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-1.6754f, -21.2955f, 0.0f));
			mapColliderTr->SetScale(Vector3(9.5908f, 8.039f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(5.79209f, -11.289675f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.68518f, 6.2085f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.2376f, -5.59004f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.6972f, 5.17090661f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.66f, -5.833f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.3071f, 4.7041f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(13.27f, -18.19995f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.4287f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(16.34f, -5.861f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.14f, 4.763f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(16.8244f, -11.832f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.1668f, 9.062f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(7.28f, -28.73645f, 0.0f));
			mapColliderTr->SetScale(Vector3(8.164f, 1.0171f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.2755f, -24.11525f, 0.0f));
			mapColliderTr->SetScale(Vector3(0.581f, 8.2049f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(17.0536f, 0.3545f, 0.0f));
			mapColliderTr->SetScale(Vector3(0.6872f, 7.693f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.7725f, 6.32398f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.095f, 4.17116f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.2575f, 3.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.675f, 10.43256f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(17.3671f, 6.274f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.2342f, 4.24472f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(10.245f, 14.5855f, 0.0f));
			mapColliderTr->SetScale(Vector3(9.07f, 4.74f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(20.1622f, 14.5957f, 0.0f));
			mapColliderTr->SetScale(Vector3(8.8444f, 4.704f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.459f, 17.373f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.25f, 7.226f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-20.f, 10.4f, 0.0f));
			mapColliderTr->SetScale(Vector3(10.072f, 1.829f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.304f, 9.67025f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.682f, 6.0795f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-18.4508f, -0.3238f, 0.0f));
			mapColliderTr->SetScale(Vector3(13.1396f, 4.3608f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.324f, 3.48119f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.684f, 4.19662f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-5.72845f, 0.809f, 0.0f));
			mapColliderTr->SetScale(Vector3(8.7271f, 4.73911f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(2.973f, 16.6012f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.908f, 27.2576f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-4.9445f, 15.3185f, 0.0f));
			mapColliderTr->SetScale(Vector3(9.839f, 1.297f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(25.7005f, 23.876f, 0.0f));
			mapColliderTr->SetScale(Vector3(2.195f, 14.422f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.341f, 31.971f, 0.0f));
			mapColliderTr->SetScale(Vector3(19.278f, 3.696f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		
		

#pragma endregion

	}

	void PlayScene::generateObject()
	{
		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-16.52f, -12.79f, -10.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-21.19f, 17.58f, -10.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.5f, -13.0f, -10.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh01");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-20.64f, 19.38f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f,5.3f, 0.1f));
		
		}
		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh02");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-17.37f, 19.38f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f, 5.3f, 0.1f));

		}
		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh03");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-18.81f, 19.38f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f, 5.3f, 0.1f));

		}

		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh02");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-7.21f, 15.04f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f, 5.3f, 0.1f));

		}

		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh02");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-3.779f, 15.04f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f, 5.3f, 0.1f));

		}

		{//램프
			GameObject* LmpObj = object::Instantiate<LampObj>(eLayerType::Dummy, this);
			LmpObj->SetName(L"Lingh03");

			Transform* mapColliderTr = LmpObj->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(1.33f, -1.18f, -2.f));
			mapColliderTr->SetScale(Vector3(5.f, 5.3f, 0.1f));

		}


		


		{//스테이지 1 문
			mainDoor1 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor1->SetName(L"DoorSide");

			mainDoor1->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor1->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-9.57f, 14.34f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol11");
			DoorColObject->SetDoor(mainDoor1);
			

			mainDoor1->isMainDoorTrue();
		}

		{//문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-0.8f, 3.5f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorSide");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-9.6f, 7.2f, -1.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));
		}
		
		{//스테이지2 문
			mainDoor2 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor2->SetName(L"DoorSide");

			mainDoor2->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor2->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-14.9f, 7.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor2);
			

			mainDoor2->isMainDoorTrue();
		}

		{//스테이지3 문
			mainDoor3 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor3->SetName(L"DoorSide");

			mainDoor3->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor3->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.955f, -1.34f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor3);

			

			mainDoor3->isMainDoorTrue();
		}
		{//문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.32f, 5.73f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.32f, -2.92f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}

		{//스테이지4 문1
			mainDoor4 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor4->SetName(L"DoorFront");

			mainDoor4->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor4->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.31f, -6.7f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor4);

			

			mainDoor4->isMainDoorTrue();
		}

		{//스테이지4 문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(9.661f, -15.3f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}

		{//스테이지4  문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorSide");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.471f,-13.73f, -1.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));
		}



		{//스테이지5 문
			mainDoor5 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor5->SetName(L"DoorSide");

			mainDoor5->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor5->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-10.24f, -14.05f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor5);
		
			mainDoor5->isMainDoorTrue();
		}
		{//스테이지5 문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-14.6f, -9.6f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//스테이지5 문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-16.5f, -18.23f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}


		
		{//itemBox
			GameObject* itemGunBox = object::Instantiate<GameObject>(eLayerType::Object, this);
			ItemBoxScr* abc = itemGunBox->AddComponent<ItemBoxScr>();

			Transform* itemTr = itemGunBox->GetComponent<Transform>();
			itemTr->SetPosition(Vector3(-16.84f, -4.f, 0.1f));
			itemTr->SetScale(Vector3(5.f, 5.f, 1.f));

			//2번총
			FightSabreObject* item = object::Instantiate<FightSabreObject>(eLayerType::Object, this);
			item->AddComponent<FightSabreBoxScr>();
			item->GetComponent<Transform>()->SetPosition(Vector3(-1000.f,-1000.f,0.f));
			abc->SetFightSabreObject(item);

		}
	

	}



}
