#include "Digged.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Hole/Hole.h"
#include "Event/Event.h"
#include "GameEvents.h"

namespace dae
{
	Dig::Dig(GameObject* digGround)
		:m_pDigGround{ digGround }
	{}

	void Dig::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == PLAYER_MOVED)
		{
			m_pDigGround->GetComponent<Hole>()->DigTile(event.args[0].v3, event.args[1].v2);
		}
	}
}