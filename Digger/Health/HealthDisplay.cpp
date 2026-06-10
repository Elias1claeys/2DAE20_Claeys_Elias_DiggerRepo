#include "HealthDisplay.h"
#include "Rendering/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Components/Transform.h"

namespace dae
{
	HealthDisplay::HealthDisplay(GameObject* owner)
		: Component(owner), m_Health(3)
	{
		GetOwner()->AddComponent<Transform>();
	}

	const void HealthDisplay::Render()
	{
		std::string path = "media/Digger/digger.png";
		auto texture = ResourceManager::GetInstance().LoadTexture(path);
		auto pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		float interval = 0;

		for (int i = 0; i < m_Health; i++)
		{
			Renderer::GetInstance().Texture(*texture, pos.x + interval, pos.y);
			interval += 50;
		}
	}
}