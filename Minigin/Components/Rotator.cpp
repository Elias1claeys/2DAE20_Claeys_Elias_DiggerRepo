#include "Rotator.h"
#include "Transform.h"
#include "Minigin/DeltaTime.h"

dae::Rotator::Rotator(GameObject* owner, float rotationSpeed)
	: Component(owner)
	, m_RotationSpeed(rotationSpeed)
{
	if (!owner->HasComponent<Transform>())
	{
		owner->AddComponent<Transform>();
	}

	m_RotationCenter = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
}

void dae::Rotator::Update()
{
	auto transform = GetOwner()->GetComponent<Transform>();

	m_CurrentAngle += m_RotationSpeed * Time::GetInstance().GetDeltaTime();

	transform->SetLocalPosition(
		m_RotationCenter.x + std::cos(m_CurrentAngle) * 50.f,
		m_RotationCenter.y + std::sin(m_CurrentAngle) * 50.f,
		m_RotationCenter.z
	);
}