#include "WanderingState.h"

namespace dae
{
	WanderingState::WanderingState(Enemy* enemy)
		: EnemyState(enemy)
	{}

	std::unique_ptr<EnemyState> WanderingState::Update(float )
	{
		return nullptr;
	}
}