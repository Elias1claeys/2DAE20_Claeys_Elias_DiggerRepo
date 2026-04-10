#pragma once
#include <vector>
#include <memory>
#include "Event.h"
#include "Observer.h"

namespace dae
{

	class Subject
	{
	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;

	protected:
		
		void Notify(Event event, GameObject* gameObject);

	public:

		void AddObserver(std::unique_ptr<Observer> observer);
		void RemoveObserver(std::unique_ptr<Observer> observer);
	};
}
