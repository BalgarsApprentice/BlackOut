#pragma once

#define _USE_MATH_DEFINES

#include <Singleton.hpp>
#include <Logger.hpp>

#include <glm/vec2.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Graphics/Input.hpp>
#include <cmath>

#include <Math/AABB.hpp>

class Mob
{
public:
	Mob();

	glm::vec2 move(glm::vec2 aPos, float deltaTime);

	glm::vec2 normalize(glm::vec2 coords);

	enum class State
	{
		Idle,
		Left,
		Right,
		Up,
		Down,
		Dead,
		None
	};

	const State getState() const;

	const State getOldState() const;

	const int getOctant() const;

private:
	glm::vec2 initialPos{ 0, 0 };
	glm::vec2 velocity{ 0, 0 };
	float playerSpeed{ 60.0f };

	State state = State::Idle;
	State oldState = State::Right;

	int octant{ 2 };

	void setState(State newState);

protected:
};
