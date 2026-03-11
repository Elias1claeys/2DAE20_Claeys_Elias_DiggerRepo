#pragma once
namespace dae
{
	enum class KeyState {
		Down,
		Pressed,
		Up
	};

	class PlayerComponent;
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(KeyState state) = 0;
	};

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

	class MoveLeft : public GameActorCommand
	{
	public:
      MoveLeft(PlayerComponent* actor) : GameActorCommand(actor) {};
		void Execute(KeyState state) override;
	};

	class MoveRight : public GameActorCommand
	{
	public:
     MoveRight(PlayerComponent* actor) : GameActorCommand(actor) {};
		void Execute(KeyState state) override;
	};

	class MoveUp : public GameActorCommand
	{
	public:
        MoveUp(PlayerComponent* actor) : GameActorCommand(actor) {};
		void Execute(KeyState state) override;
	};

	class MoveDown : public GameActorCommand
	{
	public:
      MoveDown(PlayerComponent* actor) : GameActorCommand(actor) {};
		void Execute(KeyState state) override;
	};
}
