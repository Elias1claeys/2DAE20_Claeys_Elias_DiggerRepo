#include "Core/GameObject.h"

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
	};
}