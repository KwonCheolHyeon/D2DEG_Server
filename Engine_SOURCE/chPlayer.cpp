#include "chPlayer.h"
#include "chInput.h"
#include "chMath.h"
#include "chTime.h"
namespace ch
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{


		GameObject::Initalize();
	}

	void Player::Update()
	{
		Vector3 posi = GetComponent<Transform>()->GetPosition();

	
		if (Input::GetKeyDown(eKeyCode::T) )
		{
			Vector3 target = posi + Vector3(0.f, 2.f, 0.f);
			posi = Vector3::Lerp(posi, target, 0.1f);
			GetComponent<Transform>()->SetPosition(posi);
		}


		GameObject::Update();
		//head->update();
		//body->update();

	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
