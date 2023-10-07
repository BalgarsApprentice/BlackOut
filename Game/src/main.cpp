#include <Player.hpp>
#include <Level.hpp>

#include <Graphics/Window.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Graphics/TileMap.hpp>
#include <Graphics/Timer.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Graphics/BlendMode.hpp>
#include <Graphics/Input.hpp>
#include <Math/Camera2D.hpp>

#include <fmt/core.h>

#include <iostream>

using namespace Graphics;
using namespace Math;

Window window;
Camera2D camera;
Image image1;
Image image2;
Sprite whiteLight;
SpriteAnim walkAnim;
SpriteAnim lightAnim;
TileMap groundTiles;

int map[432] = {
    7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1,
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5
};

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 576;

bool isDark = false;
Player player;
Level level1;
Level level2;
Level level3;

void InitGame()
{
    player.setPosition({ (SCREEN_WIDTH / 2 - 32), (SCREEN_HEIGHT / 2 - 32)});
}

int main()
{
    image1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    image2.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

    window.create(L"Out of Sight, Out of Mind", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.show();
    //window.setFullscreen(true);

    camera.setZoom(2.0f);

    auto playerSprites = ResourceManager::loadSpriteSheet("assets/textures/playersheet.png", 64, 64, 0, 0, BlendMode::AlphaBlend);
    auto groundtileSprites = ResourceManager::loadSpriteSheet("assets/textures/groundtiles.png", 32, 32, 0, 0);
    auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0);

    walkAnim = SpriteAnim{ playerSprites, 4, {{0, 2}} };
    lightAnim = SpriteAnim{ lightSprites, 4, {} };

    groundTiles = TileMap{ groundtileSprites, 24, 18 };

    auto whiteSpaceImage = ResourceManager::loadImage("assets/textures/whitesquare.png");

    whiteLight = Sprite(whiteSpaceImage);

    int k = 0;
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 24; ++j)
        {
            groundTiles(i, j) = map[k++];
            //groundTiles(i, j) = (i + groundtileSprites->getNumColumns() + j) % groundtileSprites->getNumSprites();
        }
    }

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    while (window)
    {
        // Update Loop

        //Update the input state
        Input::update();

        player.update(timer.elapsedSeconds());
        walkAnim.update(timer.elapsedSeconds());
        lightAnim.update(timer.elapsedSeconds());

        //Render Loop
        image1.clear(Color::Blue);
        image2.clear(Color::Black);

        if (isDark)
        {
            image2.drawSprite(lightAnim, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
        }

        groundTiles.draw(image1);

        if (isDark)
        {
            image1.copy(image2, {}, {}, BlendMode::MultiplicativeBlend);
        }

        image1.drawSprite(walkAnim, player.getPosition().x, player.getPosition().y);

        image1.drawText(Font::Default, fps, 10, 10, Color::White);

        window.present(image1);

        Event e;
        while (window.popEvent(e))
        {
            switch (e.type)
            {
            case Event::Close:
                window.destroy();
                break;
            case Event::KeyPressed:
                switch (e.key.code)
                {
                case KeyCode::Escape:
                    window.destroy();
                    break;
                case KeyCode::V:
                    window.toggleVSync();
                    break;
                case KeyCode::B:
                    if (isDark)
                    {
                        isDark = false;
                    }
                    else
                    {
                        isDark = true;
                    }
                    break;
                }

            }
        }

        timer.tick();
        ++frameCount;

        totalTime += timer.elapsedSeconds();
        if (totalTime > 1.0)
        {
            fps = fmt::format("FPS: {:.3f}", static_cast<double>(frameCount) / totalTime);

            std::cout << fps << std::endl;

            frameCount = 0;
            totalTime = 0.0;
        }
    }

    return 0;
}