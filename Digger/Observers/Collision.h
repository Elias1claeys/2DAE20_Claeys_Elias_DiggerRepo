#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Player/Player.h"

namespace dae
{
	class Hole;

	class Collision : public Observer
	{
	private:
		Hole* m_pDigGround{ nullptr };
		Player* m_pPlayer{ nullptr };
	public:

		Collision(Hole* digGround, Player* player);
		virtual ~Collision() = default;
		Collision(const Collision& other) = delete;
		Collision(Collision&& other) = delete;
		Collision& operator=(const Collision& other) = delete;
		Collision& operator=(Collision&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}