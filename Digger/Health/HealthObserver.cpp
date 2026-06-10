#include "HealthObserver.h"
#include "Components/Text.h"
#include "Event/Event.h"
#include "Observers/GameEvents.h"
#include "HealthDisplay.h"

namespace dae
{
	HealthObserver::HealthObserver(GameObject* HealthDisplay)
		: m_pHealthDisplay(HealthDisplay)
	{}

	void HealthObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == TOOK_DAMAGE)
		{
			m_pHealthDisplay->GetComponent<HealthDisplay>()->DoDamage();
		}
	}
}