#include <Drawer.hpp>

Drawer::Drawer() = default;

Drawer::Drawer(Graphics::Image& surface)
	: canvas{&surface}
{
}

void Drawer::update(float deltaTime)
{
	walkAnim.update(deltaTime);
}

void Drawer::drawMe(const glm::vec2& aPos)
{
	canvas->drawSprite(walkAnim, aPos.x, aPos.y);
}
