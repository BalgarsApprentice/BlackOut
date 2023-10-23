#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Mob.hpp>
#include <Level.hpp>

class Enemy : public GameObject
{
public:
	Enemy();

	explicit Enemy(const glm::vec2& aPos, AI& aController, Graphics::Image& surface, Level* aLevel);

	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

	CircleCollider& getCircle() override;

	BoxCollider& getBox() override;

	bool getHasFlashlight() override;

	void setHasFlashlight(bool bit) override;

private:
	Mob mob;
	Graphics::Image* canvas;
	Level* level;

	BoxCollider box{ {{0, 0, 0}, {28, 32, 0}} };
	CircleCollider circle{ {}, 16 };

};