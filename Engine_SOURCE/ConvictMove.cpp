#include "ConvictMove.h"
#include "CharacterBase.h"
#include "Convict.h"
#include "chInput.h"
#include "chTime.h"
namespace ch
{
	bool ConvictMove::canDodge = true;

	ConvictMove::ConvictMove()
	{
	}
	ConvictMove::~ConvictMove()
	{
	}
	void ConvictMove::Initalize()
	{
		pTr = GetOwner()->GetComponent<Transform>();
		pRb = GetOwner()->GetComponent<Rigidbody>();
		pS = PlayerState::Idle;
		canDodge = true;
		isDodging = false;
		isWall = false;
		directNum = 0;
		secdirectNum = 0;
		wallPosition = Vector3::Zero;
		speed = 3.5f;
		colliderCount = 0;
		GetOwner()->setHand();
	}
	void ConvictMove::Update()
	{

		chState();


		if (Input::GetKeyDown(eKeyCode::RBTN) && !isDodging)
		{
			pS = PlayerState::Rolling;
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			speed = 1.f;

		}

		switch (pS)
		{
		case PlayerState::Idle:
			Idle();
			break;
		case PlayerState::Walk:
			Walking();
			break;
		case PlayerState::Rolling:
			GetOwner()->setNoHand();
			Dodging();
			break;
		default:

			break;
		}

		afterDodging();




	}
	void ConvictMove::FixedUpdate()
	{

	}
	void ConvictMove::Render()
	{
	}

	void ConvictMove::OnCollisionEnter(Collider2D* oppo)
	{

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetName() == (L"MapWall"))
		{
			colliderCount++;

			if (colliderCount == 1)
			{

				if (isDodging == true)
				{
					pRb->SetVelocity(Vector3::Zero);
				}
				if (pS == PlayerState::Walk)
				{
					if (GetClosestDirection(oppo) == 1) //상
					{
						directNum = 1;
					}
					else if (GetClosestDirection(oppo) == 2)
					{
						directNum = 2;
					}
					else if (GetClosestDirection(oppo) == 3)
					{
						directNum = 3;
					}
					else if (GetClosestDirection(oppo) == 4)
					{
						directNum = 4;
					}
				}

			}
			else if (colliderCount == 2)
			{
				if (isDodging == true)
				{
					pRb->SetVelocity(Vector3::Zero);
				}
				if (pS == PlayerState::Walk)
				{
					if (GetClosestDirection(oppo) == 1) //상
					{
						secdirectNum = 1;
					}
					else if (GetClosestDirection(oppo) == 2)
					{
						secdirectNum = 2;
					}
					else if (GetClosestDirection(oppo) == 3)
					{
						secdirectNum = 3;
					}
					else if (GetClosestDirection(oppo) == 4)
					{
						secdirectNum = 4;
					}
				}
			}
		}

	}

	void ConvictMove::OnCollision(Collider2D* oppo)
	{

	}

	void ConvictMove::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetName() == (L"MapWall"))
		{
			colliderCount--;
			isWall = false;
			directNum = 0;
			secdirectNum = 0;
		}
	}

	void ConvictMove::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void ConvictMove::OnTrigger(Collider2D* oppo)
	{
	}

	void ConvictMove::Walking()
	{
		Vector3 direction = Vector3::Zero;

		// Up
		if (Input::GetKey(eKeyCode::W))
		{
			if (directNum == 1 || secdirectNum == 1)
			{
				direction += Vector3::Zero;
			}
			else
			{
				direction += Vector3::Up;
			}
		}
		// Down
		if (Input::GetKey(eKeyCode::S))
		{

			if (directNum == 3 || secdirectNum == 3)
			{
				direction += Vector3::Zero;
			}
			else
			{
				direction += Vector3::Down;
			}
		}
		// Left
		if (Input::GetKey(eKeyCode::A))
		{

			if (directNum == 4 || secdirectNum == 4)
			{
				direction += Vector3::Zero;
			}
			else
			{
				direction += Vector3::Left;
			}
		}
		// Right
		if (Input::GetKey(eKeyCode::D))
		{

			if (directNum == 2 || secdirectNum == 2)
			{
				direction += Vector3::Zero;
			}
			else
			{
				direction += Vector3::Right;
			}
		}

		// Normalize diagonal movement
		if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
			direction != Vector3::Left && direction != Vector3::Right)
		{
			direction.Normalize();
		}


		Vector3 velocity = direction * speed;


		pRb->SetVelocity(velocity);


	}

	void ConvictMove::Idle()
	{

	}

	void ConvictMove::OnTriggerExit(Collider2D* oppo)
	{
	}

	void ConvictMove::afterWalking()
	{
		if (Input::GetKeyUp(eKeyCode::W))
		{
			pS = PlayerState::Idle;
		}
		//					아래
		if (Input::GetKeyUp(eKeyCode::S))
		{
			pS = PlayerState::Idle;
		}
		//					왼쪽
		if (Input::GetKeyUp(eKeyCode::A)) //뒤집어서 
		{
			pS = PlayerState::Idle;
		}
		//					오른쪽
		if (Input::GetKeyUp(eKeyCode::D))
		{
			pS = PlayerState::Idle;
		}

	}

	void ConvictMove::Dodging()
	{
		isDodging = true;
		canDodge = false;
		float power = 800.f;

		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::NWDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::NEDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, -2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::EastDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, -2.0f, 0.0f) * power);
			pDD = PlayerDodgeDirections::WestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			pRb->SetVelocity(Vector3(0.f, -2.0f, 0.0f) * power);
			pDD = PlayerDodgeDirections::SouthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			pRb->SetVelocity(Vector3::Up * power);
			pDD = PlayerDodgeDirections::NorthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			pRb->SetVelocity(Vector3::Left * power);
			pDD = PlayerDodgeDirections::WestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			pRb->SetVelocity(Vector3::Right * power);
			pDD = PlayerDodgeDirections::EastDodge;
		}

	}

	void ConvictMove::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
	}

	void ConvictMove::gotoNormal()
	{
		GetOwner()->setHand();
		isDodging = false; // Reset isDodging flag
		canDodge = true; // Enable dodging again
		if (CheckKeyDirection())
		{
			pS = PlayerState::Walk;
		}
		else
		{
			pS = PlayerState::Idle;
		}

		// Reset the rolling state
		isRolling = false;
	}

	bool ConvictMove::CheckKeyDirection()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ConvictMove::chState()
	{
		if (canDodge)
		{
			bool isWalking = false;

			if (Input::GetKey(eKeyCode::W) || Input::GetKey(eKeyCode::A) ||
				Input::GetKey(eKeyCode::S) || Input::GetKey(eKeyCode::D))
			{
				isWalking = true;
			}

			if (isWalking)
			{
				pS = PlayerState::Walk;
			}
			else
			{
				pS = PlayerState::Idle;
			}
		}
		else
		{
			pS = PlayerState::Default;
		}


	}

	int ConvictMove::GetClosestDirection(Collider2D* collider)
	{
		// Get the positions and scales of the wall and character
		Vector3 wallPosition = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 wallScale = collider->GetOwner()->GetComponent<Transform>()->GetScale();

		Vector3 playerPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 playerScale = this->GetOwner()->GetComponent<Transform>()->GetScale();

		// Calculate the distances between the centers of the wall and character
		float dx = wallPosition.x - playerPosition.x;
		float dy = wallPosition.y - playerPosition.y;

		// Calculate half sizes of the wall and character
		float halfWallWidth = wallScale.x / 2.0f;
		float halfWallHeight = wallScale.y / 2.0f;
		float halfPlayerWidth = playerScale.x / 2.0f;
		float halfPlayerHeight = playerScale.y / 2.0f;

		// Calculate the distance between the centers of the wall and character along x and y axes
		float deltaX = std::abs(dx) - (halfWallWidth + halfPlayerWidth);
		float deltaY = std::abs(dy) - (halfWallHeight + halfPlayerHeight);

		// Determine the closest direction based on the distances
		if (deltaX > deltaY)
		{
			if (dx > 0)
				return 2;
			else
				return 4;
		}
		else
		{
			if (dy > 0)
				return 1;
			else
				return 3;
		}
	}

}