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
#include "Player/Player.h"
#include "Collider/Collider.h"
#include "Observers/Score.h"
#include "Resources/ResourceManager.h"
#include "Observers/GameEvents.h"
#include "Observers/SoundObserver.h"
#include "Core/DeltaTime.h"

dae::Level::Level(GameObject* owner)
	: Component(owner), m_CurrentLevel(1)
{
	auto nextLevel = std::make_shared<dae::NextLevel>(this);
	InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_F1, nextLevel);

	auto gameScreen = std::make_unique<GameObject>();
	m_pGameScreen = gameScreen.release();
	m_pGameScreen->SetParent(GetOwner(), false);

	CreateLevel();
}

void dae::Level::CreateLevel()
{
	InitBackGround();
	InitDigGround();
	ReadLevelData();
	
	//auto digGround = std::make_unique<GameObject>();
	//digGround->AddComponent<dae::Hole>(64);
	//
	//std::vector<std::unique_ptr<GameObject>> emeralds;
	//std::vector<std::unique_ptr<GameObject>> bags;
	//
	////Adding the player(s)
	//auto player = std::make_unique<GameObject>();
	//player->AddComponent<Player>(Player::InputType::keyBoard, 100.f);
	//player->GetComponent<Transform>()->SetLocalPosition(glm::vec3{ 40, 104, 0 });
	//
	//std::unique_ptr<Collision> collisionObserver = std::make_unique<Collision>(digGround->GetComponent<Hole>(), player->GetComponent<Player>());
	//player->GetComponent<Player>()->AddObserver(collisionObserver.get());
	//
	////Adding the score text
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto scoreText = std::make_unique<GameObject>();
	//scoreText->AddComponent<Text>("0", font);
	//scoreText->GetComponent<Transform>()->SetLocalPosition(10, 10);
	//
	//
	//std::unique_ptr<Score> scoreObserver = std::make_unique<Score>(scoreText.get());
	//std::unique_ptr<SoundObserver> soundObserver = std::make_unique<SoundObserver>();
	//
	//auto playerSize = player->GetComponent<Texture>()->GetSize();
	//playerSize.x /= 1.5;
	//playerSize.y /= 1.5;
	//
	//glm::vec3 playerOffset;
	//playerOffset.x = (player->GetComponent<Texture>()->GetSize().x - playerSize.x) / 2;
	//playerOffset.y = (player->GetComponent<Texture>()->GetSize().y - playerSize.y) / 2;
	//
	//// Load level file
	//if (file.is_open())
	//{
	//	int index = -1;
	//	int Startx = 32;
	//	int Starty = 96;
	//
	//	while (std::getline(file, line))
	//	{
	//		lines.push_back(line);
	//	}
	//
	//	for (int y = 0; y < lines.size(); y++)
	//	{
	//		for (int x = 0; x < lines[y].size(); x++)
	//		{
	//			index++;
	//
	//			if (lines[y][x] == ' ')
	//				continue;
	//
	//			auto obj = std::make_unique<GameObject>();
	//
	//			bool up = (y > 0) && IsVertical(lines[y - 1][x]);
	//			bool down = (y < lines.size() - 1) && IsVertical(lines[y + 1][x]);
	//			bool left = (x > 0) && IsHorizontal(lines[y][x - 1]);
	//			bool right = (x < lines[y].size() - 1) && IsHorizontal(lines[y][x + 1]);
	//			int rotation = 0;
	//
	//			switch (lines[y][x])
	//			{
	//				case 'S':
	//				{
	//					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'S', 0);
	//					break;
	//				}
	//				case 'B':
	//				{
	//					obj->AddComponent<dae::Bag>(digGround->GetComponent<Hole>());
	//					obj->GetComponent<dae::Transform>()->SetLocalPosition(Startx + x * m_TileSize, Starty + y * m_TileSize);
	//
	//					auto size = obj->GetComponent<dae::Texture>()->GetSize();
	//					size.x /= 1.5;
	//					size.y /= 1.5;
	//
	//					glm::vec3 offset;
	//					offset.x = (obj->GetComponent<Texture>()->GetSize().x - size.x) / 2;
	//					offset.y = (obj->GetComponent<Texture>()->GetSize().y - size.y) / 2;
	//
	//					Event bagEvent{ BAG_COLLISION };
	//					bagEvent.nbArgs = 1;
	//					bagEvent.args[0].go = obj.get();
	//
	//					obj->AddComponent<Collider>(offset, size);
	//					obj->GetComponent<Collider>()->AddObserver(collisionObserver.get());
	//					obj->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ player.get(), bagEvent, playerSize, playerOffset, true });
	//
	//					bags.push_back(std::move(obj));
	//					break;
	//				}
	//
	//				case 'H':
	//				{
	//					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'H', 1);
	//					break;
	//				}
	//				case 'V':
	//				{
	//					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'V', 0);
	//					break;
	//				}
	//				case'L':
	//				{
	//					if (right && down)        rotation = 1;
	//					else if (down && left)    rotation = 2;
	//					else if (left && up)      rotation = 3;
	//
	//					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'L', rotation);
	//
	//					break;
	//				}
	//				case 'T':
	//				{
	//					if (up && left && down)        rotation = 1;
	//					else if (right && up && left)  rotation = 2;
	//					else if (down && right && up)  rotation = 3;
	//
	//					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'T', rotation);
	//					break;
	//				}
	//				case 'C':
	//				{
	//					obj->AddComponent<dae::Emerald>();
	//					obj->GetComponent<dae::Transform>()->SetLocalPosition(Startx + x * m_TileSize, Starty + y * m_TileSize);
	//
	//					Event emeraldEvent{ EMERALD_COLLECTED };
	//					emeraldEvent.nbArgs = 1;
	//					emeraldEvent.args[0].go = obj.get();
	//
	//					glm::vec2 size = obj->GetComponent<dae::Texture>()->GetSize();
	//					size.x /= 2;
	//					size.y /= 2;
	//
	//					glm::vec3 offset = { size.x / 2, size.y / 2, 0 };
	//
	//					obj->AddComponent<Collider>(offset, size);
	//					obj->GetComponent<Collider>()->AddObserver(scoreObserver.get());
	//					obj->GetComponent<Collider>()->AddObserver(soundObserver.get());
	//					obj->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ player.get(), emeraldEvent, playerSize, playerOffset});
	//
	//					emeralds.push_back(std::move(obj));
	//					break;
	//				}	
	//			}
	//		}
	//	}
	//}
	//
	//m_LevelScene->Add(std::move(digGround));
	//
	//for (auto& emerald : emeralds)
	//{
	//	m_LevelScene->Add(std::move(emerald));
	//}
	//for (auto& bag : bags)
	//{
	//	m_LevelScene->Add(std::move(bag));
	//}
	//
	//m_Observers.push_back(std::move(scoreObserver));
	//m_Observers.push_back(std::move(soundObserver));
	//m_Observers.push_back(std::move(collisionObserver));
	//
	//m_LevelScene->Add(std::move(player));
	//m_LevelScene->Add(std::move(scoreText));
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
			backGroundTile.release()->SetParent(background.get(), false);
		}
	}
	
	background.release()->SetParent(m_pGameScreen, false);
}

void dae::Level::InitDigGround()
{
	auto digGround = std::make_unique<GameObject>();
	digGround->AddComponent<DigComponent>();
	digGround.release()->SetParent(m_pGameScreen, false);
}

void dae::Level::InitPlayersData()
{
	auto player = std::make_unique<GameObject>();
	player->AddComponent<Player>(Player::InputType::keyBoard, 100.f);
	player->GetComponent<Transform>()->SetLocalPosition(glm::vec3{ 40, 104, 0 });
	player.release()->SetParent(m_pGameScreen, false);
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
		m_LevelReadyForStart = true;
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

void dae::Level::NextLevel()
{
	//m_LevelScene->RemoveAll();
	//
	//if (m_CurrentLevel == 8)
	//	m_CurrentLevel = 1;
	//else
	//	m_CurrentLevel++;
	//
	//GetOwner()->RemoveComponent<Hole>();
	//CreateLevel(m_CurrentLevel);
}