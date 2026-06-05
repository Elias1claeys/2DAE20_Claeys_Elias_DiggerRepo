#include "Transform.h"


dae::Transform::Transform(GameObject* owner)
	: Component(owner)
{}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	SetPositionDirty();
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;

	for (auto& child : GetOwner()->GetChildren())
	{
		if (child->HasComponent<Transform>())
			child->GetComponent<Transform>()->SetPositionDirty();
	}
}

void dae::Transform::UpdateWorldPosition()
{
	GameObject* parent = GetOwner()->GetParent();

	

	if (m_PositionIsDirty)
	{
		if (parent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = parent->GetComponent<Transform>()->GetWorldPosition() + m_LocalPosition;
		}

		m_PositionIsDirty = false;
	}
}