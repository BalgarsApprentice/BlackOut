#pragma once

#include <Graphics/Image.hpp>
#include <glm/vec2.hpp>
#include <Graphics/SpriteAnim.hpp>

class Drawer
{
public:
	Drawer();

	Drawer(Graphics::Image& surface);

	void update(float deltaTime);

	void drawMe(const glm::vec2& aPos);

private:
	Graphics::Image* canvas;
	Graphics::SpriteAnim walkAnim;
};