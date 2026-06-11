#include "Bag.h"
#include "Core/GameObject.h"

namespace dae
{
	class GoldState : public BagState
	{
	public:
		explicit GoldState(Bag* bag);
		virtual ~GoldState() = default;
		GoldState(const GoldState& other) = delete;
		GoldState(GoldState&& other) = delete;
		GoldState& operator=(const GoldState& other) = delete;
		GoldState& operator=(GoldState&& other) = delete;

		std::unique_ptr<BagState> Update(float deltaTime) override;
		void CollideWithActor(glm::vec3 dir, GameObject* player) override;

	private:
		int m_GoldTexture{ 0 };
		float m_Time{ 1 };
		bool m_Collected{ false };
	};
}