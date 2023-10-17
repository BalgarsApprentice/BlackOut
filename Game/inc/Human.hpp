#pragma once

#include <AI.hpp>
#include <Graphics/Input.hpp>

class Human : public AI
{
public:
	Human();

	glm::vec2 getTarget(glm::vec2 aPosition) override;

private:


};