#include "Command.h"
#include "Components.h"

namespace dae
{
    //-----------------------------
    // Movement
    //-----------------------------

    Move::Move(PlayerComponent* actor, glm::vec3 dir)
        : GameActorCommand(actor), m_Direction(dir)
    {
    }

    void Move::Execute(KeyState state)
    {
        switch (state)
        {
        case KeyState::Down:
            break;
        case KeyState::Pressed:
            GetGameActor()->Move({ m_Direction });
            break;
        case KeyState::Up:
            break;
        }
    }
}
