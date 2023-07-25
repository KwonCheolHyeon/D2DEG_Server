#include "YourPlayerMove.h"
#include "YourPlayer.h"
#include "chInput.h"
#include "chTime.h"
//eServerPlayerState
//eServerPlayerDodgeDirections
namespace ch 
{
	bool YourPlayerMove::ServercanDodge = true;
	YourPlayerMove::YourPlayerMove()
	{
	}
	YourPlayerMove::~YourPlayerMove()
	{
	}
	void YourPlayerMove::Initalize()
	{
		pTr = GetOwner()->GetComponent<Transform>();
		pRb = GetOwner()->GetComponent<Rigidbody>();
		pS = eServerPlayerState::eIdle;
		ServercanDodge = true;
		isDodging = false;
		isWall = false;
		directNum = 0;
		secdirectNum = 0;
		wallPosition = Vector3::Zero;
		speed = 3.5f;
		colliderCount = 0;
		GetOwner()->setHand();
	}
	void YourPlayerMove::Update()
	{
		chState();


		if (Input::GetKeyDown(eKeyCode::RBTN) && !isDodging)
		{
			pS = eServerPlayerState::eRolling;
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			speed = 1.f;

		}

		switch (pS)
		{
		case eServerPlayerState::eIdle:
			Idle();
			break;
		case eServerPlayerState::eWalk:
			Walking();
			break;
		case eServerPlayerState::eRolling:
			GetOwner()->setNoHand();
			Dodging();
			break;
		default:

			break;
		}

		afterDodging();
	}
	void YourPlayerMove::FixedUpdate()
	{
	}
	void YourPlayerMove::Render()
	{
	}
	void YourPlayerMove::OnCollisionEnter(Collider2D* oppo)
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
				if (pS == eServerPlayerState::eWalk)
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
				if (pS == eServerPlayerState::eWalk)
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
	void YourPlayerMove::OnCollision(Collider2D* oppo)
	{
	}
	void YourPlayerMove::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetName() == (L"MapWall"))
		{
			colliderCount--;
			isWall = false;
			directNum = 0;
			secdirectNum = 0;
		}
	}
	void YourPlayerMove::Idle()
	{
	}
	void YourPlayerMove::Walking()
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
	void YourPlayerMove::afterWalking()
	{
		if (Input::GetKeyUp(eKeyCode::W))
		{
			pS = eServerPlayerState::eIdle;
		}
		//					아래
		if (Input::GetKeyUp(eKeyCode::S))
		{
			pS = eServerPlayerState::eIdle;
		}
		//					왼쪽
		if (Input::GetKeyUp(eKeyCode::A)) //뒤집어서 
		{
			pS = eServerPlayerState::eIdle;
		}
		//					오른쪽
		if (Input::GetKeyUp(eKeyCode::D))
		{
			pS = eServerPlayerState::eIdle;
		}
	}
	void YourPlayerMove::Dodging()
	{
		isDodging = true;
		ServercanDodge = false;
		float power = 800.f;

		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = eServerPlayerDodgeDirections::eNWDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = eServerPlayerDodgeDirections::eNEDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, -2.0f, 0.0f) * power); // 방향  * power
			pDD = eServerPlayerDodgeDirections::eEastDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, -2.0f, 0.0f) * power);
			pDD = eServerPlayerDodgeDirections::eWestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			pRb->SetVelocity(Vector3(0.f, -2.0f, 0.0f) * power);
			pDD = eServerPlayerDodgeDirections::eSouthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			pRb->SetVelocity(Vector3::Up * power);
			pDD = eServerPlayerDodgeDirections::eNorthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			pRb->SetVelocity(Vector3::Left * power);
			pDD = eServerPlayerDodgeDirections::eWestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			pRb->SetVelocity(Vector3::Right * power);
			pDD = eServerPlayerDodgeDirections::eEastDodge;
		}
	}
	void YourPlayerMove::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&YourPlayerMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&YourPlayerMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&YourPlayerMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&YourPlayerMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&YourPlayerMove::gotoNormal, this);
	}
	void YourPlayerMove::gotoNormal()
	{
		GetOwner()->setHand();
		isDodging = false; // Reset isDodging flag
		ServercanDodge = true; // Enable dodging again
		if (CheckKeyDirection())
		{
			pS = eServerPlayerState::eWalk;
		}
		else
		{
			pS = eServerPlayerState::eIdle;
		}

		// Reset the rolling state
		isRolling = false;
	}
	bool YourPlayerMove::CheckKeyDirection()
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
	

	void YourPlayerMove::chState()
	{
		if (ServercanDodge)
		{
			bool isWalking = false;

			if (Input::GetKey(eKeyCode::W) || Input::GetKey(eKeyCode::A) ||
				Input::GetKey(eKeyCode::S) || Input::GetKey(eKeyCode::D))
			{
				isWalking = true;
			}

			if (isWalking)
			{
				pS = eServerPlayerState::eWalk;
			}
			else
			{
				pS = eServerPlayerState::eIdle;
			}
		}
		else
		{
			pS = eServerPlayerState::eDefault;
		}
	}
	
	int YourPlayerMove::GetClosestDirection(Collider2D* collider)
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

