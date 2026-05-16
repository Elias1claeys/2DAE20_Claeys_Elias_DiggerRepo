#include "Bag.h"
#include "Components/Texture.h"

dae::Bag::Bag(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<Texture>()->SetTexture("media/Bag/bag.png");
}