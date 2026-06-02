#include "Collider.h"
#include "Components/Transform.h"
#include "Components/Texture.h"

namespace dae
{
	Collider::Collider(GameObject* owner, glm::vec3 offset, glm::vec2 size)
		: Component(owner), m_Offset(offset), m_ColliderSize(size)
	{
	}

	void Collider::AddTrigger(Trigger trigger)
	{
		m_Triggers.emplace_back(trigger);
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
		auto pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		SDL_FRect rect{};
		rect.x = pos.x + m_Offset.x;
		rect.y = pos.y + m_Offset.y;
		rect.w = m_ColliderSize.x;
		rect.h = m_ColliderSize.y;

		Renderer::GetInstance().DrawRect({255, 0, 255, 255}, rect);

		for (auto& trigger: m_Triggers)
		{
			auto triggerPos = trigger.triggerObject->GetComponent<Transform>()->GetWorldPosition();
			rect.x = triggerPos.x + trigger.offset.x;
			rect.y = triggerPos.y + trigger.offset.y;
			rect.w = trigger.size.x;
			rect.h = trigger.size.y;
			Renderer::GetInstance().DrawRect({ 255, 0, 0, 255 }, rect);
		}
	}

	bool Collider::Overlaps(Trigger trigger)
	{
		auto objectPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition() + m_Offset;
		auto triggerPos = trigger.triggerObject->GetComponent<Transform>()->GetWorldPosition() + trigger.offset;

		return objectPos.x + m_ColliderSize.x >= triggerPos.x &&
			   objectPos.x <= triggerPos.x + trigger.size.x &&
			   objectPos.y + m_ColliderSize.y >= triggerPos.y &&
			   objectPos.y <= triggerPos.y + trigger.size.y;
	}
}