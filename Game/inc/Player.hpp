#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Level.hpp>
#include <Graphics/Input.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Flashlight.hpp>
#include <Human.hpp>

class Player : public GameObject
{
public:
	Player();

	explicit Player(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Flashlight& aFlashlight, Level* aLevel);

	enum class State
	{
		Idle,
		Left,
		Right,
		Up,
		Down,
		Dead,
		None
	};

	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

	CircleCollider& getCircle() override;

	BoxCollider& getBox() override;

	bool getHasFlashlight() override;

	void setHasFlashlight(bool bit) override;

	const State getState() const;

	const State getOldState() const;
	
	Flashlight::State sendFlashlightState();

private:
	Mob mob;
	Graphics::Image* canvas;
	Level* level;

	Graphics::Sprite idleLeftSprite;
	Graphics::Sprite idleRightSprite;
	Graphics::Sprite idleUpSprite;
	Graphics::Sprite idleDownSprite;
	Graphics::SpriteAnim leftAnim;
	Graphics::SpriteAnim rightAnim;
	Graphics::SpriteAnim upAnim;
	Graphics::SpriteAnim downAnim;
	Graphics::SpriteAnim deadAnim;
	Graphics::SpriteAnim noneAnim;

	BoxCollider box{ {{0, 0, 0}, {28, 32, 0}} };
	CircleCollider circle{ {}, 16 };
	Flashlight* flashlight;

	std::string stringState{ "" };

	void updateAnims(float deltaTime);
	void updateColliders();

	State state = State::Idle;
	State oldState = State::Right;

	void setState(State newState);
};