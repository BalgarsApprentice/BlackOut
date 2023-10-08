#pragma once

#include <glm/vec2.hpp>
#include <Graphics/ResourceManager.hpp>

class Object
{
public:
	Object();

	void draw(Graphics::Image& image);

private:
	Graphics::Sprite sprite;

protected:
	glm::vec2 position{ 352.0f, 256.0f };
};
