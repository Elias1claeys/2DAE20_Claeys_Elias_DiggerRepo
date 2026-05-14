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
}