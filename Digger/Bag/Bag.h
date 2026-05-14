#pragma once
#include "Core/GameObject.h"


namespace dae
{
	class Bag : public Component
	{
	public:

		Bag(GameObject* owner);
		virtual ~Bag() = default;
		Bag(const Bag& other) = delete;
		Bag(Bag&& other) = delete;
		Bag& operator=(const Bag& other) = delete;
		Bag& operator=(Bag&& other) = delete;
	};
}