#include <Singleton.hpp>
#include <Logger.hpp>
#include <GameManager.hpp>
#include <EventHandler.hpp>
#include <VariousUI.hpp>

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
VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();

int main()
{
    logger->write("Blackout has started.");

    gameManager->initializeGame(prtWindow);

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    while (window)
    {
        Input::update();
        gameManager->updateGameObjects(timer.elapsedSeconds());

        gameManager->getCanvas().drawText(Font::Default, fps, 10, 10, Color::Black);
        gameManager->getCanvas().drawText(Font{ 2.0f }, "BLACK\nOUT", 10, 35, Color::White);
        gameManager->getCanvas().drawText(Font{ 2.0f }, "Controls", 10, 90, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "WALK", 26, 124, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "W", 40, 145, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "A", 19, 167, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "S", 41, 167, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "D", 63, 167, Color::Black);
        //gameManager->getCanvas().drawText(Font::Default, "FLASHLIGHT", 1, 205, Color::Black);

        window.present(gameManager->getCanvas());

        Singleton<EventHandler>::GetInstance().eventQueue(prtWindow);

        timer.tick();
        ++frameCount;

        totalTime += timer.elapsedSeconds();
        if (totalTime > 1.0)
        {
            fps = fmt::format("FPS: {:.2f}", static_cast<double>(frameCount) / totalTime);

            std::cout << fps << std::endl;

            frameCount = 0;
            totalTime = 0.0;
        }
    }
    return 0;
}