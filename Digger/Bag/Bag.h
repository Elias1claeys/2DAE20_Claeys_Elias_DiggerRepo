#pragma once
#include "Core/GameObject.h"
#include "BagState.h"
#include "Player/Player.h"
#include <memory>

namespace dae
{
	class Hole;

	class Bag : public Component
	{
	public:

		Bag(GameObject* owner, Hole* hole);
		virtual ~Bag() = default;
		Bag(const Bag& other) = delete;
		Bag(Bag&& other) = delete;
		Bag& operator=(const Bag& other) = delete;
		Bag& operator=(Bag&& other) = delete;

		GameObject* GetOwner() const { return Component::GetOwner(); }

		void Update() override;
		void CollideWithActor(glm::vec3 dir, Player* player);
		bool IsDugOut();

	private:
		std::unique_ptr<BagState> m_CurrentState;
		Hole* m_pHole;
	};
}