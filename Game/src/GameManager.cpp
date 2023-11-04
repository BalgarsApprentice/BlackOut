#include <GameManager.hpp>

using namespace Graphics;
using namespace Math;

void GameManager::setScreenSize(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	auto wasdImage = ResourceManager::loadImage("assets/textures/wasd.png");
	wasdSprite = Sprite{ wasdImage, {0, 0, 86, 58}, BlendMode::AlphaBlend };
	auto arrowKeysImage = ResourceManager::loadImage("assets/textures/arrowkeys.png");
	arrowKeysSprite = Sprite{ arrowKeysImage, {0, 0, 86, 58}, BlendMode::AlphaBlend };
	auto spacebarImage = ResourceManager::loadImage("assets/textures/shortspacebar.png");
	spacebarSprite = Sprite{ spacebarImage, {0, 0, 86, 27}, BlendMode::AlphaBlend };
	auto pkeyImage = ResourceManager::loadImage("assets/textures/pkey.png");
	pkeySprite = Sprite{ pkeyImage, {0, 0, 25, 27}, BlendMode::AlphaBlend };
	auto mkeyImage = ResourceManager::loadImage("assets/textures/mkey.png");
	mkeySprite = Sprite{ mkeyImage, {0, 0, 25, 27}, BlendMode::AlphaBlend };
	auto esckeyImage = ResourceManager::loadImage("assets/textures/esckey.png");
	esckeySprite = Sprite{ esckeyImage, {0, 0, 25, 27}, BlendMode::AlphaBlend };

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	UI.resize(96, SCREEN_HEIGHT);

	level.levelSetup(canvas, darkness);
	setupGameObjects();
}

void GameManager::reinitializeGame()
{
	level.levelSetup(canvas, darkness);
	setupGameObjects();
}

void GameManager::setupGameObjects()
{
	GameObject::setupGameObjects();
	player.sendFlashlightObjects(flashlightObject, darklightObject, coinGoal);
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
	UI.clear(Color::BlueWhite);

	level.getTileMap().drawOffset(canvas, level.getHorizontalOffset(), level.getVerticalOffset());

	GameObject::drawGameObjects(); //This skips drawing the player and the flashlight.
	flashlight.draw();

#if _DEBUG
	int len = sizeof(level.obstacles) / sizeof(BoxCollider);
	for (int i = 0; i < len; ++i)
	{
		canvas.drawAABB(level.obstacles[i].getAABB(), Color::Yellow, {}, FillMode::WireFrame);
	}
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

	// Drawing the UI
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	canvas.copy(UI, {}, {}, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 0, 0, 0 }, { 6, SCREEN_HEIGHT, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 0, 0 }, { 6, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 0, 0, 0 }, { 1, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { SCREEN_WIDTH - 6, 0, 0 }, { SCREEN_WIDTH, SCREEN_HEIGHT, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { SCREEN_WIDTH - 6, 0, 0 }, { SCREEN_WIDTH - 5, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { SCREEN_WIDTH - 1, 0, 0 }, { SCREEN_WIDTH, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 2, 0, 0 }, { SCREEN_WIDTH - 2, 6, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 2, 0, 0 }, { SCREEN_WIDTH - 2, 1, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 5, 0 }, { SCREEN_WIDTH - 5, 6, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 2, SCREEN_HEIGHT - 6, 0 }, { SCREEN_WIDTH - 2, SCREEN_HEIGHT, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 2, SCREEN_HEIGHT - 1, 0 }, { SCREEN_WIDTH - 2, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, SCREEN_HEIGHT - 6, 0 }, { SCREEN_WIDTH - 5, SCREEN_HEIGHT - 5, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 94, 2, 0 }, { 100, SCREEN_HEIGHT - 2, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 94, 5, 0 }, { 95, SCREEN_HEIGHT - 5, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 99, 5, 0 }, { 100, SCREEN_HEIGHT - 5, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 7, 30, 0 }, { 93, 78, 0 } }, Color::Black, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 5, 23, 0 }, { 95, 29, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 23, 0 }, { 95, 24, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 28, 0 }, { 95, 29, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 5, 79, 0 }, { 95, 85, 0 } }, Color::BlueGrey, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 79, 0 }, { 95, 80, 0 } }, Color::BlueBlack, BlendMode::Disable);
	canvas.drawAABB(AABB{ { 5, 84, 0 }, { 95, 85, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 6, 110, 0 }, { 95, 111, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 6, 200, 0 }, { 95, 201, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 6, 306, 0 }, { 95, 307, 0 } }, Color::BlueBlack, BlendMode::Disable);

	canvas.drawAABB(AABB{ { 6, 380, 0 }, { 95, 381, 0 } }, Color::BlueBlack, BlendMode::Disable);
	
	canvas.drawSprite(wasdSprite, 7, 138);
	canvas.drawSprite(arrowKeysSprite, 7, 243);
	canvas.drawSprite(spacebarSprite, 7, 348);
	canvas.drawSprite(pkeySprite, 68, 389);
	canvas.drawSprite(mkeySprite, 68, 425);
	canvas.drawSprite(esckeySprite, 68, 461);

	if (player.getLightOrDark()) 
	{
		canvas.drawText(Font{ 1.8f }, "FLASH", 24, 210, Color::Black);
		canvas.drawText(Font{ 1.8f }, "LIGHT", 24, 226, Color::Black);
	}
	else 
	{
		canvas.drawText(Font{ 1.8f }, "DARK", 29, 210, Color::Black);
		canvas.drawText(Font{ 1.8f }, "LIGHT", 24, 226, Color::Black);
	}

	canvas.drawText(Font{ 1.8f }, "TOGGLE", 16, 315, Color::Black);
	canvas.drawText(Font{ 1.8f }, "LIGHT", 24, 331, Color::Black);

	canvas.drawText(Font{ 1.8f }, "PAUSE", 9, 396, Color::Black);
	canvas.drawText(Font{ 1.8f }, "MUTE", 9, 432, Color::Black);
	canvas.drawText(Font{ 1.8f }, "EXIT", 9, 468, Color::Black);

	if (!player.getHasFlashlight())
	{
		canvas.drawAABB(AABB{ { 7, 200, 0 }, { 93, 305, 0 } }, Color::BlueWhite, BlendMode::Disable);
	}

	if (!player.getHasDarklight())
	{
		canvas.drawAABB(AABB{ { 7, 306, 0 }, { 93, 379, 0 } }, Color::BlueWhite, BlendMode::Disable);
	}

	//canvas.drawAABB(AABB{ { 7, 306, 0 }, { 93, SCREEN_HEIGHT - 7, 0 } }, Color::BlueWhite, BlendMode::Disable);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

const void GameManager::toggleMusic()
{
	isPlayingMusic = !isPlayingMusic;
}

const bool GameManager::getPlayingMusic() const
{
	return isPlayingMusic;
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
	player.setPosition({ 196.0f, 476.0f });
}

void GameManager::teleportTopLeft()
{
	player.setPosition({ 196.0f, 100.0f });
}
