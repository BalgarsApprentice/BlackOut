#include <Level.hpp>

using namespace Graphics;

Level::Level() = default;

void Level::levelSetup(Graphics::Image& surface)
{
	auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
	groundTiles = TileMap{ groundtileSprites, numRows, numColumns };

    for (int i = 0; i < 4; ++i)
    {
        arrayOfprtLights[i] = new Light(arrayOfPositions[i], surface);
    }
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

Light* Level::arrayOfprtLights[4]{ nullptr };
glm::vec2 Level::arrayOfPositions[4]{ {192, 144}, {576, 144}, {192, 432}, {576, 432} };