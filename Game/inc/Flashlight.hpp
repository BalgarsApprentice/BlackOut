#pragma once

#include <GameObject.hpp>
#include <Graphics/Sprite.hpp>

class Flashlight : public GameObject
{
public:
	Flashlight();

	Flashlight(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

private:
	Graphics::Image* darkness;
	Graphics::Sprite flashlightSprite;
};