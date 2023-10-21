#include <Collider.hpp>

Collider::Collider() = default;

Collider::Collider(const glm::vec2& aPos)
	: position(aPos)
{
}

void Collider::setPosition(const glm::vec2& pos)
{
	position = pos;
}

const glm::vec2& Collider::getPosition() const
{
	return position;
}
