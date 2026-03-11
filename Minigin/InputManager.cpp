#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		if (e.type == SDL_EVENT_KEY_DOWN && !e.key.repeat) 
		{
			ProcessKeyBoardInput(e, KeyState::Down);
		}

		if (e.type == SDL_EVENT_KEY_UP) 
		{
			ProcessKeyBoardInput(e, KeyState::Up);
		}

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	// Continuous input
	const bool* state = SDL_GetKeyboardState(nullptr);
	
	for (auto& com : keyboardCommands)
	{
		if (state[com.first])
		{
			com.second->Execute(KeyState::Pressed);
		}
	}

	//Controller input
	m_ControllerInput.ProcessInput();

	for (const auto& com : controllerCommands)
	{
		if (m_ControllerInput.IsDownThisFrame(com.first))
		{
			com.second->Execute(KeyState::Down);
		}
		else if (m_ControllerInput.IsPressed(com.first))
		{
			com.second->Execute(KeyState::Pressed);
		}
		else if (m_ControllerInput.IsUpThisFrame(com.first))
		{
			com.second->Execute(KeyState::Up);
		}
	}

	return true;
}

void dae::InputManager::ProcessKeyBoardInput(SDL_Event e, KeyState state)
{
	SDL_Scancode key = e.key.scancode;

	for (auto com : keyboardCommands)
	{
		if (com.first == key)
		{
			com.second->Execute(state);
		}
	}
}

void dae::InputManager::BindKeyBoardCommand(SDL_Scancode e, std::shared_ptr<Command> command)
{
	keyboardCommands.push_back({e, command});
}

void dae::InputManager::BindControllerCommand(unsigned int button, std::shared_ptr<Command> command)
{
	controllerCommands.push_back({button, command});
}
