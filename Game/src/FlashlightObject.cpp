#include <FlashlightObject.hpp>

using namespace Graphics;

FlashlightObject::FlashlightObject() = default;

FlashlightObject::FlashlightObject(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 16, aPos.y - 8}, this }
	, canvas{ &surface }
{
	isLit = true;
}

void FlashlightObject::setup()
{
	auto objectImage = ResourceManager::loadImage("assets/textures/flashlight_pickup32x16.png");
	objectSprite = Sprite(objectImage, BlendMode::AlphaBlend);
}

void FlashlightObject::update(float deltaTime, GameObject& player)
{
	if (gone) return;
	if (box.getAABB().intersect(player.getBox().getAABB()))
	{
		player.setHasFlashlight(true);
		gone = true;
		variousUI->setState(variousUI->UI::flashlight);
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

