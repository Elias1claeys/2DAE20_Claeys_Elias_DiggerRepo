#include "PlayerInputComponent.h"
#include "Input/InputManager.h"
#include "PlayerControls.h"
#include "Entities/Entity.h"

namespace dae
{
	PlayerInputComponent::PlayerInputComponent(GameObject* Owner, InputType input)
		:Component(Owner)
	{
		auto moveUp = std::make_shared<dae::Move>(this, glm::vec3{ 0, -1, 0 });
		auto moveDown = std::make_shared<dae::Move>(this, glm::vec3{ 0, 1, 0 });
		auto moveLeft = std::make_shared<dae::Move>(this, glm::vec3{ -1, 0, 0 });
		auto moveRight = std::make_shared<dae::Move>(this, glm::vec3{ 1, 0, 0 });
		auto attack = std::make_shared<dae::Attack>(this);

		if (input == InputType::keyBoard)
		{
			InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_W, moveUp);
			InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_A, moveLeft);
			InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_S, moveDown);
			InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_D, moveRight);
			InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_SPACE, attack);
		}
		else
		{
			InputManager::GetInstance().BindControllerCommand(0x0002, moveDown);
			InputManager::GetInstance().BindControllerCommand(0x0008, moveRight);
			InputManager::GetInstance().BindControllerCommand(0x0004, moveLeft);
			InputManager::GetInstance().BindControllerCommand(0x0010, moveUp);
			InputManager::GetInstance().BindControllerCommand(0x4000, attack);
		}
	};

	void PlayerInputComponent::SetDirection(glm::vec3 direction)
	{
		GetOwner()->GetComponent<Entity>()->SetDirection(direction);
	}

	glm::vec3 PlayerInputComponent::GetDirection()
	{
		return GetOwner()->GetComponent<Entity>()->GetDirection();
	}
}