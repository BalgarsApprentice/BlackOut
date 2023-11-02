#pragma once

#include <Collider.hpp>
#include <Graphics/Image.hpp>
#include <Math/AABB.hpp>

class BoxCollider : public Collider
{
public:
	BoxCollider();

	BoxCollider(const Math::AABB& aabb);

	enum class Side
	{
		top,
		bottom,
		left,
		right
	};

	glm::vec2 boundaryCheck(const glm::vec2& aPos);

	glm::vec2 collisionCorrection(const Math::AABB& box);

	Math::AABB getAABB() const;

	void setAABB(Math::AABB aBox);

	bool collides(const BoxCollider& aCollider) const;

	glm::vec2 faceCollision(const Math::AABB& aBox, const glm::vec2 aDir);

	glm::vec2 openCollision(const Math::AABB& aBox, const glm::vec2 aDir, const BoxCollider::Side aSide);

	bool threeLineCollision(const Math::AABB& aBox, const Math::Line a, const Math::Line b, const Math::Line c);

private:
	Math::AABB box = { };
	int counter{ 0 };
};