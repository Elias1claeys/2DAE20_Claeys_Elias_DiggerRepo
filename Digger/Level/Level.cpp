#include "Level.h"
#include "LevelControls.h"
#include "Input/InputManager.h"
#include "Core/SceneManager.h"
#include <fstream>

#include "Components/RenderTexture.h"
#include "Components/Transform.h"
#include "Hole/Hole.h"
#include "Bag/Bag.h"
#include "Emerald/Emerald.h"
#include "Player/Player.h"
#include "Observers/Digged.h"

dae::Level::Level(GameObject* owner)
	: Component(owner)
{
	auto nextLevel = std::make_shared<dae::NextLevel>(this);
	InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_F1, nextLevel);

	m_LevelScene = &dae::SceneManager::GetInstance().CreateScene();
	CreateLevel(m_CurrentLevel);
}

bool dae::Level::IsHorizontal(char c)
{
	return c == 'H' || c == 'L' || c == 'S';
}

bool dae::Level::IsVertical(char c)
{
	return c == 'V' || c == 'L' || c == 'S';
}

void dae::Level::CreateLevel(int level)
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

			BackGround->AddComponent<RenderTexture>()->SetTexture(levelBack);;
			BackGround->GetComponent<Transform>()->SetLocalPosition(x * tileSize, tileSize + y * tileSize);

			m_LevelScene->Add(std::move(BackGround));
		}
	}

	auto digGround = std::make_unique<GameObject>();
	digGround->AddComponent<dae::Hole>(64);

	std::vector<std::unique_ptr<GameObject>> levelObjects;

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

				if (lines[y][x] == ' ')
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
					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'S', 0);
					break;

				case 'B':
					obj->AddComponent<dae::Bag>();
					obj->GetComponent<dae::Transform>()->SetLocalPosition(Startx + x * tileSize, Starty + y * tileSize);
					levelObjects.push_back(std::move(obj));
					break;

				case 'H':
					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'H', 1);
					break;

				case 'V':
					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'V', 0);
					break;

				case'L':
					if (right && down)        rotation = 1;
					else if (down && left)    rotation = 2;
					else if (left && up)      rotation = 3;

					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'L', rotation);

					break;

				case 'T':
					if (up && left && down)        rotation = 1;
					else if (right && up && left)  rotation = 2;
					else if (down && right && up)  rotation = 3;

					digGround->GetComponent<dae::Hole>()->FillDigShape(index, 'T', rotation);
					break;

				case 'C':
					obj->AddComponent<dae::Emerald>();
					obj->GetComponent<dae::Transform>()->SetLocalPosition(Startx + x * tileSize, Starty + y * tileSize);
					levelObjects.push_back(std::move(obj));
					break;
				}
			}
		}
	}


	std::unique_ptr<DigObserver> digObserver = std::make_unique<DigObserver>(digGround.get());
	auto player = std::make_unique<GameObject>();
	player->AddComponent<Player>(Player::InputType::keyBoard, 100.f);
	player->GetComponent<Transform>()->SetLocalPosition(glm::vec3{ 48, 112, 0 });
	player->GetComponent<Player>()->AddObserver(std::move(digObserver));

	m_LevelScene->Add(std::move(digGround));

	for (auto& obj : levelObjects)
	{
		m_LevelScene->Add(std::move(obj));
	}

	m_LevelScene->Add(std::move(player));
}

void dae::Level::NextLevel()
{
	m_LevelScene->RemoveAll();

	if (m_CurrentLevel == 8)
		m_CurrentLevel = 1;
	else
		m_CurrentLevel++;

	GetOwner()->RemoveComponent<Hole>();
	CreateLevel(m_CurrentLevel);
}