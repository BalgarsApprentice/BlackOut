#include <Mob.hpp>

using namespace Graphics;

Mob::Mob() = default;

glm::vec2 Mob::move(glm::vec2 aPos, float deltaTime)
{
	initialPos = aPos;

	glm::vec2 coords = normalize(glm::vec2{ Input::getAxis("Horizontal"), Input::getAxis("Vertical") });

	aPos.x += coords.x * playerSpeed * deltaTime;
	aPos.y -= coords.y * playerSpeed * deltaTime;

	velocity = (aPos - initialPos) / deltaTime;

	if (glm::length(velocity) > 0)
	{
		oldState = state;

		float angle = atan2(velocity.x, velocity.y);				////////////
		octant = int(round(8 * angle / (2 * M_PI) + 8)) % 8;		//I can barely visualize the math here. Consider replacing it.
		int cardinal = octant / 2;
		switch (cardinal)
		{
		case 0:
			setState(State::Down);
			break;
		case 1:
			if (abs(velocity.y) < 0.2f )
			{
				setState(State::Right);
			}
			break;
		case 2:
			setState(State::Up);
			break;
		case 3:
			if (abs(velocity.y) < 0.2f)
			{
				setState(State::Left);
			}
			break;
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
	float normalized = glm::length(glm::vec2{ Input::getAxis("Horizontal"), Input::getAxis("Vertical") });

	if (normalized > 0)
	{
		coords /= normalized;
		return coords;
	}
	return {0, 0};
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

const int Mob::getOctant() const
{
	return octant;
}
