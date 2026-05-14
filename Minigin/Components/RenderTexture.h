#pragma once
#include "Core/GameObject.h"
#include "Rendering/Texture2D.h"

namespace dae
{
	class RenderTexture : public Component
	{
	private:
		std::shared_ptr<Texture2D> m_texture{};
		float m_rotationAngle{ 0.f };
		glm::vec2 m_size{ 0, 0 };

	public:
		const void Render() override;
		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);
		void SetRotation(float angle) { m_rotationAngle = angle; }
		void SetSize(const glm::vec2& size) { m_size = size; }
		glm::vec2 GetSize();

		RenderTexture(GameObject* owner);
		virtual ~RenderTexture() = default;
		RenderTexture(const RenderTexture& other) = delete;
		RenderTexture(RenderTexture&& other) = delete;
		RenderTexture& operator=(const RenderTexture& other) = delete;
		RenderTexture& operator=(RenderTexture&& other) = delete;
	};
}