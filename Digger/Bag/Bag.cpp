#include "Bag.h"
#include "StandardState.h"
#include "WiggleState.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"
#include "Dig/DigSystem.h"
#include "Components/Transform.h"
#include "GameEvents.h"



dae::Bag::Bag(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<Texture>();
	m_CurrentState = std::make_unique<StandardState>(this);
}

void dae::Bag::Update()
{
	auto newState = m_CurrentState->Update(Time::GetInstance().GetDeltaTime());

	if (newState != nullptr)
		m_CurrentState = std::move(newState);
}

void dae::Bag::CollideWithActor(glm::vec3 dir, GameObject* player)
{
	m_CurrentState->CollideWithActor(dir, player);
}

bool dae::Bag::IsDugOut(bool checkTop)
{
	glm::vec3 pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
	glm::vec2 size = GetOwner()->GetComponent<Texture>()->GetSize();

	return DigLocator::GetDig().BagDiggedOut(pos, size, checkTop);
}

void dae::Bag::CollectGold()
{
	Event e{ GOLD_COLLECTED };
	Notify(e, GetOwner());
	GetOwner()->RemoveComponent<Texture>();
}