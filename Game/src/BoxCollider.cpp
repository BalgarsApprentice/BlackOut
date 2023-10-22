#include <BoxCollider.hpp>

BoxCollider::BoxCollider() = default;

BoxCollider::BoxCollider(Math::AABB aabb)
    : box{aabb}
{
}

glm::vec2& BoxCollider::boundaryCheck(const glm::vec2& aPos)
{
    auto aabb = getAABB();
    glm::vec2 correction{ 0 };
    if (aabb.min.x < 0)
    {
        correction.x = -aabb.min.x;
    }
    if (aabb.min.y < 0)
    {
        correction.y = -aabb.min.y;
    }
    if (aabb.max.x >= 768)
    {
        correction.x = 768 - aabb.max.x;
    }
    if (aabb.max.y >= 576)
    {
        correction.y = 576 - aabb.max.y;
    }

    return correction;
}

glm::vec2& BoxCollider::collisionCorrection(Math::AABB aBox)
{
    auto aabb = getAABB();
    glm::vec2 correction{ 0 };
    if (aabb.min.x < aBox.max.x)
    {
        correction.x = -aabb.min.x;
    }
    if (aabb.min.y < 0)
    {
        correction.y = -aabb.min.y;
    }
    if (aabb.max.x >= 768)
    {
        correction.x = 768 - aabb.max.x;
    }
    if (aabb.max.y >= 576)
    {
        correction.y = 576 - aabb.max.y;
    }

    return correction;
}

Math::AABB BoxCollider::getAABB() const
{
    return box + glm::vec3{ position.x, position.y, 0 };
}

void BoxCollider::setAABB(Math::AABB aBox)
{
    box = aBox;
}

bool BoxCollider::collides(const BoxCollider& aCollider) const
{
    return getAABB().intersect(aCollider.getAABB());
}
