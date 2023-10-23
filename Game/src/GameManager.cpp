#include <GameManager.hpp>

using namespace Graphics;

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	level.levelSetup(canvas, darkness);
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
		GameObject::updateGameObjects(deltaTime, player);
		Light::litCheck(&player);
	}

	drawToCanvas();
}

void GameManager::drawToCanvas()
{
	canvas.clear(Color::Blue);
	darkness.clear(Color::Black);

	level.getTileMap().drawOffset(canvas, level.getHorizontalOffset(), level.getVerticalOffset());

	GameObject::drawGameObjects(); //This skips drawing the player and the flashlight.
	flashlight.draw();

#if _DEBUG
	int len = sizeof(level.obstacles) / sizeof(BoxCollider);
	for (int i = 0; i < len; ++i)
	{
		canvas.drawAABB(level.obstacles[i].getAABB(), Color::Yellow, {}, FillMode::WireFrame);
	}

	//for (int i = 0; i < Light::endOfLightArray; ++i)
	//{
	//	canvas.drawAABB(Light::arrayOfptrLights[i]->getBox().getAABB(), Color::Yellow, {}, FillMode::Solid);
	//}
#endif

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

void GameManager::teleportTopRight()
{
	player.setPosition({ 668.0f, 100.0f });
}

void GameManager::teleportBottomRight()
{
	player.setPosition({ 668.0f, 476.0f });
}

void GameManager::teleportBottomLeft()
{
	player.setPosition({ 100.0f, 476.0f });
}

void GameManager::teleportTopLeft()
{
	player.setPosition({ 100.0f, 100.0f });
}
