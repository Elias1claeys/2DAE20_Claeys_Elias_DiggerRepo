#pragma once
#include <vector>
#include <memory>
#include "Event.h"
#include "Event/Observer.h"

namespace dae
{

	class Subject
	{
	private:
		std::vector<Observer*> m_Observers;

	protected:
		
		void Notify(Event event, GameObject* gameObject);

	public:

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
	};
}
