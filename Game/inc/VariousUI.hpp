#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>

#include <Graphics/Image.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Graphics/Input.hpp>
#include <Math/AABB.hpp>
#include <Audio/Sound.hpp>

class VariousUI
{
public:
	VariousUI();

	enum UI
	{
		none,
		start,
		flashlight,
		darklight,
		pause,
		end
	};

	void setScreenSize(int width, int height);

	void initializeUI();

	const bool getDisplaySetting() const;

	void setDisplaySetting(bool bit);

	void updateUI(const float deltaTime);

	void setState(UI ui);

	void drawBorder();

	void drawCustomBorder(int xMin, int yMin, int xMax, int yMax, bool fill);

	void startMenuUI();

	void foundFlashlightUI();

	void foundDarklightUI();

	Graphics::Image& getUI();

private:
	Logger* logger = &Singleton<Logger>::GetInstance();

	int SCREEN_WIDTH{ 0 };
	int SCREEN_HEIGHT{ 0 };

	float textBoxTime{ 0.0f };
	float secondCheck{ 0.0f };
	bool isStartText{ true };
	bool isDisplaying{ true };

	Graphics::Image textBox;
	Graphics::Sprite flashlightSprite;
	Graphics::Sprite lightSprite;
	Graphics::Sprite titleSprite;
	Graphics::Sprite arrowKeysSprite;
	Graphics::Sprite spaceBarSprite;

	Audio::Sound buttonClick;

	UI ui{ none };
	std::string stateString{ "" };
	int flashlightEventDim[4]{};
};