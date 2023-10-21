#pragma once

#include <glm/vec2.hpp>

class Collider
{
public:
	Collider();

	Collider(const glm::vec2& aPos);

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getPosition() const;

private:


protected:
	glm::vec2 position{ 0 };

};