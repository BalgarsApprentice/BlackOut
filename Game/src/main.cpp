#include <Singleton.hpp>
#include <Logger.hpp>
#include <GameManager.hpp>
#include <EventHandler.hpp>
#include <VariousUI.hpp>

#include <Graphics/Window.hpp>
#include <Graphics/Timer.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Input.hpp>

#include <Audio/Sound.hpp>

#include <fmt/core.h>

using namespace Graphics;

Window window;
Window* prtWindow = &window;
Logger* logger = &Singleton<Logger>::GetInstance();
GameManager* gameManager = &Singleton<GameManager>::GetInstance();
VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();
EventHandler* eventHandler = &Singleton<EventHandler>::GetInstance();

const int SCREEN_WIDTH = 776;
const int SCREEN_HEIGHT = 584;

int main()
{
    logger->write("Blackout has started.");

    gameManager->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    gameManager->initializeGame(prtWindow);

    variousUI->setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    variousUI->initializeUI();

    Timer       timer;
    double      totalTime = 0.0;
    uint64_t    frameCount = 0ull;
    std::string fps = "FPS: 0";

    window.setFullscreen(true);

    variousUI->setState(variousUI->UI::start);
    variousUI->getSoundTrack().play();

    while (window)
    {
        Input::update();

        if (variousUI->getDisplaySetting())
        {
            variousUI->getSoundTrack().pause();
            variousUI->updateUI(timer.elapsedSeconds());
            window.present(variousUI->getUI());
        }
        else
        {
            if (gameManager->getPlayingMusic())
            {
                variousUI->getSoundTrack().play();
            }

            gameManager->updateGameObjects(timer.elapsedSeconds());

            gameManager->getCanvas().drawText(Font::Default, fps, 12, 10, Color::Black);
            gameManager->getCanvas().drawText(Font{ 2.0f }, "BLACK\nOUT", 10, 35, Color::White);
            gameManager->getCanvas().drawText(Font{ 2.0f }, "Controls", 10, 90, Color::Black);
            gameManager->getCanvas().drawText(Font{ 1.8f }, "WALK", 28, 120, Color::Black);

            window.present(gameManager->getCanvas());
        }

        eventHandler->eventQueue(prtWindow);

        timer.tick();
        ++frameCount;

        totalTime += timer.elapsedSeconds();
        if (totalTime > 1.0)
        {
            fps = fmt::format("FPS: {:.0f}", static_cast<double>(frameCount) / totalTime);

            frameCount = 0;
            totalTime = 0.0;
        }
    }

    //      DO NOT REMOVE
    // must destroy manually to prevent an order-of-destruction error
    variousUI->destroySound();

    return 0;
}