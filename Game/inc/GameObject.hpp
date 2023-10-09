#pragma once

#include <glm/vec2.hpp>
#include <Graphics/Image.hpp>

class GameObject
{
public:
	GameObject();

	explicit GameObject(const glm::vec2& pos, GameObject* derivedGameObject);

	virtual void update(float deltaTime);

	virtual void draw(Graphics::Image surface);

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getPosition() const;

private:

protected:
	glm::vec2 position{ 0 };
	int objectIndex = 0;
};