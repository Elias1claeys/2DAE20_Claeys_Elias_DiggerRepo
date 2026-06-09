#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class Score : public Observer
	{
	private:
		int m_Score{ 0 };
		int m_TotalEnemarlsCollected{ 0 };
		GameObject* m_pScoreDisplay{ nullptr };

	public:

		Score(GameObject* ScoreDisplay);
		virtual ~Score() = default;
		Score(const Score& other) = delete;
		Score(Score&& other) = delete;
		Score& operator=(const Score& other) = delete;
		Score& operator=(Score&& other) = delete;


		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}