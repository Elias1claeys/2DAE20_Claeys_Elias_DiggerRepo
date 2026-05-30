#include "Bag.h"
#include "Core/GameObject.h"

namespace dae
{
	class StandardState : public BagState
	{
	public:
		explicit StandardState(Bag* bag);
		~StandardState() = default;
		StandardState(const StandardState& other) = delete;
		StandardState(StandardState&& other) = delete;
		StandardState& operator=(const StandardState& other) = delete;
		StandardState& operator=(StandardState&& other) = delete;


		std::unique_ptr<BagState> Update(float deltaTime) override;
	};
}