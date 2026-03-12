#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <InputManager.h>

//ImGui
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

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
		glm::vec3 m_RotationCenter{};

	public:
		void Update() override;

		RotatorComponent(GameObject* owner, float rotationSpeed);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	};

	//----------------------------------
	// Trash Cache Component
	//----------------------------------

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID = 1;
	};

	class TrashCacheComponent : public Component
	{
	private:
		int m_SampleCount;
		std::vector<std::pair<int, long>> m_TrashCacheInt;
		std::vector<std::pair<int, long>> m_TrashCacheGameobject3D;

		void TrashCacheInt(int size);
		void TrashCacheGameObject3D(int size);
		float GetTrashValue(void* data, int idx);

	public:
		void Render();

		TrashCacheComponent(GameObject* owner);
		virtual ~TrashCacheComponent() = default;
		TrashCacheComponent(const TrashCacheComponent& other) = delete;
		TrashCacheComponent(TrashCacheComponent&& other) = delete;
		TrashCacheComponent& operator=(const TrashCacheComponent& other) = delete;
		TrashCacheComponent& operator=(TrashCacheComponent&& other) = delete;
	};

	//------------------------------------
	//	Player Component
	//------------------------------------

	class PlayerComponent : public Component
	{
	private:
		float m_Speed{};
		glm::vec3 m_Direction{};
		TransformComponent* m_Transform{};

	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		glm::vec3 GetDirection() { return m_Direction; };
		void SetDirection(glm::vec3 direction);
		void Update();

        PlayerComponent(GameObject* owner, InputType input, float speed);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

	};
}