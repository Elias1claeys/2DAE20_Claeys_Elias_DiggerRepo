#pragma once
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "Components.h"

namespace dae
{
	class GameObject final
	{
	public:
		void Update() 
		{
			for (auto& comp : m_pComponents)
			{
				comp->Update();
			}

			m_pComponents.erase(
				std::remove_if(
					m_pComponents.begin(),
					m_pComponents.end(),
					[](const auto& comp)
					{
						return comp->IsMarkedForDelete();
					}
				),
				m_pComponents.end()
			);
		};

		void Render() const 
		{
			if (HasComponent<RenderComponent>())
			{
				auto renderComp = GetComponent<RenderComponent>();
				renderComp->Render();
			}
		};

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			//Safety check so a component can't be added twice
			if (HasComponent<T>())
				return nullptr;

			auto component = std::unique_ptr<T>(new T(this, std::forward<Args>(args)...));
			T* ptr = component.get();
			m_pComponents.push_back(std::move(component));
			return ptr;
		}

		template<typename T>
		T* GetComponent() const 
		{
			for (auto& comp : m_pComponents)
			{
				if (auto casted = dynamic_cast<T*>(comp.get()))
					return casted;
			}
			return nullptr;
		}

		template<typename T, typename... Args>
		bool HasComponent(Args&&... args) const
		{
			for (auto& comp : m_pComponents)
			{
				if (dynamic_cast<T*>(comp.get()))
					return true;
			}
			return false;
		}

		template<typename T, typename... Args>
		void RemoveComponent(Args&&... args)
		{
			for (auto& comp : m_pComponents)
			{
				if (dynamic_cast<T*>(comp.get()))
					comp->MarkForDelete();
			}
		}

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<Component>> m_pComponents{};
		bool m_markedForDelete{ false };
	};
}
