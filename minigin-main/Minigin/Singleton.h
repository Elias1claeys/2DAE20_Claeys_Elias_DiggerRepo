#pragma once
#include <chrono>

namespace dae
{
	template <typename T>
	class Singleton
	{
	public:
		[[nodiscard]] static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
	};

	//Singleton class so I can get deltaTime from anywhere in the project without having to pass it around
	class Time : public Singleton<Time>
	{
		friend class dae::Singleton<Time>;

	private:
		Time() { m_lastTime = std::chrono::steady_clock::now(); };

		float m_deltaTime{};
		std::chrono::steady_clock::time_point m_lastTime{};

	public:

		void Tick(std::chrono::steady_clock::time_point currentTime)
		{
			m_deltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();
			m_lastTime = currentTime;
		}

		float GetDeltaTime() { return m_deltaTime; };
	};
}