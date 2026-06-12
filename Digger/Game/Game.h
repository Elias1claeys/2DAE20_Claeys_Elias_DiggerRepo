#include "Core/GameObject.h"
#include "GameState.h"

namespace dae
{
	class Game : public Component
	{
	public:

		Game(GameObject* owner);
		virtual ~Game() = default;
		Game(const Game& other) = delete;
		Game(Game&& other) = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) = delete;

		GameObject* GetOwner() const { return Component::GetOwner(); }

		void Update() override;
		void GoToNextStage();

	private:
		std::unique_ptr<GameState> m_pGameState;
	};
}