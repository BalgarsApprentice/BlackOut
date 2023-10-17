#pragma once

#define _USE_MATH_DEFINES

#include <Singleton.hpp>
#include <Logger.hpp>

#include <glm/vec2.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <AI.hpp>
#include <cmath>

#include <Math/AABB.hpp>

class Mob
{
public:
	Mob();

	explicit Mob(AI& aController);

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

private:
	AI* controller;
	glm::vec2 target{ 0, 0 };
	glm::vec2 velocity{ 0, 0 };
	float speed{ 60.0f };

	State state = State::Idle;
	State oldState = State::Right;

	void setState(State newState);

protected:
};
