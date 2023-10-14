#include <Singleton.hpp>
#include <Logger.hpp>
#include <GameManager.hpp>

#include <Graphics/Window.hpp>
#include <Graphics/Timer.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Input.hpp>

#include <fmt/core.h>

#include <iostream>

using namespace Graphics;

Window window;
Window* prtWindow = &window;
Logger* logger = &Singleton<Logger>::GetInstance();
GameManager* gameManager = &Singleton<GameManager>::GetInstance();

int main()
{
    logger->write("Blackout has started.");

    //Initialize Game
    gameManager->initializeGame(prtWindow);

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    while (window)
    {
        // Update Loop

        Input::update();
        gameManager->updateGameObjects(timer.elapsedSeconds()); // Rendering handled by the Game Manager after updating.

        //{
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
        //}

        gameManager->getCanvas().drawText(Font::Default, fps, 10, 10, Color::White);

        window.present(gameManager->getCanvas());

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
#if _DEBUG
                case KeyCode::B:
                    gameManager->flipDarkness();
                    break;
#endif
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