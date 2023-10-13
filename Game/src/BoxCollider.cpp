#include <BoxCollider.hpp>

BoxCollider::BoxCollider() = default;

BoxCollider::BoxCollider(const glm::vec2& aPos, Math::AABB aabb)
	: box{aabb}
{
}

void BoxCollider::update(float deltaTime)
{

}

void BoxCollider::draw(Graphics::Image surface)
{
//#if _DEBUG
//	surface.drawAABB(getAABB(position), Graphics::Color::Yellow, {}, Graphics::FillMode::WireFrame);
//#endif
}

const Math::AABB BoxCollider::getAABB(const glm::vec2& aPos) const
{
	return box + glm::vec3{ aPos.x + 16, aPos.y + 11, 0 };
}
