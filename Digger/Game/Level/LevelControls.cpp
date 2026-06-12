#include "LevelControls.h"
#include "Level.h"

namespace dae
{
    //-----------------------------
    //	NextLevel
    //-----------------------------

    NextLevel::NextLevel(Level* actor)
        : m_Actor(actor)
    {}

    void NextLevel::Execute(KeyState state)
    {
        switch (state)
        {
        case dae::KeyState::Down:
            m_Actor->NextLevel();
            break;
        }
    }
}