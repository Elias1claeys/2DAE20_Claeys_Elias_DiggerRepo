#include "WiggleState.h"
#include "FallState.h"
#include "Components/Texture.h"

namespace dae
{
	WiggleState::WiggleState(Bag* bag)
		:BagState(bag)
	{
	}

	std::unique_ptr<BagState> WiggleState::Update(float deltaTime)
	{
		m_Time += deltaTime;

		if (m_Time > 0.5f)
		{
			if (!facingLeft)
			{
				m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Bag/clbag.png");
			}
			else
			{
				m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Bag/crbag.png");
				m_WiggleCounter++;
			}

			m_pBag->GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(64, 64));
			facingLeft = !facingLeft;
			m_Time = 0.f;
		}

		if (m_WiggleCounter > 3)
		{
			return std::make_unique<FallState>(m_pBag);
		}

		return nullptr;
	}

	void WiggleState::CollideWithActor(glm::vec3 , GameObject* )
	{
		//if (dir != glm::vec3(0, 0, 0))
		//	player->MoveBack(glm::vec3(dir.x * 2, dir.y * 2, 0));
	}
}