#include <Player.hpp>

using namespace Graphics;

Player::Player() = default;

Player::Player(const glm::vec2& aPos, Mob aMob, Graphics::Image& surface, Flashlight& aFlashlight)
	: GameObject{ aPos, this }
	, mob{ aMob }
	, canvas{ &surface }
	, flashlight{ &aFlashlight }
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

void Player::update(float deltaTime)
{
	position = mob.move(position, deltaTime);
	position += collider.boundaryCheck(position);
	flashlight->setFlashlightPosition({ position.x - 52, position.y + 32 }, mob.getState());

	updateAnims(deltaTime);
}

void Player::draw()
{
	switch(mob.getState())
	{
	case Mob::State::Idle:
		if (mob.getOldState() != Mob::State::Idle)
		{
			switch (mob.getOldState())
			{
			case Mob::State::Left:
				canvas->drawSprite(idleLeftSprite, position.x, position.y);
				break;
			case Mob::State::Right:
				canvas->drawSprite(idleRightSprite, position.x, position.y);
				break;
			case Mob::State::Up:
				canvas->drawSprite(idleUpSprite, position.x, position.y);
				break;
			case Mob::State::Down:
				canvas->drawSprite(idleDownSprite, position.x, position.y);
				break;
			}
		}
		stringState = "Idle";
		break;

	case Mob::State::Left:
		canvas->drawSprite(leftAnim, position.x, position.y);
		stringState = "Left";
		break;

	case Mob::State::Right:
		canvas->drawSprite(rightAnim, position.x, position.y);
		stringState = "Right";
		break;

	case Mob::State::Up:
		canvas->drawSprite(upAnim, position.x, position.y);
		stringState = "Up";
		break;

	case Mob::State::Down:
		canvas->drawSprite(downAnim, position.x, position.y);
		stringState = "Down";
		break;

	case Mob::State::Dead:
		canvas->drawSprite(deadAnim, position.x, position.y);
		stringState = "Dead";
		break;

	case Mob::State::None:
		canvas->drawSprite(noneAnim, position.x, position.y);
		stringState = "None";
		break;
	}
	
#if _DEBUG
    canvas->drawAABB(collider.getAABB(position), Color::Yellow, {}, FillMode::WireFrame);
	canvas->drawText(Font::Default, stringState , position.x + 16, position.y - 2, Color::White);
#endif
}

void Player::updateAnims(float deltaTime)
{
	leftAnim.update(deltaTime);
	rightAnim.update(deltaTime);
	upAnim.update(deltaTime);
	downAnim.update(deltaTime);
}
