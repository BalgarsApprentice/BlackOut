#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <BoxCollider.hpp>
#include <Flashlight.hpp>

class Player : public GameObject
{
public:
	Player();

	explicit Player(const glm::vec2& aPos, Mob aMob, Graphics::Image& surface, Flashlight& aFlashlight);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

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

	BoxCollider collider{ {{0, 0, 0}, {28, 32, 0}} };
	Flashlight* flashlight;

	std::string stringState{ "" };

	void updateAnims(float deltaTime);
};