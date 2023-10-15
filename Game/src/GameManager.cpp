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

void GameManager::clearGameObjects()
{
	GameObject::clearGameObjects(); //This skips clearing the player
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
