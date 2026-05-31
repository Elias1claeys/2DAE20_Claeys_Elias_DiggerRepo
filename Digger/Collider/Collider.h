#include "Core/GameObject.h"
#include <glm/glm.hpp>
#include "Event/Event.h"
#include "Event/Subject.h"

namespace dae
{
	class Collider : public Component, public Subject
	{

	private:

		struct Trigger
		{	
			glm::vec3 position;
			glm::vec2 size;
			Event event;
			bool persistent{ false };
			bool markedForDelete{ false };
		};

		glm::vec2 m_ColliderSize{ 0, 0 };
		std::vector<Trigger> m_Triggers{};

		bool Overlaps(Trigger trigger);

	public:
		Collider(GameObject* owner);
		virtual ~Collider() = default;
		Collider(const Collider& other) = delete;
		Collider(Collider&& other) = delete;
		Collider& operator=(const Collider& other) = delete;
		Collider& operator=(Collider&& other) = delete;

		void AddTrigger(glm::vec3 position, glm::vec2 size, Event event);
		void AddTrigger(glm::vec3 position, glm::vec2 size, Event event, bool persistent);
		void Update() override;
		const void Render() override;
	};
}
