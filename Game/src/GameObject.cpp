#include "GameObject.hpp"
#include <GameManager.hpp>

GameObject::GameObject() = default;

GameObject::GameObject(const glm::vec2& pos, GameObject* derivedGameObject)
	: position{ pos }
{
	GameManager::instance().addGameObject(derivedGameObject);
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw(Graphics::Image surface)
{
}

void GameObject::setPosition(const glm::vec2& pos)
{
	position = pos;
}

const glm::vec2& GameObject::getPosition() const
{
	return position;
}
