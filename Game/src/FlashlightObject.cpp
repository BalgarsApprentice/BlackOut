#include <FlashlightObject.hpp>

using namespace Graphics;

FlashlightObject::FlashlightObject() = default;

FlashlightObject::FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface, const bool type)
	: GameObject{ {aPos.x - 16, aPos.y - 8}, this }
	, canvas{ &surface }
{
	isLit = true;
	isLightOrDark = type;
}

void FlashlightObject::setup()
{
	auto lightImage = ResourceManager::loadImage("assets/textures/flashlight_pickup32x16.png");
	auto darkImage = ResourceManager::loadImage("assets/textures/darklight_pickup32x16.png");
	if (isLightOrDark)
	{
		objectSprite = Sprite(lightImage, BlendMode::AlphaBlend);
	}
	else
	{
		objectSprite = Sprite(darkImage, BlendMode::AlphaBlend);
	}
	box.setPosition(position);
}

void FlashlightObject::update(float deltaTime, GameObject& player)
{
	if (gone) return;
	if (box.getAABB().intersect(player.getBox().getAABB()))
	{
		gone = true;
		if (isLightOrDark)
		{
			player.setHasFlashlight(true);
			variousUI->setState(variousUI->UI::flashlight);
		}
		else
		{
			player.setHasDarklight(true);
			variousUI->setState(variousUI->UI::darklight);
			Light::setLit(true);
		}
	}
}

void FlashlightObject::draw()
{
	if (gone) return;
	canvas->drawSprite(objectSprite, position.x , position.y );

#if _DEBUG
	canvas->drawAABB(box.getAABB(), Color::Yellow, {}, FillMode::WireFrame);
#endif
}

