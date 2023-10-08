#include <Player.hpp>
#include <Graphics/Input.hpp>

using namespace Graphics;

Player::Player() = default;

void Player::playerSetup()
{
	auto playerSprites = ResourceManager::loadSpriteSheet("assets/textures/playersheet.png", 64, 64, 0, 0, BlendMode::AlphaBlend);
	walkAnim = SpriteAnim{ playerSprites, 4, {{0, 2}} };
}

void Player::update(float deltaTime)
{
	position.x += Input::getAxis("Horizontal") * playerSpeed * deltaTime;
	position.y -= Input::getAxis("Vertical") * playerSpeed * deltaTime;
	walkAnim.update(deltaTime);
}