#pragma once
#include "Core/GameObject.h"

namespace dae
{
	class Player : public Component
	{
	private:
		float m_Time{};
		int m_TextureCount{ 1 };
		bool m_IsDead{ false };
		int m_Health{ 3 };

	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		Player(GameObject* owner, InputType input);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		bool IsDead() { return m_IsDead; }
		void SetDirection(glm::vec3 direction);
		void PlayerDead();
		void PlayerRespawn();
		void Update() override;

		glm::vec3 GetDirection();
	};
}