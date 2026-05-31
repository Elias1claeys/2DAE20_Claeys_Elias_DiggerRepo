#include "Collision.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Hole/Hole.h"
#include "Bag/bag.h"
#include "Event/Event.h"
#include "GameEvents.h"

namespace dae
{
	Collision::Collision(Hole* digGround, Player* player)
		:m_pDigGround{ digGround }, m_pPlayer{ player }
	{}

	void Collision::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == PLAYER_MOVED)
		{
			m_pDigGround->DigTile(event.args[0].v3, event.args[1].v2);
		}
		if (event.id == BAG_COLLISION)
		{
			event.args[0].go->GetComponent<Bag>()->CollideWithActor(m_pPlayer->GetDirection(), m_pPlayer);
		}
	}
}