#include "Score.h"
#include "Event/Event.h"
#include "Components/Text.h"
#include "GameEvents.h"

namespace dae
{
	Score::Score(GameObject* ScoreDisplay)
		: m_pScoreDisplay(ScoreDisplay)
	{
		m_pScoreDisplay->GetComponent<Text>()->SetText(std::to_string(m_Score));
	}

	void Score::OnNotify(GameObject* , const Event& event)
	{
		if (event.id == ENEMY_KILLED)
		{
			m_Score += 250;
		}
		else if (event.id == EMERALD_COLLECTED)
		{
			m_TotalEnemarlsCollected++;

			if (m_TotalEnemarlsCollected == 8)
			{
				m_Score += 250;
				m_TotalEnemarlsCollected = 0;
			}
			else
			{
				m_Score += 25;
			}
		}
		else if (event.id == GOLD_COLLECTED)
		{
			m_Score += 500;
		}
			

		m_pScoreDisplay->GetComponent<Text>()->SetText(std::to_string(m_Score));
	}
}