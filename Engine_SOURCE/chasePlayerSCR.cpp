#include "chasePlayerSCR.h"
#include "chGameObject.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
namespace ch 
{
	chasePlayerSCR::chasePlayerSCR()
	{
	}

	chasePlayerSCR::~chasePlayerSCR()
	{
	}

	void chasePlayerSCR::Initalize()
	{
		
		findPlayer = false;
		mCollider = GetOwner()->GetComponent<Collider2D>();
	}

	void chasePlayerSCR::Update()
	{
	}

	void chasePlayerSCR::FixedUpdate()
	{
	}

	void chasePlayerSCR::Render()
	{
	}

	void chasePlayerSCR::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Player || oppo->GetOwner()->GetName() == L"Player")
		{
			findPlayer = true;
		}
	}

	void chasePlayerSCR::OnCollision(Collider2D* oppo)
	{
	}

	void chasePlayerSCR::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Player|| oppo->GetOwner()->GetName() == L"Player" )
		{
			findPlayer = false;
		}
	}

	void chasePlayerSCR::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void chasePlayerSCR::OnTrigger(Collider2D* oppo)
	{
	}

	void chasePlayerSCR::OnTriggerExit(Collider2D* oppo)
	{
	}

}