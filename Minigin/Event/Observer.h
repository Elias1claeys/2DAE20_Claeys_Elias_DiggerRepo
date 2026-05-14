#pragma once
#include "Event.h"

namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(GameObject* gameObject, const Event& event) = 0;
	};
}
