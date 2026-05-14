#pragma once
#include "Core/GameObject.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_LocalPosition{ 0, 0, 0 };
		glm::vec3 m_WorldPosition{ 0, 0, 0 };
		bool m_PositionIsDirty{ false };

		void UpdateWorldPosition();

	public:
		void SetPositionDirty();
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3& GetWorldPosition();


		Transform(GameObject* owner);
		virtual ~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;
	};
}