#include "CollisionObserver.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Dig/Dig.h"
#include "Bag/bag.h"
#include "Event/Event.h"
#include "GameEvents.h"

namespace dae
{
	void Collision::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == BAG_COLLISION)
		{
			auto player = event.args[0].go;
			gameObject->GetComponent<Bag>()->CollideWithActor(player->GetComponent<Entity>()->GetDirection(), player);
		}
	}
}