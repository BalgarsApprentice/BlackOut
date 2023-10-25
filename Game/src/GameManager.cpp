#include <GameManager.hpp>

using namespace Graphics;
using namespace Math;

void GameManager::initializeGame(Window* prtWindow)
{
	prtWindow->create(L"Black Out", SCREEN_WIDTH, SCREEN_HEIGHT);
	prtWindow->show();

	auto borderImage = ResourceManager::loadImage("assets/textures/border.png");
	borderSprite = Sprite{ borderImage, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, BlendMode::AlphaBlend };

	canvas.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	darkness.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	UI.resize(96, SCREEN_HEIGHT);

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

	canvas.copy(UI, {}, {}, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 90, 0, 0 }, { 96, SCREEN_HEIGHT, 0 } }, Color::BlueGrey, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 90, 0, 0 }, { 91, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 95, 0, 0 }, { 96, SCREEN_HEIGHT, 0 } }, Color::BlueBlack, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 0, 30, 0 }, { 89, 78, 0 } }, Color::Black, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 0, 23, 0 }, { 92, 29, 0 } }, Color::BlueGrey, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 0, 23, 0 }, { 90, 24, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 0, 28, 0 }, { 90, 29, 0 } }, Color::BlueBlack, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 0, 79, 0 }, { 92, 85, 0 } }, Color::BlueGrey, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 0, 79, 0 }, { 90, 80, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//canvas.drawAABB(AABB{ { 0, 84, 0 }, { 90, 85, 0 } }, Color::BlueBlack, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 34, 140, 0 }, { 53, 160, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 34, 162, 0 }, { 53, 182, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 12, 162, 0 }, { 31, 182, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 56, 162, 0 }, { 75, 182, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);

	//canvas.drawAABB(AABB{ { 0, 110, 0 }, { 89, 111, 0 } }, Color::BlueBlack, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 0, 190, 0 }, { 89, 191, 0 } }, Color::BlueBlack, BlendMode::Disable);

	//canvas.drawAABB(AABB{ { 34, 221, 0 }, { 53, 241, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 34, 243, 0 }, { 53, 263, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 12, 243, 0 }, { 31, 263, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);
	//canvas.drawAABB(AABB{ { 56, 243, 0 }, { 75, 263, 0 } }, Color::Black, BlendMode::Disable, FillMode::WireFrame);

	canvas.drawSprite(borderSprite, 0, 0);
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
	player.setPosition({ 196.0f, 476.0f });
}

void GameManager::teleportTopLeft()
{
	player.setPosition({ 196.0f, 100.0f });
}
