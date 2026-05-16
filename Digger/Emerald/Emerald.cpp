#include "Emerald.h"
#include "Components/Texture.h"
#include "Observers/GameEvents.h"

dae::Emerald::Emerald(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<Texture>()->SetTexture("media/Emerald/emerald.png");
}

void dae::Emerald::Collect()
{
	if (m_IsCollected)
		return;

	m_IsCollected = true;
	GetOwner()->GetComponent<Texture>()->SetTexture("media/Emerald/emeraldEmpty.png");
	Notify(Event{ EMERALD_COLLECTED }, GetOwner());
}