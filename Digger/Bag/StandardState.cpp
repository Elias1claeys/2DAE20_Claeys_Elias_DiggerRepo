#include "StandardState.h"
#include "WiggleState.h"
#include "FallState.h"
#include "Components/Texture.h"
#include "Entities/Entity.h"

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

		if (m_pBag->IsDugOut(false))
		{
			if (m_pBag->IsDugOut(true))
			{
				return std::make_unique<FallState>(m_pBag);
			}
			else
			{
				return std::make_unique<WiggleState>(m_pBag);
			}
		}
			
		return nullptr;
	}

	void StandardState::CollideWithActor(glm::vec3 dir, GameObject* player)
	{

		glm::vec3 bagPos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 bagSize = m_pBag->GetOwner()->GetComponent<Texture>()->GetSize();

		glm::vec3 playerPos = player->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 playerSize = player->GetComponent<Texture>()->GetSize();

		if (dir.x != 0)
		{
			if (bagPos.x <= 30 || bagPos.x >= 950)
			{
				player->GetComponent<Entity>()->StopMovementInDirection(dir);
				player->GetComponent<Transform>()->SetLocalPosition(playerPos - m_PreviousDirection);
			}
			else
			{
				m_BagDir = dir;
			}
		}
		else if(dir.y != 0)
		{
			player->GetComponent<Entity>()->StopMovementInDirection(dir);
			player->GetComponent<Transform>()->SetLocalPosition(playerPos - m_PreviousDirection);
		}
		else
		{
			player->GetComponent<Transform>()->SetLocalPosition(playerPos - m_PreviousDirection);
		}

		if (dir != glm::vec3(0, 0, 0))
		{
			m_PreviousDirection = dir;
		}
	}
}