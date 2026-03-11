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

		UpdateTransForm(parent, keepWorldPosition);

		if (m_pParent) m_pParent->RemoveChild(this, keepWorldPosition);
		m_pParent = parent;
		if (m_pParent) m_pParent->AddChild(this, keepWorldPosition);

	}

	void GameObject::AddChild(GameObject* child, bool keepWorldPosition)
	{
		if (child == nullptr || child == this || IsChild(child))
			return;

		UpdateTransForm(child, keepWorldPosition);

		if (child->m_pParent) child->m_pParent->RemoveChild(child, keepWorldPosition);
		child->m_pParent = this;
		m_pChildren.push_back(child);
	}

	void GameObject::RemoveChild(GameObject* child, bool keepWorldPosition)
	{
		if (child == nullptr || child == this || !IsChild(child))
			return;

		UpdateTransForm(child, keepWorldPosition);

		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
		child->m_pParent = nullptr;
	}

	void GameObject::UpdateTransForm(GameObject* child, bool keepWorldPosition)
	{
		TransformComponent* transform = this->GetComponent<TransformComponent>();

		if (child == nullptr)
			transform->SetLocalPosition(transform->GetWorldPosition());
		else
		{
			if (keepWorldPosition)
				transform->SetLocalPosition(transform->GetWorldPosition() - child->GetComponent<TransformComponent>()->GetWorldPosition());
			transform->SetPositionDirty();
		}
	}
}
