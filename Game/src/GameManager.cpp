#include <GameManager.hpp>

using namespace Graphics;

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	level.levelSetup();
}

void GameManager::addGameObject(GameObject* object)
{
	arrayOfprtObjects[endOfObjectArray++] = object;
}

void GameManager::addLight(Light* light)
{
	arrayOfprtLights[endOfLightArray++] = light;
}

void GameManager::updateGameObjects(float deltaTime)
{
	for (int i = 0; i < endOfObjectArray; ++i)
	{
		arrayOfprtObjects[i]->update(deltaTime);
	}

	drawGameObjects();
}

void GameManager::drawGameObjects()
{
	canvas.clear(Color::Blue);
	darkness.clear(Color::Black);

	for (int i = 1; i < endOfObjectArray; ++i) //start with 1 because 0 should be the player
	{
		arrayOfprtObjects[i]->draw();
	}

	level.getTileMap().drawOffset(canvas, level.getHorizontalOffset(), level.getVerticalOffset());

#if _DEBUG
	if (isDark)
	{
		canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
	}
#else
	canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
#endif

	arrayOfprtObjects[0]->draw(); //drawing the player last

	//canvas.drawText(Font::Default, fps, 10, 10, Color::White);
}

void GameManager::clearGameObjects()
{
	for (int i = 1; i < endOfObjectArray; ++i) //start with 1 because 0 should be the player
	{
		arrayOfprtObjects[i] = nullptr;
	}
}

GraphicsFlyweight& GameManager::getGraphicsAdr()
{
	return graphicsFlyweight;
}

const void GameManager::flipDarkness()
{
	isDark = !isDark;
}
Image& GameManager::getCanvas()
{
	return canvas;
}
