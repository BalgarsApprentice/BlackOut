#include <Mob.hpp>

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
		oldState = state;

		float angle = atan2(velocity.x, velocity.y);
		octant = int(round(8 * angle / (2 * M_PI) + 8)) % 8;
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
