#pragma once

#include <glm/vec2.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/ResourceManager.hpp>

#include <Math/AABB.hpp>

class Mob
{
public:
	Mob();

	glm::vec2 move(glm::vec2 aPos, float deltaTime);

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

private:
	glm::vec2 initialPos{ 0, 0 };
	glm::vec2 velocity{ 0, 0 };
	float playerSpeed{ 60.0f };

	State state = State::None;

	void setState(State newState);

protected:
};
