#include <Mob.hpp>

using namespace Graphics;

Mob::Mob() = default;

Mob::Mob(AI& aController) 
	: controller{ &aController }
{
}

glm::vec2 Mob::move(glm::vec2 aPos, float deltaTime)
{
	glm::vec2 direction = normalize(controller->getTarget(aPos));

	direction.y = -direction.y;

	aPos += direction * speed * deltaTime;

	if (glm::length(direction) > 0)
	{
		oldState = state;
		
		if (direction.x > 0)
		{
			setState(State::Right);
		}
		else if (direction.x < 0)
		{
			setState(State::Left);
		}
		else if (direction.y > 0)
		{
			setState(State::Down);
		}
		else if (direction.y < 0)
		{
			setState(State::Up);
		}
	}
	else
	{
		setState(State::Idle);
	}
	
	return aPos;
}

glm::vec2 Mob::normalize(glm::vec2 coords)
{
	float length = glm::length(coords);

	if (length > 0)
	{
		coords /= length;
		return coords;
	}
	return { 0, 0 };
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

const Mob::State Mob::getOldState() const
{
	return oldState;
}
