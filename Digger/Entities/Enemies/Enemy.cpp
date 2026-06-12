#include "Enemy.h"
#include "WanderingState.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Enemy::Enemy(GameObject* owner)
		: Component(owner)
	{
		m_pEnemyState = std::make_unique<WanderingState>(this);
	}

	void Enemy::Update()
	{
		m_pEnemyState->Update(Time::GetInstance().GetDeltaTime());
	}

	void const Enemy::Render()
	{
		m_pEnemyState->Render();
	}
}