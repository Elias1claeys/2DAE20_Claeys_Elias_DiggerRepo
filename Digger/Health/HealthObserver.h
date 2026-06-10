#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
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

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}