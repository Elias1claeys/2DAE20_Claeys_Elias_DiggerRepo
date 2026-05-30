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

	std::unique_ptr<BagState> StandardState::Update(float )
	{
		if (m_pBag->IsDugOut())
			return std::make_unique<WiggleState>(m_pBag);

		return nullptr;
	}
}