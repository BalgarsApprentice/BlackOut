#include <VariousUI.hpp>

using namespace Graphics;
using namespace Math;

VariousUI::VariousUI() = default;

void VariousUI::initializeUI()
{
	textBox.resize(776, 584);
	auto flashlightImage = ResourceManager::loadImage("assets/textures/TitleScreen/FlashlightForTitleScreen.png");
	flashlight = Sprite{ flashlightImage, {0, 0, 700, 500}, BlendMode::AlphaBlend };
	auto lightImage = ResourceManager::loadImage("assets/textures/TitleScreen/LightForTitleScreen.png");
	light = Sprite{ lightImage, {0, 0, 700, 500}, BlendMode::AlphaBlend };
	auto titleImage = ResourceManager::loadImage("assets/textures/TitleScreen/Title.png");
	title = Sprite{ titleImage, {0, 0, 500, 259}, BlendMode::AlphaBlend };
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
	if (textBoxTime < 3.0f)
	{
		textBoxTime += deltaTime;
		return;
	}

	if (Input::getKeyDown(Graphics::KeyCode::Space))
	{
		isDisplaying = false;
		textBoxTime = 0.0f;
	}

	secondCheck += deltaTime;
	if (secondCheck > 1.0f)
	{
		isShowText = !isShowText;
		secondCheck = 0.0f;
	}
}

Image& VariousUI::getTextBox()
{
    textBox.clear(Color::Black);

	textBox.drawAABB(AABB{ { 0, 0, 0 }, { 6, 584, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 5, 0, 0 }, { 6, 584, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 0, 0, 0 }, { 1, 584, 0 } }, Color::BlueBlack, BlendMode::Disable);

	textBox.drawAABB(AABB{ { 770, 0, 0 }, { 776, 584, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 770, 0, 0 }, { 771, 584, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 775, 0, 0 }, { 776, 584, 0 } }, Color::BlueBlack, BlendMode::Disable);

	textBox.drawAABB(AABB{ { 2, 0, 0 }, { 774, 6, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 2, 0, 0 }, { 774, 1, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 5, 5, 0 }, { 771, 6, 0 } }, Color::BlueBlack, BlendMode::Disable);

	textBox.drawAABB(AABB{ { 2, 578, 0 }, { 774, 584, 0 } }, Color::BlueGrey, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 2, 582, 0 }, { 774, 584, 0 } }, Color::BlueBlack, BlendMode::Disable);
	textBox.drawAABB(AABB{ { 5, 578, 0 }, { 771, 579, 0 } }, Color::BlueBlack, BlendMode::Disable);

	textBox.drawSprite(flashlight, 7, 7);

	if (textBoxTime > 3.0f)
	{
		textBox.drawSprite(light, 7, 7);
		textBox.drawSprite(title, 40, 40);
	}

	if (isShowText)
	{
		textBox.drawText(Font{ 2.0f }, "(PRESS SPACE TO CONTINUE)", 100, 350, Color::Black);
	}

    return textBox;
}
