#pragma once

#include <Graphics/ResourceManager.hpp>
#include <Graphics/TileMap.hpp>
#include <MovingLight.hpp>
#include <FlashlightObject.hpp>
#include <Player.hpp>

class Level
{
public:
    Level();

    friend class Player;

    void levelSetup(Graphics::Image& canvas, Graphics::Image& darkness, Player& player);

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
    6,  6,  6,  6,  6,  6,  6,  11, 13, 3,  3,  3,  0,  1,  6,  6,  6,  6,  6,  6,  6,
    7,  9,  9,  9,  9,  9,  9,  15, 1,  6,  6,  6,  11, 8,  9,  9,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 12, 12, 12, 1,  6,  6,  6,  11, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 1,  6,  6,  6,  11, 12, 12, 12, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  3,  3,  0,  1,  6,  6,  6,  11, 13, 3,  3,  3,  3,  3,  3,  5,
    6,  6,  6,  6,  6,  6,  6,  11, 8,  9,  9,  9,  15, 1,  6,  6,  6,  6,  6,  6,  6,
    7,  9,  9,  9,  9,  10, 6,  11, 12, 12, 12, 12, 12, 1,  6,  7,  9,  9,  9,  9,  10,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 12, 1,  6,  11, 12, 12, 12, 12, 1,
    2,  3,  3,  3,  3,  5,  6,  2,  3,  3,  3,  3,  3,  5,  6,  2,  3,  3,  3,  3,  5
    };

    Graphics::TileMap groundTiles;

    const uint32_t horizontalOffset = 3;
    const uint32_t verticalOffset = 0;

    const uint32_t numRows = 24 - horizontalOffset;
    const uint32_t numColumns = 18 - verticalOffset;

    glm::vec2 arrayOfPositions[25]{ 
        {100, 4}, {100, 100}, {100, 196}, {196, 196}, {292, 196}, {196, 4}, {292, 4}, //top left corner lights
        { 668, 100 }, //top right corner light
        {100, 580}, {100, 484}, {100, 388}, {196, 388}, {292, 388}, {196, 580}, {292, 580}, {292, 484}, {196, 484}, //bottom left corner lights
        {772, 580}, {772, 484}, {772, 388}, {580, 388}, {676, 388}, {580, 580}, {676, 580}, {580, 484}//, {676, 484} //bottom right corner lights
    };

    glm::vec2 arrayOfMPositions[1]{ {228, 100} };

#if _DEBUG
public:
#endif

    BoxCollider obstacles[9]{
        Math::AABB{ {101, 187, 0}, {329, 233, 0} }, Math::AABB{ {283, 5, 0}, {329, 186, 0} }, //top left
        Math::AABB{ {539, 187, 0}, {772, 233, 0} }, Math::AABB{ {539, 5, 0}, {586, 186, 0} }, // top right
        Math::AABB{ {101, 350, 0}, {330, 398, 0} }, Math::AABB{ {283, 398, 0}, {330, 771, 0} }, //bottom left
        Math::AABB{ {539, 350, 0}, {772, 398, 0} }, Math::AABB{ {539, 398, 0}, {586, 771, 0} }, //bottom right
        Math::AABB{ {380, 220, 0}, {491, 362, 0} } //center
    };
};
