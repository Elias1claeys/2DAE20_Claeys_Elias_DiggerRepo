#include "LevelObserver.h"
#include "GameEvents.h"
#include "Level.h"

namespace dae
{
	LevelObserver::LevelObserver(GameObject* level)
		: m_pLevel(level)
	{}

	void LevelObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == EMERALD_SPAWNED)
		{
			m_TotalEmeralds++;
		}
		if (event.id == EMERALD_COLLECTED)
		{
			m_TotalEmeraldsCollected++;
			if (m_TotalEmeraldsCollected == m_TotalEmeralds)
			{
				m_TotalEmeralds = 0;
				m_TotalEmeraldsCollected = 0;
				m_pLevel->GetComponent<Level>()->LevelCompleted();
			}
		}
		if (event.id == LEVEL_COMPLETED)
		{
			m_TotalEmeralds = 0;
			m_TotalEmeraldsCollected = 0;
		}
	}
}