#include "Components.h"
#include "Font.h"
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"

//-------------------------------
// TextureComponent
//-------------------------------
dae::TextureComponent::TextureComponent(GameObject* owner)
	: Component(owner)
{
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
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
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y);
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

		if (owner->HasComponent<TextComponent>())
		{
			owner->GetComponent<TextComponent>()->SetText(fpsText);
		}
		else
		{
			auto textComp = owner->AddComponent<TextComponent>(fpsText, ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
			textComp->SetPosition(5, 5);
		}
	}
}