#include "Components.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "DeltaTime.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Scene.h"

#include <filesystem>
#include <fstream>




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

const void dae::RenderComponent::Render() 
{
	if (m_texture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<TransformComponent>()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_size.x, m_size.y, m_rotationAngle);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_size = m_texture->GetSize();
}

void dae::RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_texture = std::make_shared<Texture2D>(texture);
	m_size = m_texture->GetSize();
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

dae::RotatorComponent::RotatorComponent(GameObject* owner, float rotationSpeed)
	: Component(owner)
	, m_RotationSpeed(rotationSpeed)
{
	if (!owner->HasComponent<TransformComponent>())
	{
		owner->AddComponent<TransformComponent>();
	}

	m_RotationCenter = GetOwner()->GetComponent<TransformComponent>()->GetWorldPosition();
}

void dae::RotatorComponent::Update()
{	
	auto transform = GetOwner()->GetComponent<TransformComponent>();

	m_CurrentAngle += m_RotationSpeed * Time::GetInstance().GetDeltaTime();

	transform->SetLocalPosition(
		m_RotationCenter.x + std::cos(m_CurrentAngle) * 50.f,
		m_RotationCenter.y + std::sin(m_CurrentAngle) * 50.f,
		m_RotationCenter.z
	);
}

//------------------------------------
//	Actor Component
//------------------------------------

dae::PlayerComponent::PlayerComponent(GameObject* Owner, InputType input, float speed)
	:Component(Owner),
	m_Speed(speed)
{
	if (!GetOwner()->HasComponent<RenderComponent>())
	{
		GetOwner()->AddComponent<RenderComponent>();
		GetOwner()->GetComponent<RenderComponent>()->SetTexture("media/Digger/dig1.png");
		GetOwner()->GetComponent<RenderComponent>()->SetSize({ 32, 32 });
	}

	m_Transform = GetOwner()->GetComponent<TransformComponent>();

	auto moveUp = std::make_shared<dae::Move>(this, glm::vec3{0, -1, 0});
	auto moveDown = std::make_shared<dae::Move>(this, glm::vec3{0, 1, 0});
	auto moveLeft = std::make_shared<dae::Move>(this, glm::vec3{-1, 0, 0});
	auto moveRight = std::make_shared<dae::Move>(this, glm::vec3{1, 0, 0});
	auto attack = std::make_shared<dae::Attack>(this);

	if (input == InputType::keyBoard)
	{
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_W, moveUp);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_A, moveLeft);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_S, moveDown);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_D, moveRight);
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_SPACE, attack);
	}
	else
	{
		InputManager::GetInstance().BindControllerCommand(0x0002, moveDown);
		InputManager::GetInstance().BindControllerCommand(0x0008, moveRight);
		InputManager::GetInstance().BindControllerCommand(0x0004, moveLeft);
		InputManager::GetInstance().BindControllerCommand(0x0010, moveUp);
		InputManager::GetInstance().BindControllerCommand(0x4000, attack);
	}
}

void dae::PlayerComponent::Update()
{
	glm::vec3 pos = m_Transform->GetWorldPosition();

	pos.x += m_MoveDirection.x * m_Speed * Time::GetInstance().GetDeltaTime();
	pos.y += m_MoveDirection.y * m_Speed * Time::GetInstance().GetDeltaTime();

	m_Transform->SetLocalPosition(pos);
}

void dae::PlayerComponent::SetDirection(glm::vec3 dir)
{
	m_MoveDirection = dir;
}

void dae::PlayerComponent::DoDamage()
{
	EventId PLAYER_SCORED = make_sdbm_hash("PlayerScored");

	Notify(Event{ PLAYER_SCORED }, GetOwner());
}

//-------------------------------
// Level component
//-------------------------------

dae::LevelComponent::LevelComponent(GameObject* owner)
	: Component(owner)
{
	auto nextLevel = std::make_shared<dae::NextLevel>(this);
	InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_F1, nextLevel);

	m_LevelScene = &dae::SceneManager::GetInstance().CreateScene();
	CreateLevel(m_CurrentLevel);
}

bool dae::LevelComponent::IsHorizontal(char c)
{
	return c == 'H' || c == 'L' || c == 'S';
}

bool dae::LevelComponent::IsVertical(char c)
{
	return c == 'V' || c == 'L' || c == 'S';
}

void dae::LevelComponent::CreateLevel(int level)
{
	std::string line;
	std::string levelData = "./Data/media/levels/" + std::to_string(level) + "/Data.txt";
	std::string levelBack = "media/levels/" + std::to_string(level) + "/Back.png";
	std::ifstream file{ levelData };
	std::vector<std::string> lines;

	float tileSize = 64;

	// Background tiles
	for (float x = 0; x <= 15; x++)
	{
		for (float y = 0; y <= 10; y++)
		{
			auto BackGround = std::make_unique<GameObject>();

			BackGround->AddComponent<RenderComponent>()->SetTexture(levelBack);;
			BackGround->GetComponent<TransformComponent>()->SetLocalPosition(x * tileSize, tileSize + y * tileSize);

			m_LevelScene->Add(std::move(BackGround));
		}
	}

	auto digGround = std::make_unique<GameObject>();
	digGround->AddComponent<dae::HoleComponent>(64);
	
	// Load level file
	if (file.is_open())
	{
		int index = -1;
		int Startx = 32;
		int Starty = 96;

		while (std::getline(file, line))
		{
			lines.push_back(line);
		}

		for (int y = 0; y < lines.size(); y++)
		{
			for (int x = 0; x < lines[y].size(); x++)
			{
				index++;

				if(lines[y][x] == ' ')
					continue;

				auto obj = std::make_unique<GameObject>();

				bool up = (y > 0) && IsVertical(lines[y - 1][x]);
				bool down = (y < lines.size() - 1) && IsVertical(lines[y + 1][x]);
				bool left = (x > 0) && IsHorizontal(lines[y][x - 1]);
				bool right = (x < lines[y].size() - 1) && IsHorizontal(lines[y][x + 1]);
				int rotation = 0;

				switch (lines[y][x])
				{
				case 'S':
					digGround->GetComponent<dae::HoleComponent>()->FillDigShape(index, 'S', 0);
					break;

				case 'B':
					obj->AddComponent<dae::BagComponent>();
					obj->GetComponent<dae::TransformComponent>()->SetLocalPosition(Startx + x * tileSize, Starty + y * tileSize);
					m_LevelScene->Add(std::move(obj));
					break;

				case 'H':
					digGround->GetComponent<dae::HoleComponent>()->FillDigShape(index, 'H', 1);
					break;

				case 'V':
					digGround->GetComponent<dae::HoleComponent>()->FillDigShape(index, 'V', 0);
					break;

				case'L':
					if (right && down)        rotation = 1;
					else if (down && left)    rotation = 2;
					else if (left && up)      rotation = 3;
					
					digGround->GetComponent<dae::HoleComponent>()->FillDigShape(index, 'L', rotation);
					
					break;

				case 'T':
					if (up && left && down)        rotation = 1;
					else if (right && up && left)  rotation = 2;
					else if (down && right && up)  rotation = 3;
					
					digGround->GetComponent<dae::HoleComponent>()->FillDigShape(index, 'T', rotation);
					break;

				case 'C':
					obj->AddComponent<dae::EmeraldComponent>();
					obj->GetComponent<dae::TransformComponent>()->SetLocalPosition(Startx + x * tileSize, Starty + y * tileSize);
					m_LevelScene->Add(std::move(obj));
					break;
				}
			}
		}

		m_LevelScene->Add(std::move(digGround));
	}

	auto player = std::make_unique<GameObject>();
	player->AddComponent<PlayerComponent>(PlayerComponent::InputType::keyBoard, 100.f);
	player->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 48, 112, 0 });
	m_LevelScene->Add(std::move(player));
}

void dae::LevelComponent::NextLevel()
{
	m_LevelScene->RemoveAll();

	if (m_CurrentLevel == 8)
		m_CurrentLevel = 1;
	else
		m_CurrentLevel++;

	GetOwner()->RemoveComponent<HoleComponent>();
	CreateLevel(m_CurrentLevel);
}

//------------------------------------
//	Hole Component
//------------------------------------

dae::HoleComponent::HoleComponent(GameObject* owner, int tileSize)
	: Component(owner), m_tileSize(tileSize), m_DigGrid()
{

	int index = 0;
	int nextLineStart = 0;

	for (auto& tile : m_DigGrid)
	{
		tile.StartTilex = tileSize * index;
		tile.StartTiley = tileSize * nextLineStart;

		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				tile.DigCells[y][x] = false;
			}
		}

		index++;

		if (index == 15)
		{
			index = 0;
			nextLineStart++;
		}
	}
}

const void dae::HoleComponent::Render()
{
	//DrawAllDigTiles();
	FillAllDigTiles();
}

void dae::HoleComponent::DrawAllDigTiles()
{
	int size = m_tileSize / 8;
	
	for (auto& tile : m_DigGrid)
	{
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				int posx = (m_tileSize / 2) + (tile.StartTilex + x * size);
				int posy = (m_tileSize + m_tileSize / 2) + (tile.StartTiley + y * size);
				
				SDL_FRect rect{};
				rect.x = (float)posx;
				rect.y = (float)posy;
				rect.w = (float)size;
				rect.h = (float)size;
	
				Renderer::GetInstance().DrawRect({ 0, 0, 0, 0 }, rect);
			}
		}
	}
}

void dae::HoleComponent::FillAllDigTiles()
{
	int size = m_tileSize / 8;

	for (auto& tile : m_DigGrid)
	{
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				if (!tile.DigCells[y][x])
					continue;

				int posx = (m_tileSize / 2) + (tile.StartTilex + x * size);
				int posy = (m_tileSize + m_tileSize / 2) + (tile.StartTiley + y * size);

				SDL_FRect rect{};
				rect.x = (float)posx;
				rect.y = (float)posy;
				rect.w = (float)size;
				rect.h = (float)size;

				Renderer::GetInstance().FillRect({ 0, 0, 0, 0 }, rect);
			}
		}
	}
}

void dae::HoleComponent::FillDigShape(int tileId, char shape, int rotation)
{
	bool pattern[8][8];

	switch (shape)
	{
	case 'S':
		memcpy(pattern, StartPattern, sizeof(pattern));
		break;
	case 'H':
	case 'V':
		memcpy(pattern, TunnlePattern, sizeof(pattern));
		break;
	case 'L':
		memcpy(pattern, LShapePattern, sizeof(pattern));
		break;
	case 'T':
		memcpy(pattern, TShapePattern, sizeof(pattern));
		break;
	}

	RotateShape(pattern, rotation);

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			m_DigGrid[tileId].DigCells[y][x] = pattern[y][x];
		}
	}
}

void dae::HoleComponent::RotateShape(bool pattern[8][8], int rotationTimes)
{
	for (int r = 0; r < rotationTimes; r++)
	{
		bool temp[8][8];

		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				temp[x][7 - y] = pattern[y][x];
			}
		}

		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				pattern[y][x] = temp[y][x];
			}
		}
	}
}

//------------------------------------
//	Emerald Component
//------------------------------------

dae::EmeraldComponent::EmeraldComponent(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<RenderComponent>()->SetTexture("media/Emerald/emerald.png");
}

//------------------------------------
//	Bag Component
//------------------------------------

dae::BagComponent::BagComponent(GameObject* owner)
	: Component(owner)
{
	GetOwner()->AddComponent<RenderComponent>()->SetTexture("media/Bag/bag.png");
}

