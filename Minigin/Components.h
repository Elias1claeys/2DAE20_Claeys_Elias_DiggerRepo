#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "Subject.h"


namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class Scene; 

	//-------------------------------
	// Base Component class
	//-------------------------------

	class Component
	{
	private:
		GameObject* m_pOwner{};
		bool m_markedForDelete{ false };

	public:

		const virtual void Render() {}
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
		//TextureRedering
		std::shared_ptr<Texture2D> m_texture{};
		float m_rotationAngle{ 0.f };
		glm::vec2 m_size{ 0, 0 };

	public:
		const void Render() override;
		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);
		void SetRotation(float angle){m_rotationAngle = angle;}
		void SetSize(const glm::vec2& size) { m_size = size; }
		glm::vec2 GetSize();

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

	//------------------------------------
	//	Player Component
	//------------------------------------

	class PlayerComponent : public Component, public Subject
	{
	private:
		float m_Speed{};
		glm::vec3 m_MoveDirection{};
		TransformComponent* m_Transform{};

	public:
		enum InputType
		{
			keyBoard,
			controller
		};

		void DoDamage();

		glm::vec3 GetDirection() { return m_MoveDirection; };
		void SetDirection(glm::vec3 direction);

		void Update() override;

        PlayerComponent(GameObject* owner, InputType input, float speed);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		};

	//------------------------------------
	//	Level Component
	//------------------------------------

	class LevelComponent : public Component
	{
	private:
		std::vector<GameObject*> m_LevelObjects;
		Scene* m_LevelScene{};
		int m_CurrentLevel{ 1 };

		bool IsHorizontal(char c);
		bool IsVertical(char c);
	
	public:

		void CreateLevel(int level);
		void NextLevel();

		LevelComponent(GameObject* owner);
		virtual ~LevelComponent() = default;
		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;
	};

	//------------------------------------
	//	Emerald Component
	//------------------------------------

	class EmeraldComponent : public Component
	{
	private:
		bool m_IsCollected{ false };

	public:
		
		EmeraldComponent(GameObject* owner);
		virtual ~EmeraldComponent() = default;
		EmeraldComponent(const EmeraldComponent& other) = delete;
		EmeraldComponent(EmeraldComponent&& other) = delete;
		EmeraldComponent& operator=(const EmeraldComponent& other) = delete;
		EmeraldComponent& operator=(EmeraldComponent&& other) = delete;
	};

	//------------------------------------
	//	Bag Component
	//------------------------------------

	class BagComponent : public Component
	{
	public:

		BagComponent(GameObject* owner);
		virtual ~BagComponent() = default;
		BagComponent(const BagComponent& other) = delete;
		BagComponent(BagComponent&& other) = delete;
		BagComponent& operator=(const BagComponent& other) = delete;
		BagComponent& operator=(BagComponent&& other) = delete;
	};

	//-------------------------------
	//	Hole Component
	//-------------------------------

	class HoleComponent : public Component
	{
	private:

		struct Tile
		{
			int StartTilex;
			int StartTiley;
			bool DigCells[8][8];
		};

		Tile m_DigGrid[150];
		int m_tileSize;

		bool StartPattern[8][8] =
		{
			{0,0,1,1,1,1,0,0},
			{0,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,0},
			{0,0,1,1,1,1,0,0}
		};

		bool TunnlePattern[8][8] =
		{
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0}
		};

		bool LShapePattern[8][8] =
		{
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1},
			{0,0,1,1,1,1,1,1},
			{0,0,1,1,1,1,1,1},
			{0,0,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0}
		};

		bool TShapePattern[8][8] =
		{
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0}
		};

		void DrawAllDigTiles();
		void FillAllDigTiles();
		void RotateShape(bool pattern[8][8], int rotationTimes);

	public:

		const void Render() override;
		void FillDigShape(int tileId, char shape, int rotationTimes);
		void DigTile(glm::vec3 playerPos, glm::vec2 playerSize);

		HoleComponent(GameObject* owner, int tileSize);
		virtual ~HoleComponent() = default;
		HoleComponent(const HoleComponent& other) = delete;
		HoleComponent(HoleComponent&& other) = delete;
		HoleComponent& operator=(const HoleComponent& other) = delete;
		HoleComponent& operator=(HoleComponent&& other) = delete;
	};

	//-------------------------------
	//  Collision Component
	//-------------------------------

	class CollisionComponent : public Component
	{
	public:

		CollisionComponent(GameObject* owner);
		virtual ~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;
	};
}