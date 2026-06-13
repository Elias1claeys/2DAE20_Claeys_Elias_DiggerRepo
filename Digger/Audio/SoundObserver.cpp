#include "SoundObserver.h"
#include "GameEvents.h"

namespace dae
{
	SoundObserver::SoundObserver()
	{
		m_pAudio = &dae::SoundLocator::GetAudio();

		for (int i = 0; i < 8; ++i)
		{
			m_pAudio->RegisterSound(static_cast<dae::SoundId>(Sounds::COLLECT_SOUND_1 + i), "Data/Audio/emerald" + std::to_string(i) + ".wav");
		}

		m_pAudio->RegisterSound(static_cast<dae::SoundId>(Sounds::GAME_SOUND), "Data/Audio/digger.wav");
	}

	void SoundObserver::OnNotify(GameObject*, const Event& event)
	{
		switch (event.id)
		{
		case EMERALD_COLLECTED:
			m_pAudio->Play(static_cast<dae::SoundId>(Sounds::COLLECT_SOUND_1 + m_EmeraldsCollected), 1.f);
			m_EmeraldsCollected++;

			if (m_EmeraldsCollected == 8)
				m_EmeraldsCollected = 0;
			break;

		case GAME_STARTED:
			m_pAudio->Play(static_cast<dae::SoundId>(Sounds::GAME_SOUND), 1.f);
		}
	}
}