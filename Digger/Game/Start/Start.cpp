#include "Start.h"
#include "Core/GameObject.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Game/Level/Level.h"
#include "StartControls.h"
#include "Input/InputManager.h"

namespace dae
{
	Start::Start(Game* game)
		: GameState(game)
	{
		auto goUp = std::make_shared<SwitchGameMode>(this, -1);
		auto goDown = std::make_shared<SwitchGameMode>(this, 1);
		auto selectGame = std::make_shared<SelectGameMode>(this);

		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_UP, goUp);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_DOWN, goDown);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_RETURN, selectGame);

		InputManager::GetInstance().BindControllerCommand(0x0010, goUp);
		InputManager::GetInstance().BindControllerCommand(0x0002, goDown);
		InputManager::GetInstance().BindControllerCommand(0x4000, selectGame);

		InitGameModes();
	}

	void Start::InitGameModes()
	{
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto singlePlayer = std::make_unique<GameObject>();
		singlePlayer->AddComponent<Text>("SinglePlayer", font);
		singlePlayer->GetComponent<Text>()->SetColor(SDL_Color{255, 255, 0, 255});
		singlePlayer->GetComponent<Transform>()->SetLocalPosition(700, 50, 0);
		singlePlayer->SetParent(m_pGame->GetOwner(), false);
		m_pGameModes.push_back(std::move(singlePlayer));
		
		auto multiPlayer = std::make_unique<GameObject>();
		multiPlayer->AddComponent<Text>("MultiPlayer", font);
		multiPlayer->GetComponent<Text>()->SetColor(SDL_Color{255, 0, 0, 255});
		multiPlayer->GetComponent<Transform>()->SetLocalPosition(700, 100, 0);
		multiPlayer->SetParent(m_pGame->GetOwner(), false);
		m_pGameModes.push_back(std::move(multiPlayer));
		
		auto versus = std::make_unique<GameObject>();
		versus->AddComponent<Text>("Versus", font);
		versus->GetComponent<Text>()->SetColor(SDL_Color{255, 0, 0, 255});
		versus->GetComponent<Transform>()->SetLocalPosition(700, 150, 0);
		versus->SetParent(m_pGame->GetOwner(), false);
		m_pGameModes.push_back(std::move(versus));
	}

	void Start::InitHighScores()
	{

	}

	void Start::SelectButton(int direction)
	{
		m_pGameModes[m_SelectedButton]->GetComponent<Text>()->SetColor(SDL_Color{ 255, 0, 0, 255 });
		m_SelectedButton += direction;

		if (m_SelectedButton < 0)
			m_SelectedButton = 2;
		else if (m_SelectedButton > 2)
			m_SelectedButton = 0;

		m_pGameModes[m_SelectedButton]->GetComponent<Text>()->SetColor(SDL_Color{ 255, 255, 0, 255 });
	}

	void Start::GameModeSelected()
	{
		m_pGameModes.clear();
		m_pHighScores.clear();
		InputManager::GetInstance().ResetCommands();

		m_pGame->GoToNextStage();
	}

	std::unique_ptr<GameState> Start::GoToNextState()
	{
		if(m_SelectedButton == 0)
			return std::make_unique<Level>(m_pGame, Level::SinglePlayer);
		if (m_SelectedButton == 1)
			return std::make_unique<Level>(m_pGame, Level::MultiPlayer);
		else
			return std::make_unique<Level>(m_pGame, Level::Versus);
	}
}