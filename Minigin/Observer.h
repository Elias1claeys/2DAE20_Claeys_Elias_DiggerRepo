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

	//-----------------------------------
	//	Score Observer
	//-----------------------------------

	class ScoreObserver : public Observer
	{
	private:
		int m_Score{ 0 };

	public: 

		void OnNotify(GameObject* gameObject, Event event) override;
	};

	//-----------------------------------
	//	Healt Observer
	//-----------------------------------

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

	//------------------------------------
	//	Dig Observer
	//------------------------------------

	class DigObserver : public Observer
	{
	private:
		GameObject* m_pDigGround{ nullptr };
	public:

		DigObserver(GameObject* digGround);
		virtual ~DigObserver() = default;
		DigObserver(const DigObserver& other) = delete;
		DigObserver(DigObserver&& other) = delete;
		DigObserver& operator=(const DigObserver& other) = delete;
		DigObserver& operator=(DigObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, Event event) override;
	};
}
