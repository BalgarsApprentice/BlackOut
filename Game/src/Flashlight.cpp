#include <Flashlight.hpp>

using namespace Graphics;

Flashlight::Flashlight() = default;

Flashlight::Flashlight(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 53, aPos.y + 32}, this }
	, darkness{ &surface }
{
}

void Flashlight::setup()
{
	auto whiteSpaceImage = ResourceManager::loadImage("assets/textures/wideflashlight.png");
	flashlightSprite = Sprite(whiteSpaceImage, BlendMode::AlphaBlend);
}

void Flashlight::update(float deltaTime)
{
	//check for collision
}

void Flashlight::draw()
{
	darkness->drawSprite(flashlightSprite, position.x, position.y);
}
