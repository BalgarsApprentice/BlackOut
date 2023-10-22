#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Graphics/Input.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Flashlight.hpp>
#include <Human.hpp>

class Player : public GameObject
{
public:
	Player();

	explicit Player(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Flashlight& aFlashlight);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	CircleCollider& getCircle() override;

	BoxCollider& getBox() override;

	void updateColliders();

private:
	Mob mob;
	Graphics::Image* canvas;

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
};