#pragma once

#include <Singleton.hpp>
#include <VariousUI.hpp>
#include <Light.hpp>
#include <Graphics/SpriteAnim.hpp>

class FlashlightObject : public GameObject
{
public:
	FlashlightObject();

	explicit FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface, const bool type);
	
	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	BoxCollider& getBox() override;

	bool getGone();

	bool getLightOrDark();

	void pickUp();

private:
	VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();

	Graphics::Image* canvas;
	Graphics::Sprite lightSprite;
	Graphics::Sprite darkSprite;
	

	bool gone{ false };
	bool isLightOrDark{ true };

	BoxCollider box{ Math::AABB{ {-16, -8, 0}, {16, 8, 0} } };

	bool flashlightCollision();

	void updateColliders();
};