#include <FlashlightObject.hpp>

using namespace Graphics;

FlashlightObject::FlashlightObject() = default;

FlashlightObject::FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface, const bool type)
	: GameObject{ aPos, this }
	, canvas{ &surface }
{
	isLit = true;
	isLightOrDark = type;
}

void FlashlightObject::setup()
{
	auto lightImage = ResourceManager::loadImage("assets/textures/flashlight_pickup32x16.png");
	lightSprite = Sprite(lightImage, { 0, 0, 32, 16 }, BlendMode::AlphaBlend);
	auto darkImage = ResourceManager::loadImage("assets/textures/darklight_pickup32x16.png");
	darkSprite = Sprite(darkImage, { 0, 0, 32, 16 }, BlendMode::AlphaBlend);
	box.setPosition(position);
	updateColliders();
}

void FlashlightObject::update(float deltaTime)
{
	updateColliders();
}

void FlashlightObject::draw()
{
	if (gone) return;


	if (isLightOrDark)
	{
		canvas->drawSprite(lightSprite, position.x - 16, position.y - 8);
	}
	else
	{
		canvas->drawSprite(darkSprite, position.x - 16, position.y - 8);
	}

#if _DEBUG
	canvas->drawAABB(box.getAABB(), Color::Yellow, {}, FillMode::WireFrame);
#endif
}

BoxCollider& FlashlightObject::getBox()
{
	return box;
}

bool FlashlightObject::getGone()
{
	return gone;
}

bool FlashlightObject::getLightOrDark()
{
	return isLightOrDark;
}

void FlashlightObject::pickUp()
{	
	if (isLightOrDark)
	{
		variousUI->setState(variousUI->UI::flashlight);
	}
	else
	{
		variousUI->setState(variousUI->UI::darklight);
		Light::setLit(true);
	}
	gone = true;
}

void FlashlightObject::endGame()
{
	variousUI->setState(variousUI->UI::end);
}

bool FlashlightObject::flashlightCollision()
{

	return false;
}

void FlashlightObject::updateColliders()
{
	box.setPosition(position);
}

