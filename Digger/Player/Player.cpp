#include "Player.h"
#include "PlayerControls.h"
#include "Input/InputManager.h"
#include "Core/DeltaTime.h"
#include "Components/Texture.h"
#include "Observers/GameEvents.h"

dae::Player::Player(GameObject* Owner, InputType input, float speed)
	:Component(Owner),
	m_Speed(speed)
{
	if (!GetOwner()->HasComponent<Texture>())
	{
		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Texture>()->SetTexture("media/Digger/dig1.png");
		GetOwner()->GetComponent<Texture>()->SetSize({ 48, 48 });
		GetOwner()->GetComponent<Texture>()->FlipTexture();
	}

	m_Transform = GetOwner()->GetComponent<Transform>();

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
}

void dae::Player::Update()
{
	glm::vec3 pos = m_Transform->GetWorldPosition();

	if (m_MoveDirection != glm::vec3(0, 0, 0))
	{
		if ((m_MoveDirection == glm::vec3(-1, 0, 0) && pos.x <= 32) ||
			(m_MoveDirection == glm::vec3(1, 0, 0) && pos.x >= 950) ||
			(m_MoveDirection == glm::vec3(0, 1, 0) && pos.y >= 685) ||
			(m_MoveDirection == glm::vec3(0, -1, 0) && pos.y <= 96))
		{
			m_MoveDirection = glm::vec3(0, 0, 0);
			return;
		}

		Event e{ PLAYER_MOVED };
		e.nbArgs = 2;
		e.args[0].v3 = m_Transform->GetWorldPosition();
		e.args[1].v2 = GetOwner()->GetComponent<Texture>()->GetSize();
		Notify(e, GetOwner());

		pos.x += m_MoveDirection.x * m_Speed * Time::GetInstance().GetDeltaTime();
		pos.y += m_MoveDirection.y * m_Speed * Time::GetInstance().GetDeltaTime();

		m_Transform->SetLocalPosition(pos);
	}
}

void dae::Player::SetDirection(glm::vec3 dir)
{
	m_MoveDirection = dir;

	if (dir == glm::vec3{-1,  0, 0 } && !m_Flipped ||
		dir == glm::vec3{ 1,  0, 0 } &&  m_Flipped ||
		dir == glm::vec3{ 0,  1, 0 } &&  m_Flipped ||
		dir == glm::vec3{ 0, -1, 0 } && !m_Flipped)
	{
		
		GetOwner()->GetComponent<Texture>()->FlipTexture();
		m_Flipped = !m_Flipped;
	}

	if(dir == glm::vec3{0, -1, 0} ||
	   dir == glm::vec3{0, 1, 0})
	{
		GetOwner()->GetComponent<Texture>()->SetRotation(90);
	}
	else if(dir != glm::vec3{0, 0, 0})
	{
		GetOwner()->GetComponent<Texture>()->SetRotation(0);
	}
}