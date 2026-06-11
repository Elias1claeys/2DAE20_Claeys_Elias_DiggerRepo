#include "EnemyState.h"

namespace dae
{
	class WanderingState : public EnemyState
	{
	public:
		explicit WanderingState(Enemy* enemy);
		~WanderingState() = default;
		WanderingState(const WanderingState& other) = delete;
		WanderingState(WanderingState&& other) = delete;
		WanderingState& operator=(const WanderingState& other) = delete;
		WanderingState& operator=(WanderingState&& other) = delete;

		std::unique_ptr<EnemyState> Update(float deltaTime) override;
	};
}