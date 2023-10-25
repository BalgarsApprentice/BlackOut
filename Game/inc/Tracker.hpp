#pragma once

#include <AI.hpp>
#include <Player.hpp>

class Tracker : public AI
{
public:
	Tracker();

	explicit Tracker(Player* player);

	glm::vec2 getTarget(glm::vec2 aPosition) override;

private:
	Player* ptrPlayer{ nullptr };

};