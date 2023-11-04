#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>

class EndGoal : public GameObject
{
public:
	EndGoal();

	EndGoal(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

private:
	Graphics::Image* canvas;
	Graphics::SpriteAnim coinAnim;
};