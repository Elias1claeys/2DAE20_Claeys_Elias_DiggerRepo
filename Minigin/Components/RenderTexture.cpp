#include "RenderTexture.h"
#include "Transform.h"
#include "Resources/ResourceManager.h"

dae::RenderTexture::RenderTexture(GameObject* owner)
	: Component(owner)
{
	if (!owner->HasComponent<Transform>())
	{
		owner->AddComponent<Transform>();
	}
}

const void dae::RenderTexture::Render()
{
	if (m_texture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_size.x, m_size.y, m_rotationAngle);
	}
}

void dae::RenderTexture::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_size = m_texture->GetSize();
}

void dae::RenderTexture::SetTexture(SDL_Texture* texture)
{
	m_texture = std::make_shared<Texture2D>(texture);
	m_size = m_texture->GetSize();
}

glm::vec2 dae::RenderTexture::GetSize()
{
	return m_texture->GetSize();
}