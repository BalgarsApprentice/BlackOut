#include <AI.hpp>

AI::AI() = default;

glm::vec2 AI::getTarget(glm::vec2 aPosition)
{
	Singleton<Logger>::GetInstance().write("AI missed getTarget. Check for override.");
	return {0, 0};
}
