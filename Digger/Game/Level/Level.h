#pragma once
#include <vector>
#include "Core/GameObject.h"
#include "Game/GameState.h"

namespace dae
{
	class Scene;
	class Observer;
	class Score;
	class SoundObserver;
	class Collision;
	class HealthObserver;
	class LevelObserver;

	class Level : public GameState
	{
	private:
		std::unique_ptr<GameObject> m_pLevelScreen;
		int m_CurrentLevel{};
		bool m_LevelCompleted{ false };
		

		std::vector<std::unique_ptr<GameObject>> m_pLevelObjects;
		std::vector<std::unique_ptr<GameObject>> m_pGameObjects;

		//Reading the level data from a text file
		std::vector<std::string> m_LevelData;
		glm::vec2 m_Directions[4]{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
		std::vector<glm::vec2> m_AlreadyChecked{};
		std::vector<glm::vec2> m_NextCheck{ {0, -1} };
		bool m_LevelReadyForStart{ false };
		float m_Time{};
		float m_TileSize{ 64.f };

		std::vector<std::unique_ptr<GameObject>> m_pPlayers;

		//Observers
		std::unique_ptr<Score> m_ScoreObserver;
		std::unique_ptr<SoundObserver> m_SoundObserver;
		std::unique_ptr<Collision> m_CollisionObserver;
		std::unique_ptr<HealthObserver> m_HealthObserver;
		std::unique_ptr<LevelObserver> m_LevelObserver;

		bool IsHorizontal(char c);
		bool IsVertical(char c);

		void InitScoreAndHealth();
		void InitBackGround();
		void InitDigGround();
		void ReadLevelData();

		void InitPlayersData();
		void InitEmeralds();
		void InitBags();
		bool CreateStarterPath();

	public:

		void CreateLevel();
		void NextLevel();
		void LevelCompleted() { m_LevelCompleted = true; }
		

		void Update(float deltaTime) override;
		std::unique_ptr<GameState> GoToNextState() override { return nullptr; };

		explicit Level(Game* game);
		virtual ~Level() = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;
	};
}