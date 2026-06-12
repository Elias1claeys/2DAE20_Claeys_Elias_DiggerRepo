#pragma once
#include "Core/GameObject.h"

namespace dae
{
	class Player : public Component
	{
	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		float m_Time{};
		int m_TextureCount{1};
		bool m_IsDead{ false };

		Player(GameObject* owner, InputType input);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		void SetDirection(glm::vec3 direction);
		void PlayerDead();
		void PlayerRespawn();
		void Update() override;
		glm::vec3 GetDirection();
	};
}