#include "Player.h"
#include "Input/InputManager.h"
#include "PlayerInput.h"
#include "Entities/Entity.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Player::Player(GameObject* Owner, InputType input)
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

		if (!GetOwner()->HasComponent<Texture>())
		{
			GetOwner()->AddComponent<Texture>();
			GetOwner()->GetComponent<Texture>()->SetTexture("media/Digger/dig1.png");
			GetOwner()->GetComponent<Texture>()->SetSize({ 48, 48 });
			GetOwner()->GetComponent<Texture>()->FlipTexture();
		}

		GetOwner()->AddComponent<Entity>(100.f);
	};

	void Player::Update()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (!m_IsDead)
		{
			if (m_Time > 0.2f)
			{
				m_TextureCount++;
				GetOwner()->GetComponent<Texture>()->SetTexture("media/Digger/dig" + std::to_string(m_TextureCount) + ".png");
				GetOwner()->GetComponent<Texture>()->SetSize({ 48, 48 });

				if (m_TextureCount == 2)
					m_TextureCount = 0;

				m_Time = 0;
			}
		}
		else
		{
			if (m_Time > 0.5f)
			{
				m_TextureCount++;
				GetOwner()->GetComponent<Texture>()->SetRotation(90);
				GetOwner()->GetComponent<Texture>()->SetTexture("media/Grave/grave" + std::to_string(m_TextureCount) + ".png");
				GetOwner()->GetComponent<Texture>()->SetSize({ 48, 48 });
				
				if (m_TextureCount == 5)
					PlayerRespawn();

				m_Time = 0;
			}
		}
	}

	void Player::SetDirection(glm::vec3 direction)
	{
		GetOwner()->GetComponent<Entity>()->SetDirection(direction);
	}

	void Player::PlayerDead()
	{
		m_IsDead = true;
		m_TextureCount = 0;
	}

	void Player::PlayerRespawn()
	{
		GetOwner()->GetComponent<Transform>()->SetLocalPosition(glm::vec3{ 40, 104, 0 });
		m_IsDead = false;
		m_TextureCount = 0;
	}

	glm::vec3 Player::GetDirection()
	{
		return GetOwner()->GetComponent<Entity>()->GetDirection();
	}
}