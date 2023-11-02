#include <BoxCollider.hpp>

BoxCollider::BoxCollider() = default;

BoxCollider::BoxCollider(const Math::AABB& aabb)
    : box{aabb}
{
}

glm::vec2 BoxCollider::boundaryCheck(const glm::vec2& aPos)
{
    auto aabb = getAABB();
    glm::vec2 correction{ 0 };
    if (aabb.min.x < 100)
    {
        correction.x = 100 - aabb.min.x;
    }
    if (aabb.min.y < 4)
    {
        correction.y = 4 - aabb.min.y;
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

glm::vec2 BoxCollider::collisionCorrection(const Math::AABB& aBox)
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

glm::vec2 BoxCollider::faceCollision(const Math::AABB& aBox, const glm::vec2 aDir)
{
    glm::vec2 correction{ 0, 0 };
    Math::AABB aabb = getAABB();
    if (aBox.intersect({ aabb.min.x + abs(aDir.x), aabb.min.y, 0 }, { aabb.max.x - abs(aDir.x), aabb.min.y, 0 })) //up
    {
        if (aDir.y < 0)
        {
            correction.y -= aDir.y;
        }
    }
    if (aBox.intersect({ aabb.min.x + abs(aDir.x), aabb.max.y, 0 }, { aabb.max.x - abs(aDir.x), aabb.max.y, 0 })) //down
    {
        if (aDir.y > 0)
        {
            correction.y -= aDir.y;
        }
    }
    if (aBox.intersect({ aabb.min.x, aabb.min.y + abs(aDir.y), 0 }, { aabb.min.x, aabb.max.y - abs(aDir.y), 0 })) //left
    {
        if (aDir.x < 0)
        {
            correction.x -= aDir.x;
        }
    }
    if (aBox.intersect({ aabb.max.x, aabb.min.y + abs(aDir.y), 0 }, { aabb.max.x, aabb.max.y - abs(aDir.y), 0 })) //right
    {
        if (aDir.x > 0)
        {
            correction.x -= aDir.x;
        }
    }
    return correction;
}

glm::vec2 BoxCollider::openCollision(const Math::AABB& aBox, const glm::vec2 aDir, const BoxCollider::Side aSide)
{
    glm::vec2 correction{ 0, 0 };
    Math::AABB aabb = getAABB();
    Math::Line top{ { aabb.min.x + abs(aDir.x), aabb.min.y, 0 }, { aabb.max.x - abs(aDir.x), aabb.min.y, 0 } };
    Math::Line bottom{ { aabb.min.x + abs(aDir.x), aabb.max.y, 0 }, { aabb.max.x - abs(aDir.x), aabb.max.y, 0 } };
    Math::Line left{ { aabb.min.x, aabb.min.y + abs(aDir.y), 0 }, { aabb.min.x, aabb.max.y - abs(aDir.y), 0 } };
    Math::Line right{ { aabb.max.x, aabb.min.y + abs(aDir.y), 0 }, { aabb.max.x, aabb.max.y - abs(aDir.y), 0 } };

    if (aSide != Side::top)
    {
        if (aBox.intersect(top))
        {
            if (aDir.y < 0)
            {
                correction.y -= aDir.y;
            }
        }
    }
    if (aSide != Side::bottom)
    {
        if (aBox.intersect(bottom))
        {
            if (aDir.y > 0)
            {
                correction.y -= aDir.y;
            }
        }
    }
    if (aSide != Side::left)
    {
        if (aBox.intersect(left))
        {
            if (aDir.x < 0)
            {
                correction.x -= aDir.x;
            }
        }
    }
    if (aSide != Side::right)
    {
        if (aBox.intersect(right))
        {
            if (aDir.x > 0)
            {
                correction.x -= aDir.x;
            }
        }
    }
    return correction;
}

bool BoxCollider::threeLineCollision(const Math::AABB& aBox, const Math::Line a, const Math::Line b, const Math::Line c)
{

    return false;
}
