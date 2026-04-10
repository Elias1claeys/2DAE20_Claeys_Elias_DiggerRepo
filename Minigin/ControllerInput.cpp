#include "ControllerInput.h"
#include "XInput.h"

class ControllerInput::Impl
{
public:
    int m_Index = 0;
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_PreviousState{};

    unsigned int m_ButtonsPressedThisFrame{};
    unsigned int m_ButtonsReleasedThisFrame{};

    void ProcessInput();
};

void ControllerInput::Impl::ProcessInput()
{
    CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    DWORD result = XInputGetState(m_Index, &m_CurrentState);

    if (result == ERROR_SUCCESS)
    {
        auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
        m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
        m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
    }
    else
    {
        m_ButtonsPressedThisFrame = 0;
        m_ButtonsReleasedThisFrame = 0;
    }
}

ControllerInput::ControllerInput()
    : m_Impl(std::make_unique<Impl>())
{ 
}

ControllerInput::~ControllerInput() = default;

void ControllerInput::ProcessInput()
{
    m_Impl->ProcessInput();
}

bool ControllerInput::IsDownThisFrame(unsigned int button) const
{
    return (m_Impl->m_ButtonsPressedThisFrame & button) != 0;
}

bool ControllerInput::IsUpThisFrame(unsigned int button) const
{
    return (m_Impl->m_ButtonsReleasedThisFrame & button) != 0;
}

bool ControllerInput::IsPressed(unsigned int button) const
{
    return (m_Impl->m_CurrentState.Gamepad.wButtons & button) != 0;
}