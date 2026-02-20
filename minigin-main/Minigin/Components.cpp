#include "Components.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "DeltaTime.h"

//-------------------------------
// TransForm Component
//-------------------------------
dae::TransformComponent::TransformComponent(GameObject* owner)
	: Component(owner)
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_position = position;
}

//-------------------------------
// TextureComponent
//-------------------------------
dae::TextureComponent::TextureComponent(GameObject* owner)
	: Component(owner)
{
	if (!owner->HasComponent<TransformComponent>())
	{
		owner->AddComponent<TransformComponent>();
	}
	
	m_transform = owner->GetComponent<TransformComponent>();
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_transform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

//-------------------------------
// Text Component
//-------------------------------

dae::TextComponent::TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
	: Component(owner)
	, m_needsUpdate(true)
	, m_text(text)
	, m_color(color)
	, m_font(std::move(font))
	, m_textTexture(nullptr)
{
	if (!owner->HasComponent<TransformComponent>())
	{
		owner->AddComponent<TransformComponent>();
	}

	m_transform = owner->GetComponent<TransformComponent>();
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = m_transform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}

//-------------------------------
// FPS Component
//-------------------------------

dae::FPSComponent::FPSComponent(GameObject* owner)
	: Component(owner)
	, m_Time(0.f)
{
	if (!owner->HasComponent<TextComponent>())
	{
		owner->AddComponent<TextComponent>("0 FPS", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	}
}

void dae::FPSComponent::Update()
{
	m_Time += Time::GetInstance().GetDeltaTime();

	if (m_Time >= 0.5f)
	{
		m_Time = 0.f;
		auto owner = GetOwner();
		auto fps = 1.f / Time::GetInstance().GetDeltaTime();
		fps = std::round(fps * 100.f) / 100.f;

		std::string fpsText = std::format("{:.2f} FPS", fps);

		owner->GetComponent<TextComponent>()->SetText(fpsText);
	}
}