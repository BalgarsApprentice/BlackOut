#pragma once

#include <GameObject.hpp>
#include <Light.hpp>
#include <Level.hpp>
#include <Player.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Window.hpp>
#include <GraphicsFlyweight.hpp>

class GameManager
{
public:
	//Creating an instance
	static GameManager& instance()
	{
		static GameManager* instance = new GameManager();
		return *instance;
	}

	void initializeGame(Graphics::Window* window);

	void addGameObject(GameObject* object);

	void addLight(Light* light);

	void updateGameObjects(float deltaTime);

	void drawGameObjects();

	void clearGameObjects();

	GraphicsFlyweight& getGraphicsAdr();

	const void flipDarkness();

	Graphics::Image& getCanvas();

private:
	GameManager() {}

	GraphicsFlyweight graphicsFlyweight;

	Graphics::Image canvas;
	Graphics::Image darkness;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 576;

	GameObject* arrayOfprtObjects[128];
	int endOfObjectArray{};

	Player player{ {352.0f, 256.0f}, {}, canvas };

	Light* arrayOfprtLights[128];
	int endOfLightArray{};

	bool isDark = 0;

	Level level;
};