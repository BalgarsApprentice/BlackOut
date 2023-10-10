#include <GameManager.hpp>

using namespace Graphics;

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameManager::addGameObject(GameObject* object)
{
	arrayOfPointers[endOfArray++] = object;
}

void GameManager::updateGameObjects(float deltaTime)
{
	for (int i = 0; i < endOfArray; ++i)
	{
		arrayOfPointers[i]->update(deltaTime);
	}
}

void GameManager::drawGameObjects()
{
	for (int i = 1; i < endOfArray; ++i) //start with 1 because 0 should be the player
	{
		arrayOfPointers[i]->draw(*canvas);
	}

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

	arrayOfPointers[0]->draw(darkness);
}

void GameManager::clearGameObjects()
{
	for (int i = 1; i < endOfArray; ++i) //start with 1 because 0 should be the player
	{
		arrayOfPointers[i] = nullptr;
	}
}

const Image GameManager::getCanvas() const
{
	return canvas;
}
