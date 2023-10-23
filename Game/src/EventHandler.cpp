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
            case KeyCode::Z:
                Flashlight::lockFlashlight();
                break;

            case KeyCode::P:
                gameManager->flipPause();
                break;
            }
            break;
        case Event::KeyReleased:
            switch (e.key.code)
            {
            case KeyCode::Z:
                Flashlight::unlockFlashlight();
                break;

            }
            break;
        }
    }
}