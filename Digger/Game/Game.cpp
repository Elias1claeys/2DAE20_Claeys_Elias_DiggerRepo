#include "Game.h"
#include "Level/Level.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Game::Game(GameObject* owner)
		: Component(owner)
	{
		m_pGameState = std::make_unique<Level>(this);
	}

	void Game::Update()
	{
		m_pGameState->Update(Time::GetInstance().GetDeltaTime());
	}
}