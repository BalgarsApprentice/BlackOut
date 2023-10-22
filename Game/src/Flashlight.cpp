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
	auto flashlightImages = ResourceManager::loadImage("assets/textures/flashlightspritesheet.png");
	leftFlashlightSprite = Sprite(flashlightImages, { 0, 0, 134, 164 }, BlendMode::AlphaBlend);
	rightFlashlightSprite = Sprite(flashlightImages, { 0, 328, 134, 164 }, BlendMode::AlphaBlend);
	upFlashlightSprite = Sprite(flashlightImages, { 0, 164, 134, 164 }, BlendMode::AlphaBlend);
	downFlashlightSprite = Sprite(flashlightImages, { 0, 492, 134, 164 }, BlendMode::AlphaBlend);
}

void Flashlight::update(float deltaTime, GameObject& player)
{
	//add a check for collision here
	 
}

void Flashlight::draw()
{
	if (currentFlashlightSprite != nullptr)
	{
		darkness->drawSprite(*currentFlashlightSprite, position.x, position.y);
	}
}

void Flashlight::setFlashlightPosition(const glm::vec2& aPos, Mob::State state)
{
	if (isFlashlightLocked)
	{
		state = oldState;
	}

	switch (state)
	{
	case Mob::State::Left:
		position = { aPos.x - 47, aPos.y - 82 };
		currentFlashlightSprite = &leftFlashlightSprite;
		break;
	case Mob::State::Right:
		position = { aPos.x + 80, aPos.y - 86 };
		currentFlashlightSprite = &rightFlashlightSprite;
		break;
	case Mob::State::Up:
		position = { aPos.x + 16, aPos.y - 166 };
		currentFlashlightSprite = &upFlashlightSprite;
		break;
	case Mob::State::Down:
		position = { aPos.x + 16, aPos.y - 16 };
		currentFlashlightSprite = &downFlashlightSprite;
		break;
	}

	if (state != Mob::State::Idle)
	{
		oldState = state;
	}
}

void Flashlight::lockFlashlight()
{
	isFlashlightLocked = true;
}

void Flashlight::unlockFlashlight()
{
	isFlashlightLocked = false;
}


bool Flashlight::isFlashlightLocked{false};
