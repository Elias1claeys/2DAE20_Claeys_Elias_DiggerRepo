#include "Bag.h"
#include "StandardState.h"
#include "WiggleState.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"
#include "Hole/Hole.h"
#include "Components/Transform.h"

dae::Bag::Bag(GameObject* owner, Hole* hole)
	: Component(owner), m_pHole(hole)
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

bool dae::Bag::IsDugOut()
{
	glm::vec3 pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
	glm::vec2 size = GetOwner()->GetComponent<Texture>()->GetSize();

	return m_pHole->BagDiggedOut(pos, size);
}