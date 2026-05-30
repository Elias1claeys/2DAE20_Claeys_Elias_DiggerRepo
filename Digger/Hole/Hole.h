#include "Core/GameObject.h"
#include <array>
#include <glm/glm.hpp>

namespace dae
{
	class Hole : public Component
	{
	private:

		//for testing in the grid
		std::vector<SDL_FRect> m_DebugRects;

		struct Tile
		{
			int StartTilex;
			int StartTiley;
			std::array<std::array<bool, 8>, 8> DigCells;
		};

		Tile m_DigGrid[150];
		int m_tileSize;

		std::array<std::array<bool, 8>, 8> StartPattern
		{ {
			{0,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,0}
		} };

		std::array<std::array<bool, 8>, 8> TunnlePattern
		{ {
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0}
		} };

		std::array<std::array<bool, 8>, 8> LShapePattern =
		{ {
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0}
		} };

		std::array<std::array<bool, 8>, 8> TShapePattern =
		{ {
			{0,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0}
		} };

		void DrawAllDigTiles();
		void FillAllDigTiles();
		void RotateShape(std::array<std::array<bool, 8>, 8>& pattern, int rotationTimes);

	public:

		const void Render() override;
		void FillDigShape(int tileId, char shape, int rotationTimes);
		void DigTile(glm::vec3 playerPos, glm::vec2 playerSize);
		bool BagDiggedOut(glm::vec3 bagPos, glm::vec2 bagSize);

		Hole(GameObject* owner, int tileSize);
		virtual ~Hole() = default;
		Hole(const Hole& other) = delete;
		Hole(Hole&& other) = delete;
		Hole& operator=(const Hole& other) = delete;
		Hole& operator=(Hole&& other) = delete;
	};
}