#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Level.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Audio/Sound.hpp>
#include <Flashlight.hpp>
#include <FlashlightObject.hpp>
#include <Human.hpp>
#include <cmath>

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

	void update(float deltaTime) override;

	void draw() override;

	CircleCollider& getCircle() override;

	BoxCollider& getBox() override;

	bool getHasFlashlight() override;

	void setHasFlashlight(bool bit) override;

	bool getHasDarklight() override;

	void setHasDarklight(bool bit) override;

	void handleCollision(Math::AABB aabb) override;

	void sendFlashlightObjects(FlashlightObject& light, FlashlightObject& dark);

	const State getState() const;

	const State getOldState() const;
	
	Flashlight::State sendFlashlightState();

	bool getLightOrDark();

	void pickUpObject(FlashlightObject& object);

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
	const float lightArc{70.0f};

	std::string stringState{ "" };

	void updateAnims(float deltaTime);
	void updateColliders();

	State state = State::Idle;
	State oldState = State::Right;
	glm::vec2 direction{ 0, 0 };

	FlashlightObject* flashlightObject{ nullptr };
	FlashlightObject* darklightObject{ nullptr };

	void setState(State newState);
};