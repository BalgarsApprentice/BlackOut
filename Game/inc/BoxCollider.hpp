#pragma once

#include <Collider.hpp>
#include <Graphics/Image.hpp>
#include <Math/AABB.hpp>

class BoxCollider : public Collider
{
public:
	BoxCollider();

	BoxCollider(Math::AABB aabb);

	glm::vec2& boundaryCheck(const glm::vec2& aPos);

	const Math::AABB getAABB() const;

	bool collides(const BoxCollider& aCollider) const;

private:
	Math::AABB box = { };
	int counter{ 0 };
};