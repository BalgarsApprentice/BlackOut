#pragma once

#include <Collider.hpp>
#include <Graphics/Image.hpp>
#include <Math/AABB.hpp>

class BoxCollider : public Collider
{
public:
	BoxCollider();

	BoxCollider(const Math::AABB& aabb);

	glm::vec2 boundaryCheck(const glm::vec2& aPos);

	glm::vec2 collisionCorrection(const Math::AABB& box);

	Math::AABB getAABB() const;

	void setAABB(Math::AABB aBox);

	bool collides(const BoxCollider& aCollider) const;

private:
	Math::AABB box = { };
	int counter{ 0 };
};