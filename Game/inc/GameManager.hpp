#pragma once

#include <GameObject.hpp>
#include <Player.hpp>
#include <Graphics/Image.hpp>

class GameManager
{
public:
	//Creating an instance
	static GameManager& instance()
	{
		static GameManager* instance = new GameManager();												////////////////////////////////////////
		return *instance;																				///  Move image and window setup here///
	}																									////////////////////////////////////////

	void setImages(Image aCanvas, Image aDarkness)
	{
		canvas = aCanvas;
		darkness = aDarkness;
	}

	void addGameObject(GameObject* object)
	{

		arrayOfPointers[endOfArray++] = object;
	}

	void updateGameObjects(float deltaTime)
	{
		for (int i = 0; i < endOfArray; ++i)
		{
			arrayOfPointers[i]->update(deltaTime);
		}
	}

	void drawGameObjects()
	{
		for (int i = 1; i < endOfArray; ++i) //start with 1 because 0 should be the player
		{
			arrayOfPointers[i]->draw(*canvas);
		}

		if (isDark)
		{
			Graphics::Image::darkness.drawSprite(lightAnim, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
			*darkness.drawSprite(flashlight, player.getPosition().x - 53, player.getPosition().y + 32);
		}

		level1.getTileMap().drawOffset(canvas, level1.getHorizontalOffset(), level1.getVerticalOffset());

		if (isDark)
		{
			canvas.copy(darkness, {}, {}, BlendMode::MultiplicativeBlend);
		}

		arrayOfPointers[0]->draw(*darkness);
	}

	void clearGameObjects()
	{
		for (int i = 1; i < endOfArray; ++i) //start with 1 because 0 should be the player
		{
			arrayOfPointers[i] = nullptr;
		}
	}

private:
	GameManager() {}

	Graphics::Image canvas;
	Graphics::Image darkness;

	GameObject* arrayOfPointers[128];
	int endOfArray{};
};