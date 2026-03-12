#include "ControllerInput.h"
#include <minwinbase.h>

void ControllerInput::ProcessInput()
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

bool ControllerInput::IsDownThisFrame(unsigned int button) const
{
    return (buttonsPressedThisFrame & button) != 0;
}

bool ControllerInput::IsUpThisFrame(unsigned int button) const
{
    return (buttonsReleasedThisFrame & button) != 0;
}

bool ControllerInput::IsPressed(unsigned int button) const
{
    return (currentState.Gamepad.wButtons & button) != 0;
}