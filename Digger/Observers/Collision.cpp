#include "Collision.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Dig/Dig.h"
#include "Bag/bag.h"
#include "Event/Event.h"
#include "GameEvents.h"

namespace dae
{
	Collision::Collision(Player* player)
		:m_pPlayer{ player }
	{}

	void Collision::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == BAG_COLLISION)
		{
			event.args[0].go->GetComponent<Bag>()->CollideWithActor(m_pPlayer->GetDirection(), m_pPlayer);
		}
	}
}