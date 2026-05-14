#include "Bag.h"
#include "Components/RenderTexture.h"

dae::Bag::Bag(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<RenderTexture>()->SetTexture("media/Bag/bag.png");
}