#pragma once

#include <Light.hpp>
#include <Graphics/SpriteAnim.hpp>

class MovingLight : public Light
{
public:
	MovingLight();

	MovingLight(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

private:
	BoxCollider box{ {{0, 0, 0}, {128, 128, 0}} };
	float totaltime{ 0.0f };
	float speed{ 60.0f };
	int direction{ 1 };
	bool isMove{ false };
};