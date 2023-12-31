#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(const glm::vec2& pos, GameObject* derivedGameObject)
	: position{ pos }
{
	objectIndex = endOfObjectArray;
	arrayOfprtObjects[endOfObjectArray++] = derivedGameObject;
}

	//virtual functions
//////////////////////////////////////////////////////////////////////////////////////////
void GameObject::setup()
{
	Singleton<Logger>::GetInstance().write("Object missed setup. Check for override.");
}

void GameObject::update(float deltaTime)
{
	Singleton<Logger>::GetInstance().write("Object missed update. Check for override.");
}

void GameObject::draw()
{
	Singleton<Logger>::GetInstance().write("Object missed draw. Check for override.");
}
CircleCollider& GameObject::getCircle()
{
	Singleton<Logger>::GetInstance().write("Object missed getCircle. Check for override.");
	return circle;
}

BoxCollider& GameObject::getBox()
{
	Singleton<Logger>::GetInstance().write("Object missed getBox. Check for override.");
	return box;
}

bool GameObject::getHasFlashlight()
{
	return false;
}

void GameObject::setHasFlashlight(bool bit)
{
}

bool GameObject::getHasDarklight()
{
	return false;
}

void GameObject::setHasDarklight(bool bit)
{
}

//////////////////////////////////////////////////////////////////////////////////////////

	//static functions
//////////////////////////////////////////////////////////////////////////////////////////
void GameObject::setupGameObjects()
{
	for (int i = 0; i < endOfObjectArray; ++i)
	{
		arrayOfprtObjects[i]->setup();
	}
}

void GameObject::updateGameObjects(float deltaTime)
{
	for (int i = 0; i < endOfObjectArray; ++i)
	{
		arrayOfprtObjects[i]->update(deltaTime);
	}
}

void GameObject::drawGameObjects()
{
	for (int i = 2; i < endOfObjectArray; ++i) //start with 2 to skip the player and the flashlight at 0 and 1 which should be drawn separately
	{
		arrayOfprtObjects[i]->draw();
	}
}

void GameObject::clearGameObjects(int startingIndex)
{
	for (int i = startingIndex; i < endOfObjectArray; ++i) //starting with 2 skips the player and the flashlight at 0 and 1
	{
		arrayOfprtObjects[i] = nullptr;
	}
	endOfObjectArray = startingIndex;
}
//////////////////////////////////////////////////////////////////////////////////////////

const bool GameObject::getLitState()
{
	return isLit;
}

void GameObject::setLitState(const bool aBool)
{
	isLit = aBool;
}

void GameObject::setPosition(const glm::vec2& pos)
{
	position = pos;
}

const glm::vec2& GameObject::getPosition() const
{
	return position;
}

void GameObject::handleCollision(Math::AABB aabb)
{
	setPosition(lastPosition);
}

void GameObject::handleDarkCollision(Math::AABB aabb)
{
}

GameObject* GameObject::arrayOfprtObjects[128]{ nullptr };
int GameObject::endOfObjectArray{ 0 };