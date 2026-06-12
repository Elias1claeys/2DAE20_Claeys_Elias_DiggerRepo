#include "Enemy.h"
#include "WanderingState.h"
#include "Core/DeltaTime.h"
#include "Components/Texture.h"
#include "Collider/Collider.h"

namespace dae
{
	Enemy::Enemy(GameObject* owner)
		: Component(owner)
	{
		m_pEnemyState = std::make_unique<WanderingState>(this);
	}

	void Enemy::Update()
	{
		if(!m_IsDead)
			m_pEnemyState->Update(Time::GetInstance().GetDeltaTime());
	}

	void const Enemy::Render()
	{
		m_pEnemyState->Render();
	}

	void Enemy::KillEnemy()
	{
		m_IsDead = true;
		GetOwner()->GetComponent<Transform>()->SetLocalPosition(glm::vec3(1000, 1000, 0));
	}
}