#include <Enemy.hpp>

using namespace Graphics;

Enemy::Enemy() = default;

Enemy::Enemy(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Level* aLevel)
	: GameObject{ aPos, this }
	, mob{ aController }
	, canvas{ &surface }
	, level{ aLevel }
{
}

void Enemy::setup()
{
	auto enemySpriteImageIdle = ResourceManager::loadImage("assets/textures/enemyidle.png");
	auto enemySpriteImageHop = ResourceManager::loadImage("assets/textures/enemyhop.png");
	auto enemySpriteImageOther = ResourceManager::loadImage("assets/textures/enemyallvomfy.png");
	Graphics::SpriteSheet enemySpriteSheet{ enemySpriteImageHop, 32, 32, 0, 0, BlendMode::AlphaBlend };
	std::shared_ptr<SpriteSheet> shareSprites = std::make_shared<SpriteSheet>(enemySpriteSheet);
	idleDownSprite = Sprite{ enemySpriteImageIdle, {0, 0, 32, 32}, BlendMode::AlphaBlend };
	leftAnim = SpriteAnim{ shareSprites, 6, { {6, 7, 8, 9, 10, 11} } };
	rightAnim = SpriteAnim{ shareSprites, 6, { {6, 7, 8, 9, 10, 11} } };
	upAnim = SpriteAnim{ shareSprites, 6, { {12, 13, 14, 15, 16, 17} } };
	downAnim = SpriteAnim{ shareSprites, 6, { {0, 1, 2, 3, 4, 5} } };
}

void Enemy::update(float deltaTime, GameObject& player)
{
	if (!isLit) return;

	lastPosition = position;
	position = mob.move(position, deltaTime);
	updateColliders();
	glm::vec2 direction = (position - lastPosition);
	//position += box.boundaryCheck({ position.x + 32, position.y + 32 });
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
	if (length(position - player.getPosition()) < 10)
	{
		setState(State::Attacking);
	}
}

void Enemy::draw()
{
	glm::vec2 drawPosition = { getPosition().x - 16, getPosition().y - 16 };
	switch (getState())
	{
	case State::Idle:
		canvas->drawSprite(idleDownSprite, drawPosition.x, drawPosition.y);
		break;

	case State::Left:
		canvas->drawSprite(leftAnim, drawPosition.x, drawPosition.y);
		break;

	case State::Right:
		canvas->drawSprite(rightAnim, drawPosition.x, drawPosition.y);
		break;

	case State::Up:
		canvas->drawSprite(upAnim, drawPosition.x, drawPosition.y);
		break;

	case State::Down:
		canvas->drawSprite(downAnim, drawPosition.x, drawPosition.y);
		break;
	}
}

CircleCollider& Enemy::getCircle()
{
	return circle;
}

BoxCollider& Enemy::getBox()
{
	return box;
}

const Enemy::State Enemy::getState() const
{
	return state;
}

const Enemy::State Enemy::getOldState() const
{
	return oldState;
}

void Enemy::updateAnims(float deltaTime)
{
	leftAnim.update(deltaTime);
	rightAnim.update(deltaTime);
	upAnim.update(deltaTime);
	downAnim.update(deltaTime);
}

void Enemy::updateColliders()
{
	box.setPosition({ position.x + 16, position.y + 10 });
	circle.setPosition({ position.x + 30, position.y + 26 });
}

void Enemy::setState(State newState)
{
	state = newState;
}
