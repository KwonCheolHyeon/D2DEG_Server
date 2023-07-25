#include "chPlayerScr.h"
#include "chInput.h"
#include "chTransform.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chGameObject.h"
#include "chRigidbody.h"
#include "chGenericAnimator.h"
#include "chPistol.h"
#include "chObject.h"
#include "Heart_Scr.h"

namespace ch 
{
	PlayerScr::PlayerScr()
	{
		mState[(UINT)ePlayerState::Front] = true;
		mState[(UINT)ePlayerState::Back] = false;
		mState[(UINT)ePlayerState::Left] = false;
		mState[(UINT)ePlayerState::Right] = false;

		mState[(UINT)ePlayerState::Walking] = false;
		mState[(UINT)ePlayerState::Idle] = true;
		mState[(UINT)ePlayerState::Dodge] = false;

		mState[(UINT)ePlayerState::Attack] = false;
		mState[(UINT)ePlayerState::Reload] = false;
		mState[(UINT)ePlayerState::Fall] = false;

		mState[(UINT)ePlayerState::Weapone] = false;


		C2Mangle = 0.f;
	}
	PlayerScr::~PlayerScr()
	{
	
		
	}
	void PlayerScr::Initalize()
	{
		mousePositon = Vector3::Zero;
		transform = GetOwner()->GetComponent<Transform>();
		animator = GetOwner()->GetComponent<Animator>();
		canDodge = true;
		pHp = 6;
		prevHp = 6;
		playerSpeed = 2.f;
	}
	void PlayerScr::Update()
	{
		GenericAnimator.Update(Time::DeltaTime());
		mousePos();//마우스 위치
		
		if (mState[(UINT)ePlayerState::Dodge] == false) 
		{
			chCheckDirectionKey();
			playerLookMouse();

			chState();
			chWalking();
			
			if (chCheckDirectionKey() == false)
			{
				chIdleAni();
			}
		}

		if (canDodge == true) {
			if (Input::GetKeyDown(eKeyCode::RBTN) && chCheckDirectionKey()== true)
			{
				GetOwner()->setNoHand();
				canDodge = false;
				mState[(UINT)ePlayerState::Dodge] = true;
				chDodging();
				chDodgeAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::G))
		{
			pHp -= 1;
		}
		if (Input::GetKeyDown(eKeyCode::H))
		{
			pHp += 1;
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			playerSpeed = 2.f;
		}
		if (Input::GetKeyDown(eKeyCode::E))
		{
			playerSpeed = 5.f;
		}

		if (prevHp != pHp) 
		{
			SetHeart();
		}


		

	}
	void PlayerScr::FixedUpdate()
	{
	}
	void PlayerScr::Render()
	{
	}

	#pragma region 충돌
	void PlayerScr::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void PlayerScr::OnCollision(Collider2D* oppo)
	{
	}
	void PlayerScr::OnCollisionExit(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTrigger(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTriggerExit(Collider2D* oppo)
	{
	}
	
#pragma endregion
	#pragma region 행동
	void PlayerScr::chWalking()
	{
		Vector3 pos = transform->GetPosition();
		Vector3 direction = Vector3::Zero;
		{//														움직임
			//					위
			if (Input::GetKey(eKeyCode::W))
			{
				direction += 3.5f * Vector3::Up * Time::DeltaTime();
			}
			//					아래
			if (Input::GetKey(eKeyCode::S))
			{
				direction += 3.5f * Vector3::Down * Time::DeltaTime();
			}
			//					왼쪽
			if (Input::GetKey(eKeyCode::A)) //뒤집어서 
			{
				direction += 3.5f * Vector3::Left * Time::DeltaTime();
			}
			//					오른쪽
			if (Input::GetKey(eKeyCode::D))
			{
				direction += 3.5f * Vector3::Right * Time::DeltaTime();
			}
			//			대각선 방향 움직일때
			if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
				direction != Vector3::Left && direction != Vector3::Right)
			{
				direction.Normalize();
			}

			pos += direction * playerSpeed * Time::DeltaTime();
			transform->SetPosition(pos);
		}
	}
	void PlayerScr::chDodging()
	{
		Vector3 dodgepos;
		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			dodgepos =  Vector3(-2.f, 2.0f, 0.0f);
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			dodgepos = Vector3(2.f, 2.0f, 0.0f);
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			dodgepos = Vector3(2.f, -2.0f, 0.0f);
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			dodgepos = Vector3(-2.f, -2.0f, 0.0f);
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			dodgepos = Vector3(0.f, -2.0f, 0.0f);
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			dodgepos = Vector3(0.f, 2.0f, 0.0f);
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			dodgepos = Vector3(-2.f, 0.0f, 0.0f);
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			dodgepos = Vector3(2.f, 0.0f, 0.0f);
		}

		GenAnimate(dodgepos);
	}
	#pragma endregion
	void PlayerScr::mousePos()//마우스와 캐릭터 사이의 각도를 계산해주는 함수
	{
		Vector3 mousePos = Input::GetMousPosition();

		mousePositon = (mousePos / 100.f);

		CharterPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();
		mousePositon += CharterPosition;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		C2Mangle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}
	bool PlayerScr::chCheckDirectionKey()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true)
		{
			mState[(UINT)ePlayerState::Walking] = true;
			mState[(UINT)ePlayerState::Idle] = false;
			return true;
		}
		else
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			return false;
		}
	}
	bool PlayerScr::chCheckDirectionKeyDoge()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true)
		{
			allowDodge();
			return true;
		}
		else
		{
			afterDodgeIdleAni();
			return false;
		}
	}
	void PlayerScr::chIdleAni()
	{
		if (compareState())
		{
			GetOwner()->setHand();
			if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_WIdleRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_WIdleRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WIdleFront", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				
				animator->Play(L"P_WIdleBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_WIdleBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WIdleBack", true);
			}
		}
		
	}
	void PlayerScr::afterDodgeIdleAni()
	{
		GetOwner()->setHand();
		if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WIdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WIdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WIdleFront", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WIdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WIdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WIdleBack", true);
		}
		canDodge = true;
	}
	void PlayerScr::chWalkAni()
	{
		if (compareState())
		{
			GetOwner()->setHand();
			if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_WWalkingRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_WWalkingRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WWalkingFront", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_WWalkingBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				
				animator->Play(L"P_WWalkingBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WWalkingBack", true);
			}
			canDodge = true;
		}
	}

	void PlayerScr::afterDodgeWalkAni()
	{
		GetOwner()->setHand();
		if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WWalkingRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WWalkingRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WWalkingFront", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WWalkingBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WWalkingBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WWalkingBack", true);
		}
		canDodge = true;
	}

	void PlayerScr::chDodgeAni()
	{
		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			GetOwner()->SetLeft();
			animator->Play(L"P_DodgeBackRight", false);

		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			GetOwner()->SetRight();
			animator->Play(L"P_DodgeBackRight", false);
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			GetOwner()->SetRight();
			animator->Play(L"P_DodgeRight", false);
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			GetOwner()->SetLeft();
			animator->Play(L"P_DodgeRight", false);
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			animator->Play(L"P_DodgeFront", false);

		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			animator->Play(L"P_DodgeBack", false);

		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			GetOwner()->SetLeft();
			animator->Play(L"P_DodgeRight", false);
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			GetOwner()->SetRight();
			animator->Play(L"P_DodgeRight", false);

		}
		afterDodge();

	}

	void PlayerScr::chState()
	{
		if(chCheckDirectionKey()== true)
		{
			chWalkAni();
		}

		if(Input::GetKeyDown(eKeyCode::W))
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			afterDodgeWalkAni();
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
				afterDodgeIdleAni();
			}
			else
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			afterDodgeWalkAni();
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			int a = 0;
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
				afterDodgeIdleAni();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			afterDodgeWalkAni();
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
				afterDodgeIdleAni();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			afterDodgeWalkAni();
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
				afterDodgeIdleAni();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}


	}

	void PlayerScr::afterDodge()
	{
		animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBackLeft") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeFront") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBack") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&PlayerScr::chCheckDirectionKeyDoge, this);
	}

	void PlayerScr::allowDodge()
	{
		mState[(UINT)ePlayerState::Dodge] = false;
		
		afterDodgeWalkAni();
	}

	void PlayerScr::gunHandSide()
	{
		if (C2Mangle >= 90 && C2Mangle < 270) //총 위치 왼쪽 //왼쪽 보기
		{
			GetOwner()->SetLeft();
		}
		else  //총 위치 오른쪽 // 오른쪽 보기
		{
			GetOwner()->SetRight();
		}
	}
	void PlayerScr::playerLookMouse()//각도에 따라 보는 방향 
	{
		mPrevState = mState;
		if (C2Mangle >= 30 && C2Mangle < 60) //right back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;

		}
		else if (C2Mangle >= 60 && C2Mangle < 120) //back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (C2Mangle >= 120 && C2Mangle < 150) //left Back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if(C2Mangle>=150 && C2Mangle <225) //left
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (C2Mangle >= 225 && C2Mangle < 315)//front
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else //right
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		gunHandSide();
	}

	void PlayerScr::GenAnimate(Vector3 dodgePos)
	{
		Position = dodgePos;
		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.4f;
		param.DurationTime = 0.5f;
		param.DurationFunc = [this](float InCurValue) {
			// This function will be called on every tick of the animation
			Vector3 pos = transform->GetPosition();
			pos += Position * InCurValue * Time::DeltaTime();
			transform->SetPosition(pos);
		};
		param.CompleteFunc = [this](float InCurValue) {
			// This function will be called when the animation is finished
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			mState[(UINT)ePlayerState::Dodge] = false;
		};

		// Register the parameters by calling the Start function on the member variable
		GenericAnimator.Start(param);

		mState[(UINT)ePlayerState::Idle] = false;
		mState[(UINT)ePlayerState::Walking] = false;
		mState[(UINT)ePlayerState::Dodge] = true;
	}

	bool PlayerScr::compareState()
	{
		if(	mState[(UINT)ePlayerState::Front] == mPrevState[(UINT)ePlayerState::Front] &&
			mState[(UINT)ePlayerState::Back] == mPrevState[(UINT)ePlayerState::Back] &&
			mState[(UINT)ePlayerState::Left] == mPrevState[(UINT)ePlayerState::Left] &&
			mState[(UINT)ePlayerState::Right] == mPrevState[(UINT)ePlayerState::Right])
		{
			return false;
		}
		else 
		{
			return true;
		}
		
	}

	#pragma region 체력
	void PlayerScr::SetHeart()
	{
		if (pHeartControl.size() != 0) //왜 두번 되는거지?
		{
			prevHp = pHp;
			if (pHp == 8)
			{
				/*pHeartControl[3]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);*/
			}
			else if (pHp == 7)
			{
				/*pHeartControl[3]->GetComponent<Heart_Scr>()->setCountHeart(1);*/
			}
			else if (pHp == 6)
			{
				/*if (pHeartControl[3] != nullptr) 
				{
					pHeartControl[3]->GetComponent<Heart_Scr>()->setCountHeart(0);
				}*/
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 5)
			{
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(1);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 4)
			{
				pHeartControl[2]->GetComponent<Heart_Scr>()->setCountHeart(0);
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(2);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 3)
			{
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(1);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 2)
			{
				pHeartControl[1]->GetComponent<Heart_Scr>()->setCountHeart(0);
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(2);
			}
			else if (pHp == 1)
			{
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(1);
			}
			else if (pHp == 0)
			{
				pHeartControl[0]->GetComponent<Heart_Scr>()->setCountHeart(0);
			}

		}
	}

#pragma endregion
}
