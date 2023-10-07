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

#include <fmt/core.h>

#include <iostream>

using namespace Graphics;

Window window;
Image image1;
Image image2;
Sprite whiteLight;
SpriteAnim walkAnim;
TileMap groundTiles;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 576;

bool isDark = true;
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

    auto charandtilesSprites = ResourceManager::loadSpriteSheet("assets/textures/characterandtiles.png", 64, 64, 0, 0);

    walkAnim = SpriteAnim{ charandtilesSprites, 4, {{53, 54}} };

    groundTiles = TileMap{ charandtilesSprites, 12, 9 };

    auto whiteSpaceImage = ResourceManager::loadImage("assets/textures/whitesquare.png");

    whiteLight = Sprite(whiteSpaceImage);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            groundTiles(i, j) = (i + charandtilesSprites->getNumColumns() + j) % charandtilesSprites->getNumSprites();
        }
    }

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    while (window)
    {
        // Update Loop
        //auto keyState = Keyboard::getState();

        //Update the input state
        Input::update();
        player.update(timer.elapsedSeconds());
        walkAnim.update(timer.elapsedSeconds());

        //Render Loop
        image1.clear(Color::Red);
        image2.clear(Color::Black);

        image2.drawSprite(whiteLight, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);

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