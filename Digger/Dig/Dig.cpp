#include "Dig.h"

dae::Dig::Dig(int tileSize)
	: m_tileSize(tileSize), m_DigGrid()
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

const void dae::Dig::Render()
{
	//DrawAllDigTiles();
	FillAllDigTiles();

	for (auto rect : m_DebugRects)
	{
		Renderer::GetInstance().DrawRect({ 0, 255, 0, 255 }, rect);
	}
}

void dae::Dig::DrawAllDigTiles()
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

void dae::Dig::FillAllDigTiles()
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

void dae::Dig::FillDigShape(int tileId, char shape, int rotation)
{
	std::array<std::array<bool, 8>, 8> pattern{};

	switch (shape)
	{
	case 'S':
		pattern = StartPattern;
		break;
	case 'H':
	case 'V':
		pattern = TunnlePattern;
		break;
	case 'L':
		pattern = LShapePattern;
		break;
	case 'T':
		pattern = TShapePattern;
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

void dae::Dig::RotateShape(std::array<std::array<bool, 8>, 8>& pattern, int rotationTimes)
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

void dae::Dig::DigTile(glm::vec3 playerPos, glm::vec2 playerSize)
{
	int cellSize = m_tileSize / 8;
	float offsetX = (float)m_tileSize / 2;
	float offsetY = (float)m_tileSize + (float)m_tileSize / 2;

	float left = playerPos.x - offsetX;
	float right = playerPos.x + playerSize.x - offsetX;
	float bottem = playerPos.y + playerSize.y - offsetY;
	float top = playerPos.y - offsetY;

	for (auto y = top; y < bottem; y += cellSize)
	{
		for (auto x = left; x < right; x += cellSize)
		{
			int tileX = int(x) / m_tileSize;
			int tileY = int(y) / m_tileSize;

			if (tileX < 0 || tileX >= 15 || tileY < 0 || tileY >= 10)
				continue;

			int tileId = tileY * 15 + tileX;

			int localX = int(x) % m_tileSize;
			int localY = int(y) % m_tileSize;

			int cellX = localX / cellSize;
			int cellY = localY / cellSize;

			m_DigGrid[tileId].DigCells[cellY][cellX] = true;
		}
	}
}

bool dae::Dig::BagDiggedOut(glm::vec3 bagPos, glm::vec2 bagSize, bool checkTop)
{
	float offsetX = (float)m_tileSize / 2;
	float offsetY = (float)m_tileSize + (float)m_tileSize / 2;
	int cellSize = m_tileSize / 8;

	float checkY;

	if (checkTop)
	{
		checkY = bagPos.y - bagSize.y;
	}
	else
	{
		checkY = (bagPos.y + bagSize.y + 1.f) - offsetY - cellSize;
	}

	float centerX = (bagPos.x + bagSize.x / 2.f) - offsetX;

	for (float x = centerX - (cellSize * 2); x < centerX + (cellSize * 2); x += cellSize)
	{
		int tileX = (int)x / m_tileSize;
		int tileY = (int)checkY / m_tileSize;

		if (tileX < 0 || tileX >= 15 || tileY < 0 || tileY >= 10)
			return false;

		int cellX = std::clamp(((int)x % m_tileSize) / cellSize, 0, 7);
		int cellY = std::clamp(((int)checkY % m_tileSize) / cellSize, 0, 7);

		int tileId = tileY * 15 + tileX;

		if (!m_DigGrid[tileId].DigCells[cellY][cellX])
			return false;
	}

	return true;
}

void dae::Dig::ResetDig()
{
	for (auto& tile : m_DigGrid)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				tile.DigCells[y][x] = false;
			}
		}
	}
}

bool dae::Dig::IsDugOut(glm::vec3 worldPos)
{
	float offsetX = m_tileSize / 2.f;
	float offsetY = m_tileSize + m_tileSize / 2.f;

	float wx = worldPos.x - offsetX;
	float wy = worldPos.y - offsetY;

	int tileX = (int)std::floor(wx / m_tileSize);
	int tileY = (int)std::floor(wy / m_tileSize);

	if (tileX < 0 || tileX >= 15 || tileY < 0 || tileY >= 10)
		return false;

	int cellX = std::clamp((int)((wx - tileX * m_tileSize) / (m_tileSize / 8.f)), 0, 7);
	int cellY = std::clamp((int)((wy - tileY * m_tileSize) / (m_tileSize / 8.f)), 0, 7);

	return m_DigGrid[tileY * 15 + tileX].DigCells[cellY][cellX];
}

