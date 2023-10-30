#pragma once

#include <Singleton.hpp>
#include <VariousUI.hpp>

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>

class FlashlightObject : public GameObject
{
public:
	FlashlightObject();

	explicit FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface);
	
	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

private:
	VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();

	Graphics::Image* canvas;
	Graphics::Sprite objectSprite;
	

	bool gone{ false };

	BoxCollider box{ Math::AABB{ {652, 92, 0}, {684, 108, 0} } };

};