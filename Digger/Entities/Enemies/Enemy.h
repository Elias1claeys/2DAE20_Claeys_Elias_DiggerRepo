#include "Core/GameObject.h"
#include "EnemyState.h"

namespace dae
{
	class Enemy : public Component
	{
	public:
		Enemy(GameObject* owner);
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		GameObject* GetOwner() const { return Component::GetOwner(); }

		void Update() override;
		void const Render() override;

	private:
		std::unique_ptr<EnemyState> m_pEnemyState;
	};
}