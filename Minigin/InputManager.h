#pragma once
#include "Singleton.h"
#include "ControllerInput.h"
#include <Command.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();
		void BindKeyBoardCommand(SDL_Scancode e, std::shared_ptr<Command> command);
		void BindControllerCommand(unsigned int button, std::shared_ptr<Command> command);

	private:
		void ProcessKeyBoardInput(SDL_Event e, KeyState state);

		ControllerInput m_ControllerInput{};
		std::vector<std::pair<SDL_Scancode, std::shared_ptr<Command>>> keyboardCommands;
		std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> controllerCommands;
	};

}
