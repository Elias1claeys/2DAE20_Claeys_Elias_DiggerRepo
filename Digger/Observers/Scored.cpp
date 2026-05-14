#include "Scored.h"
#include "Event.h"
#include "Components/Text.h"

namespace dae
{
	void ScoreObserver::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == make_sdbm_hash("EnemyKilled"))
			m_Score += 100;

		gameObject->GetComponent<Text>()->SetText(std::to_string(m_Score));
	}
}