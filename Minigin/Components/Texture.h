#pragma once
#include "Core/GameObject.h"
#include "Rendering/Texture2D.h"

namespace dae
{
	class Texture : public Component
	{
	private:
		std::shared_ptr<Texture2D> m_texture{};
		float m_rotationAngle{ 0.f };
		glm::vec2 m_size{ 0, 0 };
		SDL_FlipMode m_FlipMode{SDL_FLIP_NONE};

	public:
		const void Render() override;
		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);
		void SetRotation(float angle) { m_rotationAngle = angle; }
		void SetSize(const glm::vec2& size) { m_size = size; }
		void FlipTexture();

		glm::vec2 GetSize();

		Texture(GameObject* owner);
		virtual ~Texture() = default;
		Texture(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) = delete;
	};
}