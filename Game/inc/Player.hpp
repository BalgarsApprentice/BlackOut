#pragma once

#include <Mob.hpp>
#include <Graphics/SpriteAnim.hpp>
#include <Graphics/ResourceManager.hpp>

class Player : public Mob
{
public:
	Player();

	void playerSetup();

	void update(float deltaTime);

	Graphics::SpriteAnim getSpriteAnim()
	{
		return Player::walkAnim;
	};

private:
	Graphics::SpriteAnim walkAnim;

protected:

};
