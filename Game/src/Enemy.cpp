#include <Enemy.hpp>

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
}

void Enemy::update(float deltaTime, GameObject& player)
{
}

void Enemy::draw()
{
}

CircleCollider& Enemy::getCircle()
{
	return circle;
}

BoxCollider& Enemy::getBox()
{
	return box;
}

bool Enemy::getHasFlashlight()
{
	return false;
}

void Enemy::setHasFlashlight(bool bit)
{
}
