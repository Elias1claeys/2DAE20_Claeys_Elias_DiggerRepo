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
		bool m_markedForDelete{ false };

	public:

		virtual void Update() {}
		void MarkForDelete() { m_markedForDelete = true; }
		bool IsMarkedForDelete() const { return m_markedForDelete; }

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		
	protected:
		explicit Component(GameObject* owner) : m_pOwner(owner) {}
		GameObject* GetOwner() const { return m_pOwner; }
	};

	//-------------------------------
	// Transform Component
	//-------------------------------

	class TransformComponent : public Component
	{
	private:
		glm::vec3 m_LocalPosition{ 0, 0, 0 };
		glm::vec3 m_WorldPosition{ 0, 0, 0 };
		bool m_PositionIsDirty{ false };

		void UpdateWorldPosition();

	public:
		void SetPositionDirty();
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition();
		

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
		std::shared_ptr<Texture2D> m_texture{};

	public:
		void Render() const;
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

	//-------------------------------
	// Rotator Component
	//-------------------------------

	class RotatorComponent : public Component
	{
	private:
		float m_RotationSpeed;
		float m_CurrentAngle{ 0.f };
		float m_RotationDirection{ 1.f };
		bool m_RotateAroundParent{ false };
		glm::vec3 m_RotationPoint{ 0, 0, 0 };

	public:
		void Update() override;
		void SetRotationPoint(float x, float y, float z = 0);
		void SetRotationPoint(const glm::vec3& rotation);
		void SetRotationDirection(bool clockwise);
		

		RotatorComponent(GameObject* owner, float rotationSpeed, bool rotateAroundParent);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	};
}
