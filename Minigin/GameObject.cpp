#include "GameObject.h"

namespace dae
{
	void GameObject::Update()
	{
		for (auto& comp : m_pComponents)
		{
			comp->Update();
		}

		//Safely remove components that are marked for deletion
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
	}

	void GameObject::Render()
	{
		if (HasComponent<RenderComponent>())
		{
			auto renderComp = GetComponent<RenderComponent>();
			renderComp->Render();
		}
	}

	bool GameObject::IsChild(GameObject* child) const
	{
		return std::find(m_pChildren.begin(), m_pChildren.end(), child) != m_pChildren.end();
	}

	void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
	{
		if (IsChild(parent) || parent == this || m_pParent == parent)
			return;

		TransformComponent* transform = this->GetComponent<TransformComponent>();

		if (parent == nullptr)
			transform->SetLocalPosition(transform->GetWorldPosition());
		else
		{
			if (keepWorldPosition)
				transform->SetLocalPosition(transform->GetWorldPosition() - parent->GetComponent<TransformComponent>()->GetWorldPosition());
			transform->SetPositionDirty();
		}

		if (m_pParent) m_pParent->RemoveChild(this, keepWorldPosition);
		m_pParent = parent;
		if (m_pParent) m_pParent->AddChild(this, keepWorldPosition);

	}

	void GameObject::AddChild(GameObject* child, bool keepWorldPosition)
	{
		if (child == nullptr || child == this || IsChild(child))
			return;

		TransformComponent* transform = this->GetComponent<TransformComponent>();

		if (child == nullptr)
			transform->SetLocalPosition(transform->GetWorldPosition());
		else
		{
			if (keepWorldPosition)
				transform->SetLocalPosition(transform->GetWorldPosition() - child->GetComponent<TransformComponent>()->GetWorldPosition());
			transform->SetPositionDirty();
		}

		RemoveChild(child, keepWorldPosition);
		//m_pParent = this;
		m_pChildren.push_back(child);
	}

	void GameObject::RemoveChild(GameObject* child, bool keepWorldPosition)
	{
		if (child == nullptr || child == this || !IsChild(child))
			return;

		TransformComponent* transform = this->GetComponent<TransformComponent>();

		if (child == nullptr)
			transform->SetLocalPosition(transform->GetWorldPosition());
		else
		{
			if (keepWorldPosition)
				transform->SetLocalPosition(transform->GetWorldPosition() - child->GetComponent<TransformComponent>()->GetWorldPosition());
			transform->SetPositionDirty();
		}

		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
		child->m_pParent = nullptr;
	}
}
