#include <Level.hpp>

using namespace Graphics;

Level::Level() = default;

void Level::levelSetup(Graphics::Image& surface)
{
	auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
	groundTiles = TileMap{ groundtileSprites, numRows, numColumns };

    int len1 = sizeof(arrayOfPositions) / sizeof(glm::vec2);
    for (int i = 0; i < len1; ++i)
    {
        new Light(arrayOfPositions[i], surface);
    }

    int len2 = sizeof(arrayOfMPositions) / sizeof(glm::vec2);
    for (int i = 0; i < len2; ++i)
    {
        new MovingLight(arrayOfMPositions[i], surface);
    }
    
    int len3 = sizeof(obstacles) / sizeof(BoxCollider);
    for (int i = 0; i < len3; ++i)
    {
        Light::initializeCollisionGroup(obstacles[i].getAABB());
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