#pragma once
#include "chGameObject.h"
#include "chBullet.h"
namespace ch
{
	class BulletPool : public GameObject
	{
	public:
		BulletPool();
		virtual ~BulletPool();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void SetBullets(Bullet* bullet) { availableBullets.push_back(bullet); }
		BulletPool* GetPool() { return pool; }

	public:
        // Function to get a Bullet object from the pool
		Bullet* GetBullet();
        // Function to return a Bullet object to the pool
		void ReturnBullet(Bullet* bullet);

	private:
		BulletPool* pool ;
		std::vector<Bullet*> availableBullets;

		int bulletCont;
	};

}

