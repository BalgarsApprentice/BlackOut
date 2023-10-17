#include <Light.hpp>

using namespace Graphics;

Light::Light() = default;

Light::Light(const glm::vec2& aPos, Graphics::Image& surface)
	: GameObject{ {aPos.x - 64, aPos.y - 64}, this }
	, darkness{ &surface }
{
	arrayOfprtLights[endOfLightArray++] = this;
}

void Light::setup()
{
	auto lightSprites = ResourceManager::loadSpriteSheet("assets/textures/lightanim.png", 128, 128, 0, 0, BlendMode::AdditiveBlend);
	lightAnim = SpriteAnim{ lightSprites, 4, {} };
}

void Light::update(float deltaTime)
{
	lightAnim.update(deltaTime);
}

void Light::draw()
{
	darkness->drawSprite(lightAnim, position.x, position.y);
}

void Light::initializeCollisionGroup(GameObject* entity)
{
	//check for AABB collision with all immobile AABB objects on screen
	//add all collisions to an array
}

void Light::litCheck(GameObject* entity)
{
	for (int i = 0; i < endOfLightArray; ++i)
	{
		if (arrayOfprtLights[i]->getLitState())
		{
			//check for circle distance with entity
			//if entity collides, check for any AABB collision with the entity and immobile AABB objects within the light's array
				//correct entity position on AABB collision
				//turn on entity AI
				//return
		}
		//turn off entity AI
		//turn off collision with player
	}
}

void Light::flipLitState()
{
	isOn = !isOn;
}

const bool Light::getLitState() const
{
	return isOn;
}

Light* Light::arrayOfprtLights[64]{ nullptr };
int Light::endOfLightArray{ 0 };
