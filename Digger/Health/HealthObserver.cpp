#include "HealthObserver.h"
#include "Components/Text.h"
#include "Event/Event.h"
#include "GameEvents.h"
#include "HealthDisplay.h"
#include "Entities/Player/Player.h"
#include "Game/Game.h"

namespace dae
{
	HealthObserver::HealthObserver(GameObject* HealthDisplay, Level* Level)
		: m_pHealthDisplay(HealthDisplay), m_pLevel(Level)
	{}

	void HealthObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == TOOK_DAMAGE)
		{
			if (!event.args[0].go->GetComponent<Player>()->IsDead())
			{
				m_pHealthDisplay->GetComponent<HealthDisplay>()->DoDamage();
				event.args[0].go->GetComponent<Player>()->PlayerDead();

				m_Health--;

				if(m_Health == 0)
					m_pLevel->EndGame();
			}
		}
	}
}