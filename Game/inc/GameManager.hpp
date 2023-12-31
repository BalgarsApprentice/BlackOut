#pragma once

#include <Light.hpp>
#include <Level.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Window.hpp>
#include <GameObject.hpp>
#include <Player.hpp>
#include <Human.hpp>
#include <FlashlightObject.hpp>
#include <EndGoal.hpp>
#include <AI.hpp>
#include <Math/AABB.hpp>

class GameManager
{
public:
	void setScreenSize(int width, int height);

	void initializeGame(Graphics::Window* window);

	void reinitializeGame();

	void setupGameObjects();

	void updateGameObjects(float deltaTime);

	void drawToCanvas();

	void clearLevelGameObjects();

	void clearAllGameObjects();

	const void flipDarkness();

	const void flipPause();

	const void toggleMusic();

	const bool getPlayingMusic() const;

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
	Graphics::Image UI;
	Graphics::Sprite wasdSprite;
	Graphics::Sprite arrowKeysSprite;
	Graphics::Sprite spacebarSprite;
	Graphics::Sprite pkeySprite;
	Graphics::Sprite mkeySprite;
	Graphics::Sprite esckeySprite;
	Graphics::SpriteAnim coinAnim;

	int SCREEN_WIDTH{ 0 };
	int SCREEN_HEIGHT{ 0 };

	bool isDark{ true };
	bool isGameRunning{ true };
	bool isPlayingMusic{ true };

	Level level;
	glm::vec2 startPosition{ 196.0f, 100.0f };
	Human human;
	Player player{ startPosition, human, canvas, flashlight, &level };
	Flashlight flashlight{ startPosition, darkness };
	//Tracker tracker{ &player };
	//Enemy enemy{ { 300.0f, 300.0f }, tracker, canvas, &level };
	FlashlightObject flashlightObject{ glm::vec2{ 668, 100 }, canvas, true };
	FlashlightObject darklightObject{ glm::vec2{ 196, 484 }, canvas, false };
	EndGoal coinGoal{ glm::vec2{ 674, 484 }, canvas };
};