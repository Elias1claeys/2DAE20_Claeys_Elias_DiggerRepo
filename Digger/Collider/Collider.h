#include "Core/GameObject.h"
#include <glm/glm.hpp>
#include "Event/Event.h"
#include "Event/Subject.h"

namespace dae
{
	class Collider : public Component, public Subject
	{
	public:
		struct Trigger
		{
			GameObject* triggerObject;
			Event event;
			glm::vec2 size;
			glm::vec3 offset;
			bool persistent{ false };
			bool markedForDelete{ false };
		};

		Collider(GameObject* owner, glm::vec3 offset, glm::vec2 size);
		virtual ~Collider() = default;
		Collider(const Collider& other) = delete;
		Collider(Collider&& other) = delete;
		Collider& operator=(const Collider& other) = delete;
		Collider& operator=(Collider&& other) = delete;

		void AddTrigger(Trigger trigger);
		void Update() override;
		const void Render() override;

	private:
		glm::vec2 m_ColliderSize{};
		glm::vec3 m_Offset{};
		std::vector<Trigger> m_Triggers{};

		bool Overlaps(Trigger trigger);
	};
}
