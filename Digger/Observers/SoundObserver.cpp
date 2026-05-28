#include "SoundObserver.h"
#include "GameEvents.h"

namespace dae
{
	SoundObserver::SoundObserver()
	{
		m_pAudio = &dae::ServiceLocator::GetAudio();

		for (int i = 0; i < 8; ++i)
		{
			m_pAudio->RegisterSound(static_cast<dae::SoundId>(CollectSound::COLLECT_SOUND_1 + i), "Data/Audio/emerald" + std::to_string(i) + ".wav");
		}
	}

	void SoundObserver::OnNotify(GameObject*, const Event& event)
	{
		switch (event.id)
		{
		case EMERALD_COLLECTED:
			m_pAudio->Play(static_cast<dae::SoundId>(CollectSound::COLLECT_SOUND_1 + event.args[0].i), 1.f);
			break;
		}
	}
}