#pragma once
#include "Input/Command.h"

namespace dae
{
	class PlayerInputComponent;

	class GameActorCommand : public Command
	{
		PlayerInputComponent* m_Actor;
	protected:
		PlayerInputComponent* GetGameActor() const { return m_Actor; };
	public:
		GameActorCommand(PlayerInputComponent* actor) { m_Actor = actor; };
		virtual ~GameActorCommand() = default;
	};

	//----------------------------
	//	Movement
	//----------------------------

	class Move : public GameActorCommand
	{
	public:

		void Execute(KeyState state) override;

		Move(PlayerInputComponent* actor, glm::vec3 dir);
		virtual ~Move() = default;
		Move(const Move& other) = delete;
		Move(Move&& other) = delete;
		Move& operator=(const Move& other) = delete;
		Move& operator=(Move&& other) = delete;

	private:
		glm::vec3 m_Direction;
	};

	//---------------------------------
	// Attack
	//---------------------------------

	class Attack : public GameActorCommand
	{
	public:

		void Execute(KeyState state) override;

		Attack(PlayerInputComponent* actor);
		virtual ~Attack() = default;
		Attack(const Attack& other) = delete;
		Attack(Attack&& other) = delete;
		Attack& operator=(const Attack& other) = delete;
		Attack& operator=(Attack&& other) = delete;
	};
}