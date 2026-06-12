#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class Game;
	class GameObject;

	class GameState
	{
	public:
		explicit GameState(Game* game) : m_pGame(game) {}
		virtual ~GameState() = default;
		GameState(const GameState& other) = delete;
		GameState(GameState&& other) = delete;
		GameState& operator=(const GameState& other) = delete;
		GameState& operator=(GameState&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual std::unique_ptr<GameState> GoToNextState() = 0;

	protected:
		Game* m_pGame;
	};
}