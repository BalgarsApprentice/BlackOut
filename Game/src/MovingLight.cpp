#include <MovingLight.hpp>

using namespace Graphics;

MovingLight::MovingLight() = default;

MovingLight::MovingLight(const glm::vec2& aPos, Graphics::Image& surface)
	: Light{aPos, surface}
{
	position = { aPos.x, aPos.y - 64 };
	arrayOfptrLights[endOfLightArray++] = this;
	circle.setPosition(aPos);
	isLit = true;
}

void MovingLight::setup()
{
	auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0, BlendMode::AdditiveBlend);
	lightAnim = SpriteAnim{ lightSprites, 4, {} };
}

void MovingLight::update(float deltaTime, GameObject& player)
{
	if (isMove)
	{
		position.x += direction * speed * deltaTime;
		if (position.x > 262)
		{
			position.x = 262;
			isMove = false;
		}
		if (position.x < 132)
		{
			position.x = 132;
			isMove = false;
		}
	}
	else if (totaltime > 3)
	{
		isMove = true;
		totaltime = 0.0f;
		direction *= -1;
	}
	else
	{
		totaltime += deltaTime;
	}

	lightAnim.update(deltaTime);
	circle.setPosition({ position.x + 64, position.y + 64});
}

void MovingLight::draw()
{
	darkness->drawSprite(lightAnim, position.x, position.y);
}
