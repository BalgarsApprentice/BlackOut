#include <CircleCollider.hpp>

CircleCollider::CircleCollider() = default;

CircleCollider::CircleCollider(const glm::vec2& aPos, const int aRadius)
    : Collider{ aPos }
    , radius{ aRadius }
{
}

const int CircleCollider::getRadius() const
{
    return radius;
}

bool CircleCollider::collides(const CircleCollider& aCollider) const
{
    glm::vec2 compCircle = aCollider.getPosition();
    float distance = (compCircle.x - position.x) * (compCircle.x - position.x) + (compCircle.y - position.y) * (compCircle.y - position.y);
    float colDistance = (radius + aCollider.getRadius()) * (radius + aCollider.getRadius());
    
    return distance < colDistance;
}