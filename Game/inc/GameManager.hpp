#pragma once

#include <Light.hpp>
#include <Level.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Window.hpp>
#include <GameObject.hpp>
#include <Player.hpp>
#include <Human.hpp>
#include <Enemy.hpp>
#include <Tracker.hpp>
#include <AI.hpp>

class GameManager
{
public:
	void initializeGame(Graphics::Window* window);

	void setupGameObjects();

	void updateGameObjects(float deltaTime);

	void drawToCanvas();

	void clearLevelGameObjects();

	void clearAllGameObjects();

	const void flipDarkness();

	const void flipPause();

	Graphics::Image& getCanvas();
	
	//Debug Commands
///////////////////////////////////////////////	
	void teleportTopRight();

	void teleportBottomRight();

	void teleportBottomLeft();
	
	void teleportTopLeft();
////////////////////////////////////////////////

private:
	Graphics::Image canvas;
	Graphics::Image darkness;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 576;

	bool isDark = 1;
	bool isGameRunning = 1;

	Level level;
	glm::vec2 startPosition{ 69.0f, 75.0f };
	Human human;
	Player player{ startPosition, human, canvas, flashlight, &level };
	Tracker tracker;
	Enemy enemy{ startPosition, human, canvas, &level };
	Flashlight flashlight{ startPosition, darkness };
};