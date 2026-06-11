#include "Bag.h"
#include "Core/GameObject.h"

namespace dae
{
	class FallState : public BagState
	{
	public:
		explicit FallState(Bag* bag);
		~FallState() = default;
		FallState(const FallState& other) = delete;
		FallState(FallState&& other) = delete;
		FallState& operator=(const FallState& other) = delete;
		FallState& operator=(FallState&& other) = delete;

		std::unique_ptr<BagState> Update(float deltaTime) override;
		void CollideWithActor(glm::vec3 dir, GameObject* player) override;

	private:
		glm::vec3 m_FirstPos{};
	};
}