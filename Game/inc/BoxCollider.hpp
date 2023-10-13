#pragma once

#include <GameObject.hpp>
#include <Math/AABB.hpp>

class BoxCollider
{
public:
	BoxCollider();

	BoxCollider(const glm::vec2& aPos, Math::AABB aabb);

	void update(float deltaTime);

	void draw(Graphics::Image surface);

	const Math::AABB getAABB(const glm::vec2& aPos) const;

private:
	Math::AABB box = { };
};