#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>

class Light : public GameObject
{
public:
	Light();

	Light(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

private:
	Graphics::Image* darkness;
	Graphics::SpriteAnim lightAnim;
};