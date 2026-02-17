#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL_pixels.h>
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;

	//-------------------------------
	// Base Component class, all components will derive from this
	//-------------------------------

	class Component
	{

	protected:
		GameObject* m_pOwner{};

	public:

		Component(GameObject* owner) : m_pOwner(owner) {}
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
	// TextureComponent, renders a texture to the screen
	//-------------------------------

	class TextureComponent : public Component
	{
	private:

		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextureComponent(GameObject* owner);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	};

	//-------------------------------
	// Text Component, renders text to the screen
	//-------------------------------

	class TextComponent : public Component
	{
	private :
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		Transform m_transform{};
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};

	public:

		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255,255,255,255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	};

	//-------------------------------
	// FPSComponent, renders the current FPS to the screen
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
