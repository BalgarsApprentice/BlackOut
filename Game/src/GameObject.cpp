#include "GameObject.hpp"
#include <GameManager.hpp>

GameObject::GameObject() = default;

GameObject::GameObject(const glm::vec2& pos, GameObject* derivedGameObject)
	: position{ pos }
{
	GameManager::instance().addGameObject(derivedGameObject);
	derivedGameObject->setGraphicsPrt(GameManager::instance().getGraphicsAdr());
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw()
{
	std::cout << "missed draw object\n";
}

void GameObject::setGraphicsPrt(GraphicsFlyweight& aFlyweight)
{
	graphicsFlyweight = &aFlyweight;
}

void GameObject::setPosition(const glm::vec2& pos)
{
	position = pos;
}

const glm::vec2& GameObject::getPosition() const
{
	return position;
}
