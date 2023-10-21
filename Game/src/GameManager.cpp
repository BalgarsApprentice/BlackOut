#include <GameManager.hpp>

using namespace Graphics;

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	level.levelSetup(darkness);
	setupGameObjects();
}

void GameManager::setupGameObjects()
{
	GameObject::setupGameObjects();
}

void GameManager::updateGameObjects(float deltaTime)
{
	if (isGameRunning)
	{
		GameObject::updateGameObjects(deltaTime);
		Light::litCheck(&player);
	}

	drawToCanvas();
}

void GameManager::drawToCanvas()
{
	canvas.clear(Color::Blue);
	darkness.clear(Color::Black);

	GameObject::drawGameObjects(); //This skips drawing the player and the flashlight.
	flashlight.draw();

	level.getTileMap().drawOffset(canvas, level.getHorizontalOffset(), level.getVerticalOffset());

#if _DEBUG
	if (isDark)
	{
		canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
	}
#else
	canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
#endif
	player.draw();
}

void GameManager::clearLevelGameObjects()
{
	level.levelUnload();
	GameObject::clearGameObjects(2); //This skips clearing the player and the flashlight.
}

void GameManager::clearAllGameObjects()
{
	level.levelUnload();
	GameObject::clearGameObjects(0);
}

const void GameManager::flipDarkness()
{
	isDark = !isDark;
}

const void GameManager::flipPause()
{
	isGameRunning = !isGameRunning;
}

Image& GameManager::getCanvas()
{
	return canvas;
}
