#include <Level.hpp>

using namespace Graphics;

Level::Level() = default;

void Level::levelSetup(Graphics::Image& surface)
{
	auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
	groundTiles = TileMap{ groundtileSprites, numRows, numColumns };

    for (int i = 0; i < 4; ++i)
    {
        Light::arrayOfprtLights[i] = new Light(arrayOfPositions[i], surface);
    }
    
}

void Level::levelUnload()
{
    for (int i = 0; i < 4; ++i)
    {
        delete Light::arrayOfprtLights[i];
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