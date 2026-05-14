#include "Digged.h"
#include "Components/Transform.h"
#include "Components/RenderTexture.h"
#include "Digger/Hole.h"
#include "Event.h"

namespace dae
{
	DigObserver::DigObserver(GameObject* digGround)
		:m_pDigGround{ digGround }
	{}

	void DigObserver::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == make_sdbm_hash("PlayerMoved"))
		{
			glm::vec3 playerPos = gameObject->GetComponent<Transform>()->GetWorldPosition();
			glm::vec2 playerSize = gameObject->GetComponent<RenderTexture>()->GetSize();

			m_pDigGround->GetComponent<Hole>()->DigTile(playerPos, playerSize);
		}
	}
}