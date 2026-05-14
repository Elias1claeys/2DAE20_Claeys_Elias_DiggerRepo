#include "Emerald.h"
#include "Components/RenderTexture.h"

dae::Emerald::Emerald(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<RenderTexture>()->SetTexture("media/Emerald/emerald.png");
}