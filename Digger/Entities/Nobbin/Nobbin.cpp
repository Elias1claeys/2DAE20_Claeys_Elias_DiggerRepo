#include "Nobbin.h"
#include "Components/Texture.h"
#include "Entities/Entity.h"
#include "Core/DeltaTime.h"
#include "Entities/Enemies/Enemy.h"

namespace dae
{
	Nobbin::Nobbin(GameObject* owner)
		:Component(owner)
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("media/nob/cnob1.png");
		GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(48, 48));
		GetOwner()->AddComponent<Enemy>();
		GetOwner()->AddComponent<Entity>(150.f);
	}

	void Nobbin::Update()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (m_Time > 0.2f)
		{
			m_Time = 0.f;
			m_TextureAct++;
			GetOwner()->GetComponent<Texture>()->SetTexture("media/nob/cnob" + std::to_string(m_TextureAct) + ".png");
			GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(48, 48));

			if (m_TextureAct == 3)
				m_TextureAct = 0;
		}
	}
}