#pragma once
#include "chGameObject.h"
#include "chPlayerHand.h"
#include "chBullet.h"
#include "chBulletPool.h"
#include "chAnimator.h"
#include "chGenericAnimator.h"

namespace ch
{
	struct GunStat
	{
		int damage; // ÃÑ µ¥¹ÌÁö
		int speed; //ÃÑ ½ºÇÇµå
		int bulletCount; // ÃÑ¾ËÀÇ °¹¼ö
		int magazineCount;//ÅºÃ¢ÀÇ ÃÑ °¹¼ö
	};

	class Gun : public GameObject
	{
	public:
		Gun();
		virtual ~Gun();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SwapGun();

		void SetHand(PlayerHand* hand) { playerHand = hand; }
		PlayerHand* GetHand() { return playerHand; }

		void SetPlayer(GameObject* _player) { player = _player; }
		GameObject* GetPlayer() { return player; }

		void SetPool(BulletPool* pool) { bulletpool = pool; }
		BulletPool* GetPool() { return bulletpool; }

		void SetGunBox(GameObject* box) { gunBox = box; }
		GameObject* GetGunBox() { return gunBox; }

		
	public:
		float angle;
		void angleFind();

	public:
		Vector3 rebound;
		void HandDownAnimate(Vector3 handPos);//GenericAnimator
		void HandUpAnimate(Vector3 handPos);//GenericAnimator
		void HandDownPos(float cur);
		void HandUpPos(float cur);

	protected:
		void GunLookCursor();
	
		PlayerHand* playerHand;
		GameObject* player;

	private:
		GameObject* gunObject;
		GameObject* gunBox;
		Transform* gunTransform;
		BulletPool* bulletpool;
		Bullet* bulletOBJ;
		std::vector<Bullet*> bullets;
		bool CollectAcces;
		Collider2D* col;


	

		GenericAnimator genericAnimator;
	};

}
