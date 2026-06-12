#include "Game/GameState.h"


namespace dae
{
	class Start : public GameState
	{
	private:

		std::vector<std::unique_ptr<GameObject>> m_pGameModes;
		std::vector<std::unique_ptr<GameObject>> m_pHighScores;
		int m_SelectedButton{ 0 };

		void InitGameModes();
		void InitHighScores();

	public:
		
		explicit Start(Game* game);
		virtual ~Start() = default;
		Start(const Start& other) = delete;
		Start(Start&& other) = delete;
		Start& operator=(const Start& other) = delete;
		Start& operator=(Start&& other) = delete;
		
		void SelectButton(int direction);
		void GameModeSelected();

		void Update(float ) override{}
		std::unique_ptr<GameState> GoToNextState() override;
	};
}