#pragma once
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene;

	class Level : public Component
	{
	private:
		std::vector<GameObject*> m_LevelObjects;
		Scene* m_LevelScene{};
		int m_CurrentLevel{ 1 };

		bool IsHorizontal(char c);
		bool IsVertical(char c);

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