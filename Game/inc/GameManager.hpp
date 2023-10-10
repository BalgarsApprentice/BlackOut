#pragma once

#include <GameObject.hpp>
#include <Player.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Window.hpp>

class GameManager
{
public:
	//Creating an instance
	static GameManager& instance()
	{
		static GameManager* instance = new GameManager();												////////////////////////////////////////
		return *instance;																				///  Move image and window setup here///
	}																									////////////////////////////////////////

	void initializeGame(Graphics::Window* window);

	void addGameObject(GameObject* object);

	void updateGameObjects(float deltaTime);

	void drawGameObjects();

	void clearGameObjects();

	const Graphics::Image getCanvas() const;

private:
	GameManager() {}

	Graphics::Image canvas;
	Graphics::Image darkness;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 576;

	GameObject* arrayOfPointers[128];
	int endOfArray{};
};