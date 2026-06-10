#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Entities/Entity.h"

namespace dae
{
	class Dig;

	class Collision : public Observer
	{
	public:
		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}