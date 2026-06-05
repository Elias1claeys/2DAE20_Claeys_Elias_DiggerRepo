#include "Core/GameObject.h"
#include "Dig/DigSystem.h"

namespace dae
{
	class DigComponent : public Component
	{

	public:
		DigComponent(GameObject* owner);
		virtual ~DigComponent() = default;
		DigComponent(const DigComponent& other) = delete;
		DigComponent(DigComponent&& other) = delete;
		DigComponent& operator=(const DigComponent& other) = delete;
		DigComponent& operator=(DigComponent&& other) = delete;

		const void Render() override;
	};
}

