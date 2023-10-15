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
            window->destroy();
            break;
        case Event::KeyPressed:
            switch (e.key.code)
            {
            case KeyCode::Escape:
                window->destroy();
                break;
            case KeyCode::V:
                window->toggleVSync();
                break;
#if _DEBUG
            case KeyCode::B:
                gameManager->flipDarkness();
                break;
#endif
            case KeyCode::M:
                Flashlight::lockFlashlight();
                break;
            }
        case Event::KeyReleased:
            switch (e.key.code)
            {
            case KeyCode::N:
                Flashlight::unlockFlashlight();
                break;

            }
        }
    }
}