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
	if (!player.getHasFlashlight()) return;

	const int up  = Input::getKey(Graphics::KeyCode::Up) ? 1 : 0;
	const int down = Input::getKey(Graphics::KeyCode::Down) ? 1 : 0;
	int vertical = up - down;

	const int left = Input::getKey(Graphics::KeyCode::Left) ? 1 : 0;
	const int right = Input::getKey(Graphics::KeyCode::Right) ? 1 : 0;
	int horizontal = left - right;

	if (vertical > 0)
	{
		state = State::Up;
	}
	if (vertical < 0)
	{
		state = State::Down;
	}
	if (horizontal < 0)
	{
		state = State::Right;
	}
	if (horizontal > 0)
	{
		state = State::Left;
	}
	if (horizontal == 0 && vertical == 0)
	{
		state = playerState;
	}
}

void Flashlight::draw()
{
	if (currentFlashlightSprite == nullptr) return;

	darkness->drawSprite(*currentFlashlightSprite, position.x, position.y);
}

BoxCollider& Flashlight::getBox()
{
	return box;
}

void Flashlight::setFlashlightPosition(const glm::vec2& aPos)
{
	if (isFlashlightLocked)
	{
		state = oldState;
	}

	switch (state)
	{
	case State::Left:
		position = { aPos.x - 99, aPos.y - 50 };
		currentFlashlightSprite = &leftFlashlightSprite;
		break;
	case State::Right:
		position = { aPos.x + 28, aPos.y - 54 };
		currentFlashlightSprite = &rightFlashlightSprite;
		break;
	case State::Up:
		position = { aPos.x - 36, aPos.y - 134 };
		currentFlashlightSprite = &upFlashlightSprite;
		break;
	case State::Down:
		position = { aPos.x - 36, aPos.y + 16 };
		currentFlashlightSprite = &downFlashlightSprite;
		break;
	case State::Old:
		switch (oldState)
		{
		case State::Left:
			position = { aPos.x - 99, aPos.y - 50 };
			currentFlashlightSprite = &leftFlashlightSprite;
			break;
		case State::Right:
			position = { aPos.x + 28, aPos.y - 54 };
			currentFlashlightSprite = &rightFlashlightSprite;
			break;
		case State::Up:
			position = { aPos.x - 36, aPos.y - 134 };
			currentFlashlightSprite = &upFlashlightSprite;
			break;
		case State::Down:
			position = { aPos.x - 36, aPos.y + 16 };
			currentFlashlightSprite = &downFlashlightSprite;
			break;
		}
		break;
	}
	if (state != State::Old)
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

void Flashlight::updateColliders()
{
	box.setPosition({ position.x + 16, position.y + 10 });
}

const Flashlight::State Flashlight::getState() const
{
	return state;
}

void Flashlight::setPlayerState(State aState)
{
	playerState = aState;
}

bool Flashlight::isFlashlightLocked{false};
