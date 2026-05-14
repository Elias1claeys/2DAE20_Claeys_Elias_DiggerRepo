#pragma once

namespace dae
{
	//Singleton class so I can get deltaTime from anywhere in the project without having to pass it around
	class Time
	{

	private:
		Time() { m_lastTime = std::chrono::steady_clock::now(); };

		float m_deltaTime{};
		std::chrono::steady_clock::time_point m_lastTime{};

	public:

		static Time& GetInstance() 
		{ 
			static Time instance;
			return instance;
		}

		void Tick(std::chrono::steady_clock::time_point currentTime)
		{
			m_deltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();
			m_lastTime = currentTime;
		}

		float GetDeltaTime() { return m_deltaTime; };
	};
}