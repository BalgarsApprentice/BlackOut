#pragma once

#include <glm/vec2.hpp>
#include <Graphics/Image.hpp>
#include <GraphicsFlyweight.hpp>
//#include <GameManager.hpp>
#include <iostream>

class GameObject
{
public:
	GameObject();

	explicit GameObject(const glm::vec2& pos, GameObject* derivedGameObject);

	virtual void update(float deltaTime);

	virtual void draw();

	virtual void setGraphicsPrt(GraphicsFlyweight& aFlyweight);

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getPosition() const;

private:
	GraphicsFlyweight* graphicsFlyweight;

protected:
	glm::vec2 position{ 0 };
	int objectIndex = 0;
};