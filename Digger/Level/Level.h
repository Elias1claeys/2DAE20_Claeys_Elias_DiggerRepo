#pragma once
#include <vector>
#include "Core/GameObject.h"

namespace dae
{
	class Scene;
	class Observer;
	class Score;
	class SoundObserver;
	class Collision;

	class Level : public Component
	{
	private:
		std::unique_ptr<GameObject> m_pGameScreen;
		int m_CurrentLevel{};

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

		std::vector<GameObject*> m_pPlayers;
		std::unique_ptr<Score> m_ScoreObserver;
		std::unique_ptr<SoundObserver> m_SoundObserver;
		std::unique_ptr<Collision> m_CollisionObserver;


		bool IsHorizontal(char c);
		bool IsVertical(char c);

		void InitScore();
		void InitBackGround();
		void InitDigGround();
		void ReadLevelData();

		void InitPlayersData();
		void InitEmeraldsAndBags();
		bool CreateStarterPath();

	public:

		void CreateLevel();
		void NextLevel();

		void Update() override;

		Level(GameObject* owner);
		virtual ~Level() = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;
	};
}