#include "FallState.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "StandardState.h"
#include "GoldState.h"

namespace dae
{
	FallState::FallState(Bag* bag)
		:BagState(bag)
	{
		m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Bag/cfbag.png");
		m_pBag->GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(64, 64));

		m_FirstPos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
	}


	std::unique_ptr<BagState> FallState::Update(float deltaTime)
	{
		glm::vec3 pos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		pos.y += deltaTime * m_Speed;

		m_pBag->GetOwner()->GetComponent<Transform>()->SetLocalPosition(pos);

		if (!m_pBag->IsDugOut(false))
		{
			auto bagpos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

			auto difference = bagpos.y - m_FirstPos.y;

			if (difference >= 128)
			{
				return std::make_unique<GoldState>(m_pBag);
			}
			else
			{
				return std::make_unique<StandardState>(m_pBag);
			}
		}

		return nullptr;
	}

	void FallState::CollideWithActor(glm::vec3, GameObject* player)
	{	
		auto bagpos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		auto playerpos = player->GetComponent<Transform>()->GetWorldPosition();

		if (bagpos.y <= playerpos.y)
		{
			player->GetComponent<Transform>()->SetLocalPosition(bagpos);
		}
	}
}