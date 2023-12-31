#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>

#include <glm/vec2.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/ResourceManager.hpp>
#include <BoxCollider.hpp>
#include <CircleCollider.hpp>
class GameObject
{
public:
	GameObject();

	explicit GameObject(const glm::vec2& pos, GameObject* derivedGameObject);

	//virtual functions
//////////////////////////////////////////////////////////////////////////////////////////
	virtual ~GameObject() = default;

	virtual void setup();

	virtual void update(float deltaTime);

	virtual void draw();

	virtual CircleCollider& getCircle();

	virtual BoxCollider& getBox();
	
	virtual bool getHasFlashlight();

	virtual void setHasFlashlight(bool bit);

	virtual bool getHasDarklight();

	virtual void setHasDarklight(bool bit);

//////////////////////////////////////////////////////////////////////////////////////////

	//static functions
//////////////////////////////////////////////////////////////////////////////////////////
	static void setupGameObjects();

	static void updateGameObjects(float deltaTime);

	static void drawGameObjects();

	static void clearGameObjects(int startingIndex);
//////////////////////////////////////////////////////////////////////////////////////////

	const bool getLitState();

	void setLitState(const bool aBool);

	void setPosition(const glm::vec2& pos);

	const glm::vec2& getPosition() const;

	virtual void handleCollision(Math::AABB aabb);

	virtual void handleDarkCollision(Math::AABB aabb);

private:
	static GameObject* arrayOfprtObjects[128];
	static int endOfObjectArray;
	BoxCollider box{};
	CircleCollider circle{};
	
protected:
	glm::vec2 position{ 0 };
	glm::vec2 lastPosition{ 0 };
	int objectIndex = 0;

	bool isLit{ false };
	bool hasFlashlight{ false };
	bool hasDarklight{ false };
};