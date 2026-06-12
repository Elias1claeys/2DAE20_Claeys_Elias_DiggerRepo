#include "WanderingState.h"
#include "EnemyState.h"
#include "Enemy.h"
#include "Components/Transform.h"
#include "Dig/DigComponent.h"
#include "Rendering/Renderer.h"
#include "Components/Texture.h"

namespace dae
{
	WanderingState::WanderingState(Enemy* enemy)
		: EnemyState(enemy)
	{}

	void const WanderingState::Render()
	{
		auto enemyPos = m_pEnemy->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		auto enemySize = m_pEnemy->GetOwner()->GetComponent<Texture>()->GetSize();


        for (auto &check : m_CheckPos)
        {
            SDL_FRect rect{};
            rect.x = (float)check.x;
            rect.y = (float)check.y;
            rect.w = 8.f;
            rect.h = 8.f;

            Renderer::GetInstance().DrawRect({ 255, 0, 0, 255 }, rect);
        }
	}

	std::unique_ptr<EnemyState> WanderingState::Update(float )
	{
        auto enemyPos = m_pEnemy->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
        float tileSize = 64;

        if (m_PosToGo == glm::vec3(0, 0, 0) || glm::distance(enemyPos, m_PosToGo) < 2.f)
        {
            // Snap to target to avoid drift
            if (m_PosToGo != glm::vec3(0, 0, 0))
                m_pEnemy->GetOwner()->GetComponent<Transform>()->SetLocalPosition(m_PosToGo);

            enemyPos = m_pEnemy->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

            std::vector<glm::vec3> valid;
            std::vector<glm::vec3> fallback; // for U-turn only

            for (auto& dir : m_Directions)
            {
                if (dir == m_PreviousDirection * -1.f)
                {
                    fallback.push_back(dir);
                    continue;
                }

                m_CheckPos.clear();
                glm::vec3 nextPos = enemyPos + dir * tileSize;
                m_CheckPos.push_back(nextPos);

                if (DigLocator::GetDig().IsDugOut(nextPos))
                    valid.push_back(dir);
            }

            // Use fallback only if no other options
            auto& choices = valid.empty() ? fallback : valid;
            if (choices.empty()) return nullptr;

            int n = rand() % choices.size();
            m_PreviousDirection = choices[n];
            m_PosToGo = enemyPos + choices[n] * tileSize;

            glm::vec3 dir = glm::normalize(m_PosToGo - enemyPos);
            m_pEnemy->GetOwner()->GetComponent<Transform>()->SetLocalPosition(enemyPos);
            m_pEnemy->GetOwner()->GetComponent<Entity>()->SetDirection(dir);
        }

        return nullptr;
	}
}