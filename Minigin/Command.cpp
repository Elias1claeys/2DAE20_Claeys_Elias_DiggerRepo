#include "Command.h"
#include "Components.h"

namespace dae
{
    void MoveLeft::Execute(KeyState state)
    {
        switch (state)
        {
        case KeyState::Down:
            break;
        case KeyState::Pressed:
            GetGameActor()->Move({ -1, 0, 0 });
            break;
        case KeyState::Up:
            break;
        }
    }

    void MoveRight::Execute(KeyState state)
    {
        switch (state)
        {
        case KeyState::Down:
            break;
        case KeyState::Pressed:
            GetGameActor()->Move({ 1, 0, 0 });
            break;
        case KeyState::Up:
            break;
        }
    }

    void MoveUp::Execute(KeyState state)
    {
        switch (state)
        {
        case KeyState::Down:
            break;
        case KeyState::Pressed:
            GetGameActor()->Move({ 0, -1, 0 });
            break;
        case KeyState::Up:
            break;
        }
    }

    void MoveDown::Execute(KeyState state)
    {
        switch (state)
        {
        case KeyState::Down:
            break;
        case KeyState::Pressed:
            GetGameActor()->Move({ 0, 1, 0 });
            break;
        case KeyState::Up:
            break;
        }
    }
}
