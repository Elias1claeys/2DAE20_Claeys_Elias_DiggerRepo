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

	private:
		std::vector<std::unique_ptr<Component>> m_pComponents{};
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		bool IsChild(GameObject* child) const;
		void AddChild(GameObject* child, bool keepWorldPosition);
		void RemoveChild(GameObject* child, bool keepWorldPosition);
		void UpdateTransForm(GameObject* child, bool keepWorldPosition);
		
	public:

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render();

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_pParent; }
		std::vector<GameObject*> GetChildren() const { return m_pChildren; }

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

		template<typename T>
		bool HasComponent() const
		{
			for (auto& comp : m_pComponents)
			{
				if (dynamic_cast<T*>(comp.get()))
					return true;
			}
			return false;
		}

		template<typename T>
		void RemoveComponent()
		{
			for (auto& comp : m_pComponents)
			{
				if (dynamic_cast<T*>(comp.get()))
					comp->MarkForDelete();
			}
		}
	};
}
