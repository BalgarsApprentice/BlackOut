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

	enum class State
	{
		Left,
		Right,
		Up,
		Down,
		Old
	};

	void setup() override;

	void update(float deltaTime, GameObject& player) override;

	void draw() override;

	BoxCollider& getBox() override;

	void setFlashlightPosition(const glm::vec2& pos);

	void updateColliders();

	const State getState() const;

	const State getOldState() const;

	void setPlayerState(State aState);

	const bool getLightOrDark() const;

private:
	Graphics::Image* darkness;
	Graphics::Sprite leftFlashlightSprite;
	Graphics::Sprite rightFlashlightSprite;
	Graphics::Sprite upFlashlightSprite;
	Graphics::Sprite downFlashlightSprite;
	Graphics::Sprite* lightSprites[4]{ &leftFlashlightSprite, &rightFlashlightSprite, &upFlashlightSprite, &downFlashlightSprite };

	Graphics::Sprite leftDarklightSprite;
	Graphics::Sprite rightDarklightSprite;
	Graphics::Sprite upDarklightSprite;
	Graphics::Sprite downDarklightSprite;
	Graphics::Sprite* darkSprites[4]{ &leftDarklightSprite, &rightDarklightSprite, &upDarklightSprite, &downDarklightSprite };


	Graphics::Sprite* currentFlashlightSprite{ nullptr };

	static bool isFlashlightLocked;
	State state{ State::Right };
	State oldState{ State::Right };
	State playerState{ State::Right };
	bool lightOrDark{ 1 }; // 1 is regular light and 0 is the dark light

	BoxCollider box{ {{0, 0, 0}, {1, 1, 0}} };

	void toggleLight();
};