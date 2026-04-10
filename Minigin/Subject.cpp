#include "Subject.h"


void dae::Subject::AddObserver(std::unique_ptr<Observer> observer)
{
	m_Observers.push_back(std::move(observer));
}

void dae::Subject::RemoveObserver(std::unique_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer),
		m_Observers.end());
}

void dae::Subject::Notify( Event event, GameObject* gameObject)
{
	for (int i = 0; i < m_Observers.size(); i++)
	{
		m_Observers[i]->OnNotify(gameObject, event);
	}
}