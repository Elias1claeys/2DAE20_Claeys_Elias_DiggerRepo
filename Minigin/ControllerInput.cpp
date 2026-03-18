#include "ControllerInput.h"
#include <Windows.h>
#include "XInput.h"

class ControllerInput::Impl
{
public:
    int index = 0;
    XINPUT_STATE currentState{};
    XINPUT_STATE previousState{};

    unsigned int buttonsPressedThisFrame{};
    unsigned int buttonsReleasedThisFrame{};

    void ProcessInput();
};

void ControllerInput::Impl::ProcessInput()
{
    CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
    ZeroMemory(&currentState, sizeof(XINPUT_STATE));
    DWORD result = XInputGetState(index, &currentState);

    if (result == ERROR_SUCCESS)
    {
        auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
        buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
        buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
    }
    else
    {
        buttonsPressedThisFrame = 0;
        buttonsReleasedThisFrame = 0;
    }
}

ControllerInput::ControllerInput()
    : impl(std::make_unique<Impl>())
{ 
}

ControllerInput::~ControllerInput() = default;

void ControllerInput::ProcessInput()
{
    impl->ProcessInput();
}

bool ControllerInput::IsDownThisFrame(unsigned int button) const
{
    return (impl->buttonsPressedThisFrame & button) != 0;
}

bool ControllerInput::IsUpThisFrame(unsigned int button) const
{
    return (impl->buttonsReleasedThisFrame & button) != 0;
}

bool ControllerInput::IsPressed(unsigned int button) const
{
    return (impl->currentState.Gamepad.wButtons & button) != 0;
}