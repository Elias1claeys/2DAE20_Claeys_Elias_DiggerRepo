#pragma once
#include "Input/Command.h"

namespace dae
{
	class Start;

	class SwitchGameMode : public Command
	{
	protected:
		Start* m_Actor;
		int m_Direction;

	public:
		void Execute(KeyState state) override;

		SwitchGameMode(Start* actor, int dir);
		virtual ~SwitchGameMode() = default;
		SwitchGameMode(const SwitchGameMode& other) = delete;
		SwitchGameMode(SwitchGameMode&& other) = delete;
		SwitchGameMode& operator=(const SwitchGameMode& other) = delete;
		SwitchGameMode& operator=(SwitchGameMode&& other) = delete;
	};

	class SelectGameMode : public Command
	{
	protected:
		Start* m_Actor;

	public:
		void Execute(KeyState state) override;

		SelectGameMode(Start* actor);
		virtual ~SelectGameMode() = default;
		SelectGameMode(const SelectGameMode& other) = delete;
		SelectGameMode(SelectGameMode&& other) = delete;
		SelectGameMode& operator=(const SelectGameMode& other) = delete;
		SelectGameMode& operator=(SelectGameMode&& other) = delete;
	};
	
}