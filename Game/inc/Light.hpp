#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Math/AABB.hpp>

class Light : public GameObject
{
public:
	Light();

	Light(const glm::vec2& aPos, Graphics::Image& surface);

	//friend class Level;

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	CircleCollider& getCircle() override;

	static void initializeCollisionGroup(Math::AABB& aObstacle);

	static void litCheck(GameObject* entity);

private:
	Graphics::Image* darkness;
	Graphics::SpriteAnim lightAnim;

	BoxCollider box{};
	CircleCollider circle{ {}, 64 };

	Math::AABB* arrayOfObstacles[8]{ nullptr };
	int endOfObstaclesArray;

	static Light* arrayOfprtLights[64];
	static int endOfLightArray;
};