#pragma once

#include <Graphics/ResourceManager.hpp>
#include <Graphics/TileMap.hpp>
#include <MovingLight.hpp>
#include <FlashlightObject.hpp>

class Level
{
public:
    Level();

    void levelSetup(Graphics::Image& canvas, Graphics::Image& darkness);

    friend class Player;

    void levelUnload();

    Graphics::TileMap& getTileMap();

    const uint32_t getHorizontalOffset() const
    {
        return horizontalOffset;
    }

    const uint32_t getVerticalOffset() const
    {
        return verticalOffset;
    }

private:
    const int map[432] = {
    7,  9,  9,  9,  9,  10, 6,  7,  9,  9,  9,  9,  9,  9,  9,  9,  10, 6,  7,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  5,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  2,  3,  3,  3,  3,  5,
    6,  6,  6,  6,  6,  6,  6,  11, 12, 12, 12, 12, 12, 12, 12, 12, 1,  6,  6,  6,  6,  6,  6,  6,
    7,  9,  9,  9,  9,  9,  9,  15, 12, 12, 12, 12, 12, 12, 12, 12, 8,  9,  9,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  5
    };

    Graphics::TileMap groundTiles;

    const uint32_t horizontalOffset = 0;
    const uint32_t verticalOffset = 0;

    const uint32_t numRows = 24 - horizontalOffset;
    const uint32_t numColumns = 18 - verticalOffset;

    glm::vec2 arrayOfPositions[8]{ 
        {4, 4}, {4, 100}, {4, 196}, {100, 196}, {196, 196}, {100, 4}, {196, 4}, { 668, 100 }
    };

    glm::vec2 arrayOfMPositions[1]{ {132, 100} };

    FlashlightObject* ptrFlashlightObject{nullptr};

#if _DEBUG
public:
#endif

    BoxCollider obstacles[4]{
        Math::AABB{ {0, 182, 0}, {230, 230, 0} },
        Math::AABB{ {182, 0, 0}, {230, 182, 0} },
        Math::AABB{ {534, 182, 0}, {768, 230, 0} },
        Math::AABB{ {534, 0, 0}, {582, 182, 0} }
    };
};
