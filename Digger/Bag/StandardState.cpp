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

	void StandardState::CollideWithActor(glm::vec3 dir, Player* player)
	{
		glm::vec3 BagPos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		if (dir == glm::vec3(1, 0, 0) || dir == glm::vec3(-1, 0, 0))
		{
			if (BagPos.x <= 64 || BagPos.x >= 886)
			{
				player->SetDirection(glm::vec3(0, 0, 0));
			}
			else
			{
				m_BagDir = dir;
			}
		}
	}
}