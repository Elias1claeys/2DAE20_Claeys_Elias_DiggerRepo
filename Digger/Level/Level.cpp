#include "Level.h"
#include "LevelControls.h"
#include "Input/InputManager.h"
#include "Core/SceneManager.h"
#include <fstream>

#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Components/Text.h"
#include "Dig/DigComponent.h"
#include "Bag/Bag.h"
#include "Emerald/Emerald.h"
#include "Entities/Entity.h"
#include "Collider/Collider.h"
#include "Resources/ResourceManager.h"
#include "Observers/GameEvents.h"
#include "Core/DeltaTime.h"
#include "Score/Score.h"
#include "Collider/CollisionObserver.h"
#include "Observers/SoundObserver.h"
#include "Health/HealthDisplay.h"
#include "Health/HealthObserver.h"
#include "LevelObserver.h"
#include "Entities/PlayerMovement/PlayerInputComponent.h"

dae::Level::Level(GameObject* owner)
	: Component(owner), m_CurrentLevel(1)
{
	auto nextLevel = std::make_shared<dae::NextLevel>(this);
	InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_F1, nextLevel);

	m_pLevelScreen = std::make_unique<GameObject>();
	m_pLevelScreen->SetParent(GetOwner(), false);

	m_SoundObserver = std::make_unique<SoundObserver>();
	m_CollisionObserver = std::make_unique<Collision>();
	m_LevelObserver = std::make_unique<LevelObserver>(GetOwner());

	InitScoreAndHealth();
	CreateLevel();
}

void dae::Level::InitScoreAndHealth()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto scoreText = std::make_unique<GameObject>();
	scoreText->AddComponent<Text>("0", font);
	scoreText->GetComponent<Transform>()->SetLocalPosition(10, 10);
	scoreText->SetParent(GetOwner(), false);

	auto health = std::make_unique<GameObject>();
	health->AddComponent<HealthDisplay>();
	health->GetComponent<Transform>()->SetLocalPosition(125, 10);
	health->SetParent(GetOwner(), false);

	m_ScoreObserver = std::make_unique<Score>(scoreText.get());
	m_HealthObserver = std::make_unique<HealthObserver>(health.get());

	m_pGameObjects.push_back(std::move(scoreText));
	m_pGameObjects.push_back(std::move(health));
}

void dae::Level::CreateLevel()
{
	InitBackGround();
	InitDigGround();
	ReadLevelData();
}

void dae::Level::InitBackGround()
{
	auto background = std::make_unique<GameObject>();

	std::string levelBack = "media/levels/" + std::to_string(m_CurrentLevel) + "/Back.png";
	
	for (float x = 0; x <= 15; x++)
	{
		for (float y = 0; y <= 10; y++)
		{
			auto backGroundTile = std::make_unique<GameObject>();
			backGroundTile->AddComponent<Texture>()->SetTexture(levelBack);;
			backGroundTile->GetComponent<Transform>()->SetLocalPosition(x * m_TileSize, m_TileSize + y * m_TileSize);
			backGroundTile->SetParent(background.get(), false);
			m_pLevelObjects.push_back(std::move(backGroundTile));
		}
	}
	
	background->SetParent(m_pLevelScreen.get(), false);
	m_pLevelObjects.push_back(std::move(background));
}

void dae::Level::InitDigGround()
{
	auto digGround = std::make_unique<GameObject>();
	digGround->AddComponent<DigComponent>();
	digGround->SetParent(m_pLevelScreen.get(), false);
	m_pLevelObjects.push_back(std::move(digGround));
}

void dae::Level::ReadLevelData()
{
	std::string line;
	std::string levelData = "./Data/media/levels/" + std::to_string(m_CurrentLevel) + "/Data.txt";
	std::ifstream file{ levelData };

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			m_LevelData.push_back(line);
		}
	}
}

void dae::Level::Update()
{
	m_Time += Time::GetInstance().GetDeltaTime();
	if (!m_LevelReadyForStart && m_Time > 0.1f)
	{
		m_Time = 0.f;
		if (!CreateStarterPath()) return;
		InitPlayersData();
		InitEmeralds();
		InitBags();

		for (auto & player: m_pPlayers)
		{
			player->SetParent(m_pLevelScreen.get(), false);
			m_pLevelObjects.push_back(std::move(player));
		}

		m_LevelReadyForStart = true;
	}

	if (m_LevelCompleted)
	{
		m_LevelCompleted = false;
		NextLevel();
	}
}

bool dae::Level::IsHorizontal(char c)
{
	return c == 'H' || c == 'L' || c == 'S';
}

bool dae::Level::IsVertical(char c)
{
	return c == 'V' || c == 'L' || c == 'S';
}

bool dae::Level::CreateStarterPath()
{
	auto checkCount = m_NextCheck.size();
	for (int i = 0; i < checkCount; i++)
	{
		for (auto dir: m_Directions)
		{
			auto currentCheck = m_NextCheck[0] + dir;

			if (currentCheck.x < 0 || currentCheck.x >= 15 || currentCheck.y < 0 || currentCheck.y >= 10 
				|| std::find(m_AlreadyChecked.begin(), m_AlreadyChecked.end(), currentCheck) != m_AlreadyChecked.end())
				continue;
			
			char tile = m_LevelData[(int)currentCheck.y][(int)currentCheck.x];
			int index = (int)currentCheck.y * 15 + (int)currentCheck.x;

			bool up = (currentCheck.y > 0) && IsVertical(m_LevelData[(int)currentCheck.y - 1][(int)currentCheck.x]);
			bool down = (currentCheck.y < 10 - 1) && IsVertical(m_LevelData[(int)currentCheck.y + 1][(int)currentCheck.x]);
			bool left = (currentCheck.x > 0) && IsHorizontal(m_LevelData[(int)currentCheck.y][(int)currentCheck.x - 1]);
			bool right = (currentCheck.x < 15 - 1) && IsHorizontal(m_LevelData[(int)currentCheck.y][(int)currentCheck.x + 1]);
			int rotation = 0;

			switch (tile)
			{
			case 'S':
			case 'V':
				rotation = 0;
				break;
			case 'H':
				rotation = 1;
				break;
			case 'L':
				if (right && down)        rotation = 1;
				else if (down && left)    rotation = 2;
				else if (left && up)      rotation = 3;
				break;
			case 'T':
				if (up && right && down)        rotation = 1;
				else if (right && down && left)  rotation = 2;
				else if (down && left && up)  rotation = 3;
				break;
			default:
				continue;
				break;
			}

			dae::DigLocator::GetDig().FillDigShape(index, tile, rotation);
			m_NextCheck.push_back(currentCheck);

		}

		if (i < m_NextCheck.size())
		{
			m_AlreadyChecked.push_back(m_NextCheck[i]);
			m_NextCheck.erase(m_NextCheck.begin());
		}
	}

	return m_NextCheck.empty();
}

void dae::Level::InitPlayersData()
{
	auto player = std::make_unique<GameObject>();
	player->AddComponent<Entity>(100.f);
	player->AddComponent<PlayerInputComponent>(PlayerInputComponent::InputType::keyBoard);
	player->GetComponent<Transform>()->SetLocalPosition(glm::vec3{ 40, 104, 0 });
	m_pPlayers.push_back(std::move(player));
}

void dae::Level::InitEmeralds()
{
	float Startx = m_TileSize / 2;
	float Starty = m_TileSize + Startx;

	auto playerSize = m_pPlayers[0]->GetComponent<Texture>()->GetSize();
	playerSize.x /= 1.5;
	playerSize.y /= 1.5;

	glm::vec3 playerOffset;
	playerOffset.x = (m_pPlayers[0]->GetComponent<Texture>()->GetSize().x - playerSize.x) / 2;
	playerOffset.y = (m_pPlayers[0]->GetComponent<Texture>()->GetSize().y - playerSize.y) / 2;

	for (int y = 0; y < m_LevelData.size(); y++)
	{
		for (int x = 0; x < m_LevelData[y].size(); x++)
		{
			if (m_LevelData[y][x] == 'C')
			{
				auto emerald = std::make_unique<GameObject>();
				emerald->AddComponent<Emerald>();
				emerald->GetComponent<Transform>()->SetLocalPosition(Startx + x * m_TileSize, Starty + y * m_TileSize);

				Event emeraldEvent{ EMERALD_COLLECTED };
				emeraldEvent.nbArgs = 1;
				emeraldEvent.args[0].go = emerald.get();

				glm::vec2 size = emerald->GetComponent<dae::Texture>()->GetSize();
				size.x /= 2;
				size.y /= 2;
				
				glm::vec3 offset = { size.x / 2, size.y / 2, 0 };

				emerald->AddComponent<Collider>(offset, size);
				emerald->GetComponent<Collider>()->AddObserver(m_ScoreObserver.get());
				emerald->GetComponent<Collider>()->AddObserver(m_SoundObserver.get());
				emerald->GetComponent<Collider>()->AddObserver(m_LevelObserver.get());
				
				for(auto& player: m_pPlayers)
				{
					emerald->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ player.get(), emeraldEvent, playerSize, playerOffset});
				}

				Event emeraldSpawned{ EMERALD_SPAWNED };
				m_LevelObserver->OnNotify(GetOwner(), emeraldSpawned);

				emerald->SetParent(m_pLevelScreen.get(), false);
				m_pLevelObjects.push_back(std::move(emerald));
			}
		}
	}
}

void dae::Level::InitBags()
{
	float Startx = m_TileSize / 2;
	float Starty = m_TileSize + Startx;

	auto playerSize = m_pPlayers[0]->GetComponent<Texture>()->GetSize();
	playerSize.x /= 1.5;
	playerSize.y /= 1.5;

	glm::vec3 playerOffset;
	playerOffset.x = (m_pPlayers[0]->GetComponent<Texture>()->GetSize().x - playerSize.x) / 2;
	playerOffset.y = (m_pPlayers[0]->GetComponent<Texture>()->GetSize().y - playerSize.y) / 2;

	for (int y = 0; y < m_LevelData.size(); y++)
	{
		for (int x = 0; x < m_LevelData[y].size(); x++)
		{
			if (m_LevelData[y][x] == 'B')
			{
				auto bag = std::make_unique<GameObject>();
				bag->AddComponent<Bag>();
				bag->GetComponent<Transform>()->SetLocalPosition(Startx + x * m_TileSize, Starty + y * m_TileSize);

				glm::vec2 size = bag->GetComponent<Texture>()->GetSize();
				size.x /= 1.5;
				size.y /= 1.5;

				glm::vec3 offset;
				offset.x = (bag->GetComponent<Texture>()->GetSize().x - size.x) / 2;
				offset.y = (bag->GetComponent<Texture>()->GetSize().y - size.y) / 2;

				bag->AddComponent<Collider>(offset, size);
				bag->GetComponent<Collider>()->AddObserver(m_CollisionObserver.get());

				for (auto& player : m_pPlayers)
				{
					Event bagEvent{ BAG_COLLISION };
					bagEvent.nbArgs = 1;
					bagEvent.args[0].go = player.get();

					bag->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ player.get(), bagEvent, playerSize, playerOffset, true });
				}

				bag->SetParent(m_pLevelScreen.get(), false);
				m_pLevelObjects.push_back(std::move(bag));
			}
		}
	}
}

void dae::Level::NextLevel()
{
	//Reset everything
	m_pLevelScreen->RemoveAllChilderen();
	m_pPlayers.clear();
	m_pLevelObjects.clear();
	m_LevelData.clear();
	m_NextCheck.clear();
	m_AlreadyChecked.clear();
	m_NextCheck.push_back({ 0, -1 });
	dae::DigLocator::GetDig().ResetDig();

	Event e{ LEVEL_COMPLETED };
	m_LevelObserver->OnNotify(GetOwner(), e);

	//Reset the controls every time
	InputManager::GetInstance().ResetCommands();
	auto nextLevel = std::make_shared<dae::NextLevel>(this);
	InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_F1, nextLevel);

	m_LevelReadyForStart = false;

	if (m_CurrentLevel == 8)
	{
		m_CurrentLevel = 1;
	}
	else
	{
		m_CurrentLevel++;
	}

	CreateLevel();
}