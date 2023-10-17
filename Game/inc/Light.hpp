#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>

class Light : public GameObject
{
public:
	Light();

	Light(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	static void initializeCollisionGroup(GameObject* entity);

	static void litCheck(GameObject* entity);

	void flipLitState();

	const bool getLitState() const;

private:
	Graphics::Image* darkness;
	Graphics::SpriteAnim lightAnim;

	bool isOn{true};

	static Light* arrayOfprtLights[64];
	static int endOfLightArray;
};