#pragma once
#include "Core/GameObject.h"
#include "Event/Subject.h"
#include "Components/Transform.h"

namespace dae 
{
	class Player : public Component, public Subject
	{
	private:
		float m_Speed{};
		glm::vec3 m_MoveDirection{};
		Transform* m_Transform{};

	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		glm::vec3 GetDirection() { return m_MoveDirection; };
		void SetDirection(glm::vec3 direction);

		void Update() override;

		Player(GameObject* owner, InputType input, float speed);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

	};
}