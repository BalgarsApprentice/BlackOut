#include <EventHandler.hpp>

using namespace Graphics;

void EventHandler::eventQueue(Window* window)
{
    Event e;
    while (window->popEvent(e))
    {
        switch (e.type)
        {
        case Event::Close:
            gameManager->clearAllGameObjects();
            window->destroy();
            break;
        case Event::KeyPressed:
            switch (e.key.code)
            {
            case KeyCode::Escape:
                gameManager->clearAllGameObjects();
                window->destroy();
                break;

            case KeyCode::V:
                window->toggleVSync();
                break;

            case KeyCode::F:
                window->toggleFullscreen();
                break;

            case KeyCode::R: //WIP
                //gameManager->clearAllGameObjects();
                //gameManager->reinitializeGame();
                break;

            case KeyCode::P:
                if (variousUI->getDisplaySetting()) break;

                gameManager->flipPause(); //consider swapping this out for the VariousUI pause state instead.
                //variousUI->setState(variousUI->UI::pause);
                break;

            case KeyCode::M:
                gameManager->toggleMusic();
                variousUI->getSoundTrack().pause();
                break;
#if _DEBUG
            case KeyCode::B:
                gameManager->flipDarkness();
                break;

            case KeyCode::NumPad1:
                gameManager->teleportTopRight();
                break;

            case KeyCode::NumPad2:
                gameManager->teleportBottomRight();
                break;

            case KeyCode::NumPad3:
                gameManager->teleportBottomLeft();
                break;

            case KeyCode::NumPad4:
                gameManager->teleportTopLeft();
                break;
#endif
            }
            break;
        }
    }
}