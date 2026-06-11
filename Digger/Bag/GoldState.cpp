#include "GoldState.h"
#include "Components/Texture.h"
#include "Collider/Collider.h"
#include "Event/Subject.h"


namespace dae
{
	GoldState::GoldState(Bag* bag)
		:BagState(bag)
	{
	}

	std::unique_ptr<BagState> GoldState::Update(float deltaTime)
	{
		if (!m_Collected)
		{
			m_Time += deltaTime;

			if (m_Time > 0.2f && m_GoldTexture < 3)
			{
				m_Time = 0;
				m_GoldTexture++;

				m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Gold/Gold" + std::to_string(m_GoldTexture) + ".png");
				m_pBag->GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(64, 64));
			}
		}

		return nullptr;
	}

	void GoldState::CollideWithActor(glm::vec3, GameObject*)
	{
		if (!m_Collected)
		{
			m_pBag->CollectGold();
			m_Collected = true;
		}
	}
}