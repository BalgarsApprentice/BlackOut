#include <Mob.hpp>
#include <Graphics/Input.hpp>

using namespace Graphics;

Mob::Mob() = default;

Mob::Mob(const Sprite& _sprite)
	: sprite{ _sprite }
	, aabb{ {0, 0, 0}, {32, 32, 0} }
{
}

glm::vec2 Mob::move(glm::vec2 aPos, float deltaTime)
{
	aPos.x += Input::getAxis("Horizontal") * playerSpeed * deltaTime;
	aPos.y -= Input::getAxis("Vertical") * playerSpeed * deltaTime;
	
	return aPos;
}

void Mob::update(float deltaTime)
{
	
}

void Mob::draw(Image& image)
{
//	image.drawSprite(sprite, position.x, position.y);
//#if _DEBUG
//	image.drawAABB(getAABB(), Color::Yellow, {}, FillMode::WireFrame);
//#endif
}

//void Mob::setPosition(const glm::vec2& pos)
//{
//	position = pos;
//}

//const glm::vec2& Mob::getPosition() const
//{
//	return position;
//}
//
//const Math::AABB Mob::getAABB() const
//{
//	return aabb + glm::vec3{ position.x + 16, position.y + 11, 0 };
//}

void Mob::translate(const glm::vec2& t)
{
//	position += t;
}
