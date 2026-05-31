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

	void Collider::AddTrigger(glm::vec3 position, glm::vec2 size, Event event)
	{
		m_Triggers.emplace_back( position, size, event);
	}

	void Collider::AddTrigger(glm::vec3 position, glm::vec2 size, Event event, bool persistent)
	{
		m_Triggers.emplace_back(position, size, event, persistent);
	}

	void Collider::Update()
	{
		for (auto& trigger : m_Triggers)
		{
			if (Overlaps(trigger))
			{
				Notify(trigger.event, GetOwner());
				if (!trigger.persistent)
					trigger.markedForDelete = true;
			}
		}

		std::erase_if(m_Triggers, [](const Trigger& t)
		{
			return t.markedForDelete;
		});
	}

	const void Collider::Render()
	{
		for (auto& trigger : m_Triggers)
		{
			SDL_FRect rect{};
			rect.x = (float)trigger.position.x;
			rect.y = (float)trigger.position.y;
			rect.w = (float)trigger.size.x;
			rect.h = (float)trigger.size.y;

			Renderer::GetInstance().DrawRect({1, 0, 0, 0}, rect);
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