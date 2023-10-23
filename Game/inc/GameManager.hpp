#pragma once

#include <Light.hpp>
#include <Level.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Window.hpp>
#include <GameObject.hpp>
#include <Player.hpp>
#include <Human.hpp>
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

private:
	Graphics::Image canvas;
	Graphics::Image darkness;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 576;

	bool isDark = 1;
	bool isGameRunning = 1;

	Level level;
	glm::vec2 startPosition{ 69.0f, 75.0f };
	glm::vec2 flashlightPosition{ 668.0f , 100.0f };
	Human human;
	Player player{ startPosition, human, canvas, flashlight, level };
	//Enemy enemy{};
	Flashlight flashlight{ startPosition, darkness };
};