#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class ScoreObserver : public Observer
	{
	private:
		int m_Score{ 0 };

	public:

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}