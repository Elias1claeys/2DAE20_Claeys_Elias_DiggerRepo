#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;

	//-------------------------------
	// Base Component class
	//-------------------------------

	class Component
	{
	private:
		GameObject* m_pOwner{};

	protected:
		Component(GameObject* owner) : m_pOwner(owner) {}

	public:

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() {}
		virtual void Render() const {}
		GameObject* GetOwner() const { return m_pOwner; }
	};

	//-------------------------------
	// Transform Component
	//-------------------------------

	class TransformComponent : public Component
	{
	private:
		glm::vec3 m_position{ 0, 0, 0 };

	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);

		TransformComponent(GameObject* owner);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;
	};

	//-------------------------------
	// Render Component
	//-------------------------------

	class RenderComponent : public Component
	{
	private:
		TransformComponent* m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);

		RenderComponent(GameObject* owner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	};

	//-------------------------------
	// Text Component
	//-------------------------------

	class TextComponent : public Component
	{
	private :
		RenderComponent* m_Render{};
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};

	public:

		void Update() override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255,255,255,255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	};

	//-------------------------------
	// FPS Component
	//-------------------------------

	class FPSComponent : public Component
	{
	private:
		float m_Time;

	public:
		void Update() override;

		FPSComponent(GameObject* owner);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	};
}
