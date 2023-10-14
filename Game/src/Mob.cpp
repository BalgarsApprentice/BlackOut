#include <Mob.hpp>
#include <Graphics/Input.hpp>

using namespace Graphics;

Mob::Mob() = default;

glm::vec2 Mob::move(glm::vec2 aPos, float deltaTime)
{
	initialPos = aPos;

	aPos.x += Input::getAxis("Horizontal") * playerSpeed * deltaTime;
	aPos.y -= Input::getAxis("Vertical") * playerSpeed * deltaTime;

	velocity = (aPos - initialPos) / deltaTime;

	if (glm::length(velocity) > 0)
	{
		setState(State::Down);
	}
	else
	{
		setState(State::Idle);
	}
	
	return aPos;
}

void Mob::setState(State newState)
{
	if (newState != state)
	{
		state = newState;
	}
}

const Mob::State Mob::getState() const
{
	return state;
}
