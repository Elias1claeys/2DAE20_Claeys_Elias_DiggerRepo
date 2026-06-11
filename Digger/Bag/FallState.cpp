#include "FallState.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "StandardState.h"

namespace dae
{
	FallState::FallState(Bag* bag)
		:BagState(bag)
	{
		m_pBag->GetOwner()->GetComponent<Texture>()->SetTexture("media/Bag/cfbag.png");
		m_pBag->GetOwner()->GetComponent<Texture>()->SetSize(glm::vec2(64, 64));
	}


	std::unique_ptr<BagState> FallState::Update(float deltaTime)
	{
		glm::vec3 pos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		pos.y += deltaTime * m_Speed;

		m_pBag->GetOwner()->GetComponent<Transform>()->SetLocalPosition(pos);

		if (!m_pBag->IsDugOut(false))
			return std::make_unique<StandardState>(m_pBag);

		return nullptr;
	}

	void FallState::CollideWithActor(glm::vec3, GameObject* player)
	{	
		auto bagpos = m_pBag->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		player->GetComponent<Transform>()->SetLocalPosition(bagpos);
		
	}
}