#include "Collider.h"
#include "Components/Transform.h"
#include "Components/Texture.h"

namespace dae
{
	Collider::Collider(GameObject* owner)
		: Component(owner)
	{}

	void Collider::AddTrigger(const glm::vec3& position, const glm::vec2& size, const Event& event)
	{
		m_Triggers.emplace_back( position, size, event );
	}

	void Collider::RemoveTrigger(int index)
	{
		m_TriggersToRemove.push_back(index);
	}

	void Collider::Update()
	{
		int index = 0;

		for (auto& trigger : m_Triggers)
		{
			if (Overlaps(trigger))
			{
				trigger.event.args[0].i = index;
				Notify(trigger.event, GetOwner());
			}
			index++;
		}

		std::sort(m_TriggersToRemove.begin(), m_TriggersToRemove.end(), std::greater<int>());
		for (int i : m_TriggersToRemove)
		{
			m_Triggers[i].position = glm::vec3{ -100, -100, 0 };
		}

		m_TriggersToRemove.clear();
	}

	bool Collider::Overlaps(Trigger trigger)
	{
		auto playerPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		auto playerSize = GetOwner()->GetComponent<Texture>()->GetSize();

		playerSize.x /= 2;
		playerSize.y /= 2;

		return playerPos.x + playerSize.x >= trigger.position.x &&
			   playerPos.x <= trigger.position.x + trigger.size.x &&
			   playerPos.y + playerSize.y >= trigger.position.y &&
			   playerPos.y <= trigger.position.y + trigger.size.y;
	}
}