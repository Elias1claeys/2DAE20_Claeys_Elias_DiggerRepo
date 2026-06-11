#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Audio/SoundSystem.h"

namespace dae
{
	enum CollectSound
	{
		COLLECT_SOUND_1 = 0,
		COLLECT_SOUND_2,
		COLLECT_SOUND_3,
		COLLECT_SOUND_4,
		COLLECT_SOUND_5,
		COLLECT_SOUND_6,
		COLLECT_SOUND_7,
		COLLECT_SOUND_8,
	};

	class SoundObserver final : public Observer
	{
	private:
		SoundSystem* m_pAudio;
		int m_EmeraldsCollected{};

	public:
		SoundObserver();
		virtual ~SoundObserver() = default;
		SoundObserver(const SoundObserver& other) = delete;
		SoundObserver(SoundObserver&& other) = delete;
		SoundObserver& operator=(const SoundObserver& other) = delete;
		SoundObserver& operator=(SoundObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}