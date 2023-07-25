#include "chOtherPlayerScript.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chAnimator.h"

#include "PacketEnum.h"
#include "GlobalPacket.h"

namespace ch
{
	OtherPlayerScript::OtherPlayerScript()
		: Script()
	{
	}

	OtherPlayerScript::~OtherPlayerScript()
	{
	}

	void OtherPlayerScript::Initalize()
	{
	}

	void OtherPlayerScript::Update()
	{
		if (0 == Packets.size())
		{
			return;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();

		while (0 != Packets.size())
		{
			std::shared_ptr<GameNetPacket> Packet = Packets.front();

			PacketEnumType Type = Packet->GetPacketIDToEnum<PacketEnumType>();

			switch (Type)
			{
			case PacketEnumType::ObjectUpdatePacket:
			{
				std::shared_ptr<ObjectUpdatePacket> ObjectPacket = Packet->DynamicConvert<ObjectUpdatePacket>();
				tr->SetPosition(ObjectPacket->Pos);
				break;
			}
			default:
				break;
			}



			Packets.pop_front();
		}



		int a = 0;

	}

	void OtherPlayerScript::Render()
	{
	}

	void OtherPlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void OtherPlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void OtherPlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void OtherPlayerScript::Start()
	{
	}

	void OtherPlayerScript::Action()
	{
	}

	void OtherPlayerScript::End()
	{
	}

}
