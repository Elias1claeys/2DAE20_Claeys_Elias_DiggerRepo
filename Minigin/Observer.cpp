#include "Observer.h"
#include "GameObject.h"
#include "Components.h"

//-------------------------------
// Score Observer
//-------------------------------

void dae::ScoreObserver::OnNotify(GameObject* gameObject, Event event)
{
	if (event.id == make_sdbm_hash("EnemyKilled"))
		m_Score += 100;

	gameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));
}

//-------------------------------
// Health Observer
//-------------------------------

dae::HealthObserver::HealthObserver(GameObject* HealthDisplay)
	: m_pHealthDisplay(HealthDisplay)
{
	m_pHealthDisplay->GetComponent<TextComponent>()->SetText(std::to_string(m_Health));
}

void dae::HealthObserver::OnNotify(GameObject*, Event event)
{
	if (event.id == make_sdbm_hash("PlayerHit"))
		m_Health -= 1;

	m_pHealthDisplay->GetComponent<TextComponent>()->SetText(std::to_string(m_Health));
}

//------------------------------------
//	Dig Observer
//------------------------------------

dae::DigObserver::DigObserver(GameObject* digGround)
	:m_pDigGround{digGround}
{
}

void dae::DigObserver::OnNotify(GameObject* gameObject, Event event)
{
	if (event.id == make_sdbm_hash("PlayerMoved"))
	{
		glm::vec3 playerPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();
		glm::vec2 playerSize = gameObject->GetComponent<RenderComponent>()->GetSize();

		m_pDigGround->GetComponent<HoleComponent>()->DigTile(playerPos, playerSize);
	}
}