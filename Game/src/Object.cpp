#include <Object.hpp>

using namespace Graphics;

Object::Object() = default;

void Object::draw(Image& image)
{
	image.drawSprite(sprite, position.x, position.y);
}