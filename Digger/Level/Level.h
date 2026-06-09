#pragma once
#include <vector>
#include "Core/GameObject.h"

namespace dae
{
	class Scene;

	class Observer;

	class Level : public Component
	{
	private:
		GameObject* m_pGameScreen;
		int m_CurrentLevel{};

		//Reading the level data from a text file
		std::vector<std::string> m_LevelData;

		glm::vec2 m_Directions[4]{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
		std::vector<glm::vec2> m_AlreadyChecked{};
		std::vector<glm::vec2> m_NextCheck{ {0, -1} };
		bool m_LevelReadyForStart{ false };
		float m_Time{};


		std::vector<std::unique_ptr<GameObject>> m_LevelObjects;
		std::vector<std::unique_ptr<Observer>> m_Observers;
		Scene* m_LevelScene{};
		float m_TileSize{ 64.f };

		bool IsHorizontal(char c);
		bool IsVertical(char c);

		void InitBackGround();
		void InitDigGround();
		void ReadLevelData();

		void InitPlayersData();
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