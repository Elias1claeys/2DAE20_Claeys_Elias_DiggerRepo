#pragma once
#include "Core/GameObject.h"

namespace dae
{
	class PlayerInputComponent : public Component
	{
	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		PlayerInputComponent(GameObject* owner, InputType input);
		virtual ~PlayerInputComponent() = default;
		PlayerInputComponent(const PlayerInputComponent& other) = delete;
		PlayerInputComponent(PlayerInputComponent&& other) = delete;
		PlayerInputComponent& operator=(const PlayerInputComponent& other) = delete;
		PlayerInputComponent& operator=(PlayerInputComponent&& other) = delete;

		void SetDirection(glm::vec3 direction);
		glm::vec3 GetDirection();
	};
}