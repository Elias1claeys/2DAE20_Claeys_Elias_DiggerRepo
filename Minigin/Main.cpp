#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Components.h"
#include "Observer.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto level = std::make_unique<dae::GameObject>();
	level->AddComponent<dae::LevelComponent>();
	scene.Add(std::move(level));

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto scoreDisplay = std::make_unique<dae::GameObject>();
	//scoreDisplay->AddComponent<dae::TextComponent>("5", font);
	//auto healthObserver = std::make_unique<dae::ScoreObserver>(scoreDisplay.get());
	//scene.Add(std::move(scoreDisplay));
	//
	//auto player = std::make_unique<dae::GameObject>();
	//player->AddComponent<dae::PlayerComponent>(dae::PlayerComponent::InputType::keyBoard, 200.f);
	//player->GetComponent<dae::TransformComponent>()->SetLocalPosition({ 100, 300, 100 });
	//player->GetComponent<dae::PlayerComponent>()->AddObserver(std::move(healthObserver));
	//scene.Add(std::move(player));

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
