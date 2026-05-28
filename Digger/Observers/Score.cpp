#include "Score.h"
#include "Event/Event.h"
#include "Components/Text.h"
#include "GameEvents.h"
#include "Emerald/Emerald.h"
#include "Collider/Collider.h"
#include "Audio/SoundSystem.h"

namespace dae
{
	Score::Score(GameObject* ScoreDisplay)
		: m_pScoreDisplay(ScoreDisplay)
	{
		m_pScoreDisplay->GetComponent<Text>()->SetText(std::to_string(m_Score));
	}

	void Score::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == ENEMY_KILLED)
		{
			m_Score += 250;
		}
		else if (event.id == EMERALD_COLLECTED)
		{
			m_TotalEnemarlsCollected++;

			event.args[0].go->GetComponent<Emerald>()->Collect();

			if (event.args[0].i == 8)
			{
				m_Score += 250;
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