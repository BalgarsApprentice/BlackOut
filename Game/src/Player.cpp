#include <Player.hpp>

using namespace Graphics;

Player::Player() = default;

Player::Player(const glm::vec2& aPos, Mob aMob)
	: GameObject{ aPos, this }
	, mob{ aMob }
{
}

void Player::playerSetup()
{
	auto playerSprites = ResourceManager::loadSpriteSheet("assets/textures/playersheet.png", 64, 64, 0, 0, BlendMode::AlphaBlend);
	walkAnim = SpriteAnim{ playerSprites, 4, {{0, 2}} };
}

void Player::update(float deltaTime)
{
	position = mob.move(position, deltaTime);

	//glm::vec2 initialPos = position;

	//position.x += Input::getAxis("Horizontal") * playerSpeed * deltaTime;
	//position.y -= Input::getAxis("Vertical") * playerSpeed * deltaTime;

	//velocity = (position - initialPos) / deltaTime;

	//if (glm::length(velocity) > 0)
	//{
	//	setState(State::Down);
	//}
	//else
	//{
	//	setState(State::Idle);
	//}
	walkAnim.update(deltaTime);
}

void Player::draw()
{

}

const BoxCollider Player::getBox() const
{
	return collider;
}

void Player::setState(State newState)
{
	if (newState != state)
	{
		state = newState;
	}
}
