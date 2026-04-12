#pragma once
#include <glm/glm.hpp>
namespace dae
{
	enum class KeyState {
		Down,
		Pressed,
		Up
	};

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(KeyState state) = 0;
	};

	class PlayerComponent;
	class LevelComponent;

	class GameActorCommand : public Command
	{
		PlayerComponent* m_Actor;
	protected:
		PlayerComponent* GetGameActor() const { return m_Actor; };
	public:
		GameActorCommand(PlayerComponent* actor) { m_Actor = actor; };
		virtual ~GameActorCommand() = default;
	};

	//----------------------------
	//	Movement
	//----------------------------

	class Move : public GameActorCommand
	{
	public:
		
		void Execute(KeyState state) override;

		Move(PlayerComponent* actor, glm::vec3 dir);
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

		Attack(PlayerComponent* actor);
		virtual ~Attack() = default;
		Attack(const Attack& other) = delete;
		Attack(Attack&& other) = delete;
		Attack& operator=(const Attack& other) = delete;
		Attack& operator=(Attack&& other) = delete;
	};

	//----------------------------
	//	Next Level
	//----------------------------

	class NextLevel : public Command
	{
	protected:
		LevelComponent* m_Actor;

	public:
		void Execute(KeyState state) override;

		NextLevel(LevelComponent* actor);
		virtual ~NextLevel() = default;
		NextLevel(const NextLevel& other) = delete;
		NextLevel(NextLevel&& other) = delete;
		NextLevel& operator=(const NextLevel& other) = delete;
		NextLevel& operator=(NextLevel&& other) = delete;
	};
}
