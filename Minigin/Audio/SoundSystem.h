#pragma once
#include "Event/Event.h"
#include <vector>
#include <memory>


namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(Event SoundID, float volume) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		void Play(Event, float) override {};
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetAudio()
		{
			return *m_Instance;
		}

		static void RegisterAudio(std::unique_ptr<SoundSystem>&& service)
		{
			if (service)
				m_Instance = std::move(service);
			else
				m_Instance = std::make_unique<NullSoundSystem>();
		}

	private:
		static std::unique_ptr<SoundSystem> m_Instance;
	};
}
