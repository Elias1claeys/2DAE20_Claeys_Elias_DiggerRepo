#pragma once
#include <Windows.h>
#include "XInput.h"

class ControllerInput
{
public:

    void ProcessInput();

    bool IsDownThisFrame(unsigned int button) const;
    bool IsUpThisFrame(unsigned int button) const;
    bool IsPressed(unsigned int button) const;

private:
    int index = 0;
    XINPUT_STATE currentState{};
    XINPUT_STATE previousState{};

    unsigned int buttonsPressedThisFrame{};
    unsigned int buttonsReleasedThisFrame{};
};