#pragma once
#include <vector>
#include <memory>
#include "Event.h"

namespace dae
{
	
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(GameObject* gameObject, Event event) = 0;
	};

	
	class ScoreObserver : public Observer
	{
	private:
		int m_Score{ 0 };

	public: 
		void OnNotify(GameObject* gameObject, Event event) override;
	};

	class HealthObserver : public Observer
	{
	private:
		int m_Health{ 5 };
		GameObject* m_pHealthDisplay{ nullptr };

	public:

		HealthObserver(GameObject* HealthDisplay);
		virtual ~HealthObserver() = default;
		HealthObserver(const HealthObserver& other) = delete;
		HealthObserver(HealthObserver&& other) = delete;
		HealthObserver& operator=(const HealthObserver& other) = delete;
		HealthObserver& operator=(HealthObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, Event event) override;
	};
}
