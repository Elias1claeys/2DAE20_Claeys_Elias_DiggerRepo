#pragma once
#include "BaseCommand.h"

namespace dae
{
	class Level;

	//----------------------------
	//	Next Level
	//----------------------------

	class NextLevel : public Command
	{
	protected:
		Level* m_Actor;

	public:
		void Execute(KeyState state) override;

		NextLevel(Level* actor);
		virtual ~NextLevel() = default;
		NextLevel(const NextLevel& other) = delete;
		NextLevel(NextLevel&& other) = delete;
		NextLevel& operator=(const NextLevel& other) = delete;
		NextLevel& operator=(NextLevel&& other) = delete;
	};
}