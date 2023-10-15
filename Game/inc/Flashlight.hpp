#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>

#include <GameObject.hpp>
#include <Graphics/Sprite.hpp>
#include <Mob.hpp>
#include <Graphics/Input.hpp>
#include <Graphics/KeyCodes.hpp>

class Flashlight : public GameObject
{
public:
	Flashlight();

	Flashlight(const glm::vec2& aPos, Graphics::Image& surface);

	void setup() override;

	void update(float deltaTime) override;

	void draw() override;

	void setFlashlightPosition(const glm::vec2& pos, Mob::State state);

	static void lockFlashlight();

	static void unlockFlashlight();

private:
	Graphics::Image* darkness;
	Graphics::Sprite leftFlashlightSprite;
	Graphics::Sprite rightFlashlightSprite;
	Graphics::Sprite upFlashlightSprite;
	Graphics::Sprite downFlashlightSprite;

	Graphics::Sprite* currentFlashlightSprite{ nullptr };

	static bool isFlashlightLocked;
	Mob::State oldState{};
};