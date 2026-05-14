#include "FPS.h"
#include "Text.h"
#include "Resources/ResourceManager.h"
#include "Core/DeltaTime.h"

dae::FPSComponent::FPSComponent(GameObject* owner)
	: Component(owner)
	, m_Time(0.f)
{
	if (!owner->HasComponent<Text>())
	{
		owner->AddComponent<Text>("0 FPS", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
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

		GetOwner()->GetComponent<Text>()->SetText(fpsText);
	}
}