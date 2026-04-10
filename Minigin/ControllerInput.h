#pragma once
#include <memory>
#include <Windows.h>

class ControllerInput
{
public:

    ControllerInput();
    ~ControllerInput();
    ControllerInput(const ControllerInput& other) = delete;
    ControllerInput(ControllerInput&& other) = delete;
    ControllerInput& operator=(const ControllerInput& other) = delete;
    ControllerInput& operator=(ControllerInput&& other) = delete;

    void ProcessInput();

    bool IsDownThisFrame(unsigned int button) const;
    bool IsUpThisFrame(unsigned int button) const;
    bool IsPressed(unsigned int button) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;
};