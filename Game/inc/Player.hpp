#pragma once

#include <GameObject.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Mob.hpp>
#include <Drawer.hpp>
#include <BoxCollider.hpp>

class Player : public GameObject
{
public:
	Player();

	explicit Player(const glm::vec2& aPos, Mob aMob, Graphics::Image& surface);

	void playerSetup();

	void update(float deltaTime) override;

	void draw() override;

	//Graphics::SpriteAnim getSpriteAnim()
	//{
	//	return Player::walkAnim;
	//};

	const BoxCollider getBox() const;

private:
	Mob mob;
	Drawer drawer;
	BoxCollider collider{ {position.x + 16, position.y + 11}, {{0, 0, 0}, {32, 32, 0}} };

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
