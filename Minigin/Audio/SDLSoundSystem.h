#include "SoundSystem.h"
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		void Play(Event SoundID, float volume) override;

	private:

		struct SoundRequest
		{
			std::string filePath;
			float volume;
		};

		void AudioThread();
		void ProcessRequest(const SoundRequest& request);
		std::string GetSoundFilePath(Event soundID) const;

		std::thread m_AudioThread;
		std::mutex m_Mutex;
		std::condition_variable m_CondVar;
		std::queue<SoundRequest> m_RequestQueue;
		std::unordered_map<std::string, MIX_Audio*> m_SoundCache;
		bool m_Running{ true };

		// SDL3_mixer types
		//std::unordered_map<std::string, MIX_Audio*> m_SoundCache;
		MIX_Mixer* m_Mixer{ nullptr };
		//bool m_Running{ true };
	};
}
