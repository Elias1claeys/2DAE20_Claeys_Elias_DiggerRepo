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


		std::vector<std::unique_ptr<GameObject>> m_LevelObjects;
		std::vector<std::unique_ptr<Observer>> m_Observers;
		Scene* m_LevelScene{};
		int m_CurrentLevel{ 1 };
		float m_TileSize{ 64.f };

		bool IsHorizontal(char c);
		bool IsVertical(char c);

		void InitBackGround(int level);
		void InitDigGround();
		void InitPlayer();

		std::unique_ptr<GameObject> CreateDigGround();

	public:

		void CreateLevel(int level);
		void NextLevel();

		Level(GameObject* owner);
		virtual ~Level() = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;
	};
}