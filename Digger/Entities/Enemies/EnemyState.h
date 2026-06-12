#pragma once
#include <memory>
#include "Entities/Entity.h"

namespace dae
{
	class Enemy;

	class EnemyState
	{
	public:
		explicit EnemyState(Enemy* enemy) : m_pEnemy(enemy) {}
		virtual ~EnemyState() = default;
		EnemyState(const EnemyState& other) = delete;
		EnemyState(EnemyState&& other) = delete;
		EnemyState& operator=(const EnemyState& other) = delete;
		EnemyState& operator=(EnemyState&& other) = delete;

		virtual void const Render() = 0;
		virtual std::unique_ptr<EnemyState> Update(float deltaTime) = 0;

	protected:
		Enemy* m_pEnemy;
	};
}