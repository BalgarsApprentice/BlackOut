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
	glm::vec2 direction = ( position - lastPosition );
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

	if (hasFlashlight)
	{
		flashlight->setFlashlightPosition({ position.x - 32, position.y - 24 });
		flashlight->setPlayerState(sendFlashlightState());
		int len = sizeof(level->obstacles) / sizeof(BoxCollider);
		for (int i = 0; i < len; ++i)
		{
			if (getBox().getAABB().intersect(level->obstacles[i].getAABB()))
			{
				switch (getState())
				{
				case State::Left:
					if (flashlight->getState() == Flashlight::State::Left || flashlight->getState() == Flashlight::State::Old)
					{
						if (getBox().getAABB().min.x > level->obstacles[i].getAABB().min.x)
						{
							setPosition({ lastPosition.x, position.y });
						}
					}
					break;
				case State::Right:
					if (flashlight->getState() == Flashlight::State::Right || flashlight->getState() == Flashlight::State::Old)
					{
						if (getBox().getAABB().max.x < level->obstacles[i].getAABB().max.x)
						{
							setPosition({ lastPosition.x, position.y });
						}
					}
					break;
				case State::Up:
					if (flashlight->getState() == Flashlight::State::Up || flashlight->getState() == Flashlight::State::Old)
					{
						if (getBox().getAABB().min.y > level->obstacles[i].getAABB().min.y)
						{
							setPosition({ position.x, lastPosition.y });
						}
					}
					break;
				case State::Down:
					if (flashlight->getState() == Flashlight::State::Down || flashlight->getState() == Flashlight::State::Old)
					{
						if (getBox().getAABB().max.y < level->obstacles[i].getAABB().max.y)
						{
							setPosition({ position.x, lastPosition.y });
						}
					}
					break;
				case State::Idle:
					goBack(level->obstacles[i].getAABB());
					break;
				}
				updateColliders();
			}
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

void Player::goBack(Math::AABB aabb)
{
	position = lastPosition;
	//switch (getState())
	//{
	//case State::Left:
	//	if (getBox().getAABB().min.x > aabb.min.x && getBox().getAABB().max.x < aabb.max.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	if (getBox().getAABB().max.y > aabb.min.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	if (getBox().getAABB().min.y > aabb.max.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	break;
	//case State::Right:
	//	if (getBox().getAABB().min.x < aabb.min.x && getBox().getAABB().max.x > aabb.max.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	if (getBox().getAABB().max.y > aabb.min.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	if (getBox().getAABB().min.y > aabb.max.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	break;
	//case State::Up:
	//	if (getBox().getAABB().min.y > aabb.min.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	if (getBox().getAABB().max.x > aabb.min.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	if (getBox().getAABB().min.x > aabb.max.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	break;
	//case State::Down:
	//	if (getBox().getAABB().max.y < aabb.max.y)
	//	{
	//		setPosition({ position.x, lastPosition.y });
	//	}
	//	if (getBox().getAABB().max.x > aabb.min.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	if (getBox().getAABB().min.x > aabb.max.x)
	//	{
	//		setPosition({ lastPosition.x, position.y });
	//	}
	//	break;
	//}
	//updateColliders();
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
