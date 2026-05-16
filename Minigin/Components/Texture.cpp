#include "Texture.h"
#include "Transform.h"
#include "Resources/ResourceManager.h"

dae::Texture::Texture(GameObject* owner)
	: Component(owner)
{
	if (!owner->HasComponent<Transform>())
	{
		owner->AddComponent<Transform>();
	}
}

const void dae::Texture::Render()
{
	if (m_texture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		Renderer::GetInstance().Texture(*m_texture, pos.x, pos.y, m_size.x, m_size.y, m_rotationAngle);
	}
}

void dae::Texture::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_size = m_texture->GetSize();
}

void dae::Texture::SetTexture(SDL_Texture* texture)
{
	m_texture = std::make_shared<Texture2D>(texture);
	m_size = m_texture->GetSize();
}

glm::vec2 dae::Texture::GetSize()
{
	return m_texture->GetSize();
}