#include "Entities/Entity.h"

namespace dae
{
	class Bag;

	class BagState
	{
	public:
		explicit BagState(Bag* bag): m_pBag(bag) {}
		virtual ~BagState() = default;
		BagState(const BagState& other) = delete;
		BagState(BagState&& other) = delete;
		BagState& operator=(const BagState& other) = delete;
		BagState& operator=(BagState&& other) = delete;

		virtual std::unique_ptr<BagState> Update(float deltaTime) = 0;
		virtual void CollideWithActor(glm::vec3 dir, Entity* player) = 0;

	protected:
		Bag* m_pBag;
		float m_Speed = 100.f;
		glm::vec3 m_BagDir = { 0, 0, 0 };
	};
}