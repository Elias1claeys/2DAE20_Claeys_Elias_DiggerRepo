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
            GetGameActor()->SetDirection(m_Direction);
            break;
        case KeyState::Up:

            //If the player was still moving in that direction, stop him
            if (m_Direction == GetGameActor()->GetDirection())
            {
                GetGameActor()->SetDirection({ 0, 0, 0 });
            }
            break;
        }
    }
}
