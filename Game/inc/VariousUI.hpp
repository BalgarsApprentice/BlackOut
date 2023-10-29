#pragma once

#include <Graphics/Image.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Math/AABB.hpp>
#include <Graphics/Input.hpp>

class VariousUI
{
public:
	VariousUI();

	void initializeUI();

	const bool getDisplaySetting() const;

	void setDisplaySetting(bool bit);

	void updateUI(const float deltaTime);

	Graphics::Image& getTextBox();

private:
	float textBoxTime{ 0.0f };
	float secondCheck{ 0.0f };
	bool isShowText{ true };
	bool isDisplaying{ true };
	Graphics::Image textBox;
	Graphics::Sprite flashlight;
	Graphics::Sprite light;
	Graphics::Sprite title;

};