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

		Singleton<Logger>::GetInstance().write(std::to_string(coords.y));
		
		if (velocity.y > 0 && abs(coords.x) < 0.7f)
		{
			setState(State::Down);
		}
		else if (velocity.y < 0 && abs(coords.x) < 0.7f)
		{
			setState(State::Up);
		}
		else if (velocity.x > 0)
		{
			setState(State::Right);
		}
		else if (velocity.x < 0)
		{
			setState(State::Left);
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
