#pragma once

#include <AI.hpp>

class SliderAI : public AI
{
public:
	SliderAI();

	glm::vec2 getTarget(glm::vec2 aPosition) override;

private:


};