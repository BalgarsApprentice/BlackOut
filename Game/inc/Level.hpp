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
    const int map[378] = {
    7,  9,  9,  9,  9,  10, 6,  7,  9,  9,  9,  9,  9,  10, 6,  7,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  5,  6,  11, 12, 12, 12, 12, 12, 1,  6,  2,  3,  3,  3,  3,  5,
    6,  6,  6,  6,  6,  6,  6,  11, 12, 12, 12, 12, 12, 1,  6,  6,  6,  6,  6,  6,  6,
    7,  9,  9,  9,  9,  9,  9,  15, 12, 12, 12, 12, 12, 8,  9,  9,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  5
    };

    Graphics::TileMap groundTiles;

    const uint32_t horizontalOffset = 3;
    const uint32_t verticalOffset = 0;

    const uint32_t numRows = 24 - horizontalOffset;
    const uint32_t numColumns = 18 - verticalOffset;

    glm::vec2 arrayOfPositions[8]{ 
        {100, 4}, {100, 100}, {100, 196}, {196, 196}, {292, 196}, {196, 4}, {292, 4}, { 668, 100 }
    };

    glm::vec2 arrayOfMPositions[1]{ {228, 100} };

    FlashlightObject* ptrFlashlightObject{nullptr};

#if _DEBUG
public:
#endif

    BoxCollider obstacles[4]{
        Math::AABB{ {101, 187, 0}, {330, 234, 0} },
        Math::AABB{ {283, 5, 0}, {330, 186, 0} },
        Math::AABB{ {539, 187, 0}, {772, 234, 0} },
        Math::AABB{ {539, 5, 0}, {586, 186, 0} }
    };
};
