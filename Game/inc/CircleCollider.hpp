#pragma once

#include <Collider.hpp>

class CircleCollider : public Collider
{
public:
	CircleCollider();

	CircleCollider(const glm::vec2& aPos, const int aRadius);

	const int getRadius() const;

	bool collides(const CircleCollider& aCollider) const;

private:
	int radius;

};