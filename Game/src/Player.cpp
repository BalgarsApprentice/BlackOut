#include <Player.hpp>
#include <Graphics/Input.hpp>

using namespace Graphics;

//Player::Player() = default;

//Player::Player(const glm::vec2& pos, const Sprite& _sprite)
//	: position{ pos }
//	, sprite{ _sprite }
//{
//}
//
void Player::update(float deltaTime)
{
	position.x += Input::getAxis("Horizontal") * playerSpeed * deltaTime;
	position.y -= Input::getAxis("Vertical") * playerSpeed * deltaTime;
}
//
//void Player::draw(Image& image)
//{
//	image.drawSprite(sprite, position.x, position.y);
//}
//
//void Player::setPosition(const glm::vec2& pos)
//{
//	position = pos;
//}
//
//const glm::vec2& Player::getPosition() const
//{
//	return position;
//}