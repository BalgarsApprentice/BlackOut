#include <Player.hpp>

using namespace Graphics;

Player::Player() = default;

Player::Player(const glm::vec2& aPos, Mob aMob, Graphics::Image& surface, Flashlight& aFlashlight)
	: GameObject{ aPos, this }
	, mob{ aMob }
	, canvas{ &surface }
	, flashlight{ &aFlashlight }
{
}

void Player::setup()
{
	auto playerSprites = ResourceManager::loadSpriteSheet("assets/textures/playersheet.png", 64, 64, 0, 0, BlendMode::AlphaBlend);
	walkAnim = SpriteAnim{ playerSprites, 4, {{0, 2}} };
}

void Player::update(float deltaTime)
{
	position = mob.move(position, deltaTime);
	position += collider.boundaryCheck(position);
	flashlight->setPosition({ position.x - 52, position.y + 32 });

	walkAnim.update(deltaTime);
}

void Player::draw()
{
	/*								State system not set up yet
	switch(mob.getState())
	{
	case Mob::State::Idle :
		break;

	case Mob::State::Left:
		break;

	case Mob::State::Right:
		break;

	case Mob::State::Up:
		break;

	case Mob::State::Down:
		break;

	case Mob::State::Dead:
		break;

	case Mob::State::None:
		break;
	}
	*/

	canvas->drawSprite(walkAnim, position.x, position.y);
#if _DEBUG
    canvas->drawAABB(collider.getAABB(position), Color::Yellow, {}, FillMode::WireFrame);
#endif
}
