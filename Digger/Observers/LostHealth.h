#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class Health : public Observer
	{
	private:
		int m_Health{ 5 };
		GameObject* m_pHealthDisplay{ nullptr };

	public:

		Health(GameObject* HealthDisplay);
		virtual ~Health() = default;
		Health(const Health& other) = delete;
		Health(Health&& other) = delete;
		Health& operator=(const Health& other) = delete;
		Health& operator=(Health&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}