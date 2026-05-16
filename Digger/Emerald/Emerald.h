#include "Core/GameObject.h"
#include "Event/Subject.h"

namespace dae
{
	class Emerald : public Component, public Subject
	{
	private:
		bool m_IsCollected{ false };

	public:

		Emerald(GameObject* owner);
		virtual ~Emerald() = default;
		Emerald(const Emerald& other) = delete;
		Emerald(Emerald&& other) = delete;
		Emerald& operator=(const Emerald& other) = delete;
		Emerald& operator=(Emerald&& other) = delete;

		void Collect();
	};
}