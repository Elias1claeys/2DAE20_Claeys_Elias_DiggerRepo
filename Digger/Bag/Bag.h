#pragma once
#include "Core/GameObject.h"
#include "BagState.h"
#include "Entities/Entity.h"
#include <memory>
#include "Event/Subject.h"


namespace dae
{
	class Bag : public Component, public Subject
	{
	public:

		Bag(GameObject* owner);
		virtual ~Bag() = default;
		Bag(const Bag& other) = delete;
		Bag(Bag&& other) = delete;
		Bag& operator=(const Bag& other) = delete;
		Bag& operator=(Bag&& other) = delete;

		GameObject* GetOwner() const { return Component::GetOwner(); }

		void Update() override;
		void CollideWithActor(glm::vec3 dir, GameObject* player);
		void CollectGold();
		bool IsDugOut(bool checkTop);
		void DestroyBag();

	private:
		std::unique_ptr<BagState> m_CurrentState;
	};
}