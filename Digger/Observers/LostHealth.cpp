#include "LostHealth.h"
#include "Components/Text.h"
#include "Event/Event.h"
#include "GameEvents.h"

namespace dae
{
	Health::Health(GameObject* HealthDisplay)
		: m_pHealthDisplay(HealthDisplay)
	{
		m_pHealthDisplay->GetComponent<Text>()->SetText(std::to_string(m_Health));
	}

	void Health::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == TOOK_DAMAGE)
			m_Health -= 1;

		m_pHealthDisplay->GetComponent<Text>()->SetText(std::to_string(m_Health));
	}
}