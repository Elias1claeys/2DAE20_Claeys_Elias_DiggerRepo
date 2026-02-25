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

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	go->GetComponent<dae::RenderComponent>()->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	go->GetComponent<dae::RenderComponent>()->SetTexture("logo.png");
	go->GetComponent<dae::TransformComponent>()->SetLocalPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	to->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	to->GetComponent<dae::TransformComponent>()->SetLocalPosition(292, 20);
	scene.Add(std::move(to));

	auto fps = std::make_unique<dae::GameObject>();
	fps->AddComponent<dae::FPSComponent>();	
	scene.Add(std::move(fps));

	auto rotator1 = std::make_unique<dae::GameObject>();
	rotator1->AddComponent<dae::RenderComponent>();
	rotator1->GetComponent<dae::RenderComponent>()->SetTexture("media/Digger/dig1.png");
	rotator1->AddComponent<dae::RotatorComponent>(5.f, false);
	rotator1->GetComponent<dae::RotatorComponent>()->SetRotationPoint(200, 200);

	auto rotator2 = std::make_unique<dae::GameObject>();
	rotator2->AddComponent<dae::RenderComponent>();
	rotator2->GetComponent<dae::RenderComponent>()->SetTexture("media/hob/hob1.png");
	rotator2->AddComponent<dae::RotatorComponent>(5.f, true);
	rotator2->GetComponent<dae::RotatorComponent>()->SetRotationDirection(false);
	rotator2->SetParent(rotator1.get(), true);
	scene.Add(std::move(rotator1));
	scene.Add(std::move(rotator2));
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
