#pragma once

#include <Singleton.hpp>
#include <VariousUI.hpp>

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>

class FlashlightObject : public GameObject
{
public:
	FlashlightObject();

	explicit FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface, const bool type);
	
	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

private:
	VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();

	Graphics::Image* canvas;
	Graphics::Sprite objectSprite;
	

	bool gone{ false };
	bool isLightOrDark{ true };

	BoxCollider box{ Math::AABB{ {0, 0, 0}, {32, 16, 0} } };

};