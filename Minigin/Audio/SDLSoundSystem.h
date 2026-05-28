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

		void Play(SoundId soundID, float volume) override;
		void RegisterSound(SoundId soundID, const std::string& filePath) override;

	private:

		struct SoundRequest
		{
			std::string filePath;
			float volume;
		};

		void AudioThread();
		void ProcessRequest(const SoundRequest& request);

		std::thread m_AudioThread;
		std::mutex m_Mutex;
		std::condition_variable m_CondVar;
		std::queue<SoundRequest> m_RequestQueue;
		std::unordered_map<SoundId, std::string> m_SoundPaths;
		std::unordered_map<std::string, MIX_Audio*> m_SoundCache;
		bool m_Running{ true };


		MIX_Mixer* m_Mixer{ nullptr };
	};
}
