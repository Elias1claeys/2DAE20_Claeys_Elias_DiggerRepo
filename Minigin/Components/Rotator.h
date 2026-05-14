#include "Core/GameObject.h"
#include <glm/glm.hpp>

namespace dae
{
	class Rotator : public Component
	{
	private:
		float m_RotationSpeed;
		float m_CurrentAngle{ 0.f };
		glm::vec3 m_RotationCenter{};

	public:
		void Update() override;

		Rotator(GameObject* owner, float rotationSpeed);
		virtual ~Rotator() = default;
		Rotator(const Rotator& other) = delete;
		Rotator(Rotator&& other) = delete;
		Rotator& operator=(const Rotator& other) = delete;
		Rotator& operator=(Rotator&& other) = delete;
	};
}