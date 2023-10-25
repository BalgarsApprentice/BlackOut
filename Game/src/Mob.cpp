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

	aPos += direction * speed * deltaTime;
	
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
