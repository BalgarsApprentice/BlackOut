#include <VariousUI.hpp>

using namespace Graphics;
using namespace Math;

VariousUI::VariousUI() = default;

void VariousUI::setScreenSize(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void VariousUI::initializeUI()
{
	textBox.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	auto flashlightImage = ResourceManager::loadImage("assets/textures/TitleScreen/FlashlightForTitleScreen.png");
	flashlightSprite = Sprite{ flashlightImage, {0, 0, 700, 500}, BlendMode::AlphaBlend };
	auto lightImage = ResourceManager::loadImage("assets/textures/TitleScreen/LightForTitleScreen.png");
	lightSprite = Sprite{ lightImage, {0, 0, 700, 500}, BlendMode::AlphaBlend };
	auto titleImage = ResourceManager::loadImage("assets/textures/TitleScreen/Title.png");
	titleSprite = Sprite{ titleImage, {0, 0, 500, 259}, BlendMode::AlphaBlend };
	auto arrowKeysImage = ResourceManager::loadImage("assets/textures/arrowkeys.png");
	arrowKeysSprite = Sprite{ arrowKeysImage, {0, 0, 86, 58}, BlendMode::AlphaBlend };
}

const bool VariousUI::getDisplaySetting() const
{
    return isDisplaying;
}

void VariousUI::setDisplaySetting(bool bit)
{
	isDisplaying = bit;
}

void VariousUI::updateUI(const float deltaTime)
{
	textBoxTime += deltaTime;

	secondCheck += deltaTime;
	if (secondCheck > 1.0f)
	{
		isStartText = !isStartText;
		secondCheck = 0.0f;
	}
}

void VariousUI::setState(UI state)
{
	isDisplaying = true;
	ui = state;

	switch (ui)
	{
	case VariousUI::UI::start:
		secondCheck = -3.0f;
		stateString = "start";
		break;

	case VariousUI::UI::flashlight:
		secondCheck = -0.5f;
		stateString = "flashlight";
		break;

	case VariousUI::UI::darklight:
		stateString = "darklight";
		break;

	case VariousUI::UI::pause:
		stateString = "pause";
		break;

	case VariousUI::UI::end:
		stateString = "end";
		break;
	}

	logger->write("variousUI has entered its " + stateString + " state.");
}

void VariousUI::drawBorder()
{
	textBox.clear(Color::Black);

	drawCustomBorder(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

void VariousUI::drawCustomBorder(int xMin, int yMin, int xMax, int yMax, bool fill)
{
	//Left
	textBox.drawAABB(AABB{ { xMin, yMin, 0 }, { xMin + 6, yMax, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin + 5, yMin, 0 }, { xMin + 6, yMax, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin, yMin, 0 }, { xMin + 1, yMax, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//Right
	textBox.drawAABB(AABB{ { xMax - 6, yMin, 0 }, { xMax, yMax, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMax - 6, yMin, 0 }, { xMax - 5, yMax, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMax - 1, yMin, 0 }, { xMax, yMax, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//Top
	textBox.drawAABB(AABB{ { xMin + 2, yMin, 0 }, { xMax - 2, yMin + 6, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin + 2, yMin, 0 }, { xMax - 2, yMin + 1, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin + 5, yMin + 5, 0 }, { xMax - 5, yMin + 6, 0 } }, Color::BlueBlack, BlendMode::Disable);
	//Bottom
	textBox.drawAABB(AABB{ { xMin + 2, yMax - 6, 0 }, { xMax - 2, yMax, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin + 2, yMax - 1, 0 }, { xMax - 2, yMax, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { xMin + 5, yMax - 6, 0 }, { xMax - 5, yMax - 5, 0 } }, Color::BlueBlack, BlendMode::Disable);

	if (fill)
	{
		textBox.drawAABB(AABB{ { xMin + 7, yMin + 7, 0 }, { xMax - 7, yMax - 7, 0 } }, Color::BlueWhite, BlendMode::Disable);
	}
}

void VariousUI::startMenuUI()
{
	textBox.drawSprite(flashlightSprite, 7, 7);

	if (textBoxTime > 3.0f)
	{
		textBox.drawSprite(lightSprite, 7, 7);
		textBox.drawSprite(titleSprite, 40, 40);

		if (Input::getKeyDown(Graphics::KeyCode::Enter))
		{
			isDisplaying = false;
			textBoxTime = 0.0f;
		}
	}

	if (isStartText)
	{
		textBox.drawText(Font{ 2.0f }, "(PRESS ENTER TO CONTINUE)", 100, 350, Color::Black);
	}
}

void VariousUI::foundFlashlightUI()
{
	if (textBoxTime > 1.0f)
	{
		if (Input::getKeyDown(Graphics::KeyCode::Enter))
		{
			isDisplaying = false;
			textBoxTime = 0.0f;
		}
	}

	drawCustomBorder(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4 * 3, true);
	textBox.drawText(Font{ 3.0f }, "You found", 308, 183, Color::Black);
	textBox.drawText(Font{ 3.0f }, "the flashlight!", 278, 219, Color::Black);
	textBox.drawText(Font{ 3.0f }, "flashlight!", 347, 219, Color::Blue);
	textBox.drawText(Font{ 2.0f }, "Control the direction of the", 237, 263, Color::Black);
	textBox.drawText(Font{ 2.0f }, "flashlight using the arrow keys.", 218, 287, Color::Black);
	textBox.drawSprite(arrowKeysSprite, 345, 321);

	if (isStartText)
	{
		textBox.drawText(Font::Default, "(PRESS ENTER TO CONTINUE)", 279, 400, Color::Black);
	}

	//textBox.drawAABB(AABB{ { SCREEN_WIDTH / 2 - 1, 0, 0 }, { SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0 } }, Color::Red, BlendMode::Disable);

}

Image& VariousUI::getUI()
{
	drawBorder();

	switch (ui)
	{
	case VariousUI::UI::start:
		startMenuUI();
		break;

	case VariousUI::UI::flashlight:
		foundFlashlightUI();
		break;

	case VariousUI::UI::darklight:
		break;

	case VariousUI::UI::pause:
		break;

	case VariousUI::UI::end:
		break;

	default:
		logger->write("UI error. VariousUI is outside its natural states.");
		isDisplaying = false;
		break;
	}

    return textBox;
}
