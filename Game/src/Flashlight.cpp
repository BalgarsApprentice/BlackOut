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

	auto darklightImages = ResourceManager::loadImage("assets/textures/darklightspritesheet.png");
	leftDarklightSprite = Sprite(darklightImages, { 0, 0, 134, 164 }, BlendMode::AlphaBlend);
	rightDarklightSprite = Sprite(darklightImages, { 0, 328, 134, 164 }, BlendMode::AlphaBlend);
	upDarklightSprite = Sprite(darklightImages, { 0, 164, 134, 164 }, BlendMode::AlphaBlend);
	downDarklightSprite = Sprite(darklightImages, { 0, 492, 134, 164 }, BlendMode::AlphaBlend);
}

void Flashlight::update(float deltaTime, GameObject& player)
{
	if (!player.getHasFlashlight()) return;

	if (player.getHasDarklight())
	{
		if (Input::getKeyDown(Graphics::KeyCode::Space))
		{
			toggleLight();
		}
	}

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
	//set flashlight to display the appropriate sprite group
	if (lightOrDark)
	{
		currentFlashlightSprite = lightSprites[0];
	}
	else
	{
		currentFlashlightSprite = darkSprites[0];
	}

	switch (state)
	{
	case State::Left:
		position = { aPos.x - 99, aPos.y - 50 };
		//currentFlashlightSprite is already set to index 0
		break;
	case State::Right:
		position = { aPos.x + 28, aPos.y - 54 };
		currentFlashlightSprite += 1;
		break;
	case State::Up:
		position = { aPos.x - 36, aPos.y - 134 };
		currentFlashlightSprite += 2;
		break;
	case State::Down:
		position = { aPos.x - 35, aPos.y + 16 };
		currentFlashlightSprite += 3;
		break;
	case State::Old:
		switch (oldState)
		{
		case State::Left:
			position = { aPos.x - 99, aPos.y - 50 };
			//currentFlashlightSprite is already set to index 0
			break;
		case State::Right:
			position = { aPos.x + 28, aPos.y - 54 };
			currentFlashlightSprite += 1;
			break;
		case State::Up:
			position = { aPos.x - 36, aPos.y - 134 };
			currentFlashlightSprite += 2;
			break;
		case State::Down:
			position = { aPos.x - 35, aPos.y + 16 };
			currentFlashlightSprite += 3;
			break;
		}
		break;
	}
	if (state != State::Old)
	{
		oldState = state;
	}
}

void Flashlight::updateColliders()
{
	box.setPosition({ position.x + 16, position.y + 10 });
}

const Flashlight::State Flashlight::getState() const
{
	return state;
}

const Flashlight::State Flashlight::getOldState() const
{
	return oldState;
}

void Flashlight::setPlayerState(State aState)
{
	playerState = aState;
}

const bool Flashlight::getLightOrDark() const
{
	return lightOrDark;
}

void Flashlight::toggleLight()
{
	lightOrDark = !lightOrDark;
}
