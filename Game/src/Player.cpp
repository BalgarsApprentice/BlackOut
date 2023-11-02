#include <Player.hpp>

using namespace Graphics;

Player::Player() = default;

Player::Player(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Flashlight& aFlashlight, Level* aLevel)
	: GameObject{ aPos, this }
	, mob{ aController }
	, canvas{ &surface }
	, flashlight{ &aFlashlight }
	, level{ aLevel }
{
}

void Player::setup()
{
	auto playerSpriteImage = ResourceManager::loadImage("assets/textures/playersheet.png");
	Graphics::SpriteSheet playerSpriteSheet{ playerSpriteImage, 64, 64, 0, 0, BlendMode::AlphaBlend };
	std::shared_ptr<SpriteSheet> shareSprites = std::make_shared<SpriteSheet>(playerSpriteSheet);
	idleLeftSprite = Sprite{ playerSpriteImage, {64, 64, 64, 64}, BlendMode::AlphaBlend };
	idleRightSprite = Sprite{ playerSpriteImage, {64, 128, 64, 64}, BlendMode::AlphaBlend };
	idleUpSprite = Sprite{ playerSpriteImage, {64, 192, 64, 64}, BlendMode::AlphaBlend };
	idleDownSprite = Sprite{ playerSpriteImage, {64, 0, 64, 64}, BlendMode::AlphaBlend };
	leftAnim	= SpriteAnim{ shareSprites, 4, { {12, 14} } };
	rightAnim	= SpriteAnim{ shareSprites, 4, { {24, 26} } };
	upAnim		= SpriteAnim{ shareSprites, 4, { {36, 38} } };
	downAnim	= SpriteAnim{ shareSprites, 4, { {0, 2} } };
	//deadAnim	= SpriteAnim{ shareSprites, 0, { {1, 1} } };
	noneAnim	= SpriteAnim{ shareSprites, 0, { {1} } };
}

void Player::update(float deltaTime, GameObject& player)
{
	lastPosition = position;
	position = mob.move(position, deltaTime);
	updateColliders();
	direction = ( position - lastPosition );
	position += box.boundaryCheck({ position.x + 16, position.y + 10 });
	updateAnims(deltaTime);

	if (length(direction) > 0)
	{
		oldState = state;

		if (direction.x > 0)
		{
			setState(State::Right);
		}
		else if (direction.x < 0)
		{
			setState(State::Left);
		}
		else if (direction.y > 0)
		{
			setState(State::Down);
		}
		else if (direction.y < 0)
		{
			setState(State::Up);
		}
	}
	else
	{
		setState(State::Idle);
	}

	if (!hasFlashlight) return; //only continue if the player has found the flashlight

	Math::AABB myAABB = getBox().getAABB();
	flashlight->setFlashlightPosition({ position.x - 32, position.y - 24 });
	flashlight->setPlayerState(sendFlashlightState());

	if (!flashlight->getLightOrDark()) return; //only continue if the flashlight is not in its darklight mode

	int len = sizeof(level->obstacles) / sizeof(BoxCollider);
	for (int i = 0; i < len; ++i)
	{
		Math::AABB aabb = level->obstacles[i].getAABB();
		if ( myAABB.intersect(aabb))
		{
			switch (flashlight->getState())
			{
			case Flashlight::State::Up:
				if (aabb.intersect({ myAABB.min.x + abs(direction.x), myAABB.min.y, 0 }, { myAABB.max.x - abs(direction.x), myAABB.min.y, 0 }))
				{
					if (direction.y < 0)
					{
						position = { position.x, lastPosition.y };
					}
				}
				break;

			case Flashlight::State::Down:
				if (aabb.intersect({ myAABB.min.x + abs(direction.x), myAABB.max.y, 0 }, { myAABB.max.x - abs(direction.x), myAABB.max.y, 0 }))
				{
					if (direction.y > 0)
					{
						position = { position.x, lastPosition.y };
					}
				}
				break;

			case Flashlight::State::Left:
				if (aabb.intersect({ myAABB.min.x, myAABB.min.y + abs(direction.y), 0 }, { myAABB.min.x, myAABB.max.y - abs(direction.y), 0 }))
				{
					if (direction.x < 0)
					{
						position = { lastPosition.x, position.y };
					}
				}
				break;

			case Flashlight::State::Right:
				if (aabb.intersect({ myAABB.max.x, myAABB.min.y + abs(direction.y), 0 }, { myAABB.max.x, myAABB.max.y - abs(direction.y), 0 }))
				{
					if (direction.x > 0)
					{
						position = { lastPosition.x, position.y };
					}
				}
				break;

			default:
				position = lastPosition;
				break;
			}
			updateColliders();
		}
	}
}

void Player::draw()
{
	glm::vec2 drawPosition = { getPosition().x - 32, getPosition().y - 24 };
	switch(getState())
	{
	case State::Idle:
		switch (getOldState())
		{
		case State::Left:
			canvas->drawSprite(idleLeftSprite, drawPosition.x, drawPosition.y);
			break;
		case State::Right:
			canvas->drawSprite(idleRightSprite, drawPosition.x, drawPosition.y);
			break;
		case State::Up:
			canvas->drawSprite(idleUpSprite, drawPosition.x, drawPosition.y);
			break;
		case State::Down:
			canvas->drawSprite(idleDownSprite, drawPosition.x, drawPosition.y);
			break;
		}
		stringState = "Idle";
		break;

	case State::Left:
		canvas->drawSprite(leftAnim, drawPosition.x, drawPosition.y);
		stringState = "Left";
		break;

	case State::Right:
		canvas->drawSprite(rightAnim, drawPosition.x, drawPosition.y);
		stringState = "Right";
		break;

	case State::Up:
		canvas->drawSprite(upAnim, drawPosition.x, drawPosition.y);
		stringState = "Up";
		break;

	case State::Down:
		canvas->drawSprite(downAnim, drawPosition.x, drawPosition.y);
		stringState = "Down";
		break;

	/*case State::Dead:
		canvas->drawSprite(deadAnim, drawPosition.x, drawPosition.y);
		stringState = "Dead";
		break;

	case State::None:
		canvas->drawSprite(noneAnim, drawPosition.x, drawPosition.y);
		stringState = "None";
		break;*/
	}
	
#if _DEBUG
	canvas->drawText(Font::Default, stringState, position.x - 16, position.y - 26, Color::White);
	canvas->drawAABB(box.getAABB(), Color::Yellow, {}, FillMode::WireFrame);
	if (isLit)
	{
		canvas->drawCircle({ { position.x - 2, position.y }, 16.0f }, Color::White, {}, FillMode::WireFrame);
	}

	canvas->drawAABB(flashlight->getBox().getAABB(), Color::Red, {}, FillMode::Solid);
#endif

	isLit = false;
}

void Player::updateColliders()
{
	box.setPosition({ position.x - 16, position.y - 16 });
	circle.setPosition({ position.x, position.y });
}

CircleCollider& Player::getCircle()
{
	return circle;
}

BoxCollider& Player::getBox()
{
	return box;
}

bool Player::getHasFlashlight()
{
	return hasFlashlight;
}

void Player::setHasFlashlight(bool bit)
{
	hasFlashlight = bit;
}

bool Player::getHasDarklight()
{
	return hasDarklight;
}

void Player::setHasDarklight(bool bit)
{
	hasDarklight = bit;
}

void Player::handleCollision(Math::AABB aabb)
{
	if (!flashlight->getLightOrDark())
	{
		switch (flashlight->getState())
		{
		case Flashlight::State::Up:
			position += box.openCollision(aabb, direction, BoxCollider::Side::top);
			break;
		case Flashlight::State::Down:
			position += box.openCollision(aabb, direction, BoxCollider::Side::bottom);
			break;
		case Flashlight::State::Left:
			position += box.openCollision(aabb, direction, BoxCollider::Side::left);
			break;
		case Flashlight::State::Right:
			position += box.openCollision(aabb, direction, BoxCollider::Side::right);
			break;
		}
		updateColliders();
		return;
	}

	if (aabb.holds(getBox().getAABB()))
	{
		position = lastPosition;
		updateColliders();
		return;
	}

	position += box.faceCollision(aabb, direction);
	updateColliders();
}

void Player::setState(State newState)
{
	if (newState != state)
	{
		state = newState;
	}
}

const Player::State Player::getState() const
{
	return state;
}

const Player::State Player::getOldState() const
{
	return oldState;
}

Flashlight::State Player::sendFlashlightState()
{
	switch (getState())
	{
	case State::Left:
		return Flashlight::State::Left;
	case State::Right:
		return Flashlight::State::Right;
	case State::Up:
		return Flashlight::State::Up;
	case State::Down:
		return Flashlight::State::Down;
	default:
		return Flashlight::State::Old;
	}
}

void Player::updateAnims(float deltaTime)
{
	leftAnim.update(deltaTime);
	rightAnim.update(deltaTime);
	upAnim.update(deltaTime);
	downAnim.update(deltaTime);
}
