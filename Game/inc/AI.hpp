#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>

#include <glm/vec2.hpp>

class AI
{
public:
	AI();

	virtual glm::vec2 getTarget(glm::vec2 aPosition);

private:


};