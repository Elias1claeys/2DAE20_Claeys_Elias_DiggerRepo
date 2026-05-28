#include "Collider.h"
#include "Components/Transform.h"
#include "Components/Texture.h"

namespace dae
{
	Collider::Collider(GameObject* owner)
		: Component(owner)
	{
		m_ColliderSize = GetOwner()->GetComponent<Texture>()->GetSize();
		m_ColliderSize.x /= 2;
		m_ColliderSize.y /= 2;
	}

	void Collider::AddTrigger(const glm::vec3& position, const glm::vec2& size, const Event& event)
	{
		m_Triggers.emplace_back( position, size, event );
	}

	void Collider::Update()
	{
		int index = 0;

		for (auto& trigger : m_Triggers)
		{
			if (Overlaps(trigger))
			{
				Notify(trigger.event, GetOwner());
				trigger.position = glm::vec3{ -500, -500, 0 };
			}
			index++;
		}
	}

	bool Collider::Overlaps(Trigger trigger)
	{
		auto playerPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		return playerPos.x + m_ColliderSize.x >= trigger.position.x &&
			   playerPos.x <= trigger.position.x + trigger.size.x &&
			   playerPos.y + m_ColliderSize.y >= trigger.position.y &&
			   playerPos.y <= trigger.position.y + trigger.size.y;
	}
}