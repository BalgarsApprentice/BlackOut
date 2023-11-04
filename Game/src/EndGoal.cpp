#include <EndGoal.hpp>

using namespace Graphics;

EndGoal::EndGoal() = default;

EndGoal::EndGoal(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ aPos, this }
	, canvas{ &surface }
{

}

void EndGoal::setup()
{
	auto coinSprites = ResourceManager::loadSpriteSheet("assets/textures/coin.png", 16, 16, 0, 0, BlendMode::AlphaBlend);
	coinAnim = SpriteAnim{ coinSprites, 4, { { 0, 1, 2, 3, 4, 5, 6, 7, 8 } } };
}

void EndGoal::update(float deltaTime)
{
	coinAnim.update(deltaTime);
}

void EndGoal::draw()
{
	canvas->drawSprite(coinAnim, position.x - 8, position.y - 8);
}
