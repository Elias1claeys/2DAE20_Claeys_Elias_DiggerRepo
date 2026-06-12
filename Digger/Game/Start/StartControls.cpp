#include "StartControls.h"
#include "Start.h"

namespace dae
{
	SwitchGameMode::SwitchGameMode(Start* actor, int dir)
		: m_Actor(actor), m_Direction(dir)
	{}

	void SwitchGameMode::Execute(KeyState state)
	{
		switch (state)
		{
		case dae::KeyState::Up:
			m_Actor->SelectButton(m_Direction);
			break;
		}
	}

	SelectGameMode::SelectGameMode(Start* actor)
		: m_Actor(actor)
	{}

	void SelectGameMode::Execute(KeyState state)
	{
		switch (state)
		{
		case dae::KeyState::Up:
			m_Actor->GameModeSelected();
			break;
		}
	}
}