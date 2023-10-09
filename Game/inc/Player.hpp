#pragma once

#include <GameObject.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Mob.hpp>
#include <BoxCollider.hpp>

class Player : public GameObject
{
public:
	Player();

	explicit Player(const glm::vec2& aPos, Mob aMob);

	void playerSetup();

	void update(float deltaTime);

	void draw();

	Graphics::SpriteAnim getSpriteAnim()
	{
		return Player::walkAnim;
	};

	const BoxCollider getBox() const;

private:
	Mob mob;
	BoxCollider collider{ {position.x + 16, position.y + 11}, {{0, 0, 0}, {32, 32, 0}} };
	//glm::vec2 position{ 352.0f, 256.0f };

	Graphics::SpriteAnim walkAnim;

	enum class State
	{
		None,
		Idle,
		Left,
		Right,
		Up,
		Down,
		Dead
	};

	State state = State::None;

	void setState(State newState);

protected:

};
