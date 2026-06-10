#include "StandardState.h"
#include "WiggleState.h"
#include "Components/Texture.h"

namespace dae
{
	StandardState::StandardState(Bag* bag)
		: BagState(bag)
	{
		m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Bag/csbag.png");
		m_pBag->GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(64, 64));
	}

	std::unique_ptr<BagState> StandardState::Update(float deltaTime)
	{
		glm::vec3 BagPos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		BagPos.x += m_BagDir.x * m_Speed * deltaTime;
		m_pBag->GetOwner()->GetComponent<Transform>()->SetLocalPosition(BagPos);
		m_BagDir = glm::vec3(0, 0, 0);

		if (m_pBag->IsDugOut())
			return std::make_unique<WiggleState>(m_pBag);

		return nullptr;
	}

	void StandardState::CollideWithActor(glm::vec3 dir, Entity* player)
	{
		glm::vec3 BagPos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		if (dir.x != 0)
		{
			if (BagPos.x <= 30 || BagPos.x >= 950)
			{
				player->MoveBack(glm::vec3(m_PreviousDirection.x * 5, 0, 0));
			}
			else
			{
				m_BagDir = dir;
			}
		}
		else
		{
			player->MoveBack(glm::vec3(m_PreviousDirection.x * 5, m_PreviousDirection.y * 5, 0));
		}

		
		m_PreviousDirection = dir;
	}
}