#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Game/Level/Level.h"

namespace dae
{
	class HealthObserver : public Observer
	{
	private:
		int m_Health{ 3 };
		GameObject* m_pHealthDisplay{ nullptr };
		Level* m_pLevel{ nullptr };

	public:

		HealthObserver(GameObject* HealthDisplay, Level* level);
		virtual ~HealthObserver() = default;
		HealthObserver(const HealthObserver& other) = delete;
		HealthObserver(HealthObserver&& other) = delete;
		HealthObserver& operator=(const HealthObserver& other) = delete;
		HealthObserver& operator=(HealthObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}