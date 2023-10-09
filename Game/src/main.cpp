#include <Player.hpp>
#include <Level.hpp>
#include <GameManager.hpp>

#include <Graphics/Window.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Graphics/Timer.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Graphics/BlendMode.hpp>
#include <Graphics/Input.hpp>

#include <fmt/core.h>

#include <iostream>

using namespace Graphics;

Window window;
Image canvas;
Image darkness;
Sprite flashlight;
SpriteAnim lightAnim;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 576;

bool isDark = 0;
Player player{ {352.0f, 256.0f}, {} };
Level level1;
Level level2;
Level level3;

void InitGame()
{
    player.setPosition({ (SCREEN_WIDTH / 2 - 16), (SCREEN_HEIGHT / 2 - 16)});
}

int main()
{
    //Load Files
    player.playerSetup();
    level1.levelSetup();

    canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

    GameManager::instance().setImages(&canvas, &darkness);

    window.create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.show();
    //window.setFullscreen(true);

    auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0);

    lightAnim = SpriteAnim{ lightSprites, 4, {} };

    auto whiteSpaceImage = ResourceManager::loadImage("assets/textures/wideflashlight.png");

    flashlight = Sprite(whiteSpaceImage, BlendMode::AlphaBlend);

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    while (window)
    {
        // Update Loop

        //Update the input state
        Input::update();
        GameManager::instance().updateGameObjects(timer.elapsedSeconds());

        //player.update(timer.elapsedSeconds());
        lightAnim.update(timer.elapsedSeconds());

        {
            //auto aabb = player.getAABB();
            //glm::vec2 correction{0};
            //if (aabb.min.x < 0)
            //{
            //    correction.x = -aabb.min.x;
            //}
            //if (aabb.min.y < 0)
            //{
            //    correction.y = -aabb.min.y;
            //}
            //if (aabb.max.x >= canvas.getWidth())
            //{
            //    correction.x = canvas.getWidth() - aabb.max.x;
            //}
            //if (aabb.max.y >= canvas.getHeight())
            //{
            //    correction.y = canvas.getHeight() - aabb.max.y;
            //}

            ////Apply correction
            //player.translate(correction);
        }

        //Render Loop
        canvas.clear(Color::Blue);
        darkness.clear(Color::Black);

        if (isDark)
        {
            darkness.drawSprite(lightAnim, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
            darkness.drawSprite(flashlight, player.getPosition().x - 53, player.getPosition().y + 32);
        }

        level1.getTileMap().drawOffset(canvas, level1.getHorizontalOffset(), level1.getVerticalOffset());

        if (isDark)
        {
            canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
        }

        canvas.drawSprite(player.getSpriteAnim(), player.getPosition().x, player.getPosition().y);
#if _DEBUG
        canvas.drawAABB(player.getBox().getAABB(player.getPosition()), Color::Yellow, {}, FillMode::WireFrame);
#endif

        canvas.drawText(Font::Default, fps, 10, 10, Color::White);

        window.present(canvas);

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
                    isDark = !isDark;
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