#include "Game.h"
#include "Start/Start.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Game::Game(GameObject* owner)
		: Component(owner)
	{
		m_pGameState = std::make_unique<Start>(this);
	}

	void Game::Update()
	{
		m_pGameState->Update(Time::GetInstance().GetDeltaTime());
	}

	void Game::GoToNextStage()
	{
		auto nextstage = m_pGameState->GoToNextState();

		if (nextstage != nullptr)
			m_pGameState = std::move(nextstage);
	}
}