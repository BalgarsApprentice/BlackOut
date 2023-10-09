#include <Level.hpp>

using namespace Graphics;

Level::Level() = default;

void Level::levelSetup()
{
	auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
	groundTiles = TileMap{ groundtileSprites, numRows, numColumns };
}

Graphics::TileMap& Level::getTileMap()
{
    int k = 0;
    for (int i = 0; i < numColumns; ++i)
    {
        for (int j = 0; j < numRows; ++j)
        {
            groundTiles(i, j) = map[k++];
        }
    }

    return groundTiles;
}