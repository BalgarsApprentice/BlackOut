#include <Light.hpp>

using namespace Graphics;

Light::Light() = default;

Light::Light(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 64, aPos.y - 64}, this }
	, darkness{ &surface }
{
}

void Light::setup()
{
	auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0, BlendMode::AdditiveBlend);
	lightAnim = SpriteAnim{ lightSprites, 4, {} };
}

void Light::update(float deltaTime)
{
	lightAnim.update(deltaTime);
}

void Light::draw()
{
	darkness->drawSprite(lightAnim, position.x, position.y);
}
