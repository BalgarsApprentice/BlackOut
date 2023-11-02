#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Math/AABB.hpp>

class Light : public GameObject
{
public:
	Light();

	explicit Light(const glm::vec2& aPos, Graphics::Image& surface);

	friend class Level;

	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

	CircleCollider& getCircle() override;

	static void initializeCollisionGroup(Math::AABB aObstacle);

	static void litCheck(GameObject* entity);

	static void setLit(bool bit);

	void updateColliders();

protected:
	Graphics::Image* darkness;
	Graphics::SpriteAnim lightAnim;

	BoxCollider box{ {{0, 0, 0}, {128, 128, 0}} };
	CircleCollider circle{ {}, 56 };

	Math::AABB arrayOfObstacles[8]{ };
	int endOfObstaclesArray{ 0 };

#if _DEBUG
public:
#endif

	static Light* arrayOfptrLights[64];
	static int endOfLightArray;
};