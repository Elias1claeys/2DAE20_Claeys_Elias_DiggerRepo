#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Core/Minigin.h"
#include "Core/SceneManager.h"
#include "Resources/ResourceManager.h"
#include "Core/Scene.h"
#include "Level/Level.h"
#include "Audio/SoundSystem.h"
#include "Audio/SDLSoundSystem.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	dae::ServiceLocator::RegisterAudio(std::make_unique<dae::SDLSoundSystem>());

	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto level = std::make_unique<dae::GameObject>();
	level->AddComponent<dae::Level>();
	scene.Add(std::move(level));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
