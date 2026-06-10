#include "Entity.h"
#include "Input/InputManager.h"
#include "Core/DeltaTime.h"
#include "Components/Texture.h"
#include "Observers/GameEvents.h"
#include "Dig/DigSystem.h"
#include "Dig/Dig.h"

dae::Entity::Entity(GameObject* Owner, float speed)
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
}

void dae::Entity::Update()
{
	glm::vec3 pos = m_Transform->GetWorldPosition();

	if (m_MoveDirection != glm::vec3(0, 0, 0))
	{
		if ((m_MoveDirection == glm::vec3(-1, 0, 0) && pos.x <= 30) ||
			(m_MoveDirection == glm::vec3(1, 0, 0) && pos.x >= 950) ||
			(m_MoveDirection == glm::vec3(0, 1, 0) && pos.y >= 685) ||
			(m_MoveDirection == glm::vec3(0, -1, 0) && pos.y <= 96))
		{
			m_MoveDirection = glm::vec3(0, 0, 0);
			return;
		}

		DigLocator::GetDig().DigTile(pos, GetOwner()->GetComponent<Texture>()->GetSize());

		pos.x += m_MoveDirection.x * m_Speed * Time::GetInstance().GetDeltaTime();
		pos.y += m_MoveDirection.y * m_Speed * Time::GetInstance().GetDeltaTime();

		m_Transform->SetLocalPosition(pos);
	}
}

void dae::Entity::SetDirection(glm::vec3 dir)
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

void dae::Entity::MoveBack(glm::vec3 offset)
{
	auto pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
	pos.x -= offset.x;
	pos.y -= offset.y;
	GetOwner()->GetComponent<Transform>()->SetLocalPosition(pos);
}