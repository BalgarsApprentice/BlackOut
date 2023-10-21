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
	glm::vec2 startPosition{ 352.0f, 256.0f };
	Human human;
	Player player{ startPosition, human, canvas, flashlight };
	//Enemy enemy{};
	Flashlight flashlight{ startPosition, darkness };
};