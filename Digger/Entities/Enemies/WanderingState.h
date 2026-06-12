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

		void const Render() override;
		std::unique_ptr<EnemyState> Update(float deltaTime) override;

	private:
		std::vector<glm::vec3> m_Directions{ {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0} };
		glm::vec3 m_PosToGo{glm::vec3(0, 0, 0)};
		glm::vec3 m_PreviousDirection{ glm::vec3(0, 0, 0) };
		std::vector<glm::vec3> m_CheckPos{};

		int m_LastDirIndex;
	};
}