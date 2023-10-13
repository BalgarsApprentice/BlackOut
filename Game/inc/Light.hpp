#pragma once

#include <Object.hpp>

class Light
{
public:
	Light();

	virtual void update(float deltaTime);

	virtual void draw(Graphics::Image surface);

private:

};