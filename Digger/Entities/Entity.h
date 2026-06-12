#pragma once
#include "Core/GameObject.h"
#include "Event/Subject.h"
#include "Components/Transform.h"

namespace dae 
{
	class Entity : public Component, public Subject
	{
	private:
		float m_Speed{};
		glm::vec3 m_MoveDirection{};
		glm::vec3 m_NotMoving{ 0, 0, 0 };
		Transform* m_Transform{};
		bool m_Flipped{ false };
		bool m_CanMove{ true };

	public:
		glm::vec3 GetDirection() { return m_MoveDirection; };
		void SetDirection(glm::vec3 direction);
		void StopMovementInDirection(glm::vec3 dir);
		void CanMove() { m_CanMove = !m_CanMove; }

		void Update() override;

		Entity(GameObject* owner, float speed);
		virtual ~Entity() = default;
		Entity(const Entity& other) = delete;
		Entity(Entity&& other) = delete;
		Entity& operator=(const Entity& other) = delete;
		Entity& operator=(Entity&& other) = delete;

	};
}