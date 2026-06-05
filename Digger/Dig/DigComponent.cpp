#include "DigComponent.h"

namespace dae
{
	DigComponent::DigComponent(GameObject* owner)
		: Component(owner)
	{}

	const void DigComponent::Render()
	{
		dae::DigLocator().GetDig().Render();
	}
}