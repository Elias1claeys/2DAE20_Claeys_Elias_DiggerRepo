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

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	SetPositionDirty();
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	SetPositionDirty();
}

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::TransformComponent::SetPositionDirty()
{
	m_PositionIsDirty = true;

	for (auto& child : GetOwner()->GetChildren())
	{
		if (child->HasComponent<TransformComponent>())
			child->GetComponent<TransformComponent>()->SetPositionDirty();
	}
}

void dae::TransformComponent::UpdateWorldPosition()
{
	GameObject* parent = GetOwner()->GetParent();

	if (m_PositionIsDirty)
	{
		if(parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = parent->GetComponent<TransformComponent>()->GetWorldPosition() + m_LocalPosition;

		m_PositionIsDirty = false;
	}
}

//-------------------------------
// Render Component
//-------------------------------
dae::RenderComponent::RenderComponent(GameObject* owner)
	: Component(owner)
{
	if (!owner->HasComponent<TransformComponent>())
	{
		owner->AddComponent<TransformComponent>();
	}
}

void dae::RenderComponent::Render() const
{
	if (m_texture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_texture = std::make_shared<Texture2D>(texture);
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
	if (!owner->HasComponent<RenderComponent>())
	{
		owner->AddComponent<RenderComponent>();
	}
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
		GetOwner()->GetComponent<RenderComponent>()->SetTexture(texture);
		m_needsUpdate = false;
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
		auto fps = 1.f / Time::GetInstance().GetDeltaTime();
		fps = std::round(fps * 100.f) / 100.f;

		std::string fpsText = std::format("{:.2f} FPS", fps);

		GetOwner()->GetComponent<TextComponent>()->SetText(fpsText);
	}
}

//-------------------------------
// Rotation Component
//-------------------------------

dae::RotatorComponent::RotatorComponent(GameObject* owner, float rotationSpeed, bool rotateAroundParent)
	: Component(owner)
	, m_RotationSpeed(rotationSpeed)
	, m_RotateAroundParent(rotateAroundParent)
{
	if (!owner->HasComponent<TransformComponent>())
	{
		owner->AddComponent<TransformComponent>();
	}
}

void dae::RotatorComponent::SetRotationPoint(float x, float y, float z)
{
	m_RotationPoint.x = x;
	m_RotationPoint.y = y;
	m_RotationPoint.z = z;
}

void dae::RotatorComponent::SetRotationPoint(const glm::vec3& rotation)
{
	m_RotationPoint = rotation;
}

void dae::RotatorComponent::SetRotationDirection(bool clockwise)
{
	m_RotationDirection = clockwise ? 1.f : -1.f;
}

void dae::RotatorComponent::Update()
{
	if (m_RotateAroundParent && GetOwner()->GetParent() != nullptr)
	{
		m_RotationPoint = GetOwner()->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition();
	}

	auto transform = GetOwner()->GetComponent<TransformComponent>();
	auto localPos = transform->GetLocalPosition();

	m_CurrentAngle += m_RotationDirection * m_RotationSpeed * Time::GetInstance().GetDeltaTime();

	transform->SetLocalPosition(
		m_RotationPoint.x + std::cos(m_CurrentAngle) * 50.f,
		m_RotationPoint.y + std::sin(m_CurrentAngle) * 50.f,
		localPos.z
	);
}