#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Level.hpp>
#include <Player.hpp>

class Enemy : public GameObject
{
public:
	Enemy();

	explicit Enemy(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Level* aLevel);

	enum class State
	{
		Idle,
		Left,
		Right,
		Up,
		Down,
		Dead,
		Attacking,
		Cooldown,
		None
	};

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	CircleCollider& getCircle() override;

	BoxCollider& getBox() override;

	const State getState() const;

	const State getOldState() const;

private:
	Mob mob;
	Graphics::Image* canvas;
	Level* level;
	//Player* ptrPlayer{ nullptr };

	Graphics::Sprite idleLeftSprite;
	Graphics::Sprite idleRightSprite;
	Graphics::Sprite idleUpSprite;
	Graphics::Sprite idleDownSprite;
	Graphics::SpriteAnim leftAnim;
	Graphics::SpriteAnim rightAnim;
	Graphics::SpriteAnim upAnim;
	Graphics::SpriteAnim downAnim;

	BoxCollider box{ {{0, 0, 0}, {28, 32, 0}} };
	CircleCollider circle{ {}, 16 };

	void updateAnims(float deltaTime);
	void updateColliders();

	State state = State::Idle;
	State oldState = State::Idle;

	void setState(State newState);

};