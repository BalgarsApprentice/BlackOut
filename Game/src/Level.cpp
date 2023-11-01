#include <Level.hpp>

using namespace Graphics;

Level::Level() = default;

void Level::levelSetup(Graphics::Image& canvas, Graphics::Image& darkness)
{
	auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
	groundTiles = TileMap{ groundtileSprites, numRows, numColumns };

    int len1 = sizeof(arrayOfPositions) / sizeof(glm::vec2);
    for (int i = 0; i < len1; ++i)
    {
        new Light(arrayOfPositions[i], darkness);
    }

    int len2 = sizeof(arrayOfMPositions) / sizeof(glm::vec2);
    for (int i = 0; i < len2; ++i)
    {
        new MovingLight(arrayOfMPositions[i], darkness);
    }

    int len3 = sizeof(obstacles) / sizeof(BoxCollider);
    for (int i = 0; i < len3; ++i)
    {
        Light::initializeCollisionGroup(obstacles[i].getAABB());
    }

    ptrFlashlightObject = new FlashlightObject({668, 100}, canvas, true);
    ptrDarklightObject = new FlashlightObject({ 196, 484 }, canvas, false);
}

void Level::levelUnload()
{
    int len = (sizeof(arrayOfPositions) + sizeof(arrayOfMPositions)) / sizeof(glm::vec2);
    for (int i = 0; i < len; ++i)
    {
        delete Light::arrayOfptrLights[i];
    }

    delete ptrFlashlightObject;
    delete ptrDarklightObject;
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