#pragma once
#include "Core/GameObject.h"

namespace dae
{
	class HealthDisplay : public Component
	{
	private:
		int m_Health;

	public:
		HealthDisplay(GameObject* owner);
		virtual ~HealthDisplay() = default;
		HealthDisplay(const HealthDisplay& other) = delete;
		HealthDisplay(HealthDisplay&& other) = delete;
		HealthDisplay& operator=(const HealthDisplay& other) = delete;
		HealthDisplay& operator=(HealthDisplay&& other) = delete;

		const void Render() override;

		void DoDamage() { m_Health--; };
		void GetExtraLife() { m_Health++; };
	};
}
