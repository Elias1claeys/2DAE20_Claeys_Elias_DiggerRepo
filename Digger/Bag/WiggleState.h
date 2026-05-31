#include "Bag.h"
#include "Core/GameObject.h"

namespace dae
{
	class WiggleState : public BagState
	{
	public:
		explicit WiggleState(Bag* bag);
		~WiggleState() = default;
		WiggleState(const WiggleState& other) = delete;
		WiggleState(WiggleState&& other) = delete;
		WiggleState& operator=(const WiggleState& other) = delete;
		WiggleState& operator=(WiggleState&& other) = delete;

		std::unique_ptr<BagState> Update(float deltaTime) override;
		void CollideWithActor(glm::vec3 dir, Player* player) override;

	private:
		float m_Time = 0.5f;
		int m_WiggleCounter = 0;
		bool facingLeft = false;
	};
}