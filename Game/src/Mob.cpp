#include <Mob.hpp>
#include <Graphics/Input.hpp>

using namespace Graphics;

Mob::Mob() = default;

Mob::Mob(const glm::vec2& pos, const Sprite& _sprite)
	: position{ pos }
	, sprite{ _sprite }
{
}

void Mob::update(float deltaTime)
{
	
}

void Mob::draw(Image& image)
{
	image.drawSprite(sprite, position.x, position.y);
}

void Mob::setPosition(const glm::vec2& pos)
{
	position = pos;
}

const glm::vec2& Mob::getPosition() const
{
	return position;
}