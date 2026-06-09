#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace dae
{ 
	class DigSystem
	{
	public:
		virtual ~DigSystem() = default;
		virtual const void Render() = 0;
		virtual void FillDigShape(int tileId, char shape, int rotationTimes) = 0;
		virtual void DigTile(glm::vec3 playerPos, glm::vec2 playerSize) = 0;
		virtual void ResetDig() = 0;
		virtual bool BagDiggedOut(glm::vec3 bagPos, glm::vec2 bagSize) = 0;
	};

	class NullDigSystem final : public DigSystem
	{
	public:
		virtual const void Render() override {};
		virtual void FillDigShape(int, char, int) override {};
		virtual void DigTile(glm::vec3, glm::vec2) override {};
		virtual void ResetDig() override {};
		virtual bool BagDiggedOut(glm::vec3, glm::vec2) override { return false; };
	};;

	class DigLocator final
	{
	public:
		static DigSystem& GetDig()
		{
			return *m_Instance;
		}

		static void RegisterDig(std::unique_ptr<DigSystem>&& service)
		{
			if (service)
				m_Instance = std::move(service);
			else
				m_Instance = std::make_unique<NullDigSystem>();
		}

	private:
		static std::unique_ptr<DigSystem> m_Instance;
	};
}