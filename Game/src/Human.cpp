#include <Human.hpp>

using namespace Graphics;

Human::Human() = default;

glm::vec2 Human::getTarget(glm::vec2 aPosition)
{
	return glm::vec2{ Input::getAxis("Horizontal"), -Input::getAxis("Vertical") };
}