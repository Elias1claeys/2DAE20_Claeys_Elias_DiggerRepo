#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class LevelObserver : public Observer
	{
	private:
		int m_TotalEmeralds = 0;
		int m_TotalEmeraldsCollected = 0;
		GameObject* m_pLevel;

	public:
		LevelObserver(GameObject* level);
		virtual ~LevelObserver() = default;
		LevelObserver(const LevelObserver& other) = delete;
		LevelObserver(LevelObserver&& other) = delete;
		LevelObserver& operator=(const LevelObserver& other) = delete;
		LevelObserver& operator=(LevelObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}